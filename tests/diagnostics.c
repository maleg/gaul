/**********************************************************************
  diagnostics.c
 **********************************************************************

  diagnostics - Generate some diagnostic output for GAUL.
  Copyright ©2003-2004, Stewart Adcock <stewart@linux-domain.com>
  All rights reserved.

  The latest version of this program should be available at:
  http://gaul.sourceforge.net/

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.  Alternatively, if your project
  is incompatible with the GPL, I will probably agree to requests
  for permission to use the terms of any other license.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY WHATSOEVER.

  A full copy of the GNU General Public License should be in the file
  "COPYING" provided with this distribution; if not, see:
  http://www.gnu.org/

 **********************************************************************

  Synopsis:	Diagnostic checking for GAUL.  This produces some
		standard diagnostic output which is helpful for
		debugging and porting.

 **********************************************************************/

/*
 * Includes
 */
#include "gaul.h"

/*
 * Ensure that any that isn't defined yet gets set to '0'.
 */
#if !defined(HAVE_ATEXIT)
# define HAVE_ATEXIT	0
#endif
#if !defined(HAVE_BCMP)
# define HAVE_BCMP	0
#endif
#if !defined(HAVE_BCOPY)
# define HAVE_BCOPY	0
#endif
#if !defined(HAVE_FDOPEN)
# define HAVE_FDOPEN	0
#endif
#if !defined(HAVE_GETHOSTNAME)
# define HAVE_GETHOSTNAME	0
#endif
#if !defined(HAVE_GETPWUID)
# define HAVE_GETPWUID	0
#endif
#if !defined(HAVE_INDEX)
# define HAVE_INDEX	0
#endif
#if !defined(HAVE_MEMCHR)
# define HAVE_MEMCHR	0
#endif
#if !defined(HAVE_MEMCMP)
# define HAVE_MEMCMP	0
#endif
#if !defined(HAVE_MEMCPY)
# define HAVE_MEMCPY	0
#endif
#if !defined(HAVE_MEMMEM)
# define HAVE_MEMMEM	0
#endif
#if !defined(HAVE_MEMMOVE)
# define HAVE_MEMMOVE	0
#endif
#if !defined(HAVE_MEMREV)
# define HAVE_MEMREV	0
#endif
#if !defined(HAVE_MEMSCAN)
# define HAVE_MEMSCAN	0
#endif
#if !defined(HAVE_MEMSET)
# define HAVE_MEMSET	0
#endif
#if !defined(HAVE_ON_EXIT)
# define HAVE_ON_EXIT	0
#endif
#if !defined(HAVE_RINDEX)
# define HAVE_RINDEX	0
#endif
#if !defined(HAVE_SELECT)
# define HAVE_SELECT	0
#endif
#if !defined(HAVE_SINCOS)
# define HAVE_SINCOS	0
#endif
#if !defined(HAVE_SNOOZE)
# define HAVE_SNOOZE	0
#endif
#if !defined(HAVE_SNPRINTF)
# define HAVE_SNPRINTF	0
#endif
#if !defined(HAVE_STDBOOL_H)
# define HAVE_STDBOOL_H	0
#endif
#if !defined(HAVE_STDINT_H)
# define HAVE_STDINT_H	0
#endif
#if !defined(HAVE_STDLIB_H)
# define HAVE_STDLIB_H	0
#endif
#if !defined(HAVE_STRCASECMP)
# define HAVE_STRCASECMP	0
#endif
#if !defined(HAVE_STRCAT)
# define HAVE_STRCAT	0
#endif
#if !defined(HAVE_STRCATV)
# define HAVE_STRCATV	0
#endif
#if !defined(HAVE_STRCHR)
# define HAVE_STRCHR	0
#endif
#if !defined(HAVE_STRCMP)
# define HAVE_STRCMP	0
#endif
#if !defined(HAVE_STRCPY)
# define HAVE_STRCPY	0
#endif
#if !defined(HAVE_STRCSPN)
# define HAVE_STRCSPN	0
#endif
#if !defined(HAVE_STRDUP)
# define HAVE_STRDUP	0
#endif
#if !defined(HAVE_STRERROR)
# define HAVE_STRERROR	0
#endif
#if !defined(HAVE_STRINGS_H)
# define HAVE_STRINGS_H	0
#endif
#if !defined(HAVE_STRING_H)
# define HAVE_STRING_H	0
#endif
#if !defined(HAVE_STRLCAT)
# define HAVE_STRLCAT	0
#endif
#if !defined(HAVE_STRLCPY)
# define HAVE_STRLCPY	0
#endif
#if !defined(HAVE_STRLEN)
# define HAVE_STRLEN	0
#endif
#if !defined(HAVE_STRNCASECMP)
# define HAVE_STRNCASECMP	0
#endif
#if !defined(HAVE_STRNCMP)
# define HAVE_STRNCMP	0
#endif
#if !defined(HAVE_STRNCPY)
# define HAVE_STRNCPY	0
#endif
#if !defined(HAVE_STRNDUP)
# define HAVE_STRNDUP	0
#endif
#if !defined(HAVE_STRNFILL)
# define HAVE_STRNFILL	0
#endif
#if !defined(HAVE_STRPBRK)
# define HAVE_STRPBRK	0
#endif
#if !defined(HAVE_STRRCHR)
# define HAVE_STRRCHR	0
#endif
#if !defined(HAVE_STRREV)
# define HAVE_STRREV	0
#endif
#if !defined(HAVE_STRSEP)
# define HAVE_STRSEP	0
#endif
#if !defined(HAVE_STRSIGNAL)
# define HAVE_STRSIGNAL	0
#endif
#if !defined(HAVE_STRSPN)
# define HAVE_STRSPN	0
#endif
#if !defined(HAVE_STRSTR)
# define HAVE_STRSTR	0
#endif
#if !defined(HAVE_STRTOD)
# define HAVE_STRTOD	0
#endif
#if !defined(HAVE_STRTOK)
# define HAVE_STRTOK	0
#endif
#if !defined(HAVE_USLEEP)
# define HAVE_USLEEP	0
#endif
#if !defined(HAVE_VSNPRINTF)
# define HAVE_VSNPRINTF	0
#endif
#if !defined(HAVE_WAITPID)
# define HAVE_WAITPID	0
#endif
#if !defined(HAVE__BOOL)
# define HAVE__BOOL	0
#endif
#if !defined(HAVE_MPI)
# define HAVE_MPI	0
#endif
#if !defined(HAVE_PTHREADS)
# define HAVE_PTHREADS	0
#endif
#if !defined(HAVE_SLANG)
# define HAVE_SLANG	0
#endif
#if !defined(V3_QUICK)
# define V3_QUICK	0
#endif
#if !defined(W32_CRIPPLED)
# define W32_CRIPPLED	0
#endif

