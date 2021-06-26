// cc2500 , ittraining 
// Date : Sep 15, 2014
#include <unistd.h>
#include <stdio.h>
#include <bcm2835.h>
#include <string.h>
#include "cc2500.h"
//typedef unsigned char uint8_t;
//typedef unsigned short  uint16_t;

uint8_t bcm2835_spi_transfer_cc(uint8_t value);

//--- CC2500 I/O
#define cc2500_CS(cs) do { \
   volatile uint32_t* paddr = bcm2835_spi0 + BCM2835_SPI0_CS/4; \
   if (cs==0) { \
    bcm2835_peri_set_bits(paddr, BCM2835_SPI0_CS_CLEAR, BCM2835_SPI0_CS_CLEAR);\
    bcm2835_peri_set_bits(paddr, BCM2835_SPI0_CS_TA, BCM2835_SPI0_CS_TA); \
    } else \
       bcm2835_peri_set_bits(paddr, 0, BCM2835_SPI0_CS_TA); \
 } while(0);
  




uint8_t _cctxF=0;

const unsigned char ccCFG[] = {
0x0B,0x2E,0x06,0x07,0xD3,0x91,0x61,0x04,
0x45,0x00,0x00,0x09,0x00,0x5D,0x93,0xB1,
0x2C,0x22,0x73,0x22,0xF8,0x01,0x07,0x00,
0x18,0x1D,0x1C,0xC7,0x00,0xB2,0x87,0x6B,
0xF8,0xB6,0x10,0xEA,0x0A,0x00,0x11,0x41,
0x00,0x59,0x7F,0x3F,0x88,0x31,0x0B,
};
uint8_t ccRX[128],ccTX[128];

//--- ccSPI
uint8_t ccSPI(uint8_t data){
return bcm2835_spi_transfer_cc(data);
}

//--- ccSetReg
void ccSetReg(uint8_t reg, uint8_t val){
 //fprintf(stderr,"%s called\n",__func__);
cc2500_CS(0);
    ccSPI(0x40 | reg);
    ccSPI(val);
cc2500_CS(1);

}
//--- ccGetReg
uint8_t ccGetReg(uint8_t reg){
uint8_t r;
cc2500_CS(0);
    ccSPI(0xC0 | reg);
    r = ccSPI(0);
cc2500_CS(1);
    return r;
}
//--- ccStrobe
void ccStrobe(uint8_t reg){
cc2500_CS(0);
    ccSPI(reg);
cc2500_CS(1);
}
//--- ccSendPkg
void ccSendPkg(uint8_t *src ){
uint8_t i,n;
    ccSIDLE();
    n=*src++;
cc2500_CS(0);
    ccSPI(0x7F);
    ccSPI(n);
    for (i=0;i<n;i++){
        ccSPI( *src++ );
        }
cc2500_CS(1);
    ccSTX();
    _cctxF=1;  //enter tx mode
}
//--- ccGetPkg
uint8_t ccGetPkg(uint8_t *dst){
uint8_t n,i;
cc2500_CS(0);            //- 操作開始
        ccSPI(0xFF);
        n = ccSPI(0);
    if (n==0 || n>61){
        cc2500_CS(1);  //- 操作結束
        ccSIDLE(); ccSFRX();
        return 2;   //- 資料長度錯誤
    }
        *dst++ = n;
    for(i=0;i<n;i++) { *dst++ = ccSPI(0xFF); }
        *dst++ = ccSPI(0);	//RSSI
        *dst  = ccSPI(0);	//LQI
cc2500_CS(1);      //- 操作結束
    if (*dst & 0x80){ return 0; } //- 正確返回
        return 3;   //- CRC 錯誤
}
#define	_CS	cc2500_CS
void ccReset(void){
    uint16_t i;
    _CS(1); for(i=0;i<10;i++){}
    _CS(0); for(i=0;i<10;i++){}
    _CS(1); for(i=0;i<1000;i++){}
    _CS(0); for(i=0;i<1000;i++){}
    ccSPI(0x30);
    _CS(1);

}

