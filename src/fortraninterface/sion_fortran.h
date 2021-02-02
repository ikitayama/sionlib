/****************************************************************************
**  SIONLIB     http://www.fz-juelich.de/jsc/sionlib                       **
*****************************************************************************
**  Copyright (c) 2008-2019                                                **
**  Forschungszentrum Juelich, Juelich Supercomputing Centre               **
**                                                                         **
**  See the file COPYRIGHT in the package base directory for details       **
****************************************************************************/
#ifndef SION_FORTRAN_H_
#define SION_FORTRAN_H_

#include "sion.h"

/*!
 * @file sion_fortran.h
 * @brief Fortran API
 * @author Ventsislav Petkov
 * @date 14.08.2008
 * @date 03.05.2013 modifications to support different Fortran interfaces, Florian Janetzko
 */

/* lsion_open() */
#if defined(_FORTRANCAPS)
#define lfsion_open_c LFSION_OPEN_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_open_c lfsion_open_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_open_c lfsion_open_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_open_c lfsion_open_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_open_c(char *fname,
		  char *file_mode,
		  int  *ntasks,
		  int  *nfiles,
		  sion_int64  *chunksizes,
		  sion_int32  *fsblksize,
		  int  *globalranks,
		  int  *sid,
		  int  fname_len,
		  int  file_mode_len);

/* lsion_open_rank() */
#if defined(_FORTRANCAPS)
#define lfsion_open_rank_c LFSION_OPEN_RANK_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_open_rank_c lfsion_open_rank_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_open_rank_c lfsion_open_rank_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_open_rank_c lfsion_open_rank_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_open_rank_c(char *fname,
                       char *file_mode,
		       sion_int64 *chunksize,
		       sion_int32 *fsblksize,
		       int  *rank,
		       int  *sid,
		       int  fname_len,
		       int  file_mode_len);

/* lsion_close() */
#if defined(_FORTRANCAPS)
#define lfsion_close_c LFSION_CLOSE_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_close_c lfsion_close_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_close_c lfsion_close_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_close_c lfsion_close_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_close_c(int *sid, 
                   int *ierr);

/* lsion_feof() */
#if defined(_FORTRANCAPS)
#define lfsion_feof_c LFSION_FEOF_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_feof_c lfsion_feof_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_feof_c lfsion_feof_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_feof_c lfsion_feof_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_feof_c(int *sid, 
                  int *eof);

/* lsion_seek() */
#if defined(_FORTRANCAPS)
#define lfsion_seek_c LFSION_SEEK_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_seek_c lfsion_seek_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_seek_c lfsion_seek_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_seek_c fsion_seek_C__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_seek_c(int *sid,
		  int *rank,
		  int *currentblocknr,
		  sion_int64 *posinblk,
		  int *ierr);

/* lsion_ensure_free_space() */
#if defined(_FORTRANCAPS)
#define lfsion_ensure_free_space_c LFSION_ENSURE_FREE_SPACE_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_ensure_free_space_c lfsion_ensure_free_space_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_ensure_free_space_c lfsion_ensure_free_space_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_ensure_free_space_c lfsion_ensure_free_space_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_ensure_free_space_c(int *sid, 
                               sion_int64 *bytes, 
                               int *ierr);

/* lsion_flush() */
#if defined(_FORTRANCAPS)
#define lfsion_flush_c LFSION_FLUSH_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_flush_c lfsion_flush_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_flush_c lfsion_flush_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_flush_c lfsion_flush_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_flush_c(int *sid, 
                   int *ierr);

/* lsion_bytes_avail_in_block() */
#if defined(_FORTRANCAPS)
#define lfsion_bytes_avail_in_block_c LFSION_BYTES_AVAIL_IN_BLOCK_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_bytes_avail_in_block_c lfsion_bytes_avail_in_block_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_bytes_avail_in_block_c lfsion_bytes_avail_in_block_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_bytes_avail_in_block_c lfsion_bytes_avail_in_block_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
sion_int64 lfsion_bytes_avail_in_block_c(int *sid);

/* lsion_get_locations() */
#if defined(_FORTRANCAPS)
#define lfsion_get_locations_c LFSION_GET_LOCATIONS_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_get_locations_c lfsion_get_locations_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_get_locations_c lfsion_get_locations_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_get_locations_c lfsion_get_locations_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_get_locations_c(int *sid,
			   int *ntasks,
			   int *maxblocks,
			   sion_int64 *globalskip,
			   sion_int64 *start_of_varheader,
			   sion_int64 **sion_chunksizes,
			   sion_int64 **sion_globalranks,
			   sion_int64 **sion_blockcount,
			   sion_int64 **sion_fsblksizes,
			   int *ierr);

/* lsion_get_current_locations() */
#if defined(_FORTRANCAPS)
#define lfsion_get_current_locations_c LFSION_GET_CURRENT_LOCATIONS_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_get_current_locations_c lfsion_get_current_locations_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_get_current_locations_c lfsion_get_current_locations_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_get_current_locations_c lfsion_get_current_locations_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_get_current_locations_c(int *sid,
				   int *ntasks,
				   sion_int64 **sion_currentpos,
				   sion_int64 **sion_currentblocknr,
				   int *ierr);

/* sion_get_chunksizes() */
#if defined(_FORTRANCAPS)
#define lfsion_get_chunksizes_c LFSION_GET_CHUNKSIZES_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_get_chunksizes_c lfsion_get_chunksizes_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_get_chunksizes_c lfsion_get_chunksizes_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_get_chunksizes_c lfsion_get_chunksizes_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_get_chunksizes_c(int *sid,
			    sion_int64  *chunksizes, 
			    int *ierr);

