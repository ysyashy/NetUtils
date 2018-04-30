#ifndef __SENDDATATCP_H
#define __SENDDATATCP_H

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTcpSocket>

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
    void sendTcpData();
    void receivedTcpData();
private:
    QTcpSocket *_tcpSocket;
    QLineEdit *_lineEditHost;
    QLineEdit *_lineEditPort;
    QPushButton *_btnSend;
    QPushButton *_btnAdvance;

    QLabel *_labelHost;
    QLabel *_labelPort;
private:
    /* about QListWidgetItem */
    QSize _itemSize;
    QListWidget *_listWidget;
    QPushButton *_btnAdd;
private slots:
    void addListItem();
    void on_btn_send_clicked();
};
}

#endif // __SENDDATATCP_H
