/* A common header file to describe the shared memory we wish to pass about. */

#define ID_SZ 10
#define WAITID 0
#define READY  1
#define DONE   5

typedef struct {
    char status;
    char data[ID_SZ+1];
}CardReader;
