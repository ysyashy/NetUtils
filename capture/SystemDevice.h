#ifndef __SYSTEMDEVICE_H
#define __SYSTEMDEVICE_H

#ifndef HAVE_REMOTE
#define HAVE_REMOTE
#endif

#include <pcap.h>
#include <vector>
#include <string>

namespace yang {
class SystemDevice
{
public:
    static SystemDevice *getInstance();
    static void destoryInstance();
    const std::vector<pcap_if_t*> &getAllDevs();
    void setDumpFileName(const std::string &name) { _dump_file_name = name; }
    const std::string &getDumpFileName() const { return _dump_file_name; }
private:
    bool init();
    static SystemDevice *_instance;
    std::vector<pcap_if_t*> _allDevs;
    std::string _dump_file_name;
protected:
    SystemDevice();
    ~SystemDevice();
};

}
#endif // SYSTEMDEVICE_H
