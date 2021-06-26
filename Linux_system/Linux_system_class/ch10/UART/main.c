
#include <sys/ioctl.h>
#include <sys/param.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/types.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include "uart.h"
#include "debug.h"

#define LOG_CATEGORY "ittrainng.uart"
#define NFC_PRIORITY_TRACE
#include "uart.h"
 int main()

{

  serial_port sp;

	log_put (LOG_CATEGORY, NFC_PRIORITY_TRACE, "Attempt to connect to: %s at %d bauds.", pndd->acPort, pndd->uiSpeed);
	 sp = uart_open (pndd->acPort);

		if (sp == INVALID_SERIAL_PORT)
	    log_put (LOG_CATEGORY, NFC_PRIORITY_ERROR, "Invalid serial port: %s", pndd->acPort);
		  if (sp == CLAIMED_SERIAL_PORT)
	    log_put (LOG_CATEGORY, NFC_PRIORITY_ERROR, "Serial port already claimed: %s", pndd->acPort);
		  if ((sp == CLAIMED_SERIAL_PORT) || (sp == INVALID_SERIAL_PORT))
	    return NULL;

		  // We need to flush input to be sure first reply does not comes from older byte transceive
      uart_flush_input (sp); 
	  uart_set_speed (sp, pndd->uiSpeed);
   return 0;
}
