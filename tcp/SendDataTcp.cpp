#include <QListWidgetItem>
#include "SendDataTcp.h"
#include "SendDataItem.h"

namespace yang {
SendDataTcp::SendDataTcp(QWidget *parent)
    : QWidget(parent),
      _lineEditHost(nullptr),
      _lineEditPort(nullptr),
      _btnSend(nullptr),
      _labelHost(nullptr),
      _labelPort(nullptr),
      _listWidget(nullptr),
      _btnAdd(nullptr)
{
    _labelPort = new QLabel(tr("端口"), this);
    _labelHost = new QLabel(tr("主机"), this);
    _btnSend = new QPushButton(tr("发送"), this);
    _listWidget = new QListWidget(this);
    _lineEditPort = new QLineEdit(this);
    _lineEditHost = new QLineEdit(this);

    _listWidget->resize(width()*0.8, height()*0.6);
    _itemSize = QSize(0.9 * _listWidget->width(), 30);
    _btnAdd = new QPushButton(tr("添加"));
    _btnAdd->resize(_itemSize);
    QListWidgetItem *item_buttom = new QListWidgetItem(_listWidget);
    item_buttom->setSizeHint(_itemSize);
    _listWidget->setItemWidget(item_buttom, _btnAdd);
    _listWidget->addItem(item_buttom);
    connect(_btnAdd, &QPushButton::clicked, this, &SendDataTcp::addListItem);
}

void SendDataTcp::addListItem()
{
    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(_itemSize);

    SendDataItem *widget = new SendDataItem(_itemSize);
    _listWidget->insertItem(_listWidget->count()-1, item);
    _listWidget->setItemWidget(item, widget);
}

SendDataTcp::~SendDataTcp()
{
}

void SendDataTcp::resizeEvent(QResizeEvent *event)
{
    int wd = size().width();
    int ht = size().height();
    _labelHost->setGeometry(wd*0.1, ht*0.02, wd*0.1, ht*0.08);
    _labelPort->setGeometry(wd*0.1, ht*0.12, wd*0.1, ht*0.1);
    _lineEditHost->setGeometry(wd*0.2, ht*0.02, wd*0.7, ht*0.08);
    _lineEditPort->setGeometry(wd*0.2, ht*0.12, wd*0.7, ht*0.08);
    _listWidget->setGeometry(wd*0.1, ht*0.2, wd*0.8, ht*0.6);
    _btnSend->setGeometry(wd*0.3, ht*0.85, wd*0.4, ht*0.1);
    QWidget::resizeEvent(event);
}

void SendDataTcp::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}


}
