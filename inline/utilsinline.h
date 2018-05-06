#ifndef __UTILSINLINE_H
#define __UTILSINLINE_H

#include "capture/comstruct.h"

inline uint16_t __ntohs(uint16_t x)
{
#if defined(__LITTLE_ENDIAN_BITFIELD)
    return ((x >> 8) & 0x00ff) | ((x & 0x00ff) << 8);
#else
    return n;
#endif
}

inline uint32_t __ntohl(uint32_t x)
{
#if defined(__LITTLE_ENDIAN_BITFIELD)
    return (
                (((x) & 0xff000000) >> 24) |
                (((x) & 0x00ff0000) >>  8) |
                (((x) & 0x0000ff00) <<  8) |
                (((x) & 0x000000ff) << 24)
                );
#else
    return x;
#endif

}

/* 是否为可见字符 */
inline bool isvAscii(char c)
{
    return ( ' ' <= c && c <= '~');
}

inline const ip_hdr *getIpHdr(const char *datas)
{
    return (const ip_hdr*)(datas+sizeof(eth_hdr));
}

inline const tcp_hdr *getTcpHdr(const char *datas)
{
    const ip_hdr *ih = getIpHdr(datas);
    return (const tcp_hdr*)(datas + sizeof(eth_hdr) + ih->ihl * 4);
}

inline const char *getNetData(const char *datas)
{
    const ip_hdr *ih = getIpHdr(datas);
    const tcp_hdr *th = getTcpHdr(datas);
    return datas + sizeof(eth_hdr) + ih->ihl*4 + th->doff*4;
}

inline int32_t getNetDataLen(const char *datas)
{
    const ip_hdr *ih = getIpHdr(datas);
    const tcp_hdr *th = getTcpHdr(datas);
    int len = __ntohs(ih->tot_len);
    return  (int32_t)len - ih->ihl*4 - th->doff*4;
}

#endif
