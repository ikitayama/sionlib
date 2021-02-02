!*****************************************************************************
!**  SIONLIB     http://www.fz-juelich.de/jsc/sionlib                       **
!*****************************************************************************
!**  Copyright (c) 2008-2019                                                **
!**  Forschungszentrum Juelich, Juelich Supercomputing Centre               **
!**                                                                         **
!**  See the file COPYRIGHT in the package base directory for details       **
!*****************************************************************************

!*****************************************************************************
!** Module file of Fortran 90 MPI interface to SIONlib                      **
!*****************************************************************************
!*
!* @file sion_f90.f90
!*
!* @brief Fortran90 interface
!*
!* @author Florian Janetzko
!* @date 05.07.2013
!* @date 05.06.2014 interface for collective routines added
!*
module sion_f90_mpi
  use sion_f90

  implicit none

!************************************************************
!* Explicit interfaces to C void functions with overloading *
!************************************************************
  interface lfsion_coll_fwrite_mpi
   module procedure lfsion_coll_fwrite_mpi_integer
   module procedure lfsion_coll_fwrite_mpi_integer8
   module procedure lfsion_coll_fwrite_mpi_real
   module procedure lfsion_coll_fwrite_mpi_double_precision
   module procedure lfsion_coll_fwrite_mpi_complex
   module procedure lfsion_coll_fwrite_mpi_logical
   module procedure lfsion_coll_fwrite_mpi_character
  end interface lfsion_coll_fwrite_mpi

  interface lfsion_coll_fread_mpi
    module procedure lfsion_coll_fread_mpi_integer
    module procedure lfsion_coll_fread_mpi_integer8
    module procedure lfsion_coll_fread_mpi_real
    module procedure lfsion_coll_fread_mpi_double_precision
    module procedure lfsion_coll_fread_mpi_complex
    module procedure lfsion_coll_fread_mpi_logical
    module procedure lfsion_coll_fread_mpi_character
  end interface lfsion_coll_fread_mpi

!***********************************************
!* Fortran interface subroutines and functions *
!***********************************************
contains
! Subroutines (without overloading)
  subroutine lfsion_paropen_mpi(fname,file_mode,nfiles,fgcomm,flcomm,chunksizes,fsblksize,&
 &                             globalrank,newfname,sid)

    implicit none 

    character(len=*), intent(in)    :: fname
    character(len=*), intent(in)    :: file_mode
    integer, intent(in)             :: nfiles
    integer, intent(in)             :: fgcomm
    integer, intent(inout)          :: flcomm
    integer*8, intent(inout)        :: chunksizes
    integer*4, intent(inout)        :: fsblksize
    integer, intent(in)             :: globalrank
    character(len=*), intent(out)   :: newfname
    integer, intent(out)            :: sid

    call lfsion_paropen_mpi_c(fname,file_mode,nfiles,fgcomm,flcomm,chunksizes,fsblksize,&
&                            globalrank,newfname,sid)
  end subroutine lfsion_paropen_mpi

  subroutine lfsion_parclose_mpi(sid,ierr)

    implicit none

    integer, intent(in)             :: sid
    integer, intent(out)            :: ierr

    call lfsion_parclose_mpi_c(sid,ierr)
  end subroutine lfsion_parclose_mpi

! Subroutines (with overloading)
! lfsion_coll_fwrite_mpi
  subroutine lfsion_coll_fwrite_mpi_integer(data,size,nitems,sid,rc)
    
    implicit none

    integer, intent(in)    :: data
    integer*8, intent(in)  :: size
    integer*8, intent(in)  :: nitems
    integer, intent(in)    :: sid
    integer*8, intent(out) :: rc

    call lfsion_coll_fwrite_mpi_c(data,size,nitems,sid,rc)

  end subroutine lfsion_coll_fwrite_mpi_integer
  subroutine lfsion_coll_fwrite_mpi_integer8(data,size,nitems,sid,rc)
    
    implicit none

    integer*8, intent(in)    :: data
    integer*8, intent(in)  :: size
    integer*8, intent(in)  :: nitems
    integer, intent(in)    :: sid
    integer*8, intent(out) :: rc

    call lfsion_coll_fwrite_mpi_c(data,size,nitems,sid,rc)

  end subroutine lfsion_coll_fwrite_mpi_integer8
  subroutine lfsion_coll_fwrite_mpi_real(data,size,nitems,sid,rc)

    implicit none

    real, intent(in)       :: data
    integer*8, intent(in)  :: size
    integer*8, intent(in)  :: nitems
    integer, intent(in)    :: sid
    integer*8, intent(out) :: rc

    call lfsion_coll_fwrite_mpi_c(data,size,nitems,sid,rc)

  end subroutine lfsion_coll_fwrite_mpi_real
  subroutine lfsion_coll_fwrite_mpi_double_precision(data,size,nitems,sid,rc)

    implicit none

    double precision, intent(in)    :: data
    integer*8, intent(in)           :: size
    integer*8, intent(in)           :: nitems
    integer, intent(in)             :: sid
    integer*8, intent(out)          :: rc

    call lfsion_coll_fwrite_mpi_c(data,size,nitems,sid,rc)

  end subroutine lfsion_coll_fwrite_mpi_double_precision
  subroutine lfsion_coll_fwrite_mpi_complex(data,size,nitems,sid,rc)

    implicit none

    complex, intent(in)    :: data
    integer*8, intent(in)  :: size
    integer*8, intent(in)  :: nitems
    integer, intent(in)    :: sid
    integer*8, intent(out) :: rc

    call lfsion_coll_fwrite_mpi_c(data,size,nitems,sid,rc)

  end subroutine lfsion_coll_fwrite_mpi_complex
  subroutine lfsion_coll_fwrite_mpi_logical(data,size,nitems,sid,rc)

    implicit none

    logical, intent(in)    :: data
    integer*8, intent(in)  :: size
    integer*8, intent(in)  :: nitems
    integer, intent(in)    :: sid
    integer*8, intent(out) :: rc

    call lfsion_coll_fwrite_mpi_c(data,size,nitems,sid,rc)

  end subroutine lfsion_coll_fwrite_mpi_logical
  subroutine lfsion_coll_fwrite_mpi_character(data,size,nitems,sid,rc)

    implicit none

    character, intent(in)  :: data
    integer*8, intent(in)  :: size
    integer*8, intent(in)  :: nitems
    integer, intent(in)    :: sid
    integer*8, intent(out) :: rc

    call lfsion_coll_fwrite_mpi_c(data,size,nitems,sid,rc)

  end subroutine lfsion_coll_fwrite_mpi_character

