#include "sion_const.h"

!*****************************************************************************
!**  SIONLIB     http://www.fz-juelich.de/jsc/sionlib                       **
!*****************************************************************************
!**  Copyright (c) 2008-2019                                                **
!**  Forschungszentrum Juelich, Juelich Supercomputing Centre               **
!**                                                                         **
!**  See the file COPYRIGHT in the package base directory for details       **
!*****************************************************************************

!*****************************************************************************
!** Module file of Fortran 90 interface to SIONlib                          **
!*****************************************************************************
!*
!* @file sion_f90.f90
!*
!* @brief Fortran90 interface
!*
!* @author Florian Janetzko
!* @date 03.05.2013
!*
module sion_f90

  implicit none

!****************************
!* SION version information *
!****************************
  integer, parameter :: sion_main_version       = SION_MAIN_VERSION
  integer, parameter :: sion_sub_version        = SION_SUB_VERSION
  integer, parameter :: sion_version_patchlevel = SION_VERSION_PATCHLEVEL
  integer, parameter :: sion_fileformat_version = SION_FILEFORMAT_VERSION

!******************
!* SION constants *
!******************
  integer,   parameter :: sion_current_rank  = SION_CURRENT_RANK
  integer,   parameter :: sion_current_blk   = SION_CURRENT_BLK
  integer,   parameter :: sion_current_chunk = SION_CURRENT_CHUNK
  integer*8, parameter :: sion_current_pos   = SION_CURRENT_POS
  integer,   parameter :: sion_absolute_pos  = SION_ABSOLUTE_POS
  integer,   parameter :: sion_success       = SION_SUCCESS

!************************************************************
!* Explicit interfaces to C void functions with overloading *
!************************************************************
  interface lfsion_swap
    module procedure lfsion_swap_integer
    module procedure lfsion_swap_integer8
    module procedure lfsion_swap_real
    module procedure lfsion_swap_double_precision
    module procedure lfsion_swap_complex
    module procedure lfsion_swap_logical
    module procedure lfsion_swap_character
  end interface lfsion_swap

  interface lfsion_write
    module procedure lfsion_write_integer
    module procedure lfsion_write_integer8
    module procedure lfsion_write_real
    module procedure lfsion_write_double_precision
    module procedure lfsion_write_complex
    module procedure lfsion_write_logical
    module procedure lfsion_write_character
  end interface lfsion_write

  interface lfsion_fwrite
    module procedure lfsion_fwrite_integer
    module procedure lfsion_fwrite_integer8
    module procedure lfsion_fwrite_real
    module procedure lfsion_fwrite_double_precision
    module procedure lfsion_fwrite_complex
    module procedure lfsion_fwrite_logical
    module procedure lfsion_fwrite_character
  end interface lfsion_fwrite

  interface lfsion_read
    module procedure lfsion_read_integer
    module procedure lfsion_read_integer8
    module procedure lfsion_read_real
    module procedure lfsion_read_double_precision
    module procedure lfsion_read_complex
    module procedure lfsion_read_logical
    module procedure lfsion_read_character
  end interface lfsion_read

  interface lfsion_fread
    module procedure lfsion_fread_integer
    module procedure lfsion_fread_integer8
    module procedure lfsion_fread_real
    module procedure lfsion_fread_double_precision
    module procedure lfsion_fread_complex
    module procedure lfsion_fread_logical
    module procedure lfsion_fread_character
  end interface lfsion_fread

