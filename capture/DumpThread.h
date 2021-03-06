#ifndef __DUMPTHREAD_H
#define __DUMPTHREAD_H

#include <QObject>
#include "DumpInterface.h"

//namespace yang {
class DumpThread
        : public QObject
        , private DumpInterface
{
    Q_OBJECT
public:
    explicit DumpThread(QObject *parent = 0);
private:
    virtual void on_tcp_received(__TcpData data) override;
    virtual void on_udp_received(__UdpData data) override;
signals:
    void sig_tcpReceived(__TcpData data);
    void sig_udpReceived(__UdpData data);
public slots:
    void slot_startCapture(const pcap_if_t *device, const QString &filter);
    void slot_stopCapture();
};

//}

#endif // DUMPTHREAD_H
