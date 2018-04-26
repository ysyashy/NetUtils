#include "SendDataItem.h"
namespace yang {
SendDataItem::SendDataItem(const QSize &size, QWidget *parent)
    : QWidget(parent),
      _comboBox(nullptr),
      _lineEdit(nullptr),
      _btn_remove(nullptr)
{
    resize(size);
    _btn_remove = new QPushButton(tr("删除"), this);
    _lineEdit = new QLineEdit(this);
    _comboBox = new QComboBox(this);
}

SendDataItem::~SendDataItem()
{}

void SendDataItem::resizeEvent(QResizeEvent *event)
{
    int wd = size().width();
    int ht = size().height();
    _comboBox->setGeometry(0, 0.1*ht, 0.3*wd, 0.9*ht);
    _lineEdit->setGeometry(0.35*wd, 0.1*ht, 0.5*wd, 0.9*ht);
    _btn_remove->setGeometry(0.9*wd, 0.1*ht, 0.1*wd, 0.9*ht);

    QWidget::resizeEvent(event);
}
void SendDataItem::remove_btn_clicked()
{

}
}
