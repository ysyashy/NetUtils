#include "DumpOfflineThread.h"
#include "SystemDevice.h"
#include <exception>

using yang::SystemDevice;

DumpOfflineThread::DumpOfflineThread(QObject *parent)
    : QObject(parent)
    , _adhandle(NULL)
{

}

DumpOfflineThread::~DumpOfflineThread()
{
    if(NULL != _adhandle) { pcap_close(_adhandle); _adhandle = NULL; }
}


void DumpOfflineThread::slot_request(uint32_t index)
{
    if(NULL != _adhandle) { pcap_close(_adhandle); _adhandle = NULL; }

    char errbuff[PCAP_ERRBUF_SIZE];
    _adhandle = pcap_open_offline(SystemDevice::getInstance()->getDumpFileName().c_str(), errbuff);
    if(NULL == _adhandle)   throw new std::runtime_error("open pcap offline error!");

    pcap_pkthdr *pkt_hdr = NULL;
    const uchar *datas;
    for(uint32_t i=0; i <= index; i++) {
        pcap_next_ex(_adhandle, &pkt_hdr, &datas);
    }
    emit sig_readComplete((const char *)datas);
}
