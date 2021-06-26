#!/bin/sh
gcc client.c tcputils.c utils.c -o client
gcc server.c tcputils.c utils.c -o server 
