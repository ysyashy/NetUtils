#ifndef __CAPTUREWIDGET_H
#define __CAPTUREWIDGET_H

#include <unordered_map>
#include <QWidget>
#include <string>
#include "DumpThread.h"
#include "DumpOfflineThread.h"
namespace Ui {
class CaptureWidget;
}

struct __LengthValue{
    int len;
    char *data;
    __LengthValue(int l = 0, char *d = NULL) : len(l), data(d) {}
};

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

    void slot_showDetials(const char *datas);
    void slot_requestDetials(uint32_t index);
signals:
    /* 网络数据抓取线程 */
    void sig_startCapture(const pcap_if_t *device);
    void sig_stopCapture();
    /* 本地数据读取线程 */
    void sig_requestData(uint32_t index);
private:
    std::string integerToIp(uint32_t a);
    char* getBrief(uint32_t totl, const char *data);
    void initTableWidget();
private:
    Ui::CaptureWidget *ui;
    DumpThread *_captureThread;
    DumpOfflineThread *_readDumpThread;
    char _rbuff[64];
    char _buff[64];
    uint32_t _itemCounts;
};

#endif // CAPTUREWIDGET_H
