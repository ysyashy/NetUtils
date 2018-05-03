#ifndef __DUMPINTERFACE_H
#define __DUMPINTERFACE_H

#include <exception>
#include <QMetaType>
#include <string>
#include <pcap.h>
#include "comstruct.h"

//namespace yang {

struct __TcpData {
    ip_hdr *ip_h;
    tcp_hdr *tcp_h;
    u_char *data;
    __TcpData(ip_hdr *ih = nullptr, tcp_hdr *th = nullptr, u_char *d = nullptr)
        : ip_h(ih), tcp_h(th), data(d)
    {}
};
Q_DECLARE_METATYPE(__TcpData)

struct __UdpData {
    ip_hdr *ip_h;
    udp_hdr *udp_h;
    u_char *data;
    __UdpData(ip_hdr *ih = nullptr, udp_hdr *uh = nullptr, u_char *d = nullptr)
        : ip_h(ih), udp_h(uh), data(d)
    {}
};
Q_DECLARE_METATYPE(__UdpData)

enum class PcapErrorType {
    CaptureError,
    FilterError
};

class PcapException : public std::exception {
public:
    PcapException(std::string str, PcapErrorType t)
        : std::exception(),
          msg(str),
          type(t)
    {}
    std::string msg;
    PcapErrorType type;
};

class DumpInterface
{
public:
    DumpInterface();
    ~DumpInterface();
public:
    void capturePacket(const pcap_if_t *dev);
    void stopCapture();
protected:
    virtual void on_tcp_received(__TcpData data) = 0;
    virtual void on_udp_received(__UdpData data) = 0;
private:
    void on_packet_received(const pcap_pkthdr *pkt_header, const u_char *pkt_data);
    pcap_t *_adhandle;
    bool _isContinue;
};

//}
#endif // __DUMPINTERFACE_H
