#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helptext.h"

/* Error code entries */

#define err_entry(e, desc) [e] = {.code = (e), .name = #e, .descr = desc}

struct errinfo_s {
  int code;
  const char *name;
  const char *descr;
};

static const struct errinfo_s ERR_LOOKUP[] = {
    [0] = {.code = 0, .name = "SUCCESS", .descr = "Success"},
    err_entry(EPERM, "Operation not permitted"),
    err_entry(ENOENT, "No such file or directory"),
    err_entry(ESRCH, "No such process"),
    err_entry(EINTR, "Interrupted system call"),
    err_entry(EIO, "I/O error"),
    err_entry(ENXIO, "No such device or address"),
    err_entry(E2BIG, "Argument list too long"),
    err_entry(ENOEXEC, "Exec format error"),
    err_entry(EBADF, "Bad file number"),
    err_entry(ECHILD, "No child processes"),
    err_entry(EAGAIN, "Try again"),
    err_entry(ENOMEM, "Out of memory"),
    err_entry(EACCES, "Permission denied"),
    err_entry(EFAULT, "Bad address"),
    err_entry(ENOTBLK, "Block device required"),
    err_entry(EBUSY, "Device or resource busy"),
    err_entry(EEXIST, "File exists"),
    err_entry(EXDEV, "Cross-device link"),
    err_entry(ENODEV, "No such device"),
    err_entry(ENOTDIR, "Not a directory"),
    err_entry(EISDIR, "Is a directory"),
    err_entry(EINVAL, "Invalid argument"),
    err_entry(ENFILE, "File table overflow"),
    err_entry(EMFILE, "Too many open files"),
    err_entry(ENOTTY, "Not a typewriter"),
    err_entry(ETXTBSY, "Text file busy"),
    err_entry(EFBIG, "File too large"),
    err_entry(ENOSPC, "No space left on device"),
    err_entry(ESPIPE, "Illegal seek"),
    err_entry(EROFS, "Read-only file system"),
    err_entry(EMLINK, "Too many links"),
    err_entry(EPIPE, "Broken pipe"),
    err_entry(EDOM, "Math argument out of domain of func"),
    err_entry(ERANGE, "Math result not representable"),
    err_entry(EDEADLK, "Resource deadlock would occur"),
    err_entry(ENAMETOOLONG, "File name too long"),
    err_entry(ENOLCK, "No record locks available"),
    err_entry(ENOSYS, "Function not implemented"),
    err_entry(ENOTEMPTY, "Directory not empty"),
    err_entry(ELOOP, "Too many symbolic links encountered"),
    {.code = 41, .name = NULL, .descr = NULL}, /* 41 is skipped */
    err_entry(ENOMSG, "No message of desired type"),
    err_entry(EIDRM, "Identifier removed"),
    err_entry(ECHRNG, "Channel number out of range"),
    err_entry(EL2NSYNC, "Level 2 not synchronized"),
    err_entry(EL3HLT, "Level 3 halted"),
    err_entry(EL3RST, "Level 3 reset"),
    err_entry(ELNRNG, "Link number out of range"),
    err_entry(EUNATCH, "Protocol driver not attached"),
    err_entry(ENOCSI, "No CSI structure available"),
    err_entry(EL2HLT, "Level 2 halted"),
    err_entry(EBADE, "Invalid exchange"),
    err_entry(EBADR, "Invalid request descriptor"),
    err_entry(EXFULL, "Exchange full"),
    err_entry(ENOANO, "No anode"),
    err_entry(EBADRQC, "Invalid request code"),
    err_entry(EBADSLT, "Invalid slot"),
    err_entry(EBFONT, "Bad font file format"),
    err_entry(ENOSTR, "Device not a stream"),
    err_entry(ENODATA, "No data available"),
    err_entry(ETIME, "Timer expired"),
    err_entry(ENOSR, "Out of streams resources"),
    err_entry(ENONET, "Machine is not on the network"),
    err_entry(ENOPKG, "Package not installed"),
    err_entry(EREMOTE, "Object is remote"),
    err_entry(ENOLINK, "Link has been severed"),
    err_entry(EADV, "Advertise error"),
    err_entry(ESRMNT, "Srmount error"),
    err_entry(ECOMM, "Communication error on send"),
    err_entry(EPROTO, "Protocol error"),
    err_entry(EMULTIHOP, "Multihop attempted"),
    err_entry(EDOTDOT, "RFS specific error"),
    err_entry(EBADMSG, "Not a data message"),
    err_entry(EOVERFLOW, "Value too large for defined data type"),
    err_entry(ENOTUNIQ, "Name not unique on network"),
    err_entry(EBADFD, "File descriptor in bad state"),
    err_entry(EREMCHG, "Remote address changed"),
    err_entry(ELIBACC, "Can not access a needed shared library"),
    err_entry(ELIBBAD, "Accessing a corrupted shared library"),
    err_entry(ELIBSCN, ".lib section in a.out corrupted"),
    err_entry(ELIBMAX, "Attempting to link in too many shared libraries"),
    err_entry(ELIBEXEC, "Cannot exec a shared library directly"),
    err_entry(EILSEQ, "Illegal byte sequence"),
    err_entry(ERESTART, "Interrupted system call should be restarted"),
    err_entry(ESTRPIPE, "Streams pipe error"),
    err_entry(EUSERS, "Too many users"),
    err_entry(ENOTSOCK, "Socket operation on non-socket"),
    err_entry(EDESTADDRREQ, "Destination address required"),
    err_entry(EMSGSIZE, "Message too long"),
    err_entry(EPROTOTYPE, "Protocol wrong type for socket"),
    err_entry(ENOPROTOOPT, "Protocol not available"),
    err_entry(EPROTONOSUPPORT, "Protocol not supported"),
    err_entry(ESOCKTNOSUPPORT, "Socket type not supported"),
    err_entry(EOPNOTSUPP, "Operation not supported on transport endpoint"),
    err_entry(EPFNOSUPPORT, "Protocol family not supported"),
    err_entry(EAFNOSUPPORT, "Address family not supported by protocol"),
    err_entry(EADDRINUSE, "Address already in use"),
    err_entry(EADDRNOTAVAIL, "Cannot assign requested address"),
    err_entry(ENETDOWN, "Network is down"),
    err_entry(ENETUNREACH, "Network is unreachable"),
    err_entry(ENETRESET, "Network dropped connection because of reset"),
    err_entry(ECONNABORTED, "Software caused connection abort"),
    err_entry(ECONNRESET, "Connection reset by peer"),
    err_entry(ENOBUFS, "No buffer space available"),
    err_entry(EISCONN, "Transport endpoint is already connected"),
    err_entry(ENOTCONN, "Transport endpoint is not connected"),
    err_entry(ESHUTDOWN, "Cannot send after transport endpoint shutdown"),
    err_entry(ETOOMANYREFS, "Too many references: cannot splice"),
    err_entry(ETIMEDOUT, "Connection timed out"),
    err_entry(ECONNREFUSED, "Connection refused"),
    err_entry(EHOSTDOWN, "Host is down"),
    err_entry(EHOSTUNREACH, "No route to host"),
    err_entry(EALREADY, "Operation already in progress"),
    err_entry(EINPROGRESS, "Operation now in progress"),
    err_entry(ESTALE, "Stale NFS file handle"),
    err_entry(EUCLEAN, "Structure needs cleaning"),
    err_entry(ENOTNAM, "Not a XENIX named type file"),
    err_entry(ENAVAIL, "No XENIX semaphores available"),
    err_entry(EISNAM, "Is a named type file"),
    err_entry(EREMOTEIO, "Remote I/O error"),
    err_entry(EDQUOT, "Quota exceeded"),
    err_entry(ENOMEDIUM, "No medium found"),
    err_entry(EMEDIUMTYPE, "Wrong medium type"),
    err_entry(ECANCELED, "Operation Canceled"),
    err_entry(ENOKEY, "Required key not available"),
    err_entry(EKEYEXPIRED, "Key has expired"),
    err_entry(EKEYREVOKED, "Key has been revoked"),
    err_entry(EKEYREJECTED, "Key was rejected by service"),
    err_entry(EOWNERDEAD, "Owner died"),
    err_entry(ENOTRECOVERABLE, "State not recoverable"),
};

