#include <sstream>
#include <winsock2.h>
#include <QDebug>
#include <QThread>
#include <QMetaType>
#include "CaptureWidget.h"
#include "ui_CaptureWidget.h"
#include "SystemDevice.h"
#include "parse/ParseData.h"
#include "inline/utilsinline.h"
#include "AdvanceWidget.h"

CaptureWidget::CaptureWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CaptureWidget)
    , _captureThread(nullptr)
    , _readDumpThread(nullptr)
    , _itemCounts(0)
{
    ui->setupUi(this);
    ui->btnStop->setEnabled(false);
    ui->btnStop->setStyleSheet("QPushButton{background: grey;}");
    ui->btnStart->setStyleSheet("QPushButton{background: green}");

    const std::vector<pcap_if_t*> &devs = yang::SystemDevice::getInstance()->getAllDevs();
    for(std::vector<pcap_if_t*>::size_type idx = 0; idx < devs.size(); idx++) {
        if('\0' == devs[idx]->description[0]) {
            ui->comboBoxInter->addItem(devs.at(idx)->name , QVariant(idx));
        } else {
            ui->comboBoxInter->addItem(devs[idx]->description, QVariant(idx));
        }
    }
    qRegisterMetaType<__TcpData>("__TcpData");
    qRegisterMetaType<__TcpData>("__UdpData");

    /* 抓取网络数据包线程 */
    _captureThread = new DumpThread();
    connect(_captureThread, &DumpThread::sig_tcpReceived, this, &CaptureWidget::deal_Tcp, Qt::QueuedConnection);
    connect(_captureThread, &DumpThread::sig_udpReceived, this, &CaptureWidget::deal_Udp, Qt::QueuedConnection);
    connect(this, &CaptureWidget::sig_startCapture, _captureThread, &DumpThread::slot_startCapture, Qt::QueuedConnection);
    connect(this, &CaptureWidget::sig_stopCapture, _captureThread, &DumpThread::slot_stopCapture, Qt::DirectConnection);

    QThread *mainLoopThread = new QThread();
    _captureThread->moveToThread(mainLoopThread);
    mainLoopThread->start();

    /* 读取本地文件线程 */
    _readDumpThread = new DumpOfflineThread();
    connect(_readDumpThread, &DumpOfflineThread::sig_readComplete, this, &CaptureWidget::slot_showDetials, Qt::QueuedConnection);
    connect(this, &CaptureWidget::sig_requestData, _readDumpThread, &DumpOfflineThread::slot_request, Qt::QueuedConnection);

    QThread *readDumpFileThread = new QThread();
    _readDumpThread->moveToThread(readDumpFileThread);
    readDumpFileThread->start();

    /**/
    initTableWidget();
}

void CaptureWidget::initTableWidget()
{
    ui->tableWidget->setColumnCount(4);
    int wd = ui->tableWidget->size().width();
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()
                                               << tr("IP+端口")
                                               << tr("长度")
                                               << tr("协议")
                                               << tr("简要信息(双击单条信息查看详情)"));
    ui->tableWidget->setColumnWidth(0, 0.3*wd);
    ui->tableWidget->setColumnWidth(1, 0.05*wd);
    ui->tableWidget->setColumnWidth(2, 0.05*wd);
    ui->tableWidget->setColumnWidth(3, 0.5*wd);
    connect(ui->tableWidget, &QTableWidget::doubleClicked, [this](const QModelIndex &index){
        if(index.row() < 0)  return;
        emit sig_requestData(index.row());
    });
}
void CaptureWidget::slot_requestDetials(uint32_t index)
{
    emit sig_requestData(index);
}

void CaptureWidget::slot_showDetials(const char *datas)
{
    const char *data = getNetData(datas);
    const int32_t len = getNetDataLen(datas);
    if(len < 0) return;
    QByteArray bytes;
    bytes.resize(len);
    for(int32_t i=0; i<len; i++) {
        bytes[i] = data[i];
    }
    yang::ParseData *parse = new yang::ParseData(std::move(bytes));
    parse->show();
}

