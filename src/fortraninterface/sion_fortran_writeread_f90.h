/****************************************************************************
**  SIONLIB     http://www.fz-juelich.de/jsc/sionlib                       **
*****************************************************************************
**  Copyright (c) 2008-2019                                                **
**  Forschungszentrum Juelich, Juelich Supercomputing Centre               **
**                                                                         **
**  See the file COPYRIGHT in the package base directory for details       **
****************************************************************************/
#ifndef SION_FORTRAN_WRITEREAD_F90_H_
#define SION_FORTRAN_WRITEREAD_F90_H_

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
#define lfsion_write_c LFSION_WRITE_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_write_c lfsion_write_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_write_c lfsion_write_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_write_c lfsion_write_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_write_c(const void *data, 
                   sion_int64 *size, 
                   sion_int64 *nitems, 
                   int *sid, 
                   sion_int64 *rc);

/* lsion_fwrite() */
#if defined(_FORTRANCAPS)
#define lfsion_fwrite_c LFSION_FWRITE_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_fwrite_c lfsion_fwrite_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_fwrite_c lfsion_fwrite_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_fwrite_c lfsion_fwrite_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_fwrite_c(const void *data, 
                    sion_int64 *size, 
                    sion_int64 *nitems, 
                    int *sid, 
                    sion_int64 *rc);

/* sion_read() */
#if defined(_FORTRANCAPS)
#define lfsion_read_c LFSION_READ_C

#elif defined(_FORTRANNOCAPS)
#define fsion_read_C lfsion_read_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_read_c lfsion_read_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_read_c lfsion_read_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_read_c(void *data, 
                  sion_int64 *size, 
                  sion_int64 *nitems, 
                  int *sid, 
                  sion_int64 *rc);

/* lsion_fread() */
#if defined(_FORTRANCAPS)
#define lfsion_fread_c LFSION_FREAD_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_fread_c lfsion_fread_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_fread_c lfsion_fread_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_fread_c lfsion_fread_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_fread_c(void *data, 
                   sion_int64 *size, 
                   sion_int64 *nitems, 
                   int *sid, 
                   sion_int64 *rc);


#endif /* SION_FORTRAN_H_ */