#define MAX_CODE ENOTRECOVERABLE

static void print_help(FILE *sink) { fprintf(sink, HELP_TEXT); }

/* WARNING: Expects that `err` exists in the lookup table. */
static void print_err(int err) {
  struct errinfo_s info = ERR_LOOKUP[err];
  printf("%d %s %s\n", err, info.name, info.descr);
}

static bool is_numberstr(const char *str) {
  for (; *str != '\0'; str++) {
    if (!isdigit(*str) && !isblank(*str)) {
      return false; /* Digits or whitespace only */
    }
  }
  return true;
}

static int fromstr(const char *err) {
  for (unsigned i = 0; i < sizeof(ERR_LOOKUP) / sizeof(ERR_LOOKUP[0]); i++) {

    /* Skip entries where the error code doesn't exist */
    if (ERR_LOOKUP[i].name == NULL) {
      continue;
    }

    if (strcasestr(ERR_LOOKUP[i].name, err) != NULL) {
      return ERR_LOOKUP[i].code;
    }
  }
  return -1;
}

int main(int argc, char **argv) {
  int errcode;

  /* Not enough arguments */

  if (argc < 2) {
    print_help(stderr);
    return EXIT_FAILURE;
  }

  /* Check if user wanted help */

  if (strstr(argv[1], "--help") != NULL) {
    print_help(stdout);
    return EXIT_SUCCESS;
  }

  /* Check if user passed numerical value or an error name to lookup */

  if (is_numberstr(argv[1])) {
    errcode = atoi(argv[1]); /* Convert number to int */
  } else {
    errcode = fromstr(argv[1]); /* Get error code from string name */
  }

  /* Handle invalid errors */

  if (errcode > MAX_CODE) {
    fprintf(stderr, "%d ? Unknown error code\n", errcode);
    return EXIT_FAILURE;
  } else if (errcode < 0) {
    fprintf(stderr, "? %s Unknown error name\n", argv[1]);
    return EXIT_FAILURE;
  }

  print_err(errcode); /* Print error info */
  return EXIT_SUCCESS;
}
