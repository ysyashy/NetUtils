#ifndef __CAPTUREWIDGET_H
#define __CAPTUREWIDGET_H

#include <QWidget>
#include <string>
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

    void deal_Tcp(__TcpData data);
    void deal_Udp(__UdpData data);
signals:
    void sig_startCapture(const pcap_if_t *device);
    void sig_stopCapture();
private:
    std::string integerToIp(uint32_t a);
private:
    Ui::CaptureWidget *ui;
    DumpThread *_dumpThread;
};

#endif // CAPTUREWIDGET_H
