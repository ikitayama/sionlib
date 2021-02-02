/****************************************************************************
**  SIONLIB     http://www.fz-juelich.de/jsc/sionlib                       **
*****************************************************************************
**  Copyright (c) 2008-2019                                                **
**  Forschungszentrum Juelich, Juelich Supercomputing Centre               **
**                                                                         **
**  See the file COPYRIGHT in the package base directory for details       **
****************************************************************************/

/*!
 * \file
 */

#ifndef SION_SION_DEBUG_H
#define SION_SION_DEBUG_H

#include <stdio.h>

#define _SION_DEFAULT_RANK -1
#ifdef DPRINTF
#undef ONLY_DEBUG
#undef DPRINTF
#undef DPRINTFP
#undef DPRINTTS
#undef DPRINTFTS2
#endif
#ifdef SION_DEBUG
#define ONLY_DEBUG(A) A
#define DPRINTF(A) lsion_dprintf A
#define DPRINTFP(A) lsion_dprintfp A
#define DPRINTFTS(rank,desc)  lsion_dprintfp(128,"TIMING",rank,"                                                       step=%-40s timestamp=%18.8f\n",desc,_lsion_get_time())
#define DPRINTFTS2(rank,desc) lsion_dprintfp(256,"TIMING",rank,"                                                       step=%-40s timestamp=%18.8f\n",desc,_lsion_get_time())
#else
#define ONLY_DEBUG(A)
#define DPRINTF(A)
#define DPRINTFP(A)
#define DPRINTFTS(A,B)
#define DPRINTFTS2(A,B)
#endif

#ifdef __cplusplus
extern "C" {
#endif

int _lsion_debug_init(void);
int lsion_dprintf(int mask, const char *format, ...);
int lsion_dprintfp(int mask, const char *callfunction, int rank, const char *format, ...);
int lsion_isdebug(void);
void lsion_debug_on(int mask, const char *filename);
void lsion_debug_off(void);
FILE *lsion_get_dfile(void);
void lsion_dclose(void);

void _sion_debug_set_lock_cb(void (*set_lock)(void), void (*unset_lock)(void));

int _lsion_debug_set_query_thread_num_function( int (*get_thread_num)(void) );

#ifdef __cplusplus
}
#endif

#endif
