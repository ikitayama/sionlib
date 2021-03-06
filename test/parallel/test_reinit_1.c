/****************************************************************************
**  SIONLIB     http://www.fz-juelich.de/jsc/sionlib                       **
*****************************************************************************
**  Copyright (c) 2008-2019                                                **
**  Forschungszentrum Juelich, Juelich Supercomputing Centre               **
**                                                                         **
**  See the file COPYRIGHT in the package base directory for details       **
****************************************************************************/

#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <mpi.h>
#include <time.h>
#include <math.h>

#include "sion.h"

int main(int argc, char **argv)
{
  int  rank, size;

  /* -------------------------- */
  /* PROLOG */
  /* -------------------------- */

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  /* ------------------------------------------------------------- */
  /* TEST A: write a small file with some different pattern (Coll) */
  /* ------------------------------------------------------------- */
  {
#define BUFSIZE 10000 
#define CHUNKSIZE 1000
    sion_int64  chunksize;
    sion_int32  fsblksize = 100;
    int         globalrank= rank;
    int         numfiles  = 1;
    char       *newfname=NULL;
    int         sid;
    MPI_Comm    lcomm;
    FILE       *fp;
    char        buffer[BUFSIZE];
    sion_int64  bytes_written=-1;
    long        sum; 
    size_t      bwrote;
    int         i;

    for (i = 0; i < BUFSIZE; i++) buffer[i] = 'A' + rank;

    chunksize=CHUNKSIZE*2;
    sid = sion_paropen_mpi("test_reinit.out", "bw", &numfiles, MPI_COMM_WORLD, &lcomm, 
			   &chunksize, &fsblksize, &globalrank, &fp, &newfname);
    if(sid>=0) {

      chunksize=CHUNKSIZE;
      sion_parreinit_mpi(sid,chunksize);
      bwrote=sion_coll_fwrite_mpi(buffer,1,CHUNKSIZE,sid);
      
      bytes_written=sion_get_bytes_written(sid);
      printf("on rank %d: bytes_written=%lld\n",rank,bytes_written);
      for (i = 0,sum=0; i < bwrote; i++) sum=sum+buffer[i];
      printf("on rank %d: bwrote=%3d blocksum=%8d \n",rank, (int) bwrote,(int) sum);
     
      sion_parclose_mpi(sid);
    } else {
      fprintf(stderr, "on rank %d: error sid = %d\n",rank,sid);

    }
  }

  fflush(stderr);
  fflush(stdout);
  MPI_Barrier(MPI_COMM_WORLD);
  printf("on rank %d: END of TEST A write coll\n",rank);
  MPI_Barrier(MPI_COMM_WORLD);

  /* --------------------------------------------------------------------------------- */
  /* TEST D.1: read small file with some  pattern (coll)                               */
  /* --------------------------------------------------------------------------------- */
  {
    sion_int64  chunksize = CHUNKSIZE;
    sion_int32  fsblksize = 100;
    int         globalrank= rank;
    int         numfiles  = 1;
    char       *newfname=NULL;
    int         sid;
    MPI_Comm    lcomm;
    FILE       *fp;
    char        buffer[BUFSIZE];
    sion_int64  bytes_avail=-1;
    size_t      bytestoread, bread;
    long        sum; 
    int         i,b;

    for (i = 0; i < BUFSIZE; i++) buffer[i] = 'Q' + rank;

    sid = sion_paropen_mpi("test_reinit.out", "br", &numfiles, MPI_COMM_WORLD, &lcomm, &chunksize, &fsblksize, &globalrank, &fp, &newfname);
    printf("on rank %d: sid           =%d\n",rank,sid);
    printf("on rank %d: numfiles      =%d\n",rank,numfiles);
    printf("on rank %d: chunksize     =%d\n",rank,(int) chunksize);
    printf("on rank %d: globalrank    =%d\n",rank, globalrank);
    printf("on rank %d: newfname      =%s\n",rank, newfname);

    if(sid>=0) {

      /* to check that everyone has data to read, otherwise error */
      bytes_avail=sion_bytes_avail_in_block(sid);  
      if(bytes_avail<=0) {
	fprintf(stderr,"on rank %d: ERROR: no bytes available in file bytes_avail=%d\n",rank,(int) bytes_avail);
      	MPI_Abort(MPI_COMM_WORLD,1);
      }
      b=0;
      while((!sion_feof(sid))) {    
	bytes_avail=sion_bytes_avail_in_block(sid);  
	printf("on rank %d: block=%d           bytes_avail=%d\n",rank,b,(int) bytes_avail);
	bytestoread=bytes_avail;
	bread=sion_coll_fread_mpi(buffer,1,bytestoread,sid);     
	for (i = 0,sum=0; i < bytestoread; i++) sum=sum+buffer[i];
	printf("on rank %d: block=%d           bread=%3d blocksum=%8d \n",rank,b, (int) bread,(int) sum);
	b++;
      }             

      sion_parclose_mpi(sid);
    } else {
      fprintf(stderr, "on rank %d: error sid = %d\n",rank,sid);

    }
  }

  fflush(stderr);
  fflush(stdout);
  MPI_Barrier(MPI_COMM_WORLD);
  printf("on rank %d: END of TEST D.1 read collective from collective file\n",rank);
  MPI_Barrier(MPI_COMM_WORLD);



  /* -------------------------- */
  /* EPILOG */
  /* -------------------------- */
  MPI_Finalize();

  return(0);
}
