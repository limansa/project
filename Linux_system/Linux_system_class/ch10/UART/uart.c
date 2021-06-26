/*-
 * Public platform independent Near Field Communication (NFC) library
 *
 * Copyright (C) 2009, 2010, Roel Verdult, Romuald Conty
 * Copyright (C) 2010, Roel Verdult, Romuald Conty
 * Copyright (C) 2011, Romuald Conty, Romain Tartière
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *
 */

/**
 * @file uart_posix.c
 * @brief POSIX UART driver
 */

/* vim: set ts=2 sw=2 et: */

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

char *serial_ports_device_radix[] = { "ttyUSB", "ttySAC", NULL };

// Work-around to claim uart interface using the c_iflag (software input processing) from the termios struct
#define CCLAIMED 0x80000000

typedef struct
{
    int           fd;             // Serial port file descriptor
    struct termios    termios_backup;     // Terminal info before using the port
    struct termios    termios_new;        // Terminal info during the transaction
} serial_port_unix;

void uart_close_ext ( const serial_port sp, const bool restore_termios );

serial_port
uart_open ( const char *pcPortName )
{
    serial_port_unix *sp = malloc ( sizeof ( serial_port_unix ) );

    if ( sp == 0 )
    {
        return INVALID_SERIAL_PORT;
    }

    sp->fd = open ( pcPortName, O_RDWR | O_NOCTTY | O_NONBLOCK );

    if ( sp->fd == -1 )
    {
        uart_close_ext ( sp, false );
        return INVALID_SERIAL_PORT;
    }

    if ( tcgetattr ( sp->fd, &sp->termios_backup ) == -1 )
    {
        uart_close_ext ( sp, false );
        return INVALID_SERIAL_PORT;
    }

    // Make sure the port is not claimed already
    if ( sp->termios_backup.c_iflag & CCLAIMED )
    {
        uart_close_ext ( sp, false );
        return CLAIMED_SERIAL_PORT;
    }

    // Copy the old terminal info struct
    sp->termios_new = sp->termios_backup;

    sp->termios_new.c_cflag = CS8 | CLOCAL | CREAD;
    sp->termios_new.c_iflag = CCLAIMED | IGNPAR;
    sp->termios_new.c_oflag = 0;
    sp->termios_new.c_lflag = 0;

    sp->termios_new.c_cc[VMIN] = 0;     // block until n bytes are received
    sp->termios_new.c_cc[VTIME] = 0;    // block until a timer expires (n * 100 mSec.)

    if ( tcsetattr ( sp->fd, TCSANOW, &sp->termios_new ) == -1 )
    {
        uart_close_ext ( sp, true );
        return INVALID_SERIAL_PORT;
    }

    return sp;
}

void
uart_flush_input ( serial_port sp )
{
    // This line seems to produce absolutely no effect on my system (GNU/Linux 2.6.35)
    tcflush ( ( ( serial_port_unix * ) sp )->fd, TCIFLUSH );
    // So, I wrote this byte-eater
    // Retrieve the count of the incoming bytes
    int available_bytes_count = 0;
    int res;
    res = ioctl ( ( ( serial_port_unix * ) sp )->fd, FIONREAD, &available_bytes_count );

    if ( res != 0 )
    {
        return;
    }

    if ( available_bytes_count == 0 )
    {
        return;
    }

    char *rx = malloc ( available_bytes_count );
    // There is something available, read the data
    res = read ( ( ( serial_port_unix * ) sp )->fd, rx, available_bytes_count );
    log_put ( LOG_CATEGORY, NFC_PRIORITY_TRACE, "%d bytes have eatten.", available_bytes_count );
    free ( rx );
}

