#include <QDebug>
#include <QThread>
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
    using yang::DumpThread;
    _dumpThread = new yang::DumpThread();
    connect(_dumpThread, &DumpThread::tcp_received, this, &CaptureWidget::deal_Tcp);
    connect(_dumpThread, &DumpThread::udp_received, this, &CaptureWidget::deal_Udp);

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

    _dumpThread->stopCapture();
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
    _dumpThread->capturePacket(device);
}

void CaptureWidget::deal_Tcp(yang::__TcpData data)
{
    qDebug() << "ip len: " << data.ip_h->ihl << ", tcp len: " << data.tcp_h->doff;
}
void CaptureWidget::deal_Udp(yang::__UdpData data)
{

}

void CaptureWidget::on_btnAdvance_clicked()
{

}
