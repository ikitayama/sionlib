/****************************************************************************
**  SIONLIB     http://www.fz-juelich.de/jsc/sionlib                       **
*****************************************************************************
**  Copyright (c) 2008-2019                                                **
**  Forschungszentrum Juelich, Juelich Supercomputing Centre               **
**                                                                         **
**  See the file COPYRIGHT in the package base directory for details       **
****************************************************************************/
#ifndef SION_FORTRAN_OMP_H_
#define SION_FORTRAN_OMP_H_

#include <omp.h>
#include "sion.h"

/* lsion_paropen_omp() */
#if defined(_FORTRANCAPS)
#define lfsion_paropen_omp_c LFSION_PAROPEN_OMP_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_paropen_omp_c lfsion_paropen_omp_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_paropen_omp_c lfsion_paropen_omp_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_paropen_omp_c lfsion_paropen_omp_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif

void lfsion_paropen_omp_c(char *fname,
                       char *file_mode,
                       sion_int64 *chunksize, 
		       sion_int32 *fsblksize, 
		       int *globalrank, 
		       char *newfname,
		       int *sid, 
		       int  fname_len, 
		       int  file_mode_len,
		       int  newfname_len);

/* lsion_parclose_omp() */
#if defined(_FORTRANCAPS)
#define lfsion_parclose_omp_c LFSION_PARCLOSE_OMP_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_parclose_omp_c lfsion_parclose_omp_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_parclose_omp_c lfsion_parclose_omp_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_parclose_omp_c lfsion_parclose_omp_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_parclose_omp_c(int  *sid, int *ierr);

#endif /* SION_FORTRAN_OMP_H_ */
