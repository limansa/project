/*
 *
 */

#define MAX_DEVICES 256
#define MAX_DRIVERS 256

typedef struct {
  unsigned int tv_sec;
  unsigned int tv_nsec;
} delta_time;

typedef struct {
  long mtype;            /* Message type / priority */
  delta_time delay;        /* delay between previous event and this one */
  unsigned char msg[4];  /* up to four bytes of MIDI message */
  int msglen;            /* length of MIDI message in buffer */
  int port;              /* which MIDI port to send the message out on */
} MidiIOEvent;