!***********************************************
!* Fortran interface subroutines and functions *
!***********************************************
contains
! Subroutines (without overloading)
  subroutine lfsion_open(fname,file_mode,ntasks,nfiles,chunksizes,fsblksize,globalranks,sid)

    implicit none 

    character(len=*), intent(in)    :: fname
    character(len=*), intent(inout) :: file_mode
    integer, intent(in)             :: ntasks
    integer, intent(in)             :: nfiles
    integer*8, intent(inout)        :: chunksizes
    integer*4, intent(inout)        :: fsblksize
    integer, intent(in)             :: globalranks
    integer, intent(out)            :: sid

    call lfsion_open_c(fname,file_mode,ntasks,nfiles,chunksizes,fsblksize,globalranks,sid)
  end subroutine lfsion_open

  subroutine lfsion_open_rank(fname,file_mode,chunksize,fsblksize,rank,sid)

    implicit none

    character(len=*), intent(in)    :: fname
    character(len=*), intent(inout) :: file_mode
    integer*8, intent(inout)        :: chunksize
    integer*4, intent(inout)        :: fsblksize
    integer, intent(in)             :: rank
    integer, intent(out)            :: sid

    call lfsion_open_rank_c(fname,file_mode,chunksize,fsblksize,rank,sid)
  end subroutine lfsion_open_rank

  subroutine lfsion_close(sid,ierr)

    implicit none

    integer, intent(in)             :: sid
    integer, intent(out)            :: ierr

    call lfsion_close_c(sid,ierr)
  end subroutine lfsion_close

  subroutine lfsion_feof(sid,eof)

    implicit none

    integer, intent(in)             :: sid
    integer, intent(out)            :: eof

    call lfsion_feof_c(sid,eof)
  end subroutine lfsion_feof

  subroutine lfsion_seek(sid,rank,currentblocknr,posinblk,ierr)

    implicit none

    integer, intent(in)             :: sid
    integer, intent(in)             :: rank
    integer, intent(in)             :: currentblocknr
    integer*8, intent(in)           :: posinblk
    integer, intent(out)            :: ierr

    call lfsion_seek_c(sid,rank,currentblocknr,posinblk,ierr)
  end subroutine lfsion_seek

  subroutine lfsion_ensure_free_space(sid,bytes,ierr)

    implicit none

    integer, intent(in)             :: sid
    integer*8, intent(in)           :: bytes
    integer, intent(out)            :: ierr

    call lfsion_ensure_free_space_c(sid,bytes,ierr)
  end subroutine lfsion_ensure_free_space

  subroutine lfsion_flush(sid,ierr)

    implicit none

    integer, intent(in)             :: sid
    integer, intent(out)            :: ierr

    call lfsion_flush_c(sid,ierr)
  end subroutine lfsion_flush

  subroutine lfsion_get_locations(sid,ntasks,maxblocks,globalskip,start_of_varheader,&
&                                sion_localsizes,sion_globalranks,sion_chunkcount,sion_chunksizes,ierr)

    implicit none

    integer, intent(in)             :: sid
    integer, intent(out)            :: ntasks
    integer, intent(out)            :: maxblocks
    integer*8, intent(out)          :: globalskip
    integer*8, intent(out)          :: start_of_varheader
    integer*8, intent(out)          :: sion_localsizes
    integer*8, intent(out)          :: sion_globalranks
    integer*8, intent(out)          :: sion_chunkcount
    integer*8, intent(out)          :: sion_chunksizes
    integer, intent(out)            :: ierr

    call lfsion_get_locations_c(sid,ntasks,maxblocks,globalskip,start_of_varheader,&
&                              sion_localsizes,sion_globalranks,sion_chunkcount,sion_chunksizes,ierr)
  end subroutine lfsion_get_locations

  subroutine lfsion_get_current_locations(sid,ntasks,sion_currentpos,sion_currentblocknr,ierr)

    implicit none

    integer, intent(in)             :: sid
    integer, intent(out)            :: ntasks
    integer*8, intent(out)          :: sion_currentpos
    integer*8, intent(out)          :: sion_currentblocknr
    integer, intent(out)            :: ierr

    call lfsion_get_current_locations_c(sid,ntasks,sion_currentpos,sion_currentblocknr,ierr)
  end subroutine

  subroutine lfsion_get_chunksizes(sid,chunksizes,ierr)

    implicit none

    integer, intent(in)             :: sid
    integer*8, intent(out)          :: chunksizes
    integer, intent(out)            :: ierr 

    call lfsion_get_chunksizes_c(sid,chunksizes,ierr)
  end subroutine lfsion_get_chunksizes

  subroutine lfsion_get_globalranks(sid,globalranks,ierr)

    implicit none

    integer, intent(in)             :: sid
    integer, intent(out)            :: globalranks
    integer, intent(out)            :: ierr

    call lfsion_get_globalranks_c(sid,globalranks,ierr)
  end subroutine lfsion_get_globalranks

  subroutine lfsion_get_mapping_spec(sid,mapping_size,numfiles,ierr)

    implicit none

    integer, intent(in)             :: sid
    integer, intent(out)            :: mapping_size
    integer, intent(out)            :: numfiles
    integer, intent(out)            :: ierr

    call lfsion_get_mapping_spec_c(sid,mapping_size,numfiles,ierr)
  end subroutine lfsion_get_mapping_spec

  subroutine lfsion_get_mapping(sid,mapping,ierr)

    implicit none

    integer, intent(in)             :: sid
    integer*4, intent(out)          :: mapping
    integer, intent(out)            :: ierr

    call lfsion_get_mapping_c(sid,mapping,ierr)
  end subroutine lfsion_get_mapping

  subroutine lfsion_get_fileno(sid,filenumber)

    implicit none

    integer, intent(in)             :: sid
    integer, intent(out)            :: filenumber    

    call lfsion_get_fileno_c(sid,filenumber)
  end subroutine lfsion_get_fileno

  subroutine lfsion_get_file_endianess(sid,endianness)

    implicit none

    integer, intent(in)             :: sid
    integer, intent(out)            :: endianness

    call lfsion_get_file_endianness_c(sid,endianness)
  end subroutine lfsion_get_file_endianess

  subroutine lfsion_get_file_endianness(sid,endianness)

    implicit none

    integer, intent(in)             :: sid
    integer, intent(out)            :: endianness

    call lfsion_get_file_endianness_c(sid,endianness)
  end subroutine lfsion_get_file_endianness

  subroutine lfsion_get_endianess(endianness)

    implicit none

    integer, intent(out)            :: endianness

    call lfsion_get_endianness_c(endianness)
  end subroutine lfsion_get_endianess

  subroutine lfsion_get_endianness(endianness)

    implicit none

    integer, intent(out)            :: endianness

    call lfsion_get_endianness_c(endianness)
  end subroutine lfsion_get_endianness

  subroutine lfsion_endianness_swap_needed(sid,needed)

    implicit none

    integer, intent(in)             :: sid
    integer, intent(out)            :: needed

    call lfsion_endianness_swap_needed_c(sid,needed)
  end subroutine lfsion_endianness_swap_needed

