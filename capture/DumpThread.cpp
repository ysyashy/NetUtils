#include "DumpThread.h"

//namespace yang {

DumpThread::DumpThread(QObject *parent) : QObject(parent)
{
}

void DumpThread::on_tcp_received(__TcpData data)
{
    emit tcp_received(data);
}
void DumpThread::on_udp_received(__UdpData data)
{
    emit udp_received(data);
}

void DumpThread::slot_startCapture(const pcap_if_t *device)
{
    capturePacket(device);
}
void DumpThread::slot_stopCapture()
{
    stopCapture();
}
//}
