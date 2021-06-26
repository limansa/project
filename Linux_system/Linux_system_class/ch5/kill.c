#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>

int sendsig( int );
volatile int sigcount=0;

void catcher( int sig ) {
    sigcount++;
}

int main( int argc, char *argv[] ) {

    struct sigaction sigact;
    int result;

    /* set up a signal catching function to handle the signals */
    /* that will be sent from the sendsig() function */

    sigemptyset( &sigact.sa_mask );
    sigact.sa_flags = 0;
    sigact.sa_handler = catcher;
    sigaction( SIGUSR1, &sigact, NULL );

    /* Call the sendsig() function that will call the kill() */
    /* function for SIGUSR1 n times based on the input value */

    result = sendsig( 21 );

    printf( "Back in main\n" );
    printf( "The kill() function was called %d times\n", result );
    printf( "The signal catching function was called %d times\n", \
             sigcount );

    return( 0 );
}

int sendsig( int count ) {

    int i;
    int j=0;

    for( i=0; i < count; i++ ) {
        if( i == ((i/10)*10) ) {
            j++;
            kill( getpid(), SIGUSR1 );
        }
    }
    return( j );
}
