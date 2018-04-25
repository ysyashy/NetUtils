#include "SendDataItem.h"
namespace yang {
SendDataItem::SendDataItem(QWidget *parent, const QSize &size)
    : QWidget(parent),
      _comboBox(nullptr),
      _lineEdit(nullptr),
      _btn_remove(nullptr)
{
    resize(size);
    _btn_remove = new QPushButton(this);
    _lineEdit = new QPushButton(this);
    _comboBox = new QComboBox(this);
}

SendDataItem::~SendDataItem()
{}

void SendDataItem::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}
}