! Functions (without overloading)
  function lfsion_bytes_avail_in_block(sid)

    implicit none

    integer*8                       :: lfsion_bytes_avail_in_block
    integer*8                       :: lfsion_bytes_avail_in_block_c
    integer, intent(in)             :: sid

    lfsion_bytes_avail_in_block = lfsion_bytes_avail_in_block_c(sid)
  end function lfsion_bytes_avail_in_block

  function lfsion_get_position(sid)

    implicit none

    integer*8                       :: lfsion_get_position
    integer*8                       :: lfsion_get_position_c
    integer, intent(in)             :: sid

    lfsion_get_position = lfsion_get_position_c(sid)
  end function lfsion_get_position

! Subroutines (with overloading)
! lfsion_swap
  subroutine lfsion_swap_integer(target,source,size,n,do_swap,rc)

    implicit none

    integer, intent (inout)         :: target
    integer, intent (in)            :: source
    integer, intent (in)            :: size
    integer, intent (in)            :: n
    integer, intent (in)            :: do_swap
    integer, intent (in)            :: rc

    call lfsion_swap_c(target,source,size,n,do_swap,rc) 
  end subroutine lfsion_swap_integer
  subroutine lfsion_swap_integer8(target,source,size,n,do_swap,rc)

    implicit none

    integer*8, intent (inout)       :: target
    integer*8, intent (in)          :: source
    integer, intent (in)            :: size
    integer, intent (in)            :: n
    integer, intent (in)            :: do_swap
    integer, intent (in)            :: rc

    call lfsion_swap_c(target,source,size,n,do_swap,rc) 
  end subroutine lfsion_swap_integer8
  subroutine lfsion_swap_real(target,source,size,n,do_swap,rc)

    implicit none

    real, intent (inout)            :: target
    real, intent (in)               :: source
    integer, intent (in)            :: size
    integer, intent (in)            :: n
    integer, intent (in)            :: do_swap
    integer, intent (in)            :: rc

    call lfsion_swap_c(target,source,size,n,do_swap,rc) 
  end subroutine lfsion_swap_real
  subroutine lfsion_swap_double_precision(target,source,size,n,do_swap,rc)

    implicit none

    double precision, intent (inout):: target
    double precision, intent (in)   :: source
    integer, intent (in)            :: size
    integer, intent (in)            :: n
    integer, intent (in)            :: do_swap
    integer, intent (in)            :: rc

    call lfsion_swap_c(target,source,size,n,do_swap,rc) 
  end subroutine lfsion_swap_double_precision
  subroutine lfsion_swap_complex(target,source,size,n,do_swap,rc)

    implicit none

    complex, intent (inout)         :: target
    complex, intent (in)            :: source
    integer, intent (in)            :: size
    integer, intent (in)            :: n
    integer, intent (in)            :: do_swap
    integer, intent (in)            :: rc

    call lfsion_swap_c(target,source,size,n,do_swap,rc) 
  end subroutine lfsion_swap_complex
  subroutine lfsion_swap_logical(target,source,size,n,do_swap,rc)

    implicit none

    logical, intent (inout)         :: target
    logical, intent (in)            :: source
    integer, intent (in)            :: size
    integer, intent (in)            :: n
    integer, intent (in)            :: do_swap
    integer, intent (in)            :: rc

    call lfsion_swap_c(target,source,size,n,do_swap,rc) 
  end subroutine lfsion_swap_logical
  subroutine lfsion_swap_character(target,source,size,n,do_swap,rc)

    implicit none

    character(len=*), intent (inout):: target
    character(len=*), intent (in)   :: source
    integer, intent (in)            :: size
    integer, intent (in)            :: n
    integer, intent (in)            :: do_swap
    integer, intent (in)            :: rc

    call lfsion_swap_c(target,source,size,n,do_swap,rc) 
  end subroutine lfsion_swap_character

