#ifndef __DUMPINTERFACE_H
#define __DUMPINTERFACE_H

#include <exception>
#include <QMetaType>
#include <string>
#include <pcap.h>
#include "comstruct.h"

//namespace yang {

struct __TcpData {
    const ip_hdr *ip_h;
    const tcp_hdr *tcp_h;
    const char *data;
    __TcpData(const ip_hdr *ih = NULL, const tcp_hdr *th = NULL, const char *d = NULL)
        : ip_h(ih), tcp_h(th), data(d)
    {}
};
Q_DECLARE_METATYPE(__TcpData)

struct __UdpData {
    const ip_hdr *ip_h;
    const udp_hdr *udp_h;
    const char *data;
    __UdpData(const ip_hdr *ih = NULL, const udp_hdr *uh = NULL, const char *d = NULL)
        : ip_h(ih), udp_h(uh), data(d)
    {}
};
Q_DECLARE_METATYPE(__UdpData)

enum class PcapErrorType {
    CaptureError,
    FilterError,
    DumpFileError
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
    void openDumpFile();
    pcap_t *_adhandle;
    pcap_dumper_t  *_dump_file;
    bool _isContinue;
};

//}
#endif // __DUMPINTERFACE_H
