#include <sstream>
#include <winsock2.h>
#include <QDebug>
#include <QThread>
#include <QMetaType>
#include "CaptureWidget.h"
#include "ui_CaptureWidget.h"
#include "SystemDevice.h"

CaptureWidget::CaptureWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CaptureWidget)
    , _dumpThread(nullptr)
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
    _dumpThread = new DumpThread();
    /* 子线程收到数据，传回主线程 */
    connect(_dumpThread, &DumpThread::tcp_received, this, &CaptureWidget::deal_Tcp, Qt::QueuedConnection);
    connect(_dumpThread, &DumpThread::udp_received, this, &CaptureWidget::deal_Udp, Qt::QueuedConnection);

    /* 通知子线程开始或结束 */
    connect(this, &CaptureWidget::sig_startCapture, _dumpThread, &DumpThread::slot_startCapture, Qt::QueuedConnection);
    connect(this, &CaptureWidget::sig_stopCapture, _dumpThread, &DumpThread::slot_stopCapture, Qt::QueuedConnection);

    QThread *thread = new QThread();
    _dumpThread->moveToThread(thread);
    thread->start();
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

    /* 清理QListWidget */
    /* ...... */
    int index = ui->comboBoxInter->currentIndex();
    const pcap_if_t *device = yang::SystemDevice::getInstance()->getAllDevs().at(index);
    emit sig_startCapture(device);
}
std::string CaptureWidget::integerToIp(uint32_t net_addr)
{
    char buff[32] = {0};
    std::stringstream sb;
#if defined(__LITTLE_ENDIAN_BITFIELD)
    sb << ((net_addr & 0x000000ff) >> 0)
       << "." << ((net_addr & 0x0000ff00) >> 8)
       << "." << ((net_addr & 0x00ff0000) >> 16)
       << "." << ((net_addr & 0xff000000) >> 24);
#else
    sb << ((net_addr & 0xff000000) >> 24)
       << "." << ((net_addr & 0x00ff0000) >> 16)
       << "." << ((net_addr & 0x0000ff00) >> 8)
       << "." << ((net_addr & 0x000000ff) >> 0);
#endif
    return sb.str();
}

void CaptureWidget::deal_Tcp(__TcpData data)
{
    qDebug() << "ip len: " << data.ip_h->ihl << ", tcp len: " << data.tcp_h->doff;
    /* 源 */
    data.ip_h->saddr;
    data.tcp_h->source;
    /* 目的 */
    data.ip_h->daddr;
    data.tcp_h->dest;
    /* 数据长度 */
    data.ip_h->tot_len - data.ip_h->ihl*4*8 - data.tcp_h->doff*4*8;

    /* 数据内容 */
    data.data;
    qDebug() << integerToIp(data.ip_h->saddr).c_str() << ":" << ntohs(data.tcp_h->source) << ">>"
             << integerToIp(data.ip_h->daddr).c_str() << ":" << ntohs(data.tcp_h->dest) << "    len"
             << (ntohs(data.ip_h->tot_len) - data.ip_h->ihl*4 - data.tcp_h->doff*4);
}

void CaptureWidget::deal_Udp(__UdpData data)
{

}

void CaptureWidget::on_btnAdvance_clicked()
{

}
