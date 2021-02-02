/****************************************************************************
**  SIONLIB     http://www.fz-juelich.de/jsc/sionlib                       **
*****************************************************************************
**  Copyright (c) 2008-2019                                                **
**  Forschungszentrum Juelich, Juelich Supercomputing Centre               **
**                                                                         **
**  See the file COPYRIGHT in the package base directory for details       **
****************************************************************************/
#ifndef SION_FORTRAN_OMPI_C_H_
#define SION_FORTRAN_OMPI_C_H_

#include <mpi.h>
#include "sion.h"

/* sion_paropen_ompi_c() */
#if defined(_FORTRANCAPS)
#define lfsion_paropen_ompi_c LFSION_PAROPEN_OMPI_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_paropen_ompi_c lfsion_paropen_ompi_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_paropen_ompi_c lfsion_paropen_ompi_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_paropen_ompi_c lfsion_paropen_ompi_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif

void lfsion_paropen_ompi_c(char *fname,
			  char *file_mode,
			  int  *numFiles,
			  MPI_Fint * fgComm,
			  MPI_Fint * flComm,
			  sion_int64 *chunksize, 
			  sion_int32 *fsblksize, 
			  int *globalrank, 
			  char *newfname,
			  int *sid, 
			  int fname_len, 
			  int file_mode_len,
			  int newfname_len);

/* sion_paropen_multi_ompi_c() */
#if defined(_FORTRANCAPS)
#define lfsion_paropen_multi_ompi_c LFSION_PAROPEN_MULTI_OMPI_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_paropen_multi_ompi_c lfsion_paropen_multi_ompi_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_paropen_multi_ompi_c lfsion_paropen_multi_ompi_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_paropen_multi_ompi_c lfsion_paropen_multi_ompi_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_paropen_multi_ompi_c(  char *fname,
				  char *file_mode,
				  int  *numFiles,
				  MPI_Fint *fgComm,
				  MPI_Fint *flComm,
				  sion_int64 *chunksize,
				  sion_int32 *fsblksize,
				  int  *globalrank,
				  int  *sid,
				  char *newfname,
				  int  fname_len,
				  int  file_mode_len,
				  int  newfname_len);

/* sion_parclose_ompi_c() */
#if defined(_FORTRANCAPS)
#define lfsion_parclose_ompi_c LFSION_PARCLOSE_OMPI_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_parclose_ompi_c lfsion_parclose_ompi_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_parclose_ompi_c lfsion_parclose_ompi_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_parclose_ompi_c lfsion_parclose_ompi_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_parclose_ompi_c(int  *sid, int *ierr);

#endif /* SION_FORTRAN_OMPI_C_H_ */
