#include <bcm2835.h>
#include <stdio.h>
#include "I2C_Profile.h"
#include "Gsensor.h"
#include "gpio_ini.h"
#define MQTT_PUB 0

unsigned char gsensor_value[6];
extern LIS3DHSample sample;
void mqtt_pub();
int main(int argc, char **argv) //int argc, char **argv
{
    	// If you call this, it will not actually access the GPIO
    	// Use for testing
//    	bcm2835_set_debug(1);
	    int i;
		
    	if (!bcm2835_init())
		  return 1; 
     
    	LIS3DH_Init();
    	gpio_init();

    
    
    	if (!bcm2835_init())
		return 1;

    	LED1_OFF;LED2_OFF;LED3_OFF;LED4_OFF;LED5_OFF;
    	bcm2835_gpio_write(COM, HIGH);
    	// Blink
    	while (1) {	

      		bcm2835_delay(200);
      		Read_Sensor_Data();
				
			printf("{\"x\":%d,\"y\":%d,\"z\":%d}\n",sample.x,sample.y,sample.z);

            if( sample.x>0) {
             LED3_OFF; LED2_ON; 
            } else {
            LED3_ON;  LED2_OFF;     
		    }
           
		    if( sample.y>0) {
             LED4_ON;  LED5_OFF;
            } else {
             LED4_OFF; LED5_ON;     
		    }
           
		
           if( sample.z>0)
            LED1_ON; 
            else
            LED1_OFF;
		
		
			   
	        #if MQTT_PUB==1
	           mqtt_pub();
	  
		    #endif
		
    	}

    	bcm2835_close();
	return 0;
}


void mqtt_pub()
{

	char msg[128];
	char cmd[128];
	char *MQTT_BROKER="220.132.124.155";
	char *topic="sensor/gsensor";
	//mosquitto_pub -h 220.132.124.155 -t sensor/gsensor -m "{\"x\":-1280,\"y\":-1792,\"z\":15102}"
	sprintf(msg,"{\\\"x\\\":%d,\\\"y\\\":%d,\\\"z\\\":%d}",sample.x,sample.y,sample.z);
	sprintf(cmd,"mosquitto_pub -h %s -t %s -m %s",MQTT_BROKER,topic,msg);
	system(cmd);

}

