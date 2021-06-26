
 /*i2cdetect.c - a user-space program to scan for I2C devices 
 Copyright (C) 1999-2004  Frodo Looijaard <frodol@dds.nl>, and ark D. Studebaker <mdsxyz123@yahoo.com>
    Copyright (C) 2004-2010  Jean Delvare <khali@linux-fr.org>*/
#ifndef __LIST_H
#define __LIST_H


struct list_head {
	struct list_head *next, *prev;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

#define INIT_LIST_HEAD(ptr) do { \
	(ptr)->next = (ptr); (ptr)->prev = (ptr); \
} while (0)


