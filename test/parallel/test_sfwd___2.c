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

  /* ------------------------------------------------------ */
  /* TEST B: write a small file with some different pattern */
  /* ------------------------------------------------------ */
  {
#define BUFSIZE 1000  
#define CHUNKSIZE 200
    sion_int64  chunksize = CHUNKSIZE;
    sion_int32  fsblksize = 10;
    int         globalrank= rank;
    int         numfiles  = 1;
    char       *newfname=NULL;
    int         sid;
    MPI_Comm    lcomm;
    FILE       *fp, *logfp;
    char        buffer[BUFSIZE];
    sion_int64  bytes_written=-1;
    long        sum; 
    uint64_t    key;
    size_t      bwrote, len;
    int         i,j, c;
    char        logfilename[256];
    const int   cycle_len = 3;
    const int   cycle_full = 26;

    for (i = 0; i < BUFSIZE; i++) buffer[i] = 'A' + rank;
    
    sid = sion_paropen_mpi("testB.out", "bw,keyval=inline,sionfwd", &numfiles, MPI_COMM_WORLD, &lcomm, &chunksize, &fsblksize, &globalrank, &fp, &newfname);
    if(sid>=0) {

      
      sprintf(logfilename, "keys_rank%04d_in.log", rank);
      logfp=fopen(logfilename,"w");
      if (logfp == NULL) {
	fprintf(stderr, "cannot open outfile %s , aborting ...\n", logfilename);
	return (1);
      }
      /* fprintf(logfp,"KEY List for rank %04d\n",rank);  */
      sum=0;
      len=16;
      for(j=0;  j < (int) chunksize / ((int) len + 32); j++) {
	key=4711 + (rank + j) % cycle_len;
	for (i = 0; i < 16; i++) {
	  buffer[i] = 'A' + ((key - 4711 + j / cycle_len) % cycle_full);
	}
	bwrote=sion_fwrite_key(buffer, key, (size_t) 1, (size_t) len, sid);
	fprintf(logfp,"on rank %d: key=%6d len=%ld val=",rank, (int) key, (long) len);
	for (c = 0,sum=0; c < len; c++) {
	  fprintf(logfp,"%c",buffer[c]);
	  sum=sum+buffer[c];
	}
	fprintf(logfp,"\n");
      }
      bytes_written=sion_get_bytes_written(sid);

      printf("on rank %d: bytes_written=%lld\n",rank,bytes_written);
      printf("on rank %d: bwrote=%3d blocksum=%8d \n",rank, (int) bwrote,(int) sum);

      fclose(logfp);
      sion_parclose_mpi(sid);


    } else {
      fprintf(stderr, "on rank %d: error sid = %d\n",rank,sid);

    }
  }

  fflush(stderr);
  fflush(stdout);
  MPI_Barrier(MPI_COMM_WORLD);
  printf("on rank %d: END of TEST B write\n",rank);
  MPI_Barrier(MPI_COMM_WORLD);

