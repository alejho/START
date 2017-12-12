#ifndef NETWORK_H
#define NETWORK_H

//ip address www.xxx.yyy.zzz
#define IP_www  192
#define IP_xxx  168
#define IP_yyy  1
#define IP_zzz  177

//subnet maks www.xxx.yyy.zzz
#define SBN_www  255
#define SBN_xxx  255
#define SBN_yyy  255
#define SBN_zzz  0

//default gateway www.xxx.yyy.zzz
#define GW_www  192
#define GW_xxx  168
#define GW_yyy  1
#define GW_zzz  1

//default dns www.xxx.yyy.zzz
#define DNS_www  192
#define DNS_xxx  168
#define DNS_yyy  1
#define DNS_zzz  1

//mac address { byte_1, byte_2, byte_3, byte_4, byte_5, byte_6 }; 

#define MAC_byte_1  0xDE
#define MAC_byte_2  0xAD
#define MAC_byte_3  0xBE
#define MAC_byte_4  0xEF
#define MAC_byte_5  0xFE
#define MAC_byte_6  0xED

#endif
