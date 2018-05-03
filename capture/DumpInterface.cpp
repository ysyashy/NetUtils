#include "DumpInterface.h"
#include <exception>
#include <winsock2.h>

//namespace yang {
DumpInterface::DumpInterface()
    : _adhandle(NULL),
      _isContinue(true)
{
}
DumpInterface::~DumpInterface()
{
    if(NULL != _adhandle) { pcap_close(_adhandle); _adhandle = NULL; }
}

void DumpInterface::capturePacket(const pcap_if_t *dev)
{
    if(NULL != _adhandle) {
        pcap_close(_adhandle);  _adhandle = NULL;
    }

    const char *devName = dev->name;
    char errbuf[PCAP_ERRBUF_SIZE + 1];
    _adhandle = pcap_open_live(devName, /* device name */
                               65536, /*portion of packet to capture*/
                               1,
                               1000, /* read timeout */
                               errbuf);
    if(NULL == _adhandle) {
        throw new PcapException("capture error", PcapErrorType::CaptureError);
    }
    /* 创建过滤器 */
    u_int netmask;
    if(NULL != dev->addresses) {
        netmask = ((sockaddr_in *)(dev->addresses->addr))->sin_addr.S_un.S_addr;
    } else {
        netmask = 0x00ffffff;
    }
    struct bpf_program fcode;
    const char *packet_filter = "ip and tcp";
    if(0 > pcap_compile(_adhandle, &fcode, packet_filter, 1, netmask)) {
        throw new PcapException("compile filter error", PcapErrorType::FilterError);
    }
    if(0 > pcap_setfilter(_adhandle, &fcode)) {
        throw new PcapException("set filter error!", PcapErrorType::FilterError);
    }

    /* 开始抓取数据 */
    int res = 0;
    pcap_pkthdr *pkt_header;
    const u_char *pkt_data;
    while(_isContinue && 0 <= (res = pcap_next_ex(_adhandle, &pkt_header, &pkt_data))) {
        if(0 == res) continue;
        on_packet_received(pkt_header, pkt_data);
    }
}
void DumpInterface::stopCapture()
{
    _isContinue = false;
}

void DumpInterface::on_packet_received(const pcap_pkthdr *, const u_char *data)
{
    u_char *pkt_data = const_cast<u_char*>(data);
    ip_hdr *ih = (ip_hdr*)(pkt_data + sizeof(eth_hdr));

    if(6 == ih->protocol) { /* tcp protectol */
        tcp_hdr *th = (tcp_hdr*)(pkt_data + sizeof(eth_hdr) + ih->ihl * 4);
        __TcpData netData(
                    ih,
                    th,
                    pkt_data + sizeof(eth_hdr) + ih->ihl * 4 + th->doff * 4);
        on_tcp_received(netData);
    } else if(17 == ih->protocol) { /* udp protectol */
        udp_hdr *uh = (udp_hdr*)(pkt_data+sizeof(eth_hdr) + ih->ihl*4);
        __UdpData netData(
                    ih,
                    uh,
                    pkt_data + sizeof(eth_hdr) + ih->ihl * 4 + sizeof(udp_hdr));
        on_udp_received(netData);
    } else if(1 == ih->protocol) { /* icmp protectol */

    } else {

    }
}

//}