! lfsion_coll_fread_mpi
  subroutine lfsion_coll_fread_mpi_integer(data,size,nitems,sid,rc)

    implicit none

    integer, intent(out)    :: data
    integer*8, intent(in)  :: size
    integer*8, intent(in)  :: nitems
    integer, intent(in)    :: sid
    integer*8, intent(out) :: rc 

    call lfsion_coll_fread_mpi_c(data,size,nitems,sid,rc)

  end subroutine lfsion_coll_fread_mpi_integer
  subroutine lfsion_coll_fread_mpi_integer8(data,size,nitems,sid,rc)

    implicit none

    integer*8, intent(out)    :: data
    integer*8, intent(in)  :: size
    integer*8, intent(in)  :: nitems
    integer, intent(in)    :: sid
    integer*8, intent(out) :: rc 

    call lfsion_coll_fread_mpi_c(data,size,nitems,sid,rc)

  end subroutine lfsion_coll_fread_mpi_integer8
  subroutine lfsion_coll_fread_mpi_real(data,size,nitems,sid,rc)

    implicit none

    real, intent(out)       :: data
    integer*8, intent(in)  :: size
    integer*8, intent(in)  :: nitems
    integer, intent(in)    :: sid
    integer*8, intent(out) :: rc

    call lfsion_coll_fread_mpi_c(data,size,nitems,sid,rc)

  end subroutine lfsion_coll_fread_mpi_real
  subroutine lfsion_coll_fread_mpi_double_precision(data,size,nitems,sid,rc)

    implicit none

    double precision, intent(out)  :: data
    integer*8, intent(in)         :: size
    integer*8, intent(in)         :: nitems
    integer, intent(in)           :: sid
    integer*8, intent(out)        :: rc

    call lfsion_coll_fread_mpi_c(data,size,nitems,sid,rc)

  end subroutine lfsion_coll_fread_mpi_double_precision
  subroutine lfsion_coll_fread_mpi_complex(data,size,nitems,sid,rc)

    implicit none

    complex, intent(out)    :: data
    integer*8, intent(in)  :: size
    integer*8, intent(in)  :: nitems
    integer, intent(in)    :: sid
    integer*8, intent(out) :: rc

    call lfsion_coll_fread_mpi_c(data,size,nitems,sid,rc)

  end subroutine lfsion_coll_fread_mpi_complex
  subroutine lfsion_coll_fread_mpi_logical(data,size,nitems,sid,rc)

    implicit none

    logical, intent(out)    :: data
    integer*8, intent(in)  :: size
    integer*8, intent(in)  :: nitems
    integer, intent(in)    :: sid
    integer*8, intent(out) :: rc

    call lfsion_coll_fread_mpi_c(data,size,nitems,sid,rc)

  end subroutine lfsion_coll_fread_mpi_logical
  subroutine lfsion_coll_fread_mpi_character(data,size,nitems,sid,rc)

    implicit none

    character, intent(out)  :: data
    integer*8, intent(in)  :: size
    integer*8, intent(in)  :: nitems
    integer, intent(in)    :: sid
    integer*8, intent(out) :: rc

    call lfsion_coll_fread_mpi_c(data,size,nitems,sid,rc)

  end subroutine lfsion_coll_fread_mpi_character
end module sion_f90_mpi
