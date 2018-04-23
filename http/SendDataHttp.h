#ifndef SENDDATAHTTP_H
#define SENDDATAHTTP_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QLabel>

namespace yang {

class SendDataHttp : public QWidget
{
    Q_OBJECT
public:
    explicit SendDataHttp(QWidget *parent = nullptr);
    virtual ~SendDataHttp();
protected:
     virtual void resizeEvent(QResizeEvent *event) override;
private slots:
     void onSendBtnClick();
private:
    QComboBox *_comboBox;       /* 选择post和get */
    QLineEdit *_lineEdit_url;   /* url： http://hostname:port/ */
    QPlainTextEdit *_textEdit_params;  /* 参数 */
    QPushButton *_btn_send;     /* 发送按钮 */
    QLabel *_labelHost;
    QLabel *_labelParams;
};

}

#endif // SENDDATAHTTP_H