! lfsion_write
  subroutine lfsion_write_integer(data,size,nitems,sid,rc)

    implicit none

    integer, intent (in)            :: data
    integer*8, intent(in)           :: size  
    integer*8, intent(in)           :: nitems  
    integer, intent(in)             :: sid  
    integer*8, intent(out)          :: rc  

    call lfsion_write_c(data,size,nitems,sid,rc)
  end subroutine lfsion_write_integer
  subroutine lfsion_write_integer8(data,size,nitems,sid,rc)

    implicit none

    integer*8, intent(in)           :: data
    integer*8, intent(in)           :: size  
    integer*8, intent(in)           :: nitems  
    integer, intent(in)             :: sid  
    integer*8, intent(out)          :: rc  

    call lfsion_write_c(data,size,nitems,sid,rc)
  end subroutine lfsion_write_integer8
  subroutine lfsion_write_real(data,size,nitems,sid,rc)

    implicit none

    real, intent (in)               :: data
    integer*8, intent(in)           :: size
    integer*8, intent(in)           :: nitems
    integer, intent(in)             :: sid
    integer*8, intent(out)          :: rc

    call lfsion_write_c(data,size,nitems,sid,rc)
  end subroutine lfsion_write_real
  subroutine lfsion_write_double_precision(data,size,nitems,sid,rc)

    implicit none

    double precision, intent (in)   :: data
    integer*8, intent(in)           :: size
    integer*8, intent(in)           :: nitems
    integer, intent(in)             :: sid
    integer*8, intent(out)          :: rc

    call lfsion_write_c(data,size,nitems,sid,rc)
  end subroutine lfsion_write_double_precision
  subroutine lfsion_write_complex(data,size,nitems,sid,rc)

    implicit none

    complex, intent (in)            :: data
    integer*8, intent(in)           :: size
    integer*8, intent(in)           :: nitems
    integer, intent(in)             :: sid
    integer*8, intent(out)          :: rc

    call lfsion_write_c(data,size,nitems,sid,rc)
  end subroutine lfsion_write_complex
  subroutine lfsion_write_logical(data,size,nitems,sid,rc)

    implicit none

    logical, intent (in)            :: data
    integer*8, intent(in)           :: size
    integer*8, intent(in)           :: nitems
    integer, intent(in)             :: sid
    integer*8, intent(out)          :: rc

    call lfsion_write_c(data,size,nitems,sid,rc)
  end subroutine lfsion_write_logical
  subroutine lfsion_write_character(data,size,nitems,sid,rc)

    implicit none

    character(len=*), intent (in)   :: data
    integer*8, intent(in)           :: size
    integer*8, intent(in)           :: nitems
    integer, intent(in)             :: sid
    integer*8, intent(out)          :: rc

    call lfsion_write_c(data,size,nitems,sid,rc)
  end subroutine lfsion_write_character

