#include <QListWidgetItem>
#include <QHostAddress>
#include "SendDataTcp.h"
#include "SendDataItem.h"
#include "parse/ParseData.h"

namespace yang {
SendDataTcp::SendDataTcp(QWidget *parent)
    : QWidget(parent),
      _tcpSocket(nullptr),
      _lineEditHost(nullptr),
      _lineEditPort(nullptr),
      _btnSend(nullptr),
      _btnAdvance(nullptr),
      _labelHost(nullptr),
      _labelPort(nullptr),
      _listWidget(nullptr),
      _btnAdd(nullptr)
{
    _tcpSocket = new QTcpSocket(this);
    connect(_tcpSocket, &QTcpSocket::connected, this, &SendDataTcp::sendTcpData);
    connect(_tcpSocket, &QTcpSocket::readyRead, this, &SendDataTcp::receivedTcpData);

    _labelPort = new QLabel(tr("端口"), this);
    _labelHost = new QLabel(tr("主机"), this);
    _lineEditHost = new QLineEdit(this);
    _lineEditPort = new QLineEdit(this);
    _listWidget = new QListWidget(this);
    _btnSend = new QPushButton(tr("发送"), this);
    _btnAdvance = new QPushButton(tr("高级"), this);
    connect(_btnSend, &QPushButton::clicked, this, &SendDataTcp::on_btn_send_clicked);

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

    SendDataItem *widget = new SendDataItem(_listWidget->count(), _itemSize);
    _listWidget->insertItem(_listWidget->count()-1, item);
    _listWidget->setItemWidget(item, widget);
    _listWidget->scrollToBottom();
    connect(widget, &SendDataItem::removeItemSignal, this, [=](){
        _listWidget->removeItemWidget(item);
        if(nullptr != item) delete item;
        if(nullptr != widget) delete widget;
        /* update index number */
        for(int idx = 0; idx < _listWidget->count(); idx++) {
            SendDataItem *item = dynamic_cast<SendDataItem*>(_listWidget->itemWidget(_listWidget->item(idx)));
            if(nullptr == item) continue;
            item->updateIndex(idx + 1);
        }
    });
}

void SendDataTcp::on_btn_send_clicked()
{
    qDebug() << "btn clicked";
    QString host = _lineEditHost->text();
    int port = _lineEditPort->text().toInt();
    _tcpSocket->connectToHost(QHostAddress(host) , port);
}
void SendDataTcp::sendTcpData()
{
    qDebug() << "sendTcpData";
    QByteArray bytes;
    for(int idx = 0; idx < _listWidget->count(); idx++) {
        SendDataItem *item = dynamic_cast<SendDataItem*>(_listWidget->itemWidget(_listWidget->item(idx)));
        if(nullptr == item) continue;
        bytes.append(item->getItemData());
    }
    if(bytes.isEmpty()) return;
    qDebug() << bytes.size();
    _tcpSocket->write(bytes);
}
void SendDataTcp::receivedTcpData()
{
    qDebug() << "received tcp data";
    QByteArray bytes = _tcpSocket->readAll();
    ParseData *parseData = new ParseData(bytes);
    parseData->show();
    qDebug() << bytes.size();
    _tcpSocket->close();
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
    _lineEditHost->setGeometry(wd*0.2, ht*0.02, wd*0.6, ht*0.08);
    _lineEditPort->setGeometry(wd*0.2, ht*0.12, wd*0.6, ht*0.08);
    _btnSend->setGeometry(wd*0.825, ht*0.03, wd*0.1, ht*0.16);
    _btnAdvance->setGeometry(wd*0.95, 0, wd*0.05, ht*0.05);
    _listWidget->setGeometry(wd*0.1, ht*0.2, wd*0.8, ht*0.8);
    QWidget::resizeEvent(event);
}

void SendDataTcp::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}


}
