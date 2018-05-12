#include "DumpThread.h"

//namespace yang {

DumpThread::DumpThread(QObject *parent) : QObject(parent)
{
}

void DumpThread::on_tcp_received(__TcpData data)
{
    emit sig_tcpReceived(data);
}
void DumpThread::on_udp_received(__UdpData data)
{
    emit sig_udpReceived(data);
}

void DumpThread::slot_startCapture(const pcap_if_t *device, const QString &filter)
{
    capturePacket(device, filter.toStdString());
}
void DumpThread::slot_stopCapture()
{
    stopCapture();
}
//}
