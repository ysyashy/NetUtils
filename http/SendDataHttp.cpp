#include "SendDataHttp.h"
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

    manager->post(request, QByteArray(params.c_str(), params.size()));
    connect(manager, &QNetworkAccessManager::finished, this, &SendDataHttp::received_Data);
}

void SendDataHttp::received_Data(QNetworkReply *reply)
{
    if(!reply) {
        qDebug() << "QNetworkReply is nullptr";
    } else if(reply->error() == QNetworkReply::NoError){
        QByteArray data = reply->readAll();
        QFile recv("./text.html");
        if(recv.exists()){
            recv.remove();
        }
        if(!recv.open(QFile::WriteOnly)){
            qDebug() << "open file error";
        }
        recv.write(data);
        recv.close();
        // QProcess *p = new QProcess(this);
        // p->start("C:\Windows\System32\cmd.exe /c C:\Windows\explorer.exe E:\qt_project\build-NetUtils-Desktop_Qt_5_7_0_MinGW_32bit-Debug\text.html");
        QProcess::execute("explorer.exe C:\\Users\\ysyas\\.gitconfig");
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
}
