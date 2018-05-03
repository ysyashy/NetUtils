#ifndef __COMSTRUCT_H
#define __COMSTRUCT_H

#include <stdint.h>

#ifndef __LITTLE_ENDIAN_BITFIELD
#define __LITTLE_ENDIAN_BITFIELD
#endif

struct ip_hdr {
#if defined(__LITTLE_ENDIAN_BITFIELD)
    uint8_t	ihl:4,
            version:4;
#elif defined (__BIG_ENDIAN_BITFIELD)
    uint8_t	version:4,
            ihl:4;
#else
#error	"Please fix <asm/byteorder.h>"
#endif
    uint8_t     tos;
    uint16_t	tot_len;
    uint16_t	id;
    uint16_t	frag_off;
    uint8_t     ttl;
    uint8_t     protocol;
    uint16_t	check;
    uint32_t	saddr;
    uint32_t	daddr;
    /*The options start here. */
};

struct tcp_hdr {
    uint16_t	source;
    uint16_t	dest;
    uint32_t	seq;
    uint32_t	ack_seq;
#if defined(__LITTLE_ENDIAN_BITFIELD)
    uint16_t	res1:4,
        doff:4,
        fin:1,
        syn:1,
        rst:1,
        psh:1,
        ack:1,
        urg:1,
        ece:1,
        cwr:1;
#elif defined(__BIG_ENDIAN_BITFIELD)
    uint16_t	doff:4,
        res1:4,
        cwr:1,
        ece:1,
        urg:1,
        ack:1,
        psh:1,
        rst:1,
        syn:1,
        fin:1;
#else
#error	"Adjust your <asm/byteorder.h> defines"
#endif
    uint16_t	window;
    uint16_t	check;
    uint16_t	urg_ptr;
};

struct udp_hdr {
    uint16_t	source;
    uint16_t	dest;
    uint16_t	len;
    uint16_t	check;
};

#pragma pack(1)
struct eth_hdr {
    unsigned char dstmac[6];
    unsigned char srcmac[6];
    uint16_t eth_type;
};
#pragma pack()

#endif