void
uart_set_speed ( serial_port sp, const uint32_t uiPortSpeed )
{
    log_put ( LOG_CATEGORY, NFC_PRIORITY_TRACE, "Serial port speed requested to be set to %d bauds.", uiPortSpeed );
    serial_port_unix *spu = ( serial_port_unix * ) sp;

    // Portability note: on some systems, B9600 != 9600 so we have to do
    // uint32_t <=> speed_t associations by hand.
    speed_t stPortSpeed = B9600;

    switch ( uiPortSpeed )
    {
        case 9600:
            stPortSpeed = B9600;
            break;

        case 19200:
            stPortSpeed = B19200;
            break;

        case 38400:
            stPortSpeed = B38400;
            break;
#ifdef B57600

        case 57600:
            stPortSpeed = B57600;
            break;
#endif
#ifdef B115200

        case 115200:
            stPortSpeed = B115200;
            break;
#endif
#ifdef B230400

        case 230400:
            stPortSpeed = B230400;
            break;
#endif
#ifdef B460800

        case 460800:
            stPortSpeed = B460800;
            break;
#endif

        default:
            log_put ( LOG_CATEGORY, NFC_PRIORITY_ERROR, "Unable to set serial port speed to %d bauds. Speed value must be one of those defined in termios(3).",
                      uiPortSpeed );
            return;
    };

    // Set port speed (Input and Output)
    cfsetispeed ( &( spu->termios_new ), stPortSpeed );

    cfsetospeed ( &( spu->termios_new ), stPortSpeed );

    if ( tcsetattr ( spu->fd, TCSADRAIN, &( spu->termios_new ) ) == -1 )
    {
        log_put ( LOG_CATEGORY, NFC_PRIORITY_ERROR, "%s", "Unable to apply new speed settings." );
    }
}

uint32_t
uart_get_speed ( serial_port sp )
{
    uint32_t uiPortSpeed = 0;
    const serial_port_unix *spu = ( serial_port_unix * ) sp;

    switch ( cfgetispeed ( &spu->termios_new ) )
    {
        case B9600:
            uiPortSpeed = 9600;
            break;

        case B19200:
            uiPortSpeed = 19200;
            break;

        case B38400:
            uiPortSpeed = 38400;
            break;
#ifdef B57600

        case B57600:
            uiPortSpeed = 57600;
            break;
#endif
#ifdef B115200

        case B115200:
            uiPortSpeed = 115200;
            break;
#endif
#ifdef B230400

        case B230400:
            uiPortSpeed = 230400;
            break;
#endif
#ifdef B460800

        case B460800:
            uiPortSpeed = 460800;
            break;
#endif
    }

    return uiPortSpeed;
}

void
uart_close_ext ( const serial_port sp, const bool restore_termios )
{
    if ( ( ( serial_port_unix * ) sp )->fd >= 0 )
    {
        if ( restore_termios )
        {
            tcsetattr ( ( ( serial_port_unix * ) sp )->fd, TCSANOW, &( ( serial_port_unix * ) sp )->termios_backup );
        }

        close ( ( ( serial_port_unix * ) sp )->fd );
    }

    free ( sp );
}

void
uart_close ( const serial_port sp )
{
    uart_close_ext ( sp, true );
}

/**
 * @brief Receive data from UART and copy data to \a pbtRx
 *
 * @return 0 on success, otherwise driver error code
 */
int
uart_receive ( serial_port sp, byte_t *pbtRx, const size_t szRx, void *abort_p, struct timeval *timeout )
{
    int iAbortFd = abort_p ? *( ( int * )abort_p ) : 0;
    int received_bytes_count = 0;
    int available_bytes_count = 0;
    const int expected_bytes_count = ( int )szRx;
    int res;
    fd_set rfds;
    int i;

    do
    {
    select:
        // Reset file descriptor
        FD_ZERO ( &rfds );
        FD_SET ( ( ( serial_port_unix * ) sp )->fd, &rfds );

        if ( iAbortFd )
        {
            FD_SET ( iAbortFd, &rfds );
        }

        /*
         * Some implementations (e.g. Linux) of select(2) will update *timeout.
         * Make a copy so that it will be updated on these systems,
         */
        struct timeval fixed_timeout;

        if ( timeout )
        {
            fixed_timeout = *timeout;
            timeout = &fixed_timeout;
        }

        res = select ( MAX( ( ( serial_port_unix * ) sp )->fd, iAbortFd ) + 1, &rfds, NULL, NULL, timeout );

        if ( ( res < 0 ) && ( EINTR == errno ) )
        {
            // The system call was interupted by a signal and a signal handler was
            // run.  Restart the interupted system call.
            goto select;
        }

        // Read error
        if ( res < 0 )
        {
            log_put ( LOG_CATEGORY, NFC_PRIORITY_TRACE, "%s", "RX error." );
            return ECOMIO;
        }

        // Read time-out
        if ( res == 0 )
        {
            log_put ( LOG_CATEGORY, NFC_PRIORITY_TRACE, "Timeout!" );
            return ECOMTIMEOUT;
        }

        if ( FD_ISSET ( iAbortFd, &rfds ) )
        {
            // Abort requested
            log_put ( LOG_CATEGORY, NFC_PRIORITY_TRACE, "Abort!" );
            close ( iAbortFd );
            return EOPABORT;
        }

        // Retrieve the count of the incoming bytes
        res = ioctl ( ( ( serial_port_unix * ) sp )->fd, FIONREAD, &available_bytes_count );

        if ( res != 0 )
        {
            return ECOMIO;
        }

        // There is something available, read the data
        res = read ( ( ( serial_port_unix * ) sp )->fd, pbtRx + received_bytes_count, MIN( available_bytes_count, ( expected_bytes_count - received_bytes_count ) ) );

        // Stop if the OS has some troubles reading the data
        if ( res <= 0 )
        {
            return ECOMIO;
        }

        received_bytes_count += res;

    }
    while ( expected_bytes_count > received_bytes_count );

    //LOG_HEX ( "RX", pbtRx, szRx );
    return 0;
}

