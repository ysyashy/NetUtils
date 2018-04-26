#include "SendDataTcp.h"

namespace yang {
SendDataTcp::SendDataTcp(QWidget *parent)
    : QWidget(parent),
      _lineEditHost(nullptr),
      _lineEditPort(nullptr),
      _listWidget(nullptr),
      _btnSend(nullptr)
{
    _btnSend = new QPushButton(this);
    _listWidget = new QListWidget(this);
    _lineEditPort = new QLineEdit(this);
    _lineEditPort = new QLineEdit(this);
}
SendDataTcp::~SendDataTcp()
{
}

void SendDataTcp::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}

void SendDataTcp::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}


}
