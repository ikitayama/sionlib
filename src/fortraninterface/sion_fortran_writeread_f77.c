/****************************************************************************
**  SIONLIB     http://www.fz-juelich.de/jsc/sionlib                       **
*****************************************************************************
**  Copyright (c) 2008-2019                                                **
**  Forschungszentrum Juelich, Juelich Supercomputing Centre               **
**                                                                         **
**  See the file COPYRIGHT in the package base directory for details       **
****************************************************************************/
/*!
 * @file sion_fortran.c
 *
 * @brief Fortran API
 *
 * @author Ventsislav Petkov
 * @date 14.08.2008
 * @date 03.05.2013 modifications to support different Fortran interfaces, Florian Janetzko
 */

#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* #define _FORTRANUNDERSCORE
   #define _FORTRANNOCAPS
   #define _FORTRANCAPS
   #define _FORTRANDOUBLEUNDERSCORE */
#include "sion.h"
#include "sion_debug.h"
#include "sion_fd.h"
#include "sion_filedesc.h"
#include "sion_fortran_writeread_f77.h"


#define DFUNCTION "lfsion_write"
/*!
 * @brief Fortran procedure to write to a sion file.
 *
 * This fortran procedure writes nitems objects, each size bytes long, to a sion file,
 * obtaining them from the location given by data. It advances the file position indicator
 * by the number of bytes written.
 *
 * @param[in]   data    pointer to the data to be written
 * @param[in]   size    size of the data
 * @param[in]   nitems  number of items of data to write to the file
 * @param[in]   sid     sion file handle
 *
 * @param[out]  rc      number of objects written or a short object count (or zero)
 *                      if an error occurs, or the end-of-file is reached
 */
void lfsion_write(const void *data, 
                   sion_int64 *size, 
                   sion_int64 *nitems, 
                   int *sid, 
                   sion_int64 *rc)
{
  /* (*rc) = (sion_int64) fwrite(data, *size, (int) *nitems, lsion_get_fp(*sid)); */
  DPRINTFP((1, DFUNCTION, -1, "enter size=%ld nitems=%ld\n",(long) *size, (long) *nitems));
  (*rc) = (sion_int64) lsion_fwrite(data, (size_t) *size, (size_t) *nitems, *sid);
  DPRINTFP((1, DFUNCTION, -1, "leave rc=%d\n",*rc));
}
#undef DFUNCTION

#define DFUNCTION "lfsion_fwrite"
/*!
 * @brief Fortran procedure to write to a sion file.
 *
 * This fortran procedure writes nitems objects, each size bytes long, to a sion file,
 * obtaining them from the location given by data. It advances the file position indicator
 * by the number of bytes written.
 *
 * @param[in]   data    pointer to the data to be written
 * @param[in]   size    size of the data
 * @param[in]   nitems  number of items of data to write to the file
 * @param[in]   sid     sion file handle
 *
 * @param[out]  rc      number of objects written or a short object count (or zero)
 *                      if an error occurs, or the end-of-file is reached
 */
void lfsion_fwrite(const void *data, 
                    sion_int64 *size, 
                    sion_int64 *nitems, 
                    int *sid, 
                    sion_int64 *rc)
{
  /* (*rc) = (sion_int64) fwrite(data, *size, (int) *nitems, lsion_get_fp(*sid)); */
  DPRINTFP((1, DFUNCTION, -1, "enter size=%ld nitems=%ld\n",(long) *size, (long) *nitems));
  (*rc) = (sion_int64) lsion_fwrite(data, (size_t) *size, (size_t) *nitems, *sid);
  DPRINTFP((1, DFUNCTION, -1, "leave rc=%d\n",*rc));
}
#undef DFUNCTION



/*!
 * @brief Fortran procedure to read from a sion file.
 *
 * This fortran procedure reads nitems objects, each size bytes long, from a sion file,
 * storing them at the location given by data. It advances the file position indicator
 * by the number of bytes read or written.
 *
 * @param[in]   data    pointer to the store location
 * @param[in]   size    size of the data
 * @param[in]   nitems  number of items of data to read from the file
 * @param[in]   sid             sion file handle
 *
 * @param[out]  rc              number of objects read or a short object count (or zero)
 *                                              if an error occurs, or the end-of-file is reached
 */
void lfsion_read(void *data, 
                  sion_int64 *size, 
                  sion_int64 *nitems, 
                  int *sid, 
                  sion_int64 *rc)
{
  /* (*rc) = (sion_int64) fread(data, *size, (int) *nitems, lsion_get_fp(*sid)); */
  (*rc) = (sion_int64) lsion_fread(data, (size_t) *size, (size_t) *nitems, *sid);
}

/*!
 * @brief Fortran procedure to read from a sion file.
 *
 * This fortran procedure reads nitems objects, each size bytes long, from a sion file,
 * storing them at the location given by data. It advances the file position indicator
 * by the number of bytes read or written.
 *
 * @param[in]   data    pointer to the store location
 * @param[in]   size    size of the data
 * @param[in]   nitems  number of items of data to read from the file
 * @param[in]   sid             sion file handle
 *
 * @param[out]  rc              number of objects read or a short object count (or zero)
 *                                              if an error occurs, or the end-of-file is reached
 */
void lfsion_fread(void *data, 
                   sion_int64 *size, 
                   sion_int64 *nitems, 
                   int *sid, 
                   sion_int64 *rc)
{
  /* (*rc) = (sion_int64) fread(data, *size, (int) *nitems, lsion_get_fp(*sid)); */
  (*rc) = (sion_int64) lsion_fread(data, (size_t) *size, (size_t) *nitems, *sid);
}