/**
 * @brief Receive data from UART and copy data to \a pbtRx
 *
 * @return 0 on success, otherwise driver error code
 */
int
uart_receive_non_fix_size ( serial_port sp, byte_t *pbtRx, const size_t szRx, void *abort_p, struct timeval *timeout, int isDial )
{
    int iAbortFd = abort_p ? *( ( int * )abort_p ) : 0;
    int received_bytes_count = 0;
    int available_bytes_count = 0;
    const int expected_bytes_count = ( int )szRx;
    int res;
    fd_set rfds;
    int i, j = 0, AT_retrun_msg_eof = 0;
    byte_t *tmp, p;

    do
    {
    select:
        // Reset file descriptor
        FD_ZERO ( &rfds );
        FD_SET ( ( ( serial_port_unix * ) sp )->fd, &rfds );

        if ( iAbortFd )
        {
            FD_SET ( iAbortFd, &rfds );
        }

        /*
         * Some implementations (e.g. Linux) of select(2) will update *timeout.
         * Make a copy so that it will be updated on these systems,
         */
        struct timeval fixed_timeout;

        if ( timeout )
        {
            fixed_timeout = *timeout;
            timeout = &fixed_timeout;
        }

        res = select ( MAX( ( ( serial_port_unix * ) sp )->fd, iAbortFd ) + 1, &rfds, NULL, NULL, timeout );

        if ( ( res < 0 ) && ( EINTR == errno ) )
        {
            // The system call was interupted by a signal and a signal handler was
            // run.  Restart the interupted system call.
            goto select;
        }

        // Read error
        if ( res < 0 )
        {
            log_put ( LOG_CATEGORY, NFC_PRIORITY_TRACE, "%s", "RX error." );
            return ECOMIO;
        }

        // Read time-out
        if ( res == 0 )
        {
            if ( !isDial )
            {
                //log_put ( LOG_CATEGORY, NFC_PRIORITY_TRACE, "Timeout!" );
                log_put ( LOG_CATEGORY, NFC_PRIORITY_TRACE, "Wait!" );
            }

            return ECOMTIMEOUT;
        }

        if ( FD_ISSET ( iAbortFd, &rfds ) )
        {
            // Abort requested
            log_put ( LOG_CATEGORY, NFC_PRIORITY_TRACE, "Abort!" );
            close ( iAbortFd );
            return EOPABORT;
        }

        // Retrieve the count of the incoming bytes
        res = ioctl ( ( ( serial_port_unix * ) sp )->fd, FIONREAD, &available_bytes_count );

        if ( res != 0 )
        {
            return ECOMIO;
        }

        if ( ( received_bytes_count + available_bytes_count ) >  expected_bytes_count )
        {
            return EBUFOVERFOLLOW;
        }

        // There is something available, read the data
        res = read ( ( ( serial_port_unix * ) sp )->fd, pbtRx + received_bytes_count, available_bytes_count );

        // Stop if the OS has some troubles reading the data
        if ( res <= 0 )
        {
            return ECOMIO;
        }

        /*
                else

                {
                    printf("j=%d, ",j++);
                    for (i=0;i<res;i++)
                    {
                        printf("%02X ",*(pbtRx+received_bytes_count+i));
                    }
                }
        */

        received_bytes_count += res;

        /*if (check_msg_eof(pbtRx, received_bytes_count))
        {
             AT_retrun_msg_eof =1;
        }*/

        //if ( !strncmp(pbtRx+received_bytes_count-4, "OK\r\n", 4)  || !strncmp(pbtRx+received_bytes_count-7, "ERROR\r\n", 7) )
        if ( strstr( pbtRx, "OK" )          || strstr( pbtRx, "ERROR" )     ||
             strstr( pbtRx, "NO CARRIER" )  || strstr( pbtRx, "CONNECT" )   ||
             strstr( pbtRx, "Call Ready" )  || strstr( pbtRx, "POWER DOWN" )  ||
             strstr( pbtRx, "RING" ) )
        {
            //printf("OK eof:%s ",pbtRx+received_bytes_count-4);
            //printf("ERROR eof:%s ",pbtRx+received_bytes_count-7);
            //log_put ( LOG_CATEGORY, NFC_PRIORITY_TRACE, "pbtRx:{%s}\n",pbtRx);
            AT_retrun_msg_eof = 1;
        }
    }

    //while ( expected_bytes_count > received_bytes_count );
    while ( !AT_retrun_msg_eof );

    //LOG_HEX ( "RX", pbtRx, szRx );
    return 0;
}

