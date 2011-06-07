#ifndef _ERRNO_H
#define _ERRNO_H

#include <sys/types.h>

//Change this to call a simple function
int errno;

#define EDOM		1
#define EILSEQ		2
#define ERANGE		3
#define E2BIG   	4
#define EACCES  	5
#define EADDRINUSE 	6
#define EADDRNOTAVAIL   7
#define EAFNOSUPPORT    8
#define EAGAIN          9
#define EALREADY        10
#define EBADF		11
#define EBADMSG		12
#define EBUSY		13
#define ECANCELED	14
#define ECHILD		15
#define ECONNABORTED	16
#define ECONNREFUSED	17
#define ECONNRESET	18
#define EDEADLK		19
#define EDESTADDRREQ	20
#define EDQUOT		22
#define EEXIST		23
#define EFAULT		24
#define EFBIG		25
#define EHOSTUNREACH	26
#define EIDRM		27
#define EINPROGRESS	29
#define EINTR		30
#define EINVAL		31
#define EIO		32
#define EISCONN		33
#define EISDIR		34
#define ELOOP		35
#define EMFILE		36
#define EMLINK		37
#define EMSGSIZE	38
#define EMULTIHOP	39
#define ENAMETOOLONG	40
#define ENETDOWN	41
#define ENETRESET	42
#define ENETUNREACH	43
#define ENFILE		44
#define ENOBUFS		45
#define ENODATA		46
#define ENODEV		47
#define ENOENT		48
#define ENOEXEC		49
#define ENOLCK		50
#define ENOLINK		51
#define ENOMEM		52
#define ENOMSG		53
#define ENOPROTOOPT	54
#define ENOSPC		55
#define ENOSR		56
#define ENOSTR		57
#define ENOSYS		58
#define ENOTCONN	59
#define ENOTDIR		60
#define ENOTEMPTY	61
#define ENOTSOCK	62
#define ENOTSUP		63
#define ENOTTY		64
#define ENXIO		65
#define EOPNOTSUPP	66
#define EOVERFLOW	67
#define EPERM		68
#define EPIPE		69
#define EPROTO		70
#define EPROTONOSUPPORT	71
#define EPROTOTYPE	72
#define EROFS		73
#define ESPIPE		74
#define ESRCH		75
#define ESTALE		76
#define ETIME		77
#define ETIMEDOUT	78
#define ETXTBSY		79
#define EWOULDBLOCK	80
#define EXDEV		81

#endif

