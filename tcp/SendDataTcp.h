#ifndef __SENDDATATCP_H
#define __SENDDATATCP_H

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>

namespace yang {
class SendDataTcp : public QWidget
{
    Q_OBJECT
public:
    explicit SendDataTcp(QWidget *parent);
    virtual ~SendDataTcp();
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
private:
    QLineEdit *_lineEditHost;
    QLineEdit *_lineEditPort;
    QListWidget *_listWidget;
    QPushButton *_btnSend;
};
}

#endif // __SENDDATATCP_H
