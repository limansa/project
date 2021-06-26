
#ifndef CC_2500_H__
 #define CC_2500_H__


 extern uint8_t _cctxF;
#define ccSetPW(n)      ccSetReg(0x7E,n)
#define ccGetPW()       ccGetReg(0xFE)
#define ccStatus(reg)   ccGetReg(0xC0 | reg)
#define ccFSM() ccStatus(0x35)
//---
//cc Command
#define ccSRX()         ccStrobe(0x34)
#define ccSTX()         ccStrobe(0x35)
#define ccSIDLE()       ccStrobe(0x36)
#define ccSFRX()        ccStrobe(0x3A)
#define ccSFTX()        ccStrobe(0x3B)

#endif