/* config.h.  Generated automatically by configure.  */
/* config.h.in.  Generated automatically from configure.in by autoheader.  */
/* acconfig.h

 GAUL's default settings.

 */



/* Other stuff */

/* #undef MEMORY_ALLOC_DEBUG */
#define MEMORY_ALLOC_SAFE 1
#define MEMORY_ALIGN_SIZE 4
#define MEMORY_PADDING 0

#define DEBUG 0
#define GA_DEBUG 0
#define GA_WRITE_STATS 0

/* #undef VERSION */
#define VERSION_STRING "0.1838-2"
#define BUILD_DATE_STRING "29/04/02"
#define MAJOR_VERSION 0
#define MINOR_VERSION 1838
#define PATCH_VERSION 2
#define UNAME_STRING "Linux chemcca0 2.4.9-13smp #1 SMP Tue Oct 30 19:57:16 EST 2001 i686 unknown"

#define AVLTREE_KEY_TYPE void *
#define PARALLEL 0
#define V3_QUICK 1
#define HAVE_SLANG 1
#define MPI_NUM_THREADS_ENVVAR_STRING "GA_NUM_THREADS"

/* #undef HAVE_FLOAT_H */
#define HAVE_LIMITS_H 1
/* #undef HAVE_POLL */
#define HAVE_PWD_H 1
/* #undef HAVE_SYS_PARAM_H */
/* #undef HAVE_SYS_POLL_H */
#define HAVE_SYS_SELECT_H 1
#define HAVE_SYS_TIME_H 1
/* #undef HAVE_SYS_TIMES_H */
#define HAVE_STRERROR 1
#define HAVE_STRSIGNAL 1
#define HAVE_UNISTD_H 1
#define HAVE_VALUES_H 1

/* Kludge required for linking to LAM-MPI */
#define HAVE_ITOA 1

/* #undef NO_SYS_ERRLIST */

#define SIZEOF_DOUBLE 8
#define SIZEOF_CHAR 1
/* #undef SIZEOF_SHORT */
#define SIZEOF_LONG 4
#define SIZEOF_INT 4
#define SIZEOF_VOID_P 4

/* #undef PACKAGE */


/* Type of key used by AVL routines */
#define AVLTREE_KEY_TYPE void *

/* Date of compilation */
#define BUILD_DATE_STRING "29/04/02"

/* Define if you have the <arpa/inet.h> header file. */
#define HAVE_ARPA_INET_H 1

/* Define if you have the `atexit' function. */
#define HAVE_ATEXIT 1

/* Define if you have the `basename' function. */
#define HAVE_BASENAME 1

/* Define if you have the `bcopy' function. */
#define HAVE_BCOPY 1

/* Define if you don't have `vprintf' but do have `_doprnt.' */
/* #undef HAVE_DOPRNT */

/* Define if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define if you have the `fdopen' function. */
#define HAVE_FDOPEN 1

/* Define if you have the `gethostname' function. */
#define HAVE_GETHOSTNAME 1

/* Define if you have the `getpwuid' function. */
#define HAVE_GETPWUID 1

/* Define if you have the `gettimeofday' function. */
#define HAVE_GETTIMEOFDAY 1

/* Define if you have the `index' function. */
#define HAVE_INDEX 1

/* Define if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define if you have the `max' function. */
/* #undef HAVE_MAX */

/* Define if you have the `memchr' function. */
#define HAVE_MEMCHR 1

/* Define if you have the `memcmp' function. */
#define HAVE_MEMCMP 1

/* Define if you have the `memcpy' function. */
#define HAVE_MEMCPY 1

/* Define if you have the `memmem' function. */
#define HAVE_MEMMEM 1

/* Define if you have the `memmove' function. */
#define HAVE_MEMMOVE 1

/* Define if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define if you have the `memrev' function. */
/* #undef HAVE_MEMREV */

/* Define if you have the `memscan' function. */
/* #undef HAVE_MEMSCAN */

/* Define if you have the `memset' function. */
#define HAVE_MEMSET 1

/* Define if you have the `min' function. */
/* #undef HAVE_MIN */

/* Define if you have the <netdb.h> header file. */
#define HAVE_NETDB_H 1

/* Define if you have the <netinet/in.h> header file. */
#define HAVE_NETINET_IN_H 1

/* Define if you have the `on_exit' function. */
#define HAVE_ON_EXIT 1

/* Define if you have the <pwd.h> header file. */
#define HAVE_PWD_H 1

/* Define if you have the `readline' function. */
/* #undef HAVE_READLINE */

/* Define if you have the `rindex' function. */
#define HAVE_RINDEX 1

/* Define if you have the `select' function. */
#define HAVE_SELECT 1

/* Define if you have the `sincos' function. */
#define HAVE_SINCOS 1

/* Define if you have the `snooze' function. */
/* #undef HAVE_SNOOZE */

/* Define if you have the `snprintf' function. */
#define HAVE_SNPRINTF 1

/* Define if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define if you have the `strcasecmp' function. */
#define HAVE_STRCASECMP 1

