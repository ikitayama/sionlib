/****************************************************************************
**  SIONLIB     http://www.fz-juelich.de/jsc/sionlib                       **
*****************************************************************************
**  Copyright (c) 2008-2019                                                **
**  Forschungszentrum Juelich, Juelich Supercomputing Centre               **
**                                                                         **
**  See the file COPYRIGHT in the package base directory for details       **
****************************************************************************/
#ifndef SION_SION_GENERIC_BUDDY_H
#define SION_SION_GENERIC_BUDDY_H

#include "sion_const.h"
#include "sion_buddy_common.h"
#include "sion_generic_apidesc.h"
#include "sion_flags.h"

int _lsion_paropen_generic_buddy(
				int sid,
				const char  *fname,
				_sion_flags_store *flags_store,
				char  *prefix,
				int   *numFiles,
				int   *filenumber, 
				sion_int64  *chunksize,
				sion_int32  *fsblksize,
				int    rank,
				int    ntasks,
				int   *globalrank,
				FILE **fileptr,
				_sion_generic_gendata *sion_gendata );

int _lsion_parclose_generic_buddy(int sid,
				 int rank,
				 int ntasks,
				 int mapping_size,
				 sion_int32 *mapping,
				_sion_generic_gendata *sion_gendata );

int _lsion_coll_fwrite_buddy(const void *data, 
			    size_t size, 
			    size_t nitems, 
			    int sid,
			    _sion_generic_gendata *sion_gendata );

int _lsion_coll_fread_buddy(void *data, 
			    size_t size, 
			    size_t nitems, 
			    int sid);

int _lsion_buddy_map(
		    _sion_generic_gendata *sion_gendata,
		    int capability,
		    int buddy_idx,
		    _sion_generic_buddy_info *buddy_send,
		    _sion_generic_buddy_info *buddy_coll );

int _lsion_buddy_bwsched(int groupnr, int numgroups, int pass);

int _lsion_generic_collect_mapping_buddy(  _sion_generic_buddy   *buddyptr,
					  _sion_generic_gendata *sion_gendata,
					  int                   *mapping_size,
					  sion_int32           **mapping);

int _lsion_generic_buddy_get_and_distribute_info_from_file(  _sion_generic_gendata *sion_gendata, char *fname, int root,
							    sion_int32 *filenumber, sion_int32 *numfiles, sion_int32 *lrank, sion_int32 *lsize);

int _lsion_generic_buddy_get_and_distribute_info_from_one_file(  _sion_generic_gendata *sion_gendata, char *fname, int root,
								sion_int32 *filenumber, sion_int32 *numfiles, 
								sion_int32 *lrank, sion_int32 *lsize);

char* _lsion_buddy_role_to_str (unsigned int flag);

#endif