! lfsion_fwrite
  subroutine lfsion_fwrite_integer(data,size,nitems,sid,rc)

    implicit none

    integer, intent (in)            :: data
    integer*8, intent(in)           :: size  
    integer*8, intent(in)           :: nitems  
    integer, intent(in)             :: sid  
    integer*8, intent(out)          :: rc  

    call lfsion_fwrite_c(data,size,nitems,sid,rc)
  end subroutine lfsion_fwrite_integer
  subroutine lfsion_fwrite_integer8(data,size,nitems,sid,rc)

    implicit none

    integer*8, intent (in)          :: data
    integer*8, intent(in)           :: size  
    integer*8, intent(in)           :: nitems  
    integer, intent(in)             :: sid  
    integer*8, intent(out)          :: rc  

    call lfsion_fwrite_c(data,size,nitems,sid,rc)
  end subroutine lfsion_fwrite_integer8
  subroutine lfsion_fwrite_real(data,size,nitems,sid,rc)

    implicit none

    real, intent (in)               :: data
    integer*8, intent(in)           :: size
    integer*8, intent(in)           :: nitems
    integer, intent(in)             :: sid
    integer*8, intent(out)          :: rc

    call lfsion_fwrite_c(data,size,nitems,sid,rc)
  end subroutine lfsion_fwrite_real
  subroutine lfsion_fwrite_double_precision(data,size,nitems,sid,rc)

    implicit none

    double precision, intent (in)   :: data
    integer*8, intent(in)           :: size
    integer*8, intent(in)           :: nitems
    integer, intent(in)             :: sid
    integer*8, intent(out)          :: rc

    call lfsion_fwrite_c(data,size,nitems,sid,rc)
  end subroutine lfsion_fwrite_double_precision
  subroutine lfsion_fwrite_complex(data,size,nitems,sid,rc)

    implicit none

    complex, intent (in)            :: data
    integer*8, intent(in)           :: size
    integer*8, intent(in)           :: nitems
    integer, intent(in)             :: sid
    integer*8, intent(out)          :: rc

    call lfsion_fwrite_c(data,size,nitems,sid,rc)
  end subroutine lfsion_fwrite_complex
  subroutine lfsion_fwrite_logical(data,size,nitems,sid,rc)

    implicit none

    logical, intent (in)            :: data
    integer*8, intent(in)           :: size
    integer*8, intent(in)           :: nitems
    integer, intent(in)             :: sid
    integer*8, intent(out)          :: rc

    call lfsion_fwrite_c(data,size,nitems,sid,rc)
  end subroutine lfsion_fwrite_logical
  subroutine lfsion_fwrite_character(data,size,nitems,sid,rc)

    implicit none

    character(len=*), intent (in)   :: data
    integer*8, intent(in)           :: size
    integer*8, intent(in)           :: nitems
    integer, intent(in)             :: sid
    integer*8, intent(out)          :: rc

    call lfsion_fwrite_c(data,size,nitems,sid,rc)
  end subroutine lfsion_fwrite_character

