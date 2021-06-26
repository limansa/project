#include<stdio.h>
#include<stdlib.h>
#include"lib_lcd1602.h"

/*
*    lcm [message at line 1] [optional: message at line 2]
*/


int main(int argc,char *argv[]){

	uint8_t i ;
    bcm2835_init();
	lcd_init();


    if(argc == 1){
	    uint8_t selfCh[][8] ={{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1f},
	                          {0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0x1f},
	                          {0x00,0x00,0x00,0x00,0x00,0x1f,0x1f,0x1f},
	                          {0x00,0x00,0x00,0x00,0x1f,0x1f,0x1f,0x1f},
	                          {0x00,0x00,0x00,0x1f,0x1f,0x1f,0x1f,0x1f},
	                          {0x00,0x00,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f},
	                          {0x00,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f}};
	    // setup self building char
	    lcd_build_self_char(0, selfCh[0]);
	    lcd_build_self_char(1, selfCh[1]);
	    lcd_build_self_char(2, selfCh[2]);
	    lcd_build_self_char(3, selfCh[3]);
	    lcd_build_self_char(4, selfCh[4]);
	    lcd_build_self_char(5, selfCh[5]);
	    lcd_build_self_char(6, selfCh[6]);

	    lcd_putStr_at(0,0,"   ITTraining ");
	    lcd_putStr_at(1,0,"LCM-TEST-");
        lcd_putc('A');
	    for(i = 0 ;i<7 ;i++ )
	    	lcd_putc(i);
        printf("lcm [message at line 1] [optional: message at line 2]\n");
    }
    if(argc == 2){
        lcd_putStr_at(0,0,argv[1]);
    }
    if(argc >= 3){
        lcd_putStr_at(0,0,argv[1]);
        lcd_putStr_at(1,0,argv[2]);
    }

	return 0;
}

