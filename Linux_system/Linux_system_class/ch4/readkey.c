#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <termios.h>
#include <signal.h>


#define POLLTIME 100000  // us
#define KEYPAD_DEVICE "/dev/input/event1"
char get_keycode(int fd);
void handle_keyevent(char key);
int execute_cmd(void *arg);
typedef int (*EV_Handler) (void * arg);
typedef struct {

  char keycode;
  EV_Handler handler;
 }KEY_ACTION_MAP;

#define KEY1  115 
#define KEY2  105
#define KEY3  106
#define KEY4  229
#define KEY5  114
#define KEY6  158
#define KEY7  28
#define KEY8  107
#define KEYNUM 8

KEY_ACTION_MAP key_action[KEYNUM]={
  {KEY1,NULL},
  {KEY2,NULL},
  {KEY3,NULL},
  {KEY4,NULL},
  {KEY5,NULL},
  {KEY6,NULL},
  {KEY7,NULL},
  {KEY8,execute_cmd},
};




int main(int argc, char *argv[]) {
  fd_set rfds;
 
  struct timeval tv;
  int retval;
  char *device = KEYPAD_DEVICE; //default
 
  int fd_key;
  char name[256] = "Unknown";
   
  if (argc > 1)
    device = argv[1];
 
   if ((getuid ()) != 0)
    printf ("You are not root! This may not work...\n");
 
   
  //Open Device
  if ((fd_key = open (device, O_RDONLY)) == -1)
    printf ("%s is not a vaild device\n", device);
 
  //Print Device Name
  ioctl (fd_key, EVIOCGNAME (sizeof (name)), name);
  printf ("Reading From : %s (%s)\n", device, name);
    

  while (1) {

    /* Watch stdin (fd 0) to see when it has input. */
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    FD_SET(fd_key, &rfds);
   
    /* Wait up to five seconds. */
    tv.tv_sec = 0;
    tv.tv_usec = POLLTIME;
  
   retval = select(fd_key+1, &rfds, NULL, NULL, &tv);
    /* Don't rely on the value of tv now! */
    if (retval == -1)
        perror("select()");
    else if (retval) {
      // handle keypad event
        if (FD_ISSET(fd_key, &rfds)) {
               char key=get_keycode(fd_key);
                printf ("key Code=%d\n", key);
                handle_keyevent(key);

      //    } else if (FD_ISSET(mice_fd, &rfds)) {
      //       do_event();
      //     }
          
            
	}
	

    } else {

        // select timeout
       

   }

   }

   close(fd_key);

    return 0;
}

char get_keycode(int fd)
{

   struct input_event ev;
  int rd, value, size = sizeof (struct input_event);
 
   if ((rd = read (fd, &ev, size)) < size)
         perror ("read from key:");      

    if (ev.type == 1 && ev.value==1) //value=> 1: key pressed, 0: release key : 2: key presseed continuously....
	   // printf ("Code=%d,value=%d\n", ev.code,ev.value);
      return ev.code;  
    else 
      return 0;
}

void handle_keyevent(char key)
{

 
   //handle key
  int i;
  for(i=0;i<KEYNUM;i++)  
   if (key==key_action[i].keycode && key_action[i].handler!=NULL) {
     printf ("key Code=%d\n", key); 
     key_action[i].handler(NULL);
   }

 }


int execute_cmd(void *arg)
{
  printf("%s\n",__func__);

}