/* SetFreq(0~10) */
#define FREQ2(x)    ccSetReg(0x0D, x)
#define FREQ1(x)    ccSetReg(0x0E, x)
#define FREQ0(x)    ccSetReg(0x0F, x)
void ccSetFreq(uint8_t ch){
    switch (ch){
        case 0: FREQ2(0x5C); FREQ1(0x58); FREQ0(0x9D); break;
        case 1: FREQ2(0x5C); FREQ1(0x9D); FREQ0(0x89); break;
        case 2: FREQ2(0x5C); FREQ1(0xEC); FREQ0(0x4E); break;
        case 3: FREQ2(0x5D); FREQ1(0x3B); FREQ0(0x13); break;
        case 4: FREQ2(0x5D); FREQ1(0x89); FREQ0(0xD8); break;
        case 5: FREQ2(0x5D); FREQ1(0xD8); FREQ0(0x9D); break;
        case 6: FREQ2(0x5E); FREQ1(0x27); FREQ0(0x62); break;
        case 7: FREQ2(0x5E); FREQ1(0x76); FREQ0(0x27); break;
        case 8: FREQ2(0x5E); FREQ1(0xC4); FREQ0(0xEC); break;
        case 9: FREQ2(0x5F); FREQ1(0x13); FREQ0(0xB1); break;
        case 10: FREQ2(0x5F); FREQ1(0x62); FREQ0(0x76); break;
        default: FREQ2(0x5E); FREQ1(0xC4); FREQ0(0xEC); break;
    }
}
//--- ccInit
void ccInit(void){
uint8_t i;
	
    ccReset();
    ccSIDLE();
    for (i=0;i<47;i++){
        ccSetReg(i,ccCFG[i]);
    }
    ccSetFreq(8);
    ccSetPW(0xFB);
    _cctxF=0;
	ccSRX();
}

 #if 0
/*  
 *  返迴值：0，表示收到封包
 */
 //joseph mark here for compiling, ccFSM??? _cctxF??

uint8_t ccProc(void){
static uint8_t ccsta;
    uint8_t r;
    uint8_t fsm;
            fsm=ccFSM();
    switch (ccsta){  
        case 1:  //tx or rx complete 
            if (_cctxF){ _cctxF=0; ccSRX(); return 1;}
                r=ccGetPkg(ccRX);	//<<<--- 收到封包 ccRX[]
                ccSFRX(); ccSRX();
                return r;
        //--- TX
        case 17:  //tx error
        case 22:   //rx error
            ccSFTX();   ccSFRX(); 
	    ccSIDLE(); //enter IDEL mode
	    ccSRX(); // enter RX mode
            break;
    }
    return 1;
}
#endif
////----------------------joseph add, Sep 15, 2014 ------------------------------
//                        for CC2500 RF                                   
//-------------------------------------------------------------------------
// no CS action
uint8_t bcm2835_spi_transfer_cc(uint8_t value)
{
    volatile uint32_t* paddr = bcm2835_spi0 + BCM2835_SPI0_CS/4;
    volatile uint32_t* fifo = bcm2835_spi0 + BCM2835_SPI0_FIFO/4;

    // This is Polled transfer as per section 10.6.1
    // BUG ALERT: what happens if we get interupted in this section, and someone else
    // accesses a different peripheral? 
    // Clear TX and RX fifos
  //   bcm2835_peri_set_bits(paddr, BCM2835_SPI0_CS_CLEAR, BCM2835_SPI0_CS_CLEAR);

    // Maybe wait for TXD // TXD TX FIFO can accept data ? 1 means FIFO has space
    while (!(bcm2835_peri_read(paddr) & BCM2835_SPI0_CS_TXD))
	;

    // Write to FIFO, no barrier
    bcm2835_peri_write_nb(fifo, value);

    // Wait for DONE to be set
    while (!(bcm2835_peri_read_nb(paddr) & BCM2835_SPI0_CS_DONE))
	;

    // Read any byte that was sent back by the slave while we sere sending to it
    uint32_t ret = bcm2835_peri_read_nb(fifo);

   

    return ret;
}