/*
 * This file was generated using rpcgen.
 * 
 * This file has been edited, SAVE IT before running rpcgen so that it does not get overwritten.
 */

#include "communicate.h"
#include "communicate_server.h"

#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <errno.h>
#include <netdb.h>
#include <pthread.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static bool_t *
_ping_1 (void  *argp, struct svc_req *rqstp)
{
	return (ping_1_svc(rqstp));
}

static Page_t *
_read_1 (int  *argp, struct svc_req *rqstp)
{
	return (read_1_svc(*argp, rqstp));
}

static char **
_get_mode_1 (void  *argp, struct svc_req *rqstp)
{
	return (get_mode_1_svc(rqstp));
}

static bool_t *
_fetch_articles_1 (Written_seqnums_t  *argp, struct svc_req *rqstp)
{
	return (fetch_articles_1_svc(*argp, rqstp));
}

static int *
_write_1 (write_1_argument *argp, struct svc_req *rqstp)
{
	return (write_1_svc(argp->Article, argp->Nr, argp->Nw, rqstp));
}

static int *
_get_seqnum_1 (void  *argp, struct svc_req *rqstp)
{
	return (get_seqnum_1_svc(rqstp));
}

static bool_t *
_server_write_1 (Article_t  *argp, struct svc_req *rqstp)
{
	return (server_write_1_svc(*argp, rqstp));
}

static int *
_highest_seqnum_1 (void  *argp, struct svc_req *rqstp)
{
	return (highest_seqnum_1_svc(rqstp));
}

static Article_t *
_choose_1 (int  *argp, struct svc_req *rqstp)
{
	return (choose_1_svc(*argp, rqstp));
}

static void
communicate_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		int read_1_arg;
		Written_seqnums_t fetch_articles_1_arg;
		write_1_argument write_1_arg;
		Article_t server_write_1_arg;
		int choose_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case Ping:
		_xdr_argument = (xdrproc_t) xdr_void;
		_xdr_result = (xdrproc_t) xdr_bool;
		local = (char *(*)(char *, struct svc_req *)) _ping_1;
		break;

	case Read:
		_xdr_argument = (xdrproc_t) xdr_int;
		_xdr_result = (xdrproc_t) xdr_Page_t;
		local = (char *(*)(char *, struct svc_req *)) _read_1;
		break;

	case Get_mode:
		_xdr_argument = (xdrproc_t) xdr_void;
		_xdr_result = (xdrproc_t) xdr_wrapstring;
		local = (char *(*)(char *, struct svc_req *)) _get_mode_1;
		break;

	case Fetch_articles:
		_xdr_argument = (xdrproc_t) xdr_Written_seqnums_t;
		_xdr_result = (xdrproc_t) xdr_bool;
		local = (char *(*)(char *, struct svc_req *)) _fetch_articles_1;
		break;

	case Write:
		_xdr_argument = (xdrproc_t) xdr_write_1_argument;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) _write_1;
		break;

	case Get_seqnum:
		_xdr_argument = (xdrproc_t) xdr_void;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) _get_seqnum_1;
		break;

	case Server_write:
		_xdr_argument = (xdrproc_t) xdr_Article_t;
		_xdr_result = (xdrproc_t) xdr_bool;
		local = (char *(*)(char *, struct svc_req *)) _server_write_1;
		break;

	case Highest_seqnum:
		_xdr_argument = (xdrproc_t) xdr_void;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) _highest_seqnum_1;
		break;

	case Choose:
		_xdr_argument = (xdrproc_t) xdr_int;
		_xdr_result = (xdrproc_t) xdr_Article_t;
		local = (char *(*)(char *, struct svc_req *)) _choose_1;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
main (int argc, char **argv)
{
	// get server information as cmd args

	if (argc < 4) {
		printf ("usage: %s server_ip server_port mode\nmode is one of primary-backup, quorum, or local-write\n", argv[0]);
		exit (1);
	}
	
	char *server_ip = argv[1];

	char *server_port_str = argv[2];
	int server_port_int = atoi(server_port_str);

	char *mode = argv[3];

	initialize(server_ip, server_port_int, mode);
	

	register SVCXPRT *transp;

	pmap_unset (COMMUNICATE, COMMUNICATE_VERSION);

	//setup rpc server on given port:

    // create the socket
	int sockfd;
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }


	// fill in server information

	struct sockaddr_in servaddr;   
    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(server_port_int);
       
    // Bind the socket on the given port
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) {
		close(sockfd);
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

	//pass the socket for use with automatically generated rpc code, which firstly will create an application lvl transport buffer
	transp = svcudp_create(sockfd);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}

	if (!svc_register(transp, COMMUNICATE, COMMUNICATE_VERSION, communicate_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (COMMUNICATE, COMMUNICATE_VERSION, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, COMMUNICATE, COMMUNICATE_VERSION, communicate_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (COMMUNICATE, COMMUNICATE_VERSION, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
