#include "AdvanceWidget.h"
#include "ui_AdvanceWidget.h"

AdvanceWidget::AdvanceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdvanceWidget)
{
    ui->setupUi(this);
}

AdvanceWidget::~AdvanceWidget()
{
    delete ui;
}

void AdvanceWidget::on_btnCancel_clicked()
{

}

void AdvanceWidget::on_btnOk_clicked()
{

}
