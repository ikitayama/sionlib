/****************************************************************************
**  SIONLIB     http://www.fz-juelich.de/jsc/sionlib                       **
*****************************************************************************
**  Copyright (c) 2008-2019                                                **
**  Forschungszentrum Juelich, Juelich Supercomputing Centre               **
**                                                                         **
**  See the file COPYRIGHT in the package base directory for details       **
****************************************************************************/

/*!
 * @file
 *
 * @author David Montoya
 */


#define _XOPEN_SOURCE 700

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <sion_debug.h>
#include <sion_fd.h>


#ifdef SION_OMP
#define SION_OMPLOCK
#else
#ifdef SION_OMPI
#define SION_OMPLOCK
#endif
#endif


#ifdef SION_OMPLOCK
#include "omp.h"

static int _lsion_opmi_first_lock = 1;

void _lsion_par_init_debug(void){
	#pragma omp critical
		{

			if(_lsion_opmi_first_lock){
				_lsion_opmi_first_lock = 0;
				_lsion_debug_init();
			}

		}
}


#else

void _sion_par_init_lock(void){

}

#endif



