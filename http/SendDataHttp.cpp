#include "SendDataHttp.h"

namespace yang {

SendDataHttp::SendDataHttp(QWidget *parent)
    : QWidget(parent),
      _comboBox(nullptr),
      _lineEdit_url(nullptr),
      _textEdit_params(nullptr),
      _btn_send(nullptr),
      _labelHost(nullptr),
      _labelParams(nullptr)
{
    _labelHost = new QLabel(this);  _labelHost->setText("Url");
    _labelParams = new QLabel(this);_labelParams->setText("Params");
    _btn_send = new QPushButton(tr("发送"), this);
    _textEdit_params = new QPlainTextEdit(this);
    _lineEdit_url = new QLineEdit(this);
    _comboBox = new QComboBox(this);
    _comboBox->addItem("GET", QVariant(0));
    _comboBox->addItem("POST", QVariant(1));
}
SendDataHttp::~SendDataHttp()
{

}

void SendDataHttp::onSendBtnClick()
{
}
void SendDataHttp::resizeEvent(QResizeEvent *event)
{
    _labelHost->setGeometry(width() * 0.08, height() * 0.05, width() * 0.08, height() * 0.1);
    _lineEdit_url->setGeometry(width()*0.16, height() * 0.05, width() * 0.8, height()*0.1);
    _labelParams->setGeometry(width() * 0.08, height() *0.2, width() * 0.08, height() * 0.1);
     _textEdit_params->setGeometry(width()*0.16, height() * 0.2, width() * 0.8, height() * 0.4);
    _comboBox->setGeometry(width() * 0.30, height() * 0.7, width() * 0.15, height() * 0.1);
    _btn_send->setGeometry(width() * 0.55, height() * 0.7, width() * 0.15, height() * 0.1);
    QWidget::resizeEvent(event);
}
}
