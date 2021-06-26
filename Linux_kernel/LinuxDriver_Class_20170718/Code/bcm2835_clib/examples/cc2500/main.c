// cc2500 , ittraining 
// Date : Sep 15, 2014
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <bcm2835.h>

#include "cc2500.h"
#define PIN 		RPI_GPIO_P1_16
#define RELAY_PIN 	RPI_GPIO_P1_11

struct _packet {
  
   uint8_t len;
   uint8_t TargetID;   
   uint8_t SourceID;   
   uint8_t GroupID;
   uint8_t type;
   uint16_t data;
} __attribute__((packed));  

typedef struct _packet PACKET;

uint8_t tx[64],rx[64];
//uint8_t ss,cc='A',TXF=0;
uint8_t ss_relay=0;

int main(void) {

 // -----start ----
     uint8_t r,n;
     uint8_t value;
     uint8_t count=0;
     uint8_t data[10]={0};
     PACKET pkt,rx_pkt;
      if (!bcm2835_init())
	return 1;
   printf(" RF CC2500 Demo \n\n");
 
   bcm2835_spi_begin();

    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // The default
    bcm2835_spi_chipSelect(BCM2835_SPI_CS1);                      // The default
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS1, LOW);      // the default

    //button init
    
     bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_INPT);
     bcm2835_gpio_fsel(RELAY_PIN, BCM2835_GPIO_FSEL_OUTP);

	
    
 //-------end start------------------------------

  // for test OK
  #if 0
    uint8_t ret,addr=0x6,value=23; 
    ccSetReg(addr,value);
    printf("Write value %d  to %#x address\n",value,addr);
    ret=ccGetReg(addr);
    printf("Read value %d from address %#x\n",ret,addr);
 #endif
    //-----------------------------------
  // cc2500 init
   ccInit();
   ccSIDLE();
   r=ccFSM();
   printf("11 enter cc2500 state machine,%d\n",r);
   ccSFRX();  // flush rx buffer
   ccSRX();  //enter rx mode
  

    //--- Main Loop
 while (1) {

#define MYID    29
#define SID MYID
#define TID 6
        //---
        r=ccFSM(); // cc2500 state machine
	//printf("enter cc2500 state machine,%d\n",r);
	usleep(10000);
        switch(r){
            case 17: 
	    case 22:   //rx error
             ccSFTX();   ccSFRX(); 
	     ccSIDLE(); //enter IDEL mode
	     ccSRX(); // enter RX mode
                break;
            case 1:
                if(_cctxF==1){ _cctxF=0; ccSRX(); break; }
		
		
                if( ccGetPkg(rx)==0){
		 // printf("%#x %#x %#x %#x %#x %#x %#x \n",rx[0],rx[1],rx[2],rx[3],rx[4],rx[5],rx[6]);
		  memcpy(&rx_pkt,rx,rx[0]+1);
		
		   printf("ID=%d, vr=%d \n",rx_pkt.TargetID,rx_pkt.data);
		  
		   if (rx_pkt.TargetID==28 ) //control relay 
		   {
		       if (rx_pkt.data>512 && ss_relay==0) {
		          //relay on
		       bcm2835_gpio_write(RELAY_PIN, HIGH);
		       ss_relay=1;
		       } else if (rx_pkt.data<=512 && ss_relay==1) {
		           //relay off
		       bcm2835_gpio_write(RELAY_PIN,LOW);
		       ss_relay=0;
		       }
		   }
    
                }
                ccSRX();
                break;
        }
     // send packet w
        value= bcm2835_gpio_lev(PIN);
	//printf("read from pin 15: %d\n", value);
	if ( value==0) {   //pressed
	  printf("Send packet %d\n", value);
	  pkt.len=6; //LEN
	  pkt.TargetID=6; //Target ID ServerID
	  pkt.SourceID=MYID; //Source ID
	  pkt.GroupID=7; //Group ID
	  pkt.type=1; // type, fixed
	  pkt.data=++count;
	  
	   memcpy(tx,&pkt,sizeof(PACKET));
	   ccSendPkg(tx);                     
	  
	 }


    }//while

 
  // -----end----
    bcm2835_spi_end();
    bcm2835_close();
 
 return 0;
}//main
