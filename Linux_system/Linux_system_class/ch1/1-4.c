#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdlib.h>
#include <linux/cdrom.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#define CDDEVICE "/dev/cdrom"           /* CDROM device */


int main(int argc,char **argv)
{
   int cdrom;                 /* CDROM device file descriptor */

   /* Open the CDROM device. The linux/cdrom.h header file specifies that
   ** it must be given the O_NONBLOCK flag when opening. My tests showed
   ** that if this isn't done, this program will not work. 
   */
   if ((cdrom = open(CDDEVICE,O_RDONLY | O_NONBLOCK)) < 0) {
        perror("open");
        exit(1);
   }

   /* Use ioctl to send the CDROMEJECT command to the device
   */
   if (ioctl(cdrom,CDROMEJECT,0)<0) {
        perror("ioctl");
        exit(1);
   }

   close(cdrom);
   return 0;
}