! lfsion_read
  subroutine lfsion_read_integer(data,size,nitems,sid,rc)

    implicit none

    integer, intent (out)           :: data
    integer*8, intent(in)           :: size  
    integer*8, intent(in)           :: nitems  
    integer, intent(in)             :: sid  
    integer*8, intent(out)          :: rc  

    call lfsion_read_c(data,size,nitems,sid,rc)
  end subroutine lfsion_read_integer
  subroutine lfsion_read_integer8(data,size,nitems,sid,rc)

    implicit none

    integer*8, intent(out)           :: data
    integer*8, intent(in)           :: size  
    integer*8, intent(in)           :: nitems  
    integer, intent(in)             :: sid  
    integer*8, intent(out)          :: rc  

    call lfsion_read_c(data,size,nitems,sid,rc)
  end subroutine lfsion_read_integer8
  subroutine lfsion_read_real(data,size,nitems,sid,rc)

    implicit none

    real, intent (out)              :: data
    integer*8, intent(in)           :: size
    integer*8, intent(in)           :: nitems
    integer, intent(in)             :: sid
    integer*8, intent(out)          :: rc

    call lfsion_read_c(data,size,nitems,sid,rc)
  end subroutine lfsion_read_real
  subroutine lfsion_read_double_precision(data,size,nitems,sid,rc)

    implicit none

    double precision, intent (out)  :: data
    integer*8, intent(in)           :: size
    integer*8, intent(in)           :: nitems
    integer, intent(in)             :: sid
    integer*8, intent(out)          :: rc

    call lfsion_read_c(data,size,nitems,sid,rc)
  end subroutine lfsion_read_double_precision
  subroutine lfsion_read_complex(data,size,nitems,sid,rc)

    implicit none

    complex, intent (out)           :: data
    integer*8, intent(in)           :: size
    integer*8, intent(in)           :: nitems
    integer, intent(in)             :: sid
    integer*8, intent(out)          :: rc

    call lfsion_read_c(data,size,nitems,sid,rc)
  end subroutine lfsion_read_complex
  subroutine lfsion_read_logical(data,size,nitems,sid,rc)

    implicit none

    logical, intent (out)           :: data
    integer*8, intent(in)           :: size
    integer*8, intent(in)           :: nitems
    integer, intent(in)             :: sid
    integer*8, intent(out)          :: rc

    call lfsion_read_c(data,size,nitems,sid,rc)
  end subroutine lfsion_read_logical
  subroutine lfsion_read_character(data,size,nitems,sid,rc)

    implicit none

    character(len=*), intent (out)  :: data
    integer*8, intent(in)           :: size
    integer*8, intent(in)           :: nitems
    integer, intent(in)             :: sid
    integer*8, intent(out)          :: rc

    call lfsion_read_c(data,size,nitems,sid,rc)
  end subroutine lfsion_read_character

! lfsion_fread
  subroutine lfsion_fread_integer(data,size,nitems,sid,rc)

    implicit none

    integer, intent (out)           :: data
    integer*8, intent(in)           :: size  
    integer*8, intent(in)           :: nitems  
    integer, intent(in)             :: sid  
    integer*8, intent(out)          :: rc  

    call lfsion_fread_c(data,size,nitems,sid,rc)
  end subroutine lfsion_fread_integer
  subroutine lfsion_fread_integer8(data,size,nitems,sid,rc)

    implicit none

    integer*8, intent (out)         :: data
    integer*8, intent(in)           :: size  
    integer*8, intent(in)           :: nitems  
    integer, intent(in)             :: sid  
    integer*8, intent(out)          :: rc  

    call lfsion_fread_c(data,size,nitems,sid,rc)
  end subroutine lfsion_fread_integer8
  subroutine lfsion_fread_real(data,size,nitems,sid,rc)

    implicit none

    real, intent (out)              :: data
    integer*8, intent(in)           :: size
    integer*8, intent(in)           :: nitems
    integer, intent(in)             :: sid
    integer*8, intent(out)          :: rc

    call lfsion_fread_c(data,size,nitems,sid,rc)
  end subroutine lfsion_fread_real
  subroutine lfsion_fread_double_precision(data,size,nitems,sid,rc)

    implicit none

    double precision, intent (out)  :: data
    integer*8, intent(in)           :: size
    integer*8, intent(in)           :: nitems
    integer, intent(in)             :: sid
    integer*8, intent(out)          :: rc

    call lfsion_fread_c(data,size,nitems,sid,rc)
  end subroutine lfsion_fread_double_precision
  subroutine lfsion_fread_complex(data,size,nitems,sid,rc)

    implicit none

    complex, intent (out)           :: data
    integer*8, intent(in)           :: size
    integer*8, intent(in)           :: nitems
    integer, intent(in)             :: sid
    integer*8, intent(out)          :: rc

    call lfsion_fread_c(data,size,nitems,sid,rc)
  end subroutine lfsion_fread_complex
  subroutine lfsion_fread_logical(data,size,nitems,sid,rc)

    implicit none

    logical, intent (out)           :: data
    integer*8, intent(in)           :: size
    integer*8, intent(in)           :: nitems
    integer, intent(in)             :: sid
    integer*8, intent(out)          :: rc

    call lfsion_fread_c(data,size,nitems,sid,rc)
  end subroutine lfsion_fread_logical
  subroutine lfsion_fread_character(data,size,nitems,sid,rc)

    implicit none

    character(len=*), intent (out)   :: data
    integer*8, intent(in)           :: size
    integer*8, intent(in)           :: nitems
    integer, intent(in)             :: sid
    integer*8, intent(out)          :: rc

    call lfsion_fread_c(data,size,nitems,sid,rc)
  end subroutine lfsion_fread_character

end module sion_f90