CaptureWidget::~CaptureWidget()
{
    yang::SystemDevice::destoryInstance();
    delete ui;
}

void CaptureWidget::on_btnStop_clicked()
{
    ui->btnStart->setStyleSheet("QPushButton{background: green}");
    ui->btnStart->setEnabled(true);
    ui->btnStop->setStyleSheet("QPushButton{background: grey;}");
    ui->btnStop->setEnabled(false);

    emit sig_stopCapture();
}

void CaptureWidget::on_btnStart_clicked()
{
    ui->btnStop->setStyleSheet("QPushButton{background: red;}");
    ui->btnStop->setEnabled(true);
    ui->btnStart->setStyleSheet("QPushButton{background: grey}");
    ui->btnStart->setEnabled(false);

    /* 清理QTableWidget */
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    _itemCounts = 0;
    /* 读取筛选器 */
    std::stringstream sb;
//     and ip host 192.168.42.230 and tcp port 80 and len >= 54
    if(!ui->lineEditHost->text().isEmpty()) {
        sb << " and ip host " << ui->lineEditHost->text().toStdString();
    }
    if(!ui->lineEditPort->text().isEmpty()) {
        sb << " and tcp port " << ui->lineEditPort->text().toInt();
    }
    if(!ui->lineEditLength->text().isEmpty()) {
        sb << " and len >= " << ui->lineEditLength->text().toInt() + 54;
    }
    /* ...... */
    int index = ui->comboBoxInter->currentIndex();
    const pcap_if_t *device = yang::SystemDevice::getInstance()->getAllDevs().at(index);
    emit sig_startCapture(device, QString(sb.str().c_str()));
}
std::string CaptureWidget::integerToIp(uint32_t net_addr)
{
    char buff[32] = {0};
#if defined(__LITTLE_ENDIAN_BITFIELD)
    snprintf(buff, sizeof(buff), "%d.%d.%d.%d"
             , (net_addr & 0x000000ff) >> 0
             , (net_addr & 0x0000ff00) >> 8
             , (net_addr & 0x00ff0000) >> 16
             , (net_addr & 0xff000000) >> 24);
#else
    snprintf(buff, sizeof(buff), "%d.%d.%d.%d"
             , (net_addr & 0xff000000) >> 24
             , (net_addr & 0x00ff0000) >> 16
             , (net_addr & 0x0000ff00) >> 8
             , (net_addr & 0x000000ff) >> 0);
#endif
    return std::string(buff);
}
char* CaptureWidget::getBrief(uint32_t totl, const char *data)
{
    memset(_rbuff, 0x00, sizeof(_rbuff));
    if(totl>0)
    {
        uint32_t idx;
        char c;
        for(idx = 0; idx < totl && idx < sizeof(_rbuff)-2; idx++) {
            c = data[idx];
            _rbuff[idx] = isvAscii(c) ? c : '.';
        }
    }
    return _rbuff;
}

void CaptureWidget::deal_Tcp(__TcpData data)
{
    int data_length = ntohs(data.ip_h->tot_len) - data.ip_h->ihl*4 - data.tcp_h->doff*4;

    memset(_buff, 0x00, sizeof(_buff));
    snprintf(_buff, sizeof(_buff), "%s:%d->%s:%d",
             integerToIp(data.ip_h->saddr).c_str(), ntohs(data.tcp_h->source),
             integerToIp(data.ip_h->daddr).c_str(), ntohs(data.tcp_h->dest));

    if(0 == _itemCounts % 4) {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    }
    uint32_t rowIdx = ui->tableWidget->rowCount() - 1;
    ui->tableWidget->setItem(rowIdx, 0, new QTableWidgetItem(_buff));
    ui->tableWidget->setItem(rowIdx, 1, new QTableWidgetItem(std::to_string(data_length).c_str()));
    ui->tableWidget->setItem(rowIdx, 3, new QTableWidgetItem(getBrief(data_length, data.data)));
}

void CaptureWidget::deal_Udp(__UdpData)
{

}

void CaptureWidget::on_btnAdvance_clicked()
{
    AdvanceWidget *advance = new AdvanceWidget();
    advance->show();
}
