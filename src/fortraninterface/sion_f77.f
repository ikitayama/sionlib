************************************************************************
**  SIONLIB     http://www.fz-juelich.de/jsc/sionlib                  **
************************************************************************
**  Copyright (c) 2008-2019                                           **
**  Forschungszentrum Juelich, Juelich Supercomputing Centre          **
**                                                                    **
**  See the file COPYRIGHT in the package base directory for details  **
************************************************************************

**************************************************************
** Fortran 77 interface to SIONlib                          **
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
      SUBROUTINE LFSION_OPEN(FNAME,FILE_MODE,NTASKS,NFILES,CHUNKSIZES,
     &                      FSBLKSIZE,GLOBALRANKS,SID)
      
        IMPLICIT NONE 

        INCLUDE 'sion_f77.h'
      
        CHARACTER(LEN=*) FNAME
        CHARACTER(LEN=*) FILE_MODE
        INTEGER          NTASKS
        INTEGER          NFILES
        INTEGER*8        CHUNKSIZES
        INTEGER*4        FSBLKSIZE
        INTEGER          GLOBALRANKS
        INTEGER          SID
      
        CALL LFSION_OPEN_C(FNAME,FILE_MODE,NTASKS,NFILES,CHUNKSIZES,
     &                    FSBLKSIZE,GLOBALRANKS,SID)
      END 
      
      SUBROUTINE LFSION_OPEN_RANK(FNAME,FILE_MODE,CHUNKSIZE,FSBLKSIZE,
     &                           RANK,SID)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        CHARACTER(LEN=*) FNAME
        CHARACTER(LEN=*) FILE_MODE
        INTEGER*8        CHUNKSIZE
        INTEGER*4        FSBLKSIZE
        INTEGER          RANK
        INTEGER          SID
      
        CALL LFSION_OPEN_RANK_C(FNAME,FILE_MODE,CHUNKSIZE,FSBLKSIZE,
     &                         RANK,SID)
      END 
      
      SUBROUTINE LFSION_CLOSE(SID,IERR)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        INTEGER SID
        INTEGER IERR
      
        CALL LFSION_CLOSE_C(SID,IERR)
      END 
      
      SUBROUTINE LFSION_FEOF(SID,EOF)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        INTEGER SID
        INTEGER EOF
      
        CALL LFSION_FEOF_C(SID,EOF)
      END 
      
      SUBROUTINE LFSION_SEEK(SID,RANK,CURRENTBLOCKNR,POSINBLK,IERR)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        INTEGER   SID
        INTEGER   RANK
        INTEGER   CURRENTBLOCKNR
        INTEGER*8 POSINBLK
        INTEGER   IERR
      
        CALL LFSION_SEEK_C(SID,RANK,CURRENTBLOCKNR,POSINBLK,IERR)
      END 
      
      SUBROUTINE LFSION_ENSURE_FREE_SPACE(SID,BYTES,IERR)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        INTEGER   SID
        INTEGER*8 BYTES
        INTEGER   IERR
      
        CALL LFSION_ENSURE_FREE_SPACE_C(SID,BYTES,IERR)
      END 
      
      SUBROUTINE LFSION_FLUSH(SID,IERR)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        INTEGER SID
        INTEGER IERR
      
        CALL LFSION_FLUSH_C(SID,IERR)
      END 
      
      SUBROUTINE LFSION_GET_LOCATIONS(SID,NTASKS,MAXBLOCKS,GLOBALSKIP,
     &                               START_OF_VARHEADER,SION_LOCALSIZES,
     &                               SION_GLOBALRANKS,SION_CHUNKCOUNT,
     &                               SION_CHUNKSIZES,IERR)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        INTEGER   SID
        INTEGER   NTASKS
        INTEGER   MAXBLOCKS
        INTEGER*8 GLOBALSKIP
        INTEGER*8 START_OF_VARHEADER
        INTEGER*8 SION_LOCALSIZES
        INTEGER*8 SION_GLOBALRANKS
        INTEGER*8 SION_CHUNKCOUNT
        INTEGER*8 SION_CHUNKSIZES
        INTEGER   IERR
      
        CALL LFSION_GET_LOCATIONS_C(SID,NTASKS,MAXBLOCKS,GLOBALSKIP,
     &                             START_OF_VARHEADER,SION_LOCALSIZES,
     &                             SION_GLOBALRANKS,SION_CHUNKCOUNT,
     &                             SION_CHUNKSIZES,IERR)
      END 
      
      SUBROUTINE LFSION_GET_CURRENT_LOCATIONS(SID,NTASKS,
     &                                       SION_CURRENTPOS,  
     &                                       SION_CURRENTBLOCKNR,IERR)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        integer   SID
        integer   NTASKS
        integer*8 SION_CURRENTPOS
        integer*8 SION_CURRENTBLOCKNR
        integer   IERR
      
        CALL LFSION_GET_CURRENT_LOCATIONS_C(SID,NTASKS,
     &                                     SION_CURRENTPOS,
     &                                     SION_CURRENTBLOCKNR,IERR)
      END 
      
      SUBROUTINE LFSION_GET_CHUNKSIZES(SID,CHUNKSIZES,IERR)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        INTEGER   SID
        INTEGER*8 CHUNKSIZES
        INTEGER   IERR 
      
        CALL LFSION_GET_CHUNKSIZES_C(SID,CHUNKSIZES,IERR)
      END 
      
      SUBROUTINE LFSION_GET_GLOBALRANKS(SID,GLOBALRANKS,IERR)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        INTEGER   SID
        INTEGER   GLOBALRANKS
        INTEGER   IERR
      
        CALL LFSION_GET_GLOBALRANKS_C(SID,GLOBALRANKS,IERR)
      END 
      
      SUBROUTINE LFSION_GET_MAPPING_SPEC(SID,MAPPING_SIZE,NUMFILES,IERR)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        INTEGER SID
        INTEGER MAPPING_SIZE
        INTEGER NUMFILES
        INTEGER IERR
      
        CALL LFSION_GET_MAPPING_SPEC_C(SID,MAPPING_SIZE,NUMFILES,IERR)
      END 
      
      SUBROUTINE LFSION_GET_MAPPING(SID,MAPPING,IERR)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        INTEGER   SID
        INTEGER*4 MAPPING
        INTEGER   IERR
      
        CALL LFSION_GET_MAPPING_C(SID,MAPPING,IERR)
      END 
      
      SUBROUTINE LFSION_GET_FILENO(SID,FILENUMBER)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        INTEGER SID
        INTEGER FILENUMBER    
      
        CALL LFSION_GET_FILENO_C(SID,FILENUMBER)
      END 
      
      SUBROUTINE LFSION_GET_FILE_ENDIANESS(SID,ENDIANNESS)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        INTEGER SID
        INTEGER ENDIANNESS
      
        CALL LFSION_GET_FILE_ENDIANNESS_C(SID,ENDIANNESS)
      END 
      
      SUBROUTINE LFSION_GET_FILE_ENDIANNESS(SID,ENDIANNESS)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        INTEGER SID
        INTEGER ENDIANNESS
      
        CALL LFSION_GET_FILE_ENDIANNESS_C(SID,ENDIANNESS)
      END 
      
      SUBROUTINE LFSION_GET_ENDIANESS(ENDIANNESS)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        INTEGER ENDIANNESS
      
        CALL LFSION_GET_ENDIANNESS_C(ENDIANNESS)
      END 
      
      SUBROUTINE LFSION_GET_ENDIANNESS(ENDIANNESS)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        INTEGER ENDIANNESS
      
        CALL LFSION_GET_ENDIANNESS_C(ENDIANNESS)
      END 
      
      SUBROUTINE LFSION_ENDIANNESS_SWAP_NEEDED(SID,NEEDED)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        INTEGER SID
        INTEGER NEEDED
      
        CALL LFSION_ENDIANNESS_SWAP_NEEDED_C(SID,NEEDED)
      END 
      