/* Define if you have the `strcat' function. */
#define HAVE_STRCAT 1

/* Define if you have the `strcatv' function. */
/* #undef HAVE_STRCATV */

/* Define if you have the `strchr' function. */
#define HAVE_STRCHR 1

/* Define if you have the `strcmp' function. */
#define HAVE_STRCMP 1

/* Define if you have the `strcpy' function. */
#define HAVE_STRCPY 1

/* Define if you have the `strcspn' function. */
#define HAVE_STRCSPN 1

/* Define if you have the `strdup' function. */
#define HAVE_STRDUP 1

/* Define if you have the `strerror' function. */
#define HAVE_STRERROR 1

/* Define if you have the `stricmp' function. */
/* #undef HAVE_STRICMP */

/* Define if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define if you have the `strlcat' function. */
/* #undef HAVE_STRLCAT */

/* Define if you have the `strlcpy' function. */
/* #undef HAVE_STRLCPY */

/* Define if you have the `strlen' function. */
#define HAVE_STRLEN 1

/* Define if you have the `strncasecmp' function. */
#define HAVE_STRNCASECMP 1

/* Define if you have the `strncmp' function. */
#define HAVE_STRNCMP 1

/* Define if you have the `strncpy' function. */
#define HAVE_STRNCPY 1

/* Define if you have the `strndup' function. */
#define HAVE_STRNDUP 1

/* Define if you have the `strnfill' function. */
/* #undef HAVE_STRNFILL */

/* Define if you have the `strnicmp' function. */
/* #undef HAVE_STRNICMP */

/* Define if you have the `strpbrk' function. */
#define HAVE_STRPBRK 1

/* Define if you have the `strrchr' function. */
#define HAVE_STRRCHR 1

/* Define if you have the `strrev' function. */
/* #undef HAVE_STRREV */

/* Define if you have the `strsep' function. */
#define HAVE_STRSEP 1

/* Define if you have the `strsignal' function. */
#define HAVE_STRSIGNAL 1

/* Define if you have the `strspn' function. */
#define HAVE_STRSPN 1

/* Define if you have the `strstr' function. */
#define HAVE_STRSTR 1

/* Define if you have the `strtod' function. */
#define HAVE_STRTOD 1

/* Define if you have the `strtok' function. */
#define HAVE_STRTOK 1

/* Define if you have the <sys/ioctl.h> header file. */
#define HAVE_SYS_IOCTL_H 1

/* Define if you have the <sys/select.h> header file. */
#define HAVE_SYS_SELECT_H 1

/* Define if you have the <sys/signal.h> header file. */
#define HAVE_SYS_SIGNAL_H 1

/* Define if you have the <sys/socket.h> header file. */
#define HAVE_SYS_SOCKET_H 1

/* Define if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define if you have the <sys/termio.h> header file. */
/* #undef HAVE_SYS_TERMIO_H */

/* Define if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define if you have the <sys/uio.h> header file. */
#define HAVE_SYS_UIO_H 1

/* Define if you have the <termios.h> header file. */
#define HAVE_TERMIOS_H 1

/* Define if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define if you have the `usleep' function. */
#define HAVE_USLEEP 1

/* Define if you have the <values.h> header file. */
#define HAVE_VALUES_H 1

/* Define if you have the `vprintf' function. */
#define HAVE_VPRINTF 1

/* Define if you have the `vsnprintf' function. */
#define HAVE_VSNPRINTF 1

/* Define if you have the `waitpid' function. */
#define HAVE_WAITPID 1

/* Major version number */
#define MAJOR_VERSION 0

/* Minor version number */
#define MINOR_VERSION 1838

/* Environment variable used to request threads */
#define MPI_NUM_THREADS_ENVVAR_STRING "GA_NUM_THREADS"

/* Name of package */
/* #undef PACKAGE */

/* type of parallisation */
#define PARALLEL 0

/* Patch count */
#define PATCH_VERSION 2

/* The size of a `char', as computed by sizeof. */
#define SIZEOF_CHAR 1

/* The size of a `double', as computed by sizeof. */
#define SIZEOF_DOUBLE 8

/* The size of a `int', as computed by sizeof. */
#define SIZEOF_INT 4

/* The size of a `long', as computed by sizeof. */
#define SIZEOF_LONG 4

/* The size of a `void *', as computed by sizeof. */
#define SIZEOF_VOID_P 4

/* Define if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define if you can safely include both <sys/time.h> and <time.h>. */
#define TIME_WITH_SYS_TIME 1

/* Define if your <sys/time.h> declares `struct tm'. */
/* #undef TM_IN_SYS_TIME */

/* System information */
#define UNAME_STRING "Linux chemcca0 2.4.9-13smp #1 SMP Tue Oct 30 19:57:16 EST 2001 i686 unknown"

/* Define to skip error checking in vector routines */
#define V3_QUICK 1

/* Version number of package */
/* #undef VERSION */

/* Version string */
#define VERSION_STRING "0.1838-2"

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

