#include "SendDataHttp.h"
#include <sstream>
#include <QProcess>

namespace yang {

SendDataHttp::SendDataHttp(QWidget *parent)
    : QWidget(parent),
      _comboBox(nullptr),
      _textEdit_url(nullptr),
      _btn_send(nullptr),
      _labelParams(nullptr)
{
    _labelParams = new QLabel(this);_labelParams->setText("URL");
    _btn_send = new QPushButton(tr("发送"), this);
    connect(_btn_send, &QPushButton::clicked, this, &SendDataHttp::onSendBtnClick);
    _textEdit_url = new QPlainTextEdit(this);
    _comboBox = new QComboBox(this);
    _comboBox->addItem("GET", QVariant(0));
    _comboBox->addItem("POST", QVariant(1));
    initContentTypeMap();
}
SendDataHttp::~SendDataHttp()
{

}

void SendDataHttp::onSendBtnClick()
{
    QString text_url = _textEdit_url->document()->toPlainText();
    std::string comboBox_text = _comboBox->currentText().toStdString();
    if( 0 == comboBox_text.compare("GET")){
        request_by_get(text_url);
    } else {
        request_by_post(text_url);
    }
}

void SendDataHttp::request_by_get(const QString &url)
{
     QNetworkAccessManager *manager = new QNetworkAccessManager(this);
     QNetworkRequest request;
     request.setUrl(QUrl(url));
     manager->get(request);
     connect(manager, &QNetworkAccessManager::finished, this, &SendDataHttp::received_Data);
}

void SendDataHttp::request_by_post(const QString &text)
{
    std::string str = text.toStdString();
    int pos = str.find_first_of('?');

    std::string url = std::string(str, 0, pos);
    std::string params = std::string(str, pos+1, str.size()-url.size()-1);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(QUrl(QString(tr(url.c_str()))));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain;"));

    manager->post(request, QByteArray(params.c_str(), params.size()));
    connect(manager, &QNetworkAccessManager::finished, this, &SendDataHttp::received_Data);
}

void SendDataHttp::received_Data(QNetworkReply *reply)
{
    if(!reply) {
        qDebug() << "QNetworkReply is nullptr";
    } else if(reply->error() == QNetworkReply::NoError){
        QString filename = "text";
        std::string all_header = reply->header(QNetworkRequest::ContentTypeHeader).toString().toStdString();
        /* http contentType 也可能分为多段，用分号隔开 */
        std::string header = all_header.substr(0, all_header.find_first_of(';'));
        filename.append(getSuffix(header).c_str());

        QByteArray data = reply->readAll();
        QFile recv(filename);
        if(recv.exists()){
            recv.remove();
        }
        if(!recv.open(QFile::WriteOnly)){
            qDebug() << "open file error";
        }
        recv.write(data);
        recv.close();
        QProcess::execute("explorer.exe", QStringList() << filename);
    } else {
        qDebug() << reply->errorString();
    }
}

void SendDataHttp::resizeEvent(QResizeEvent *event)
{
    _labelParams->setGeometry(width() * 0.08, height() *0.05, width() * 0.08, height() * 0.1);
     _textEdit_url->setGeometry(width()*0.16, height() * 0.05, width() * 0.8, height() * 0.4);
    _comboBox->setGeometry(width() * 0.30, height() * 0.55, width() * 0.15, height() * 0.1);
    _btn_send->setGeometry(width() * 0.55, height() * 0.55, width() * 0.15, height() * 0.1);
    QWidget::resizeEvent(event);
}

void SendDataHttp::initContentTypeMap()
{
    QFile file(":/http/httpContentType.txt");
    file.open(QFile::ReadOnly);
    std::string txt = file.readAll().toStdString();
    file.close();

    std::stringstream in(txt);
    std::string key, value;
    while(!in.eof()){
        in >> value >> key;
        _contentType_map.emplace(key, value);
    }
}

std::string SendDataHttp::getSuffix(const std::string &contentType)
{
    if(_contentType_map.count(contentType) <= 0)
        return "";
    else
        return _contentType_map[contentType];
}

}
