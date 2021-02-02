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

#ifndef SION_SION_CACHE_H
#define SION_SION_CACHE_H

#include "sion_const.h"
#include "sion_filedesc.h"

int  _lsion_cache_check_env(_sion_filedesc *sion_filedesc);

int  _lsion_cache_init(_sion_filedesc *sion_filedesc);

int  _lsion_cache_destroy(_sion_filedesc *sion_filedesc);


/* internal */
int  _lsion_cache_create_linux(_sion_filedesc *sion_filedesc);
int  _lsion_cache_load_linux(_sion_filedesc *sion_filedesc);
int  _lsion_cache_destroy_linux(_sion_filedesc *sion_filedesc);

#endif