/* sion_get_globalranks() */
#if defined(_FORTRANCAPS)
#define lfsion_get_globalranks_c LFSION_GET_GLOBALRANKS_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_get_globalranks_c lfsion_get_globalranks_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_get_globalranks_c lfsion_get_globalranks_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_get_globalranks_c lfsion_get_globalranks_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_get_globalranks_c(int *sid,
			     int *globalranks, 
			     int *ierr);

/* sion_get_mapping_spec() */
#if defined(_FORTRANCAPS)
#define lfsion_get_mapping_spec_c LFSION_GET_MAPPING_SPEC_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_get_mapping_spec_c lfsion_get_mapping_spec_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_get_mapping_spec_c lfsion_get_mapping_spec_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_get_mapping_spec_c lfsion_get_mapping_spec_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_get_mapping_spec_c(int *sid,
			      int *mapping_size, 
			      int *numfiles, 
			      int *ierr);

/* lsion_get_mapping() */
#if defined(_FORTRANCAPS)
#define lfsion_get_mapping_c LFSION_GET_MAPPING_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_get_mapping_c lfsion_get_mapping_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_get_mapping_c lfsion_get_mapping_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_get_mapping_c lfsion_get_mapping_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_get_mapping_c(int *sid, 
		         sion_int32 *mapping, 
		         int *ierr);

/* lsion_get_position() */
#if defined(_FORTRANCAPS)
#define lfsion_get_position_c LFSION_GET_POSITION_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_get_position_c lfsion_get_position_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_get_position_c lfsion_get_position_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_get_position_c lfsion_get_position_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
sion_int64 lfsion_get_position_c(int *sid);

/* sion_get_fileno() */
#if defined(_FORTRANCAPS)
#define lfsion_get_fileno_c LFSION_GET_FILENO_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_get_fileno_c lfsion_get_fileno_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_get_fileno_c lfsion_get_fileno_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_get_fileno_c lfsion_get_fileno_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_get_fileno_c(int *sid, 
                        int *filenumber);

/* lsion_set_fp_closed() */
#if defined(_FORTRANCAPS)
#define fsion_set_fp_closed_c FSION_SET_FP_CLOSED_C

#elif defined(_FORTRANNOCAPS)
#define fsion_set_fp_closed_c fsion_set_fp_closed_c

#elif defined(_FORTRANUNDERSCORE)
#define fsion_set_fp_closed_c fsion_set_fp_closed_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define fsion_set_fp_closed_c fsion_set_fp_closed_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void fsion_set_fp_closed_c(int *sid, 
                           int *ierr);

/* lsion_get_file_endianness() */
#if defined(_FORTRANCAPS)
#define lfsion_get_file_endianness_c LFSION_GET_FILE_ENDIANNESS_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_get_file_endianness_c lfsion_get_file_endianness_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_get_file_endianness_c lfsion_get_file_endianness_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_get_file_endianness_c lfsion_get_file_endianness_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_get_file_endianness_c(int *sid, 
                                 int *endianness);

/* lsion_get_endianness() */
#if defined(_FORTRANCAPS)
#define lfsion_get_endianness_c LFSION_GET_ENDIANNESS_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_get_endianness_c lfsion_get_endianness_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_get_endianness_c lfsion_get_endianness_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_get_endianness_c lfsion_get_endianness_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_get_endianness_c(int *filenumber);

/* lsion_endianness_swap_needed() */
#if defined(_FORTRANCAPS)
#define lfsion_endianness_swap_needed_c LFSION_ENDIANNESS_SWAP_NEEDED_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_endianness_swap_needed_c lfsion_endianness_swap_needed_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_endianness_swap_needed_c lfsion_endianness_swap_needed_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_endianness_swap_needed_c lfsion_endianness_swap_needed_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_endianness_swap_needed_c(int *sid,
                                    int *needed);

/* lsion_swap() */
#if defined(_FORTRANCAPS)
#define lfsion_swap_c LFSION_SWAP_C

#elif defined(_FORTRANNOCAPS)
#define lfsion_swap_c lfsion_swap_c

#elif defined(_FORTRANUNDERSCORE)
#define lfsion_swap_c lfsion_swap_c_

#elif defined(_FORTRANDOUBLEUNDERSCORE)
#define lfsion_swap_c lfsion_swap_c__

#elif defined(_FORTRANNOUNDERSCORE)
#else
#error nothing defined for fortran externals
#endif
void lfsion_swap_c(void *target, 
                  void *source, 
                  int *size, 
                  int *n, 
                  int *do_swap, 
                  int *rc);

/* endianness FIX */
#define SWAP_2(x) ( (((x) & 0xff) << 8) | ((unsigned short)(x) >> 8) )
#define SWAP_4(x) ( ((x) << 24) | (((x) << 8) & 0x00ff0000) | \
         (((x) >> 8) & 0x0000ff00) | ((x) >> 24) )
#define FIX_SHORT(x) (*(unsigned short *)&(x) = SWAP_2(*(unsigned short *)&(x)))
#define FIX_LONG(x) (*(unsigned *)&(x) = SWAP_4(*(unsigned *)&(x)))
#define FIX_FLOAT(x) FIX_LONG(x)

#endif /* SION_FORTRAN_H_ */
