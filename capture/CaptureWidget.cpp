#include "CaptureWidget.h"
#include "ui_CaptureWidget.h"

CaptureWidget::CaptureWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CaptureWidget)
{
    ui->setupUi(this);
    ui->btnStop->setEnabled(false);
    ui->btnStop->setStyleSheet("QPushButton{background: grey;}");
    ui->btnStart->setStyleSheet("QPushButton{background: green}");
}

CaptureWidget::~CaptureWidget()
{
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
}


void CaptureWidget::on_pushButton_clicked()
{

}
