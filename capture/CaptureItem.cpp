#include "CaptureItem.h"
#include "ui_CaptureItem.h"

CaptureItem::CaptureItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CaptureItem)
{
    ui->setupUi(this);
}

CaptureItem::~CaptureItem()
{
    delete ui;
}

void CaptureItem::on_btnDetial_clicked()
{

}
