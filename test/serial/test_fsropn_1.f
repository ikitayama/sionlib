************************************************************************
**  SIONLIB     http://www.fz-juelich.de/jsc/sionlib                  **
************************************************************************
**  Copyright (c) 2008-2019                                           **
**  Forschungszentrum Juelich, Juelich Supercomputing Centre          **
**                                                                    **
**  See the file COPYRIGHT in the package base directory for details  **
************************************************************************
      PROGRAM MAIN

      IMPLICIT NONE
      

      INTEGER            I
      INTEGER*8          IERR
      CHARACTER(len=255) LFILENAME
      CHARACTER(len=3)   FILEMODE
      INTEGER            NTASKS
      INTEGER            MAXNTASKS
      INTEGER            NFILES
      PARAMETER          (MAXNTASKS = 4)

      INTEGER            SID
      INTEGER            FSBLKSIZE
      REAL*8             SUM, BUFFER(1000)
      INTEGER*8          CHUNKSIZES(MAXNTASKS)
      INTEGER            GLOBALRANKS(MAXNTASKS)
      INTEGER*8          SIZE, NELEM 
      
      INTEGER     CEND, FEND, DOSWAP, SWAP_NEEDED
      INTEGER     SION_CURRENT_RANK, SION_CURRENT_BLK
      INTEGER*8   SION_CURRENT_POS
      PARAMETER(  SION_CURRENT_RANK=-101, 
     &            SION_CURRENT_BLK= -102, 
     &            SION_CURRENT_POS= -103 )
      
* ---------------------------------- *
* TEST A: test                       *
* ---------------------------------- *
      NFILES    = 1
      NTASKS    = MAXNTASKS
      FSBLKSIZE = 1000
      LFILENAMe = "testA.out"
      FILEMODE  = 'wb'
      DO I = 1,NTASKS
        CHUNKSIZES(I)  = 8000
        GLOBALRANKS(I) = I
      ENDDO
      
      CALL LFSION_OPEN(TRIM(LFILENAME), TRIM(FILEMODE), NTASKS, NFILES, 
     &                CHUNKSIZES, FSBLKSIZE, GLOBALRANKS, SID)
      IF (SID .LT. 0) THEN
        WRITE (6,*) 'TEST A: sion_open returned', SID
      ELSE
        CALL LFSION_SEEK(SID,0,SION_CURRENT_BLK,SION_CURRENT_POS,IERR)

        BUFFER = 1111.0
        SIZE=8
        NELEM=1000
        CALL LFSION_WRITE(BUFFER,SIZE,NELEM,SID,IERR)
        WRITE (6,'(A,I10)') 'TEST A: wrote=',IERR
     
        CALL LFSION_CLOSE(SID,IERR)
      END IF

      FILEMODE = 'rb'
      CALL LFSION_OPEN(TRIM(LFILENAME),TRIM(FILEMODE),NTASKS, NFILES, 
     &                CHUNKSIZES, FSBLKSIZE, GLOBALRANKS, SID);

      IF (SID .LT. 0) THEN
        WRITE (6,'(A)') 'TEST A: sion_open returned', SID
      ELSE
        CALL LFSION_GET_CHUNKSIZES(SID,CHUNKSIZES,IERR);
        CALL LFSION_SEEK(sid,0,SION_CURRENT_BLK,SION_CURRENT_POS,IERR)

        BUFFER = 0
        SIZE=8
        NELEM=1000
        CALL LFSION_READ(BUFFER,SIZE,NELEM,SID,IERR)
        WRITE (6,'(A,I10)') 'TEST A: read =',IERR

C check endianness routines
        CALL LFSION_GET_ENDIANNESS(CEND);
        CALL LFSION_GET_FILE_ENDIANNESS(SID,FEND);
        CALL LFSION_ENDIANNESS_SWAP_NEEDED(SID,SWAP_NEEDED)
        IF (CEND .EQ. FEND) THEN
          WRITE (6,'(A)') 'TEST A: same endianness'
          IF (SWAP_NEEDED .NE. 0) THEN
             WRITE (6,'(A)') 'TEST A: wrong SWAP_NEEDED'
          ENDIF
        ELSE
          WRITE (6,'(A)') 'TEST A: different endianness'
          IF (SWAP_NEEDED .EQ. 0) THEN
             WRITE (6,'(A)') 'TEST A: wrong SWAP_NEEDED'
          ENDIF
        ENDIF
     
        DOSWAP = 1
        CALL LFSION_SWAP(BUFFER,BUFFER,8,1000,DOSWAP,IERR)
        CALL LFSION_SWAP(BUFFER,BUFFER,8,1000,DOSWAP,IERR)
    
        SUM = 0
        DO I = 0,1000
          SUM = SUM + BUFFER(I)
        END DO
        WRITE (6,'(A,F17.5)') 'TEST A: sum=',SUM

        CALL LFSION_CLOSE(SID,IERR)
        WRITE (6,'(A,I8)')  'TEST A: nfiles=   ',NFILES
        WRITE (6,'(A,2I8)') 'TEST A: chunksizes=',CHUNKSIZES(1),
     &                       CHUNKSIZES(2)
        WRITE (6,'(A,I8)')  'TEST A: fsblksize=',FSBLKSIZE
      ENDIF
      END PROGRAM MAIN
