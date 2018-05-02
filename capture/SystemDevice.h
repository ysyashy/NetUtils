#ifndef __SYSTEMDEVICE_H
#define __SYSTEMDEVICE_H

#include <pcap.h>
#include <vector>

namespace yang {
class SystemDevice
{
public:
    static SystemDevice *getInstance();
    static void destoryInstance();
    const std::vector<pcap_if_t*> &getAllDevs();
private:
    bool init();
    static SystemDevice *_instance;
    std::vector<pcap_if_t*> _allDevs;
protected:
    SystemDevice();
    ~SystemDevice();
};

}
#endif // SYSTEMDEVICE_H
