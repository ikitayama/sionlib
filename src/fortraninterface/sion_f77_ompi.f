************************************************************************
**  SIONLIB     http://www.fz-juelich.de/jsc/sionlib                  **
************************************************************************
**  Copyright (c) 2008-2019                                           **
**  Forschungszentrum Juelich, Juelich Supercomputing Centre          **
**                                                                    **
**  See the file COPYRIGHT in the package base directory for details  **
************************************************************************

**************************************************************
** Fortran 77 hybrid MPI/OpenMP interface to SIONlib       **
**************************************************************
*
* @file sion_f77.f
*
* @brief Fortran77 interface
*
* @author Florian Janetzko
* @date 29.05.2013
*

***********************************************
* Fortran interface subroutines and functions *
***********************************************
* Subroutines (without overloading)
      SUBROUTINE LFSION_PAROPEN_OMPI(FNAME,FILE_MODE,NFILES,
     &                             GCOMM,LCOMM,
     &                             CHUNKSIZE,FSBLKSIZE,GLOBALRANK,
     &                             NEWFN,SID)
      
        IMPLICIT NONE 

        INCLUDE 'sion_f77.h'
      
        CHARACTER(LEN=*) FNAME
        CHARACTER(LEN=*) FILE_MODE
        CHARACTER(LEN=*) NEWFN
        INTEGER          GCOMM
        INTEGER          LCOMM
        INTEGER          NFILES
        INTEGER*8        CHUNKSIZE
        INTEGER*4        FSBLKSIZE
        INTEGER          GLOBALRANK
        INTEGER          SID
      
        CALL LFSION_PAROPEN_OMPI_C(FNAME,FILE_MODE,NFILES,GCOMM,LCOMM,
     &                           CHUNKSIZE,FSBLKSIZE,GLOBALRANK,
     &                           NEWFN,SID)
      END 


      SUBROUTINE LFSION_PARCLOSE_OMPI(SID,IERR)
      
        IMPLICIT NONE 

        INCLUDE 'sion_f77.h'
      
        INTEGER          SID
        INTEGER          IERR
      
        CALL LFSION_PARCLOSE_OMPI_C(SID,IERR)
      END 
