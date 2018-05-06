#ifndef __DUMPOFFLINETHREAD_H
#define __DUMPOFFLINETHREAD_H

#include <cinttypes>
#include <QObject>
#include <pcap.h>

class DumpOfflineThread : public QObject
{
    Q_OBJECT
public:
    explicit DumpOfflineThread(QObject *parent = nullptr);
    ~DumpOfflineThread();

signals:
    void sig_readComplete(const char *datas);
public slots:
    void slot_request(uint32_t index);
private:
    pcap_t *_adhandle;
};

#endif // DUMPOFFLINETHREAD_H