/**********************************************************************
  main()
  synopsis:	Produce some standard diagnostic output.
  parameters:
  return:
  updated:	23 Sep 2003
 **********************************************************************/

int main(int argc, char **argv)
  {

/*
 * What machine type is this?
 */
  printf("Execution machine characteristics:\n");
#if W32_CRIPPLED != 1
  system("uname -a");
#else
  printf("Native MS Windows support.");
#endif

/*
 * Usual initializations.
 */
  random_init();

/*
 * Output GAUL's diagnostic info.
 */
  printf("This program is linked against GAUL %d.%d-%d\n",
         ga_get_major_version(), ga_get_minor_version(), ga_get_patch_version());
  printf("This program was compiled with the GAUL %d.%d-%d headers.\n",
         GA_MAJOR_VERSION, GA_MINOR_VERSION, GA_PATCH_VERSION);

  ga_diagnostics();

  printf("Configuration details:\n");

  printf("GA_BUILD_DATE_STRING:           %s\n", GA_BUILD_DATE_STRING);
  printf("GA_DEFAULT_NUM_PROCESSES:       %d\n",GA_DEFAULT_NUM_PROCESSES);
  printf("GA_DEFAULT_NUM_THREADS:         %d\n", GA_DEFAULT_NUM_THREADS);
  printf("GA_NUM_PROCESSES_ENVVAR_STRING: %s\n", GA_NUM_PROCESSES_ENVVAR_STRING);
  printf("GA_NUM_THREADS_ENVVAR_STRING:   %s\n", GA_NUM_THREADS_ENVVAR_STRING);
  printf("HAVE_ATEXIT:                    %s\n", HAVE_ATEXIT?"true":"false");
  printf("HAVE_BCMP:                      %s\n", HAVE_BCMP?"true":"false");
  printf("HAVE_BCOPY:                     %s\n", HAVE_BCOPY?"true":"false");
  printf("HAVE_FDOPEN:                    %s\n", HAVE_FDOPEN?"true":"false");
  printf("HAVE_GETHOSTNAME:               %s\n", HAVE_GETHOSTNAME?"true":"false");
  printf("HAVE_GETPWUID:                  %s\n", HAVE_GETPWUID?"true":"false");
  printf("HAVE_INDEX:                     %s\n", HAVE_INDEX?"true":"false");
  printf("HAVE_MEMCHR:                    %s\n", HAVE_MEMCHR?"true":"false");
  printf("HAVE_MEMCMP:                    %s\n", HAVE_MEMCMP?"true":"false");
  printf("HAVE_MEMCPY:                    %s\n", HAVE_MEMCPY?"true":"false");
  printf("HAVE_MEMMEM:                    %s\n", HAVE_MEMMEM?"true":"false");
  printf("HAVE_MEMMOVE:                   %s\n", HAVE_MEMMOVE?"true":"false");
  printf("HAVE_MEMREV:                    %s\n", HAVE_MEMREV?"true":"false");
  printf("HAVE_MEMSCAN:                   %s\n", HAVE_MEMSCAN?"true":"false");
  printf("HAVE_MEMSET:                    %s\n", HAVE_MEMSET?"true":"false");
  printf("HAVE_ON_EXIT:                   %s\n", HAVE_ON_EXIT?"true":"false");
  printf("HAVE_RINDEX:                    %s\n", HAVE_RINDEX?"true":"false");
  printf("HAVE_SELECT:                    %s\n", HAVE_SELECT?"true":"false");
  printf("HAVE_SINCOS:                    %s\n", HAVE_SINCOS?"true":"false");
  printf("HAVE_SNOOZE:                    %s\n", HAVE_SNOOZE?"true":"false");
  printf("HAVE_SNPRINTF:                  %s\n", HAVE_SNPRINTF?"true":"false");
  printf("HAVE_STDBOOL_H:                 %s\n", HAVE_STDBOOL_H?"true":"false");
  printf("HAVE_STDINT_H:                  %s\n", HAVE_STDINT_H?"true":"false");
  printf("HAVE_STDLIB_H:                  %s\n", HAVE_STDLIB_H?"true":"false");
  printf("HAVE_STRCASECMP:                %s\n", HAVE_STRCASECMP?"true":"false");
  printf("HAVE_STRCAT:                    %s\n", HAVE_STRCAT?"true":"false");
  printf("HAVE_STRCATV:                   %s\n", HAVE_STRCATV?"true":"false");
  printf("HAVE_STRCHR:                    %s\n", HAVE_STRCHR?"true":"false");
  printf("HAVE_STRCMP:                    %s\n", HAVE_STRCMP?"true":"false");
  printf("HAVE_STRCPY:                    %s\n", HAVE_STRCPY?"true":"false");
  printf("HAVE_STRCSPN:                   %s\n", HAVE_STRCSPN?"true":"false");
  printf("HAVE_STRDUP:                    %s\n", HAVE_STRDUP?"true":"false");
  printf("HAVE_STRERROR:                  %s\n", HAVE_STRERROR?"true":"false");
  printf("HAVE_STRINGS_H:                 %s\n", HAVE_STRINGS_H?"true":"false");
  printf("HAVE_STRING_H:                  %s\n", HAVE_STRING_H?"true":"false");
  printf("HAVE_STRLCAT:                   %s\n", HAVE_STRLCAT?"true":"false");
  printf("HAVE_STRLCPY:                   %s\n", HAVE_STRLCPY?"true":"false");
  printf("HAVE_STRLEN:                    %s\n", HAVE_STRLEN?"true":"false");
  printf("HAVE_STRNCASECMP:               %s\n", HAVE_STRNCASECMP?"true":"false");
  printf("HAVE_STRNCMP:                   %s\n", HAVE_STRNCMP?"true":"false");
  printf("HAVE_STRNCPY:                   %s\n", HAVE_STRNCPY?"true":"false");
  printf("HAVE_STRNDUP:                   %s\n", HAVE_STRNDUP?"true":"false");
  printf("HAVE_STRNFILL:                  %s\n", HAVE_STRNFILL?"true":"false");
  printf("HAVE_STRPBRK:                   %s\n", HAVE_STRPBRK?"true":"false");
  printf("HAVE_STRRCHR:                   %s\n", HAVE_STRRCHR?"true":"false");
  printf("HAVE_STRREV:                    %s\n", HAVE_STRREV?"true":"false");
  printf("HAVE_STRSEP:                    %s\n", HAVE_STRSEP?"true":"false");
  printf("HAVE_STRSIGNAL:                 %s\n", HAVE_STRSIGNAL?"true":"false");
  printf("HAVE_STRSPN:                    %s\n", HAVE_STRSPN?"true":"false");
  printf("HAVE_STRSTR:                    %s\n", HAVE_STRSTR?"true":"false");
  printf("HAVE_STRTOD:                    %s\n", HAVE_STRTOD?"true":"false");
  printf("HAVE_STRTOK:                    %s\n", HAVE_STRTOK?"true":"false");
  printf("HAVE_USLEEP:                    %s\n", HAVE_USLEEP?"true":"false");
  printf("HAVE_VSNPRINTF:                 %s\n", HAVE_VSNPRINTF?"true":"false");
  printf("HAVE_WAITPID:                   %s\n", HAVE_WAITPID?"true":"false");
  printf("HAVE__BOOL:                     %s\n", HAVE__BOOL?"true":"false");
  printf("HAVE_MPI:                       %s\n", HAVE_MPI?"true":"false");
  printf("HAVE_PTHREADS:                  %s\n", HAVE_PTHREADS?"true":"false");
  printf("HAVE_SLANG:                     %s\n", HAVE_SLANG?"true":"false");
  printf("V3_QUICK:                       %s\n", V3_QUICK?"true":"false");
  printf("W32_CRIPPLED:                   %s\n", W32_CRIPPLED?"true":"false");

  exit(EXIT_SUCCESS);
  }