/**
 * @brief Send \a pbtTx content to UART
 *
 * @return 0 on success, otherwise a driver error is returned
 */
int
uart_send ( serial_port sp, const byte_t *pbtTx, const size_t szTx, struct timeval *timeout )
{
    ( void ) timeout;
    //LOG_HEX ( "TX", pbtTx, szTx );

    if ( ( int ) szTx == write ( ( ( serial_port_unix * ) sp )->fd, pbtTx, szTx ) )
    {
        return 0;
    }
    else
    {
        return ECOMIO;
    }
}

int
uart_send_new ( serial_port sp, const byte_t *pbtTx, const size_t szTx, struct timeval *timeout )
{
    ( void ) timeout;
    int res, i;
    int transmitted_bytes_count = 0;

    while ( transmitted_bytes_count < szTx )
    {
        if ( ( res = write ( ( ( serial_port_unix * ) sp )->fd, pbtTx + transmitted_bytes_count, szTx - transmitted_bytes_count ) ) < 0 )
        {
            switch ( errno )
            {
                case EAGAIN:
                    //log_put ( LOG_CATEGORY, NFC_PRIORITY_TRACE, "* EAGAIN *\n" );
                    res = 0;
                    break;

                case EINTR:
                    //log_put ( LOG_CATEGORY, NFC_PRIORITY_TRACE, "* EINTR *\n" );
                    res = 0;
                    break;

                default:
                    perror( "serial write error" );
                    return ECOMIO;
            }
        }

        if ( res )
        {
            log_put ( LOG_CATEGORY, NFC_PRIORITY_TRACE, "%02d uart_write %.5d bytes\n" , i++, res );
        }

        transmitted_bytes_count += res;
    }

    return 0;
}

char **
uart_list_ports ( void )
{
    char **res = malloc ( sizeof ( char * ) );
    size_t szRes = 1;

    res[0] = NULL;

    DIR *pdDir = opendir( "/dev" );
    struct dirent *pdDirEnt;

    while ( ( pdDirEnt = readdir( pdDir ) ) != NULL )
    {
        if ( !isdigit ( pdDirEnt->d_name[strlen ( pdDirEnt->d_name ) - 1] ) )
        {
            continue;
        }

        char **p = serial_ports_device_radix;

        while ( *p )
        {
            if ( !strncmp( pdDirEnt->d_name, *p, strlen ( *p ) ) )
            {
                char **res2 = realloc ( res, ( szRes + 1 ) * sizeof ( char * ) );

                if ( !res2 )
                {
                    goto oom;
                }

                res = res2;

                if ( !( res[szRes - 1] = malloc ( 6 + strlen ( pdDirEnt->d_name ) ) ) )
                {
                    goto oom;
                }

                sprintf ( res[szRes - 1], "/dev/%s", pdDirEnt->d_name );

                szRes++;
                res[szRes - 1] = NULL;
            }

            p++;
        }
    }

oom:
    closedir ( pdDir );

    return res;
}

int
check_msg_eof( const byte_t *pbtTx, const size_t szReceived )
{
    int i = 0;
    char *p;

    enum MSG_STAT
    {
        NO_MATCH,
        AT_OK,
        AT_ERROR,
        AT_RING,
        AT_NO_CARRIER
    };

    typedef struct
    {
        uint8_t msg_type[16];
        uint8_t msg_stat;
    } Receive_Massage;

    Receive_Massage rmsg[] =
    {
        {"OK", AT_OK},
        {"ERROR", AT_ERROR},
        {"NO CARRIER", AT_NO_CARRIER},
        {0, 0}
    };

    while ( rmsg[i].msg_type )
    {
        p = strstr( pbtTx, rmsg[i].msg_type );

        if ( p != NULL )
        {
            return rmsg[i].msg_stat;
        }

        i++;
    }

    return NO_MATCH;
}
