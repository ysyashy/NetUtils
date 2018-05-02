#include "SystemDevice.h"
#include <iostream>

namespace yang {
SystemDevice *SystemDevice::_instance = nullptr;

SystemDevice *SystemDevice::getInstance()
{
    if(nullptr == _instance) {
        _instance = new (std::nothrow) SystemDevice();
        if(!_instance->init()){
            delete _instance;
            _instance = nullptr;
        }
    }
    return _instance;
}
void SystemDevice::destoryInstance()
{
    if(_instance->_allDevs.size() > 0) pcap_freealldevs(_instance->_allDevs[0]);
    _instance->_allDevs.clear();
    if(nullptr != _instance) {
        delete _instance;
        _instance = nullptr;
    }
}

bool SystemDevice::init()
{
    pcap_if_t *devs;
    char errbuff[PCAP_ERRBUF_SIZE];
    if(-1 == pcap_findalldevs(&devs, errbuff)) {
        return false;
    }
    for(pcap_if_t *dev = devs; dev; dev = dev->next) {
        _allDevs.push_back(dev);
    }
    return true;
}

const std::vector<pcap_if_t*> &SystemDevice::getAllDevs()
{
    return _allDevs;
}

SystemDevice::SystemDevice()
{
}
SystemDevice::~SystemDevice()
{
}

}
