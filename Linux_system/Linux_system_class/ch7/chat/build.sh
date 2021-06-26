#!/bin/sh
gcc chat_client.c helper.c -o client -lpthread
gcc chat_server.c helper.c -o server -lpthread
