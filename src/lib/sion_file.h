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

#ifndef SION_SION_FILE_H
#define SION_SION_FILE_H

#include <stdio.h>

#include "sion_const.h"
#include "sion_datatypes.h"

#define SION_FILE_FLAG_ANSI       1          /*!< ANSI fileptr available */
#define SION_FILE_FLAG_SCNDANSI   2          /*!< ANSI second fileptr available */
#define SION_FILE_FLAG_POSIX      4          /*!< POSIX file pointer available */
#define SION_FILE_FLAG_CREATE     8          /*!< create file */
#define SION_FILE_FLAG_WRITE     16          /*!< write mode */
#define SION_FILE_FLAG_READ      32          /*!< read mode */
#define SION_FILE_FLAG_SIONFWD   64          /*!< SIONfwd file descriptor available */

struct _sion_fileptr_s {
  unsigned int flags;
  FILE *fileptr;
  FILE *second_fileptr;
  int fd;
  sion_int64 position;
};
typedef struct _sion_fileptr_s _sion_fileptr;

/* open/close */
_sion_fileptr   *_lsion_file_open(const char *fname, unsigned int flags, unsigned int addflags);
int              _lsion_file_close( _sion_fileptr *sion_fileptr );

/* write/read */
sion_int64       _lsion_file_write(const void *data, sion_int64 bytes, _sion_fileptr *sion_fileptr );
sion_int64       _lsion_file_read(void *data, sion_int64 bytes, _sion_fileptr *sion_fileptr );

/* utility */
int              _lsion_file_set_second_fileptr( _sion_fileptr *sion_fileptr, FILE* fileptr);
int              _lsion_file_unset_second_fileptr( _sion_fileptr *sion_fileptr);
long             _lsion_file_get_opt_blksize( _sion_fileptr *fileptr);
int              _lsion_file_stat_file(const char *fname);
int              _lsion_file_stat_file2(const char *fname, unsigned int apiflag);

sion_int64       _lsion_file_set_position(_sion_fileptr *fileptr, sion_int64 startpointer);
sion_int64       _lsion_file_get_position(_sion_fileptr *fileptr);

int            _lsion_file_flush(_sion_fileptr *fileptr);
int            _lsion_file_purge(_sion_fileptr *fileptr);

int            _lsion_file_set_buffer(_sion_fileptr *fileptr, char *buffer, sion_int32 buffer_size);
int            _lsion_file_get_fd( _sion_fileptr *sion_fileptr);


/* ********************************************************************************************** */
/* *** Internal INTERFACE Functions (ANSI, POSIX)                                                 */
/* ********************************************************************************************** */
FILE  *_lsion_file_open_ansi_write_create(const char *fname, unsigned int addflags);
FILE  *_lsion_file_open_ansi_write_existing(const char *fname, unsigned int addflags);
FILE  *_lsion_file_open_ansi_read(const char *fname, unsigned int addflags);
int    _lsion_file_close_ansi(FILE *fileptr);
long   _lsion_file_get_opt_blksize_ansi( FILE *fileptr);
sion_int64 _lsion_file_set_position_ansi(FILE *fileptr, sion_int64 startpointer);
sion_int64 _lsion_file_get_position_ansi(FILE *fileptr);
int _lsion_file_flush_ansi(FILE *fileptr);
int _lsion_file_purge_ansi(FILE *fileptr);
int _lsion_file_set_buffer_ansi(FILE *fileptr, char *buffer, sion_int32 buffer_size);
sion_int64  _lsion_file_write_ansi(const void *data, sion_int64 bytes, FILE *fileptr );
sion_int64  _lsion_file_read_ansi(void *data, sion_int64 bytes, FILE *fileptr );

int  _lsion_file_open_posix_write_create(const char *fname, unsigned int addflags);
int  _lsion_file_open_posix_write_existing(const char *fname, unsigned int addflags);
int  _lsion_file_open_posix_read(const char *fname, unsigned int addflags);
int  _lsion_file_close_posix(int fd);
long _lsion_file_get_opt_blksize_posix( int fd);
sion_int64 _lsion_file_set_position_posix(int fd, sion_int64 startpointer);
sion_int64 _lsion_file_get_position_posix(int fd);
int _lsion_file_flush_posix(int fd);
int _lsion_file_purge_posix(int fd);
int _lsion_file_set_buffer_posix(int fd, char *buffer, sion_int32 buffer_size);
sion_int64  _lsion_file_write_posix(const void *data, sion_int64 bytes, int fd );
sion_int64  _lsion_file_read_posix(void *data, sion_int64 bytes, int fd );

#if defined(_SION_SIONFWD)
int _sion_file_open_sionfwd_write_create(const char *fname, unsigned int addflags);
int _sion_file_open_sionfwd_write_existing(const char *fname, unsigned int addflags);
int _sion_file_open_sionfwd_read(const char *fname, unsigned int addflags);
int _sion_file_close_sionfwd(int fd);
long _sion_file_get_opt_blksize_sionfwd(int fd);
int _sion_file_flush_sionfwd(int fd);
int _sion_file_purge_sionfwd(int fd);
int _sion_file_set_buffer_sionfwd(int fd, char *buffer, sion_int32 buffer_size);
sion_int64 _sion_file_write_sionfwd(const void *data, sion_int64 bytes, int fd, sion_int64 *position);
sion_int64 _sion_file_read_sionfwd(void *data, sion_int64 bytes, int fd, sion_int64 *position);
#endif

/* ********************************************************************************************** */
/* *** Internal Utility Functions                                                                 */
/* ********************************************************************************************** */
_sion_fileptr *_lsion_file_alloc_and_init_sion_fileptr(void);
char* _lsion_get_fileptr_desc(_sion_fileptr *sion_fileptr);


#endif
