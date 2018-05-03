#ifndef __CAPTUREWIDGET_H
#define __CAPTUREWIDGET_H

#include <QWidget>
#include "DumpThread.h"
namespace Ui {
class CaptureWidget;
}

class CaptureWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CaptureWidget(QWidget *parent = 0);
    ~CaptureWidget();
private slots:
    void on_btnStop_clicked();
    void on_btnStart_clicked();
    void on_btnAdvance_clicked();

    void deal_Tcp(yang::__TcpData data);
    void deal_Udp(yang::__UdpData data);
private:
    Ui::CaptureWidget *ui;
    yang::DumpThread *_dumpThread;
};

#endif // CAPTUREWIDGET_H
