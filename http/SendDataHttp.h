#ifndef SENDDATAHTTP_H
#define SENDDATAHTTP_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QLabel>
#include <QNetWorkReply>
#include <unordered_map>
#include <string>

namespace yang {

class SendDataHttp : public QWidget
{
    Q_OBJECT
public:
    explicit SendDataHttp(QWidget *parent = nullptr);
    virtual ~SendDataHttp();
protected:
     virtual void resizeEvent(QResizeEvent *event) override;
private:
    QComboBox *_comboBox;       /* 选择post和get */
    QPlainTextEdit *_textEdit_url;  /* url */
    QPushButton *_btn_send;     /* 发送按钮 */
    QLabel *_labelParams;
private:
    /* http相关 */
    std::unordered_map<std::string, std::string> _contentType_map;
    void request_by_get(const QString &url);
    void request_by_post(const QString &url);
private slots:
     void onSendBtnClick();
     void received_Data(QNetworkReply *reply);
};

}

#endif // SENDDATAHTTP_H
