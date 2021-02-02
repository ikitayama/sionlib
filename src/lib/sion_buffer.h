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

#ifndef SION_SION_BUFFER_H
#define SION_SION_BUFFER_H

#include "sion_const.h"
#include "sion_filedesc.h"

int  _lsion_buffer_check_env(_sion_filedesc *sion_filedesc);


int  _lsion_buffer_init(_sion_filedesc *sion_filedesc);


sion_int64 _lsion_buffer_push(_sion_filedesc *sion_filedesc,
			     const void *data, sion_int64 bytes);

int _lsion_buffer_get_data_ptr(_sion_filedesc *sion_filedesc,
			      void **data, sion_int64 *bytes);

int _lsion_buffer_flush(_sion_filedesc *sion_filedesc);

#endif
