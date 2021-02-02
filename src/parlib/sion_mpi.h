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
 *
 * \ref api_page
 */

#ifndef SION_SION_MPI_H
#define SION_SION_MPI_H

#if defined(MPI_VERSION) || defined(SION_MPI)

#include <stdio.h>

#include "mpi.h"

#include "sion_const.h"
#include "sion_datatypes.h"
#include "sion_datatypes_mpi.h"

#ifdef __cplusplus
extern "C" {
#endif

  int lsion_paropen_mpi(    const char     *fname,
			   const char     *file_mode,
			   int            *numFiles,
			   MPI_Comm        gComm,
			   const MPI_Comm *lComm,
			   sion_int64     *chunksize,
			   sion_int32     *fsblksize,
			   int            *globalrank,
			   FILE          **fileptr,
			   char          **newfname);

  int lsion_parclose_mpi(   int      sid  );
  int lsion_parreinit_mpi(  int sid,
			   sion_int64 chunksize );

/* new mapped functions */

/* open function:
   write-mode:
     if numFiles > 1  --> mapping_filenrs, mapping_lranks contains local mappping
    */

  int lsion_paropen_mapped_mpi(    char          *fname,
				  const char    *file_mode,
				  int           *numFiles,
				  MPI_Comm       gComm,
				  int           *nlocaltasks,
				  int          **globalranks,
				  sion_int64   **chunksizes,
				  int          **mapping_filenrs, 
				  int          **mapping_lranks,
				  sion_int32    *fsblksize,
				  FILE         **fileptr);

  int lsion_parclose_mapped_mpi(   int      sid  );

  /* Serialization */
  int lsion_startof_transaction_mpi(   int      sid  );
  int lsion_endof_transaction_mpi  (   int      sid  );
  size_t lsion_coll_fwrite_mpi(const void *data, size_t size, size_t nitems, int sid);
  size_t lsion_coll_fread_mpi( void *data, size_t size, size_t nitems, int sid);

  /* for backward compatibility */
  int lsion_paropen_comms_mpi(char *fname,
			     const char *file_mode,
			     int *numFiles,
			     MPI_Comm gComm,
			     MPI_Comm lComm, sion_int64 *chunksize, sion_int32 *fsblksize, int *globalrank, FILE **fileptr, char *newfname);
  int lsion_paropen_multi_mpi(char *fname,
			     const char *file_mode,
			     int *numFiles,
			     MPI_Comm gComm,
			     MPI_Comm *lComm, sion_int64 *chunksize, sion_int32 *fsblksize, int *globalrank, FILE **fileptr, char *newfname);

  /* for file check */
  typedef struct _sion_file_check_par_args_mpi_struct sion_file_check_par_args_mpi;
  sion_file_check_par_args_mpi *lsion_file_check_par_args_init_mpi( const char     *file_mode,
								   MPI_Comm        gComm, 
								   int             numfiles, 
								   MPI_Comm        lComm 
								   );
  int lsion_file_check_par_args_free_mpi( sion_file_check_par_args_mpi *args );
  int lsion_file_check_par_cb_mpi( char *fname, void *args );

#ifdef __cplusplus
}
#endif

#endif

#endif
