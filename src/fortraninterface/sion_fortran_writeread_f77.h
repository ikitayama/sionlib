/****************************************************************************
**  SIONLIB     http://www.fz-juelich.de/jsc/sionlib                       **
*****************************************************************************
**  Copyright (c) 2008-2019                                                **
**  Forschungszentrum Juelich, Juelich Supercomputing Centre               **
**                                                                         **
**  See the file COPYRIGHT in the package base directory for details       **
****************************************************************************/
#ifndef SION_FORTRAN_WRITEREAD_F77_H_
#define SION_FORTRAN_WRITEREAD_F77_H_

#include "sion.h"

/*!
 * @file sion_fortran.h
 * @brief Fortran API
 * @author Ventsislav Petkov
 * @date 14.08.2008
 * @date 03.05.2013 modifications to support different Fortran interfaces, Florian Janetzko
 */

/* sion_write() */
#if defined(_FORTRANCAPS)
#define lfsion_write LFSION_WRITE

#elif defined(_FORTRANNOCAPS)
#define lfsion_write lfsion_write

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_write lfsion_write_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_write lfsion_write__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_write(const void *data, 
                   sion_int64 *size, 
                   sion_int64 *nitems, 
                   int *sid, 
                   sion_int64 *rc);

/* lsion_fwrite() */
#if defined(_FORTRANCAPS)
#define lfsion_fwrite LFSION_FWRITE

#elif defined(_FORTRANNOCAPS)
#define lfsion_fwrite lfsion_fwrite

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_fwrite lfsion_fwrite_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_fwrite lfsion_fwrite__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_fwrite(const void *data, 
                    sion_int64 *size, 
                    sion_int64 *nitems, 
                    int *sid, 
                    sion_int64 *rc);

/* sion_read() */
#if defined(_FORTRANCAPS)
#define lfsion_read LFSION_READ

#elif defined(_FORTRANNOCAPS)
#define lfsion_read lfsion_read

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_read lfsion_read_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_read lfsion_read__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_read(void *data, 
                  sion_int64 *size, 
                  sion_int64 *nitems, 
                  int *sid, 
                  sion_int64 *rc);

/* lsion_fread() */
#if defined(_FORTRANCAPS)
#define lfsion_fread LFSION_FREAD

#elif defined(_FORTRANNOCAPS)
#define lfsion_fread lfsion_fread

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_fread lfsion_fread_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_fread lfsion_fread__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_fread(void *data, 
                   sion_int64 *size, 
                   sion_int64 *nitems, 
                   int *sid, 
                   sion_int64 *rc);


#endif /* SION_FORTRAN_H_ */
