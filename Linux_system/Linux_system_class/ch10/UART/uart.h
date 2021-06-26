/*-
 * Public platform independent Near Field Communication (NFC) library
 *
 * Copyright (C) 2009, Roel Verdult, Romuald Conty
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
 * @file uart.h
 * @brief UART driver header
 */

#ifndef __NFC_BUS_UART_H__
#  define __NFC_BUS_UART_H__

#  include <sys/time.h>

#  include <stdio.h>
#  include <string.h>
#  include <stdlib.h>


//#  include <nfc/nfc-types.h>
#  include "nfc-types.h"

// Define shortcut to types to make code more readable
typedef void *serial_port;
#  define INVALID_SERIAL_PORT (void*)(~1)
#  define CLAIMED_SERIAL_PORT (void*)(~2)

#define ECOMIO (-1)
#define ECOMTIMEOUT (-2)
#define EOPABORT (-3)
#define EBUFOVERFOLLOW (-4)

serial_port uart_open ( const char *pcPortName );
void    uart_close ( const serial_port sp );
void    uart_flush_input ( const serial_port sp );

void    uart_set_speed ( serial_port sp, const uint32_t uiPortSpeed );
uint32_t uart_get_speed ( const serial_port sp );

int     uart_receive ( serial_port sp, byte_t *pbtRx, const size_t szRx, void *abort_p, struct timeval *timeout );
int     uart_receive_non_fix_size ( serial_port sp, byte_t *pbtRx, const size_t szRx, void *abort_p, struct timeval *timeout, int isDial );
int     uart_send ( serial_port sp, const byte_t *pbtTx, const size_t szTx, struct timeval *timeout );

char  **uart_list_ports ( void );

int     check_msg_eof( const byte_t *pbtTx, const size_t szReceived );
#endif // __NFC_BUS_UART_H__