* Functions (without overloading)
      FUNCTION LFSION_BYTES_AVAIL_IN_BLOCK(SID)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        INTEGER*8 LFSION_BYTES_AVAIL_IN_BLOCK
        INTEGER*8 LFSION_BYTES_AVAIL_IN_BLOCK_C
        INTEGER   SID
      
        LFSION_BYTES_AVAIL_IN_BLOCK = LFSION_BYTES_AVAIL_IN_BLOCK_C(SID)
      END 
      
      FUNCTION LFSION_GET_POSITION(SID)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        INTEGER*8 LFSION_GET_POSITION
        INTEGER*8 LFSION_GET_POSITION_C
        INTEGER   SID
      
        LFSION_GET_POSITION = LFSION_GET_POSITION_C(SID)
      END 
      
* Subroutines (with overloading)
      SUBROUTINE LFSION_SWAP(TARGET,SOURCE,SIZE,N,AFLAG,RC)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        INTEGER TARGET
        INTEGER SOURCE
        INTEGER SIZE
        INTEGER N
        INTEGER AFLAG
        INTEGER RC
      
        CALL LFSION_SWAP_C(TARGET,SOURCE,SIZE,N,AFLAG,RC) 
      END 

      
* Datatype INTEGER
      SUBROUTINE LFSION_WRITE_INTEGER(DATA,SIZE,NITEMS,SID,RC)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        INTEGER   DATA
        INTEGER*8 SIZE  
        INTEGER*8 NITEMS  
        INTEGER   SID  
        INTEGER*8 RC  
      
        CALL LFSION_WRITE(DATA,SIZE,NITEMS,SID,RC)
      END 
      
      SUBROUTINE LFSION_FWRITE_INTEGER(DATA,SIZE,NITEMS,SID,RC)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        INTEGER   DATA
        INTEGER*8 SIZE  
        INTEGER*8 NITEMS  
        INTEGER   SID  
        INTEGER*8 RC  
      
        CALL LFSION_FWRITE(DATA,SIZE,NITEMS,SID,RC)
      END 

      SUBROUTINE LFSION_READ_INTEGER(DATA,SIZE,NITEMS,SID,RC)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        INTEGER   DATA
        INTEGER*8 SIZE  
        INTEGER*8 NITEMS  
        INTEGER   SID  
        INTEGER*8 RC  
      
        CALL LFSION_READ(DATA,SIZE,NITEMS,SID,RC)
      END 
      
      SUBROUTINE LFSION_FREAD_INTEGER(DATA,SIZE,NITEMS,SID,RC)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        INTEGER   DATA
        INTEGER*8 SIZE  
        INTEGER*8 NITEMS  
        INTEGER   SID  
        INTEGER*8 RC  
      
        CALL LFSION_FREAD(DATA,SIZE,NITEMS,SID,RC)
      END 


