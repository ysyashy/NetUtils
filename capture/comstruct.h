#ifndef __COMSTRUCT_H
#define __COMSTRUCT_H

#include <stdint.h>

#pragma pack(1)
struct _eth_hdr {
    unsigned char dstmac[6];
    unsigned char srcmac[6];
    uint16_t eth_type;
};

struct ip_header {
   uint32_t ver   : 4;
   uint32_t hlen  : 4;
   uint32_t dsc   : 7;
   uint32_t ecn   : 1;
   uint32_t len   : 16;

   uint32_t ide   : 16;
   uint32_t flg   : 2;
   uint32_t off   : 14;

   uint32_t ttl   : 8;
   uint32_t pro   : 8;
   uint32_t chk   : 16;

   uint32_t saddr;
   uint32_t daddr;
};

struct tcp_header {
    uint32_t s_port : 16;
    uint32_t p_port : 16;
    uint32_t seq;
    uint32_t asq;

    uint32_t off : 4;
    uint32_t rev : 6;
    uint32_t urg : 1;
    uint32_t ack : 1;
    uint32_t psh : 1;
    uint32_t rst : 1;
    uint32_t syn : 1;
    uint32_t fin : 1;
    uint32_t win : 16;

    uint32_t chksum : 16;
    uint32_t urg_point    : 16;
};

struct _udp_hdr{
    uint32_t src_port : 16;
    uint32_t dst_port : 16;
    uint32_t h_len : 16;
    uint32_t chk_sum : 16;
};


#pragma pack()

#endif