#undef BUFSIZE
#undef CHUNKSIZE

  /* ------------------------------------------------------ */
  /* TEST B: read small file with some different pattern    */
  /* ------------------------------------------------------ */
  if(1){
#define BUFSIZE 1000  
#define CHUNKSIZE 200
    sion_int64  chunksize = CHUNKSIZE;
    sion_int32  fsblksize = 10;
    int         globalrank= rank;
    int         numfiles  = 1;
    char       *newfname=NULL;
    int         sid;
    MPI_Comm    lcomm;
    FILE       *fp, *logfp;
    char        buffer[BUFSIZE];
    size_t      bread, len;
    char        logfilename[256];
    long        sum; 
    int         i,c;
    uint64_t    key;
    const int   cycle_len = 3;

    for (i = 0; i < BUFSIZE; i++) buffer[i] = 'Q' + rank;

    sid = sion_paropen_mpi("testB.out", "br,keyval=inline,sionfwd", &numfiles, MPI_COMM_WORLD, &lcomm, &chunksize, &fsblksize, &globalrank, &fp, &newfname);
    printf("on rank %d: sid           =%d\n",rank,sid);
    printf("on rank %d: numfiles      =%d\n",rank,numfiles);
    printf("on rank %d: chunksize     =%d\n",rank,(int) chunksize);
    printf("on rank %d: globalrank    =%d\n",rank, globalrank);
    printf("on rank %d: newfname      =%s\n",rank, newfname);

    if(sid>=0) {

      sprintf(logfilename, "keys_rank%04d_out.log", rank);
      logfp=fopen(logfilename,"w");
      if (logfp == NULL) {
	fprintf(stderr, "cannot open outfile %s , aborting ...\n", logfilename);
	return (1);
      }

      len=16;
      
      for(key = 4711;key<=4711+cycle_len;key++ ) { 

	/* find key */
	printf("on rank %d: key = %ld\n", rank, (long) key);
	for (i = 0; i < 15; i++) {
	  bread = sion_fread_key(buffer,  key, 1, len, sid);
	  if (bread != len) {
	    printf("on rank %d: end of data for key %d \n",rank, (int) key);
	    break;
	  }

	  printf("on rank %d: %3hhu | %c\n", rank, buffer[0], buffer[0]);
	  for (c = 1; c < 16; c++) {
	    if (buffer[0] != buffer[c]) {
	      printf("ERROR: inconsistent buffer\n");
	    }
	  }

	  fprintf(logfp,"on rank %d: key=%6d len=%ld val=",rank, (int) key, (long) len);
	  for (c = 0,sum=0; c < len; c++) {
	    fprintf(logfp,"%c",buffer[c]);
	    sum=sum+buffer[c];
	  }
	  fprintf(logfp,"\n");

	}

      }
      fclose(logfp);
      sion_parclose_mpi(sid);
    } else {
      fprintf(stderr, "on rank %d: error sid = %d\n",rank,sid);

    }
  }

  fflush(stderr);
  fflush(stdout);
  MPI_Barrier(MPI_COMM_WORLD);
  printf("on rank %d: END of TEST B read keyval order\n",rank);
  MPI_Barrier(MPI_COMM_WORLD);


  /* ------------------------------------------------------ */
  /* TEST C: read keyvals with iterator                     */
  /* ------------------------------------------------------ */
  if(1){
#define BUFSIZE 1000  
#define CHUNKSIZE 200
    sion_int64  chunksize = CHUNKSIZE;
    sion_int32  fsblksize = 10;
    int         globalrank= rank;
    int         numfiles  = 1;
    char       *newfname=NULL;
    int         sid;
    MPI_Comm    lcomm;
    FILE       *fp, *logfp;
    char        buffer[BUFSIZE];
    size_t      bread, len;
    char        logfilename[256];
    long        sum; 
    int         i,c, loop;
    uint64_t    key;

    for (i = 0; i < BUFSIZE; i++) buffer[i] = 'Q' + rank;

    sid = sion_paropen_mpi("testB.out", "br,keyval=inline,sionfwd", &numfiles, MPI_COMM_WORLD, &lcomm, &chunksize, &fsblksize, &globalrank, &fp, &newfname);
    printf("on rank %d: sid           =%d\n",rank,sid);
    printf("on rank %d: numfiles      =%d\n",rank,numfiles);
    printf("on rank %d: chunksize     =%d\n",rank,(int) chunksize);
    printf("on rank %d: globalrank    =%d\n",rank, globalrank);
    printf("on rank %d: newfname      =%s\n",rank, newfname);

    if(sid>=0) {


      /* iterate two time to test reset of iterator */
      for(loop=1;loop<=2;loop++)  {
	
	/* iterator reset */
	printf("on rank %d: ITERATOR Loop%d\n", rank, loop);


	sprintf(logfilename, "keys_iter_l%d_rank%04d_out.log", loop, rank);
	logfp=fopen(logfilename,"w");
	if (logfp == NULL) {
	  fprintf(stderr, "cannot open outfile %s , aborting ...\n", logfilename);
	  return (1);
	}

	sion_fread_key_iterator_reset(sid);
	
	/* loop over key-value blocks */
	while(sion_fread_key_iterator_next(sid,&key,&len)==SION_SUCCESS) {
	  
	  printf("on rank %d: key = %ld\n", rank, (long) key);
	
	  bread = sion_fread_key(buffer,  key, 1, len, sid);
	  if (bread != len) {
	    printf("on rank %d: end of data for key %d \n",rank, (int) key);
	    break;
	  }
	  /* check data */
	  printf("on rank %d: %3hhu | %c\n", rank, buffer[0], buffer[0]);
	  for (c = 1; c < 16; c++) {
	    if (buffer[0] != buffer[c]) {
	      printf("ERROR: inconsistent buffer\n");
	    }
	  }

	  /* log data */
	  fprintf(logfp,"on rank %d: key=%6d len=%ld val=",rank, (int) key, (long) len);
	  for (c = 0,sum=0; c < len; c++) {
	    fprintf(logfp,"%c",buffer[c]);
	    sum=sum+buffer[c];
	  }
	  fprintf(logfp,"\n");

	
	}

      fclose(logfp);

      }

      sion_parclose_mpi(sid);
    } else {
      fprintf(stderr, "on rank %d: error sid = %d\n",rank,sid);

    }
  }

  fflush(stderr);
  fflush(stdout);
  MPI_Barrier(MPI_COMM_WORLD);
  printf("on rank %d: END of TEST C read iterative\n",rank);
  MPI_Barrier(MPI_COMM_WORLD);

  /* -------------------------- */
  /* EPILOG */
  /* -------------------------- */
  MPI_Finalize();

  return(0);
}