* Datatype CHARACTER
      SUBROUTINE LFSION_WRITE_CHARACTER(DATA,SIZE,NITEMS,SID,RC)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        CHARACTER DATA
        INTEGER*8 SIZE  
        INTEGER*8 NITEMS  
        INTEGER   SID  
        INTEGER*8 RC  
      
        CALL LFSION_WRITE(DATA,SIZE,NITEMS,SID,RC)
      END 
      
      SUBROUTINE LFSION_FWRITE_CHARACTER(DATA,SIZE,NITEMS,SID,RC)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        CHARACTER DATA
        INTEGER*8 SIZE  
        INTEGER*8 NITEMS  
        INTEGER   SID  
        INTEGER*8 RC  
      
        CALL LFSION_FWRITE(DATA,SIZE,NITEMS,SID,RC)
      END 
      
      SUBROUTINE LFSION_READ_CHARACTER(DATA,SIZE,NITEMS,SID,RC)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        CHARACTER DATA
        INTEGER*8 SIZE  
        INTEGER*8 NITEMS  
        INTEGER   SID  
        INTEGER*8 RC  
      
        CALL LFSION_READ(DATA,SIZE,NITEMS,SID,RC)
      END 
      
      SUBROUTINE LFSION_FREAD_CHARACTER(DATA,SIZE,NITEMS,SID,RC)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        CHARACTER DATA
        INTEGER*8 SIZE  
        INTEGER*8 NITEMS  
        INTEGER   SID  
        INTEGER*8 RC  
      
        CALL LFSION_FREAD(DATA,SIZE,NITEMS,SID,RC)
      END 


* Datatype REAL
      SUBROUTINE LFSION_WRITE_REAL(DATA,SIZE,NITEMS,SID,RC)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        REAL DATA
        INTEGER*8 SIZE  
        INTEGER*8 NITEMS  
        INTEGER   SID  
        INTEGER*8 RC  
      
        CALL LFSION_WRITE(DATA,SIZE,NITEMS,SID,RC)
      END 
      
      SUBROUTINE LFSION_FWRITE_REAL(DATA,SIZE,NITEMS,SID,RC)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        REAL DATA
        INTEGER*8 SIZE  
        INTEGER*8 NITEMS  
        INTEGER   SID  
        INTEGER*8 RC  
      
        CALL LFSION_FWRITE(DATA,SIZE,NITEMS,SID,RC)
      END 
      
      SUBROUTINE LFSION_READ_REAL(DATA,SIZE,NITEMS,SID,RC)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        REAL DATA
        INTEGER*8 SIZE  
        INTEGER*8 NITEMS  
        INTEGER   SID  
        INTEGER*8 RC  
      
        CALL LFSION_READ(DATA,SIZE,NITEMS,SID,RC)
      END 
      
      SUBROUTINE LFSION_FREAD_REAL(DATA,SIZE,NITEMS,SID,RC)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        REAL DATA
        INTEGER*8 SIZE  
        INTEGER*8 NITEMS  
        INTEGER   SID  
        INTEGER*8 RC  
      
        CALL LFSION_FREAD(DATA,SIZE,NITEMS,SID,RC)
      END 

