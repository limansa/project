/* vi: set sw=4 ts=4: */
/*
 * Mini ping implementation for busybox
 *
 * Copyright (C) 1999 by Randolph Chung <tausq@debian.org>
 *
 * Adapted from the ping in netkit-base 0.10:
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Mike Muuss.
 *
 * Licensed under GPLv2 or later, see file LICENSE in this tarball for details.
 */
/* from ping6.c:
 * Copyright (C) 1999 by Randolph Chung <tausq@debian.org>
 *
 * This version of ping is adapted from the ping in netkit-base 0.10,
 * which is:
 *
 * Original copyright notice is retained at the end of this file.
 *
 * This version is an adaptation of ping.c from busybox.
 * The code was modified by Bart Visscher <magick@linux-fan.com>
 */

#include <net/if.h>
#include <netinet/ip_icmp.h>
//#include "libbb.h"
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
typedef struct len_and_sockaddr {
	    socklen_t len;
		
			struct sockaddr sa;
			 struct sockaddr_in sin;
	
} len_and_sockaddr;

enum {
	DEFDATALEN = 56,
	MAXIPLEN = 60,
	MAXICMPLEN = 76,
	MAXPACKET = 65468,
	MAX_DUP_CHK = (8 * 128),
	MAXWAIT = 10,
	PINGINTERVAL = 1, /* 1 second */
};

/* common routines */

static int in_cksum(unsigned short *buf, int sz)
{
	int nleft = sz;
	int sum = 0;
	unsigned short *w = buf;
	unsigned short ans = 0;

	while (nleft > 1) {
		sum += *w++;
		nleft -= 2;
	}

	if (nleft == 1) {
		*(unsigned char *) (&ans) = *(unsigned char *) w;
		sum += ans;
	}

	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	ans = ~sum;
	return ans;
}



/* simple version */

static char *hostname;

static void noresp(int ign)
{
	printf("No response from %s\n", hostname);
	exit(1);

}

static void ping4(len_and_sockaddr *lsa)
{
	struct sockaddr_in pingaddr;
	struct icmp *pkt;
	int pingsock, c;
	char packet[DEFDATALEN + MAXIPLEN + MAXICMPLEN];

	pingsock = create_icmp_socket();
	pingaddr = lsa->sin;

	pkt = (struct icmp *) packet;
	memset(pkt, 0, sizeof(packet));
	pkt->icmp_type = ICMP_ECHO;
	pkt->icmp_cksum = in_cksum((unsigned short *) pkt, sizeof(packet));

	c = xsendto(pingsock, packet, DEFDATALEN + ICMP_MINLEN,
			   (struct sockaddr *) &pingaddr, sizeof(pingaddr));

	/* listen for replies */
	while (1) {
		struct sockaddr_in from;
		socklen_t fromlen = sizeof(from);

		c = recvfrom(pingsock, packet, sizeof(packet), 0,
				(struct sockaddr *) &from, &fromlen);
		if (c < 0) {
			if (errno != EINTR)
				bb_perror_msg("recvfrom");
			continue;
		}
		if (c >= 76) {			/* ip + icmp */
			struct iphdr *iphdr = (struct iphdr *) packet;

			pkt = (struct icmp *) (packet + (iphdr->ihl << 2));	/* skip ip hdr */
			if (pkt->icmp_type == ICMP_ECHOREPLY)
				break;
		}
	}
	
}



int ping_main(int argc, char **argv);
int ping_main(int argc, char **argv)
{
	len_and_sockaddr *lsa;

	argv++;


	hostname = *argv;
	if (!hostname)
		bb_show_usage();


	lsa = xhost_and_af2sockaddr(hostname, 0, AF_INET);

	/* Set timer _after_ DNS resolution */
	signal(SIGALRM, noresp);
	alarm(5); /* give the host 5000ms to respond */

		ping4(lsa);
	printf("%s is alive!\n", hostname);
	return 0;
}


