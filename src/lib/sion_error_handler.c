/****************************************************************************
**  SIONLIB     http://www.fz-juelich.de/jsc/sionlib                       **
*****************************************************************************
**  Copyright (c) 2008-2019                                                **
**  Forschungszentrum Juelich, Juelich Supercomputing Centre               **
**                                                                         **
**  See the file COPYRIGHT in the package base directory for details       **
****************************************************************************/
#define _XOPEN_SOURCE 700

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#include "sion.h"
#include "sion_debug.h"
#include "sion_lock.h"
#include "sion_error_handler.h"
#include "sion_internal.h"

#define MAXOMPTHREADS 300

int _lsion_error_get_thread_num_default(void);
static int (*_lsion_my_get_thread_num)(void) = _lsion_error_get_thread_num_default;

/*! first call of dprintf? */
static int _lsion_errorprint_flag[MAXOMPTHREADS] = {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
						   0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
						   0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
						   0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
						   0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
						   
						   0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
						   0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
						   0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
						   0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
						   0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
						   
						   0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
						   0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
						   0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
						   0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
						   0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0};

#define _ERRORHANDLER_INIT_THREAD \
   int threadid=0; \
   threadid = _lsion_my_get_thread_num(); \
   if(threadid>MAXOMPTHREADS) threadid=(MAXOMPTHREADS-1);

/* default thread number */
int _lsion_error_get_thread_num_default(void) {
  return(0);
}

/* default thread number */
int _lsion_error_set_query_thread_num_function( int (*get_thread_num)(void) ) {
  _lsion_lock();
  _lsion_my_get_thread_num=get_thread_num;
  _lsion_unlock();
  return(1);
}


int _lsion_errorprint_set_flag( int flag)
{
  int rc=SION_SUCCESS;
  _ERRORHANDLER_INIT_THREAD

  _lsion_errorprint_flag[threadid]=flag;

  return (rc);
}


/*!\brief Internal SION error
 *
 * Exit the program with an error status
 */
int _lsion_errorprint(int rc, int level, const char *format, ...)
{
  int     rank=-1;
  int     thread=-1;
  va_list ap;

  va_start(ap, format);
  rc=__sion_errorprint_vargs(rc, level, rank, thread, format, ap);
  va_end(ap);
  
  return (rc);
}

int _lsion_errorprint_on_rank(int rc, int level, int rank, const char *format, ...)
{

  int     thread=-1;
  va_list ap;

  va_start(ap, format);
  rc=__sion_errorprint_vargs(rc, level, rank, thread, format, ap);
  va_end(ap);

  return (rc);
}


int __sion_errorprint_vargs(int rc, int level, int rank, int thread, const char *format, va_list ap) {

  int do_print=1;
  char *t;
  int rankselect=-1;
  int threadselect=-1;
  _ERRORHANDLER_INIT_THREAD

  /* check env */
  if(do_print) {
    t = _lsion_getenv("SION_ERROR_MSG_RANK");
    if (t) rankselect = atoi(t);
    if((rankselect>=0) && (rank>=0)) do_print = (rankselect==rank);
  }
  if(do_print) {
    t = _lsion_getenv("SION_ERROR_MSG_THREAD");
    if (t) threadselect = atoi(t);
    if((threadselect>=0) && (thread>=0)) do_print = (threadselect==thread);
  }

  if(do_print) {
    if(_lsion_errorprint_flag[threadid] & _SION_ERROR_FLAG_SUPPRESS_MSG) do_print=0;
  }
  
  if(do_print) {
    if(thread>=0) {
      fprintf(stderr,"%s on rank %d, thread %d, rc=%d: ", __sion_error_level_to_str(level),rank,thread,rc);
    } else {
      fprintf(stderr,"%s on rank %d, rc=%d: ", __sion_error_level_to_str(level),rank,rc);
    }
    vfprintf(stderr, format, ap);
    fprintf(stderr,"\n");
  }

  switch (level) {
  case _SION_ERROR_RETURN: 
    return (rc);
    break;
    case _SION_ERROR_WARN: 
      return (rc);
      break;
    case _SION_ERROR_ABORT: 
      exit (rc);
      break;
  default:
    fprintf(stderr,"ERROR in error handler: unknown level %d\n",level);
    return (rc);
  }

  return (rc);

}

#define STR_PRT(X) case X: return # X
char* __sion_error_level_to_str (unsigned int flag) {
  switch (flag) {
  case _SION_ERROR_RETURN: return "SION_ERROR_RETURN";
  case _SION_ERROR_WARN:   return "SION_ERROR_WARN";
  case _SION_ERROR_ABORT:  return "SION_ERROR_ABORT";
  default: return "SION_ERROR_UNKNOWN";
  }	           
  return "";
}