* Datatype DOUBLE PRECISION
      SUBROUTINE LFSION_WRITE_DOUBLE(DATA,SIZE,NITEMS,SID,RC)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        DOUBLE PRECISION DATA
        INTEGER*8 SIZE  
        INTEGER*8 NITEMS  
        INTEGER   SID  
        INTEGER*8 RC  
      
        CALL LFSION_WRITE(DATA,SIZE,NITEMS,SID,RC)
      END 
      
      SUBROUTINE LFSION_FWRITE_DOUBLE(DATA,SIZE,NITEMS,SID,RC)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        DOUBLE PRECISION DATA
        INTEGER*8 SIZE  
        INTEGER*8 NITEMS  
        INTEGER   SID  
        INTEGER*8 RC  
      
        CALL LFSION_FWRITE(DATA,SIZE,NITEMS,SID,RC)
      END 
      
      SUBROUTINE LFSION_READ_DOUBLE(DATA,SIZE,NITEMS,SID,RC)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        DOUBLE PRECISION DATA
        INTEGER*8 SIZE  
        INTEGER*8 NITEMS  
        INTEGER   SID  
        INTEGER*8 RC  
      
        CALL LFSION_READ(DATA,SIZE,NITEMS,SID,RC)
      END 
      
      SUBROUTINE LFSION_FREAD_DOUBLE(DATA,SIZE,NITEMS,SID,RC)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        DOUBLE PRECISION DATA
        INTEGER*8 SIZE  
        INTEGER*8 NITEMS  
        INTEGER   SID  
        INTEGER*8 RC  
      
        CALL LFSION_FREAD(DATA,SIZE,NITEMS,SID,RC)
      END 

* Datatype COMPLEX
      SUBROUTINE LFSION_WRITE_COMPLEX(DATA,SIZE,NITEMS,SID,RC)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        COMPLEX   DATA
        INTEGER*8 SIZE  
        INTEGER*8 NITEMS  
        INTEGER   SID  
        INTEGER*8 RC  
      
        CALL LFSION_WRITE(DATA,SIZE,NITEMS,SID,RC)
      END 
      
      SUBROUTINE LFSION_FWRITE_COMPLEX(DATA,SIZE,NITEMS,SID,RC)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        COMPLEX   DATA
        INTEGER*8 SIZE  
        INTEGER*8 NITEMS  
        INTEGER   SID  
        INTEGER*8 RC  
      
        CALL LFSION_FWRITE(DATA,SIZE,NITEMS,SID,RC)
      END 
      
      SUBROUTINE LFSION_READ_COMPLEX(DATA,SIZE,NITEMS,SID,RC)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        COMPLEX   DATA
        INTEGER*8 SIZE  
        INTEGER*8 NITEMS  
        INTEGER   SID  
        INTEGER*8 RC  
      
        CALL LFSION_READ(DATA,SIZE,NITEMS,SID,RC)
      END 
      
      SUBROUTINE LFSION_FREAD_COMPLEX(DATA,SIZE,NITEMS,SID,RC)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        COMPLEX   DATA
        INTEGER*8 SIZE  
        INTEGER*8 NITEMS  
        INTEGER   SID  
        INTEGER*8 RC  
      
        CALL LFSION_FREAD(DATA,SIZE,NITEMS,SID,RC)
      END 

* Datatype LOGICAL
      SUBROUTINE LFSION_WRITE_LOGICAL(DATA,SIZE,NITEMS,SID,RC)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        LOGICAL   DATA
        INTEGER*8 SIZE  
        INTEGER*8 NITEMS  
        INTEGER   SID  
        INTEGER*8 RC  
      
        CALL LFSION_WRITE(DATA,SIZE,NITEMS,SID,RC)
      END 
      
      SUBROUTINE LFSION_FWRITE_LOGICAL(DATA,SIZE,NITEMS,SID,RC)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        LOGICAL   DATA
        INTEGER*8 SIZE  
        INTEGER*8 NITEMS  
        INTEGER   SID  
        INTEGER*8 RC  
      
        CALL LFSION_FWRITE(DATA,SIZE,NITEMS,SID,RC)
      END 
      
      SUBROUTINE LFSION_READ_LOGICAL(DATA,SIZE,NITEMS,SID,RC)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        LOGICAL   DATA
        INTEGER*8 SIZE  
        INTEGER*8 NITEMS  
        INTEGER   SID  
        INTEGER*8 RC  
      
        CALL LFSION_READ(DATA,SIZE,NITEMS,SID,RC)
      END 
      
      SUBROUTINE LFSION_FREAD_LOGICAL(DATA,SIZE,NITEMS,SID,RC)
      
        IMPLICIT NONE

        INCLUDE 'sion_f77.h'
      
        LOGICAL   DATA
        INTEGER*8 SIZE  
        INTEGER*8 NITEMS  
        INTEGER   SID  
        INTEGER*8 RC  
      
        CALL LFSION_FREAD(DATA,SIZE,NITEMS,SID,RC)
      END 


