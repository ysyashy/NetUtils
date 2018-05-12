#include <fstream>
#include <QStandardPaths>
#include <QDebug>
#include <exception>
#include <ctime>
#include "DumpInterface.h"
#include "SystemDevice.h"

//namespace yang {
DumpInterface::DumpInterface()
    : _adhandle(NULL)
    , _dump_file(NULL)
    , _isContinue(true)
{
}
DumpInterface::~DumpInterface()
{
    if(NULL != _adhandle) { pcap_close(_adhandle); _adhandle = NULL; }
}

void DumpInterface::capturePacket(const pcap_if_t *dev, const std::string &filter)
{
    _isContinue = true;
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
    std::string packet_filter = "tcp and ip";
    packet_filter.append(filter);
    if(0 > pcap_compile(_adhandle, &fcode, packet_filter.c_str(), 1, netmask)) {
        throw new PcapException("compile filter error", PcapErrorType::FilterError);
    }
    if(0 > pcap_setfilter(_adhandle, &fcode)) {
        throw new PcapException("set filter error!", PcapErrorType::FilterError);
    }
    openDumpFile();
    /* 开始抓取数据 */
    int res = 0;
    pcap_pkthdr *pkt_header;
    const u_char *pkt_data;
    while(_isContinue && 0 <= (res = pcap_next_ex(_adhandle, &pkt_header, &pkt_data))) {
        if(0 == res) continue;
        on_packet_received(pkt_header, pkt_data);
    }
}
void DumpInterface::openDumpFile()
{
    /* 设置dump文件名 */
    time_t times = time(NULL);
    struct tm *t = localtime(&times);
    char dump_file_name[128];
    memset(dump_file_name, 0x00, sizeof(dump_file_name));
    snprintf(dump_file_name, sizeof(dump_file_name)
             , "%04d%02d%02d_%02d%02d%02d.pcapng"
             , t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
    /* 新建文件 */
    std::string file_path = QStandardPaths::writableLocation(QStandardPaths::TempLocation).toStdString();
    file_path.append("/").append(dump_file_name);
    /* 保存文件名 */
    yang::SystemDevice::getInstance()->setDumpFileName(file_path);
    _dump_file = pcap_dump_open(_adhandle, file_path.c_str());
    qDebug() << file_path.c_str();
    if(NULL == _dump_file) {
        throw new PcapException("open dump file error!", PcapErrorType::DumpFileError);
    }
}

void DumpInterface::stopCapture()
{
    _isContinue = false;
    if(NULL != _adhandle) { pcap_close(_adhandle); _adhandle = NULL; }
    if(NULL != _dump_file) { pcap_dump_close(_dump_file); _dump_file = NULL; }
}

void DumpInterface::on_packet_received(const pcap_pkthdr *pkt_hdr, const u_char *data)
{
    const char *pkt_data = (const char*)data;
    const ip_hdr *ih = (const ip_hdr*)(pkt_data + sizeof(eth_hdr));

    if(6 == ih->protocol) { /* tcp protectol */
        const tcp_hdr *th = (const tcp_hdr*)(pkt_data + sizeof(eth_hdr) + ih->ihl * 4);
        __TcpData netData(
                    ih,
                    th,
                    pkt_data + sizeof(eth_hdr) + ih->ihl * 4 + th->doff * 4);
        on_tcp_received(netData);
        pcap_dump((u_char*)_dump_file, pkt_hdr, data);
        pcap_dump_flush(_dump_file);
    } else if(17 == ih->protocol) { /* udp protectol */
        const udp_hdr *uh = (const udp_hdr*)(pkt_data+sizeof(eth_hdr) + ih->ihl*4);
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
