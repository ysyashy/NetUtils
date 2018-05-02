#include "CaptureWidget.h"
#include "ui_CaptureWidget.h"
#include "SystemDevice.h"

CaptureWidget::CaptureWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CaptureWidget)
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
}

void CaptureWidget::on_btnStart_clicked()
{
    ui->btnStop->setStyleSheet("QPushButton{background: red;}");
    ui->btnStop->setEnabled(true);
    ui->btnStart->setStyleSheet("QPushButton{background: grey}");
    ui->btnStart->setEnabled(false);

    int index = ui->comboBoxInter->currentIndex();
    const pcap_if_t *device = yang::SystemDevice::getInstance()->getAllDevs().at(index);
}


void CaptureWidget::on_pushButton_clicked()
{

}
