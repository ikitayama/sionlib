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

#define ONRANK if(rank==0)

#define SAFE_FREE(ptr, null) {if (ptr) {free(ptr); ptr = null;}}

#define BUFSIZE 10000 
#define CHUNKSIZE 1000

#include "test_genapi_INC_MPI_api.c"

int _write_keys_sample ( char *test,
			 int rank,
			 int sid ) {
  const int   cycle_full = 26;
  int i,j,c;
  long        sum; 
  uint64_t    key;
  size_t      bwrote, len;
  char        buffer[BUFSIZE];
  char        logfilename[256];
  FILE       *logfp;

  sprintf(logfilename, "keys%s_rank%04d_in.log", test, rank);
  logfp=fopen(logfilename,"w");

  sum=0;
  len=16;
  for(j=0;  j < (int) CHUNKSIZE / ((int) len + 32); j++) {
    
    key=4711 + j;
    for (i = 0; i < 16; i++) {
      buffer[i] = 'A' + ((key - 4711 + rank) % cycle_full);
    }
    bwrote=sion_fwrite_key(buffer, key, (size_t) 1, (size_t) len, sid); 
    if(bwrote!=len) {
      fprintf(stderr,"cannot write data bwrote==%d (%d), aborting ...\n",(int) bwrote, (int) len );
      return(1);
      
    }
    fprintf(logfp,"on rank %02d: key=%6d len=%ld val=",rank, (int) key, (long) len);
    for (c = 0,sum=0; c < len; c++) {
      fprintf(logfp,"%c",buffer[c]);
      sum=sum+buffer[c];
    }
    fprintf(logfp,"\n");
  }
  
  fclose(logfp);

  return(1);
}

int _read_keys_sample ( char *test,
			int rank,
			int sid,
			int mytask ) {
  int i,c;
  long        sum; 
  uint64_t    key;
  size_t      len;
  char        buffer[BUFSIZE];
  char        logfilename[256];
  FILE       *logfp;
  size_t      bread;
  int         numkeys;

  sprintf(logfilename, "keys%s_rank%02dt%04d_out.log", test, mytask,rank);
  logfp=fopen(logfilename,"w");

  sum=0;
  len=16;

  numkeys=(int) CHUNKSIZE / ((int) len + 32);

  for(key = 4711;key<=4711+numkeys;key++ ) { 
    
    /* find key */
    ONRANK printf("key = %ld\n", (long) key);
    for (i = 0; i < 15; i++) {
	  bread = sion_fread_key(buffer,  key, 1, len, sid);
	  if (bread != len) {
	    ONRANK printf("on rank %d: end of data for key %d \n",rank, (int) key);
	    break;
	  }
	  
	  ONRANK printf("on rank %d: %3hhu | %c\n", rank, buffer[0], buffer[0]);
	  for (c = 1; c < 16; c++) {
	    if (buffer[0] != buffer[c]) {
	      ONRANK printf("on rank %d: ERROR: inconsistent buffer\n",rank);
	    }
	  }
	  
	  fprintf(logfp,"on rank %02d: key=%6d len=%ld val=",rank, (int) key, (long) len);
	  for (c = 0,sum=0; c < len; c++) {
	    fprintf(logfp,"%c",buffer[c]);
	    sum=sum+buffer[c];
	  }
	  fprintf(logfp,"\n");
	  
    }
    
  }
  fclose(logfp);

  return(1);
}

int _read_mappedB ( char *test,
		    char * filename,
		    int aid,
		    int rank,
		    int size,
		    _sample_api_commdata *gcomm,
		    int nlocaltasks,
		    int **globalranks
		    ) {

  int rc=SION_SUCCESS;
  sion_int32  fsblksize = 100;
  sion_int64 *chunksizes = NULL;
  int         numfiles    = 3;
  int         sid;
  FILE       *fp;
  int         i,grank;
  int        *mapping_filenrs=NULL;
  int        *mapping_lranks=NULL;


  MPI_Barrier(MPI_COMM_WORLD);

  sid = sion_generic_paropen_mapped(aid,filename, "br,keyval=inline", &numfiles, gcomm, rank, size,
				    &nlocaltasks, globalranks, &chunksizes, &mapping_filenrs, &mapping_lranks,
				    &fsblksize, &fp);

  
  ONRANK printf("Test %s: rank=%02d sid=%d after open\n",test,rank,sid);

  if(sid>=0) {

    for (i = 0; i < nlocaltasks; i++) {
      ONRANK printf("Test %s: rank=%02d ltask=%0d globalrank=%02d, chunksize=%02d mapping_filenrs=%02d,mapping_lranks=%02d\n", test,
		       rank, i, (*globalranks)[i], (int) chunksizes[i], mapping_filenrs[i],mapping_lranks[i]);
    }

    for (i = 0; i < nlocaltasks; i++) {
      grank=(*globalranks)[i];
      sion_seek_fp(sid,grank,SION_CURRENT_BLK,SION_CURRENT_POS, &fp);
      
      _read_keys_sample(test,grank,sid,rank);
      
    }

    {
      int numbytes, numfds;
      sion_get_sizeof(sid, &numbytes, &numfds);
      ONRANK printf("on rank %d: sizeof(%d)=(%dbytes, %dfds)\n",rank, sid, numbytes, numfds);
    }

    ONRANK printf("Test %s: rank=%02d sid=%d before close\n",test,rank,sid);
    sion_generic_parclose_mapped(sid);

  } else {
    fprintf(stderr, "Test %s: on rank %d: error sid = %d\n",test,rank,sid);
    rc=SION_NOT_SUCCESS;
  }

  MPI_Barrier(MPI_COMM_WORLD);

  SAFE_FREE(chunksizes, NULL);
  SAFE_FREE(mapping_filenrs, NULL);
  SAFE_FREE(mapping_lranks, NULL);

  return(rc);
}

int _read_mappedB_dup ( char *test,
			char * filename,
			int aid,
			int rank,
			int size,
			_sample_api_commdata *gcomm,
			int nlocaltasks,
			int **globalranks
			) {

  int rc=SION_SUCCESS;
  sion_int32  fsblksize = 100;
  sion_int64 *chunksizes = NULL;
  int         numfiles    = 3;
  int         sid, new_sid;;
  FILE       *fp;
  int         i,grank;
  int        *mapping_filenrs=NULL;
  int        *mapping_lranks=NULL;


  MPI_Barrier(MPI_COMM_WORLD);

  sid = sion_generic_paropen_mapped(aid,filename, "br,keyval=inline", &numfiles, gcomm, rank, size,
				    &nlocaltasks, globalranks, &chunksizes, &mapping_filenrs, &mapping_lranks,
				    &fsblksize, &fp);

  
  ONRANK printf("Test %s: rank=%02d sid=%d after open\n",test,rank,sid);

  if(sid>=0) {

    /* dup sion file pointer  */
    new_sid=sion_dup(sid,SION_DUP_ALL,0,0);
    ONRANK printf("on rank %d: dup, new_sid       =%d\n",rank,new_sid);

    for (i = 0; i < nlocaltasks; i++) {
      ONRANK printf("Test %s: rank=%02d ltask=%0d globalrank=%02d, chunksize=%02d mapping_filenrs=%02d,mapping_lranks=%02d\n", test,
		       rank, i, (*globalranks)[i], (int) chunksizes[i], mapping_filenrs[i],mapping_lranks[i]);
    }

    for (i = 0; i < nlocaltasks; i++) {
      grank=(*globalranks)[i];
      sion_seek_fp(new_sid,grank,SION_CURRENT_BLK,SION_CURRENT_POS, &fp);
      
      _read_keys_sample(test,grank,new_sid,rank);
      
    }

    {
      int numbytes, numfds;
      sion_get_sizeof(new_sid, &numbytes, &numfds);
      ONRANK printf("on rank %d: sizeof(%d)=(%d bytes, %d fds)\n",rank,new_sid, numbytes, numfds);
    }

    /* destry dup sion file pointer */
    ONRANK printf("on rank %d: dedup(%d)\n",rank,new_sid);
    sion_dedup(new_sid);

    {
      int numbytes, numfds;
      sion_get_sizeof(sid, &numbytes, &numfds);
      ONRANK printf("on rank %d: sizeof(%d)=(%d bytes, %d fds)\n",rank, sid, numbytes, numfds);
    }

    ONRANK printf("Test %s: rank=%02d sid=%d before close\n",test,rank,sid);
    sion_generic_parclose_mapped(sid);

  } else {
    fprintf(stderr, "Test %s: on rank %d: error sid = %d\n",test,rank,sid);
    rc=SION_NOT_SUCCESS;
  }

  MPI_Barrier(MPI_COMM_WORLD);

  SAFE_FREE(chunksizes, NULL);
  SAFE_FREE(mapping_filenrs, NULL);
  SAFE_FREE(mapping_lranks, NULL);

  return(rc);
}

int main(int argc, char **argv)
{
  int  rank, size;
  int aid;
  _sample_api_commdata gcomm;

  /* -------------------------- */
  /* PROLOG */
  /* -------------------------- */

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  /* -------------------------- */
  /* TEST 0: define new API     */
  /* -------------------------- */
  {
    aid=sion_generic_create_api("SampleAPI");
    ONRANK printf("on rank %d: new API: aid=%d\n",rank,aid);  

    gcomm.comm=MPI_COMM_WORLD;
    gcomm.commset=1;
    gcomm.local=0;    gcomm.rank=rank; gcomm.rank=size;
  
    sion_generic_register_create_local_commgroup_cb(aid,&_sample_create_lcg_cb);
    sion_generic_register_free_local_commgroup_cb(aid,&_sample_free_lcg_cb);

    sion_generic_register_barrier_cb(aid,&_sample_barrier_cb);
    sion_generic_register_bcastr_cb(aid,&_sample_bcastr_cb);
    sion_generic_register_gatherr_cb(aid,&_sample_gatherr_cb);
    sion_generic_register_scatterr_cb(aid,&_sample_scatterr_cb);
    sion_generic_register_gathervr_cb(aid,&_sample_gathervr_cb);
    sion_generic_register_scattervr_cb(aid,&_sample_scattervr_cb);

    ONRANK printf("on rank %d: END of TEST 0\n",rank);
   
  }


  /* ---------------------------------------------------------------------------- */
  /* TEST B: create from 4 task multiple sion file containing 20 tasks in 3 files */
  /* ---------------------------------------------------------------------------- */
  if(1){
    sion_int32  fsblksize = 100; 
    /* sion_int32  fsblksize = -1; */
    sion_int64 *chunksizes = NULL;
    int        *globalranks = NULL;
    int        *mapping_filenrs;
    int        *mapping_lranks;
    int         numfiles    = 3;
    int         nlocaltasks = 5;
    int         sid;
    FILE       *fp;
    int         i,t,taskperfile,grank;

    chunksizes = (sion_int64 *) malloc(nlocaltasks * sizeof(sion_int64));
    if (chunksizes == NULL) {
      fprintf(stderr,"TEST B: cannot allocate chunksizes of size %lu, aborting ...\n",
	      (unsigned long) nlocaltasks * sizeof(sion_int64));
      return(1);
    }
    globalranks = (int *) malloc(nlocaltasks * sizeof(int));
    if (globalranks== NULL) {
      fprintf(stderr,"TEST B: cannot allocate globalranks size %lu, aborting ...\n",
	      (unsigned long) nlocaltasks * sizeof(int));
      return(1);
    }
    mapping_filenrs = (int *) malloc(nlocaltasks * sizeof(int));
    if (mapping_filenrs == NULL) {
      fprintf(stderr,"TEST B: cannot allocate mapping_filenrs size %lu, aborting ...\n",
	      (unsigned long) mapping_filenrs * sizeof(int));
      return(1);
    }
    mapping_lranks = (int *) malloc(nlocaltasks * sizeof(int));
    if (mapping_lranks == NULL) {
      fprintf(stderr,"TEST B: cannot allocate mapping_lranks size %lu, aborting ...\n",
	      (unsigned long) mapping_lranks * sizeof(int));
      return(1);
    }

    taskperfile=(nlocaltasks*size)/numfiles;
    if((nlocaltasks*size)%numfiles>0)  taskperfile++;
 
    for (i = 0; i < nlocaltasks; i++) {
      globalranks[i] = rank+i*size;  /* strided ordering */
      chunksizes[i]  = CHUNKSIZE;
      mapping_filenrs[i] = globalranks[i]/taskperfile; 
      mapping_lranks[i]  = globalranks[i]%taskperfile; 
    }

    for (t = 0; t < size; t++) {
      MPI_Barrier(MPI_COMM_WORLD);
      if(t==rank) {
	for (i = 0; i < nlocaltasks; i++) {
	  ONRANK printf("Test B: rank=%02d ltask=%0d globalrank=%02d, chunksize=%02d mapping_filenrs=%02d,mapping_lranks=%02d\n",
		 rank,i, globalranks[i], (int) chunksizes[i], mapping_filenrs[i],mapping_lranks[i]);
	}
      }

    }
    MPI_Barrier(MPI_COMM_WORLD);

    sid = sion_generic_paropen_mapped(aid,"test_mappedB.out", "bw,keyval=inline", &numfiles, &gcomm, rank, size,
				      &nlocaltasks, &globalranks, &chunksizes, &mapping_filenrs, &mapping_lranks,
				      &fsblksize, &fp);
    if(sid>=0) {

      for (i = 0; i < nlocaltasks; i++) {
	grank=globalranks[i];
	sion_seek_fp(sid,grank,SION_CURRENT_BLK,SION_CURRENT_POS, &fp);	
	
	_write_keys_sample("B",grank,sid);
	
      }

      sion_generic_parclose_mapped(sid);
    } else {
      fprintf(stderr, "on rank %d: error sid = %d\n",rank,sid);

    }
    SAFE_FREE(chunksizes, NULL);
    SAFE_FREE(globalranks, NULL);
    SAFE_FREE(mapping_filenrs, NULL);
    SAFE_FREE(mapping_lranks, NULL);
  }

  fflush(stderr);
  fflush(stdout);
  MPI_Barrier(MPI_COMM_WORLD);
  ONRANK printf("on rank %d: END of TEST B multiple files\n",rank);
  MPI_Barrier(MPI_COMM_WORLD);


  /* globalranks for test_mappedB file are in range from 0..19 and distributed as follows: ([grank -> (file,lrank)])
     
     [00000 -> (f000,t000)] [00001 -> (f000,t001)] [00002 -> (f000,t002)]
     [00003 -> (f000,t003)] [00004 -> (f000,t004)] [00005 -> (f000,t005)]
     [00006 -> (f000,t006)] 
     
     [00007 -> (f001,t000)] [00008 -> (f001,t001)] [00009 -> (f001,t002)]
     [00010 -> (f001,t003)] [00011 -> (f001,t004)] [00012 -> (f001,t005)]
     [00013 -> (f001,t006)] 
     
     [00014 -> (f002,t000)] [00015 -> (f002,t001)] [00016 -> (f002,t002)]
     [00017 -> (f002,t003)] [00018 -> (f002,t004)] [00019 -> (f002,t005)]
     
  */



  /* ---------------------------------------------------------------------------- */
  /* TEST C: create from 4 task multiple sion file containing 20 tasks in 5 files */
  /* ---------------------------------------------------------------------------- */
  if(1){
    sion_int32  fsblksize = 100; 
    /* sion_int32  fsblksize = -1; */
    sion_int64 *chunksizes = NULL;
    int        *globalranks = NULL;
    int        *mapping_filenrs;
    int        *mapping_lranks;
    int         numfiles    = 5;
    int         nlocaltasks = 5;
    int         sid;
    FILE       *fp;
    int         i,t,taskperfile,grank;

    chunksizes = (sion_int64 *) malloc(nlocaltasks * sizeof(sion_int64));
    if (chunksizes == NULL) {
      fprintf(stderr,"TEST C: cannot allocate chunksizes of size %lu, aborting ...\n",
	      (unsigned long) nlocaltasks * sizeof(sion_int64));
      return(1);
    }
    globalranks = (int *) malloc(nlocaltasks * sizeof(int));
    if (globalranks== NULL) {
      fprintf(stderr,"TEST C: cannot allocate globalranks size %lu, aborting ...\n",
	      (unsigned long) nlocaltasks * sizeof(int));
      return(1);
    }
    mapping_filenrs = (int *) malloc(nlocaltasks * sizeof(int));
    if (mapping_filenrs == NULL) {
      fprintf(stderr,"TEST C: cannot allocate mapping_filenrs size %lu, aborting ...\n",
	      (unsigned long) mapping_filenrs * sizeof(int));
      return(1);
    }
    mapping_lranks = (int *) malloc(nlocaltasks * sizeof(int));
    if (mapping_lranks == NULL) {
      fprintf(stderr,"TEST C: cannot allocate mapping_lranks size %lu, aborting ...\n",
	      (unsigned long) mapping_lranks * sizeof(int));
      return(1);
    }

    taskperfile=(nlocaltasks*size)/numfiles;
    if((nlocaltasks*size)%numfiles>0)  taskperfile++;
 
    for (i = 0; i < nlocaltasks; i++) {
      globalranks[i] = rank+i*size;  /* strided ordering */
      chunksizes[i]  = CHUNKSIZE;
      mapping_filenrs[i] = globalranks[i]/taskperfile; 
      mapping_lranks[i]  = globalranks[i]%taskperfile; 
    }

    for (t = 0; t < size; t++) {
      MPI_Barrier(MPI_COMM_WORLD);
      if(t==rank) {
	for (i = 0; i < nlocaltasks; i++) {
	  ONRANK printf("Test C: rank=%02d ltask=%0d globalrank=%02d, chunksize=%02d mapping_filenrs=%02d,mapping_lranks=%02d\n",
		 rank,i, globalranks[i], (int) chunksizes[i], mapping_filenrs[i],mapping_lranks[i]);
	}
      }

    }
    MPI_Barrier(MPI_COMM_WORLD);

    sid = sion_generic_paropen_mapped(aid,"test_mappedC.out", "bw,keyval=inline", &numfiles, &gcomm, rank, size,
				      &nlocaltasks, &globalranks, &chunksizes, &mapping_filenrs, &mapping_lranks,
				      &fsblksize, &fp);
    if(sid>=0) {

      for (i = 0; i < nlocaltasks; i++) {
	grank=globalranks[i];
	sion_seek_fp(sid,grank,SION_CURRENT_BLK,SION_CURRENT_POS, &fp);	
	
	_write_keys_sample("C",grank,sid);
	
      }
      
      sion_generic_parclose_mapped(sid);
    } else {
      fprintf(stderr, "on rank %d: error sid = %d\n",rank,sid);

    }
    SAFE_FREE(chunksizes, NULL);
    SAFE_FREE(globalranks, NULL);
    SAFE_FREE(mapping_filenrs, NULL);
    SAFE_FREE(mapping_lranks, NULL);
  }

  fflush(stderr);
  fflush(stdout);
  MPI_Barrier(MPI_COMM_WORLD);
  ONRANK printf("on rank %d: END of TEST C multiple files\n",rank);
  MPI_Barrier(MPI_COMM_WORLD);


  /* globalranks for test_mappedC file are in range from 0..19 and distributed as follows: ([grank -> (file,lrank)])
     
        [00000 -> (f000,t000)] [00001 -> (f000,t001)] [00002 -> (f000,t002)]
        [00003 -> (f000,t003)]
	
	[00004 -> (f001,t000)] [00005 -> (f001,t001)] [00006 -> (f001,t002)]
	[00007 -> (f001,t003)]

	[00008 -> (f002,t000)] [00009 -> (f002,t001)] [00010 -> (f002,t002)]
        [00011 -> (f002,t003)]

	[00012 -> (f003,t000)] [00013 -> (f003,t001)] [00014 -> (f003,t002)]
        [00015 -> (f003,t003)]

	[00016 -> (f004,t000)] [00017 -> (f004,t001)] [00018 -> (f004,t002)]
	[00019 -> (f004,t003)]
     
  */

  /* ------------------------------------------------------------------ */
  /* TEST D: read from 4 task multiple sion file containing 20 tasks    */
  /* ------------------------------------------------------------------ */
  if(1) {
    int        *globalranks = NULL;
    int         nlocaltasks = 5;
    int         i;

    globalranks = (int *) malloc(nlocaltasks * sizeof(int));
    if (globalranks== NULL) {
      fprintf(stderr,"TEST D: cannot allocate globalranks size %lu, aborting ...\n",
	      (unsigned long) nlocaltasks * sizeof(int));
      return(1);
    }
    /* define access pattern: strided ordering */
    for (i = 0; i < nlocaltasks; i++) {
      globalranks[i] = rank+i*size;
    }
    _read_mappedB("D","test_mappedB.out",aid,rank,size,&gcomm,nlocaltasks,&globalranks);

    SAFE_FREE(globalranks, NULL);
  }

  fflush(stderr);
  fflush(stdout);
  MPI_Barrier(MPI_COMM_WORLD);
  ONRANK printf("on rank %d: END of TEST D multiple files\n",rank);
  MPI_Barrier(MPI_COMM_WORLD);

  /* ------------------------------------------------------------------------------------------ */
  /* TEST E: read from 4 task multiple sion file containing 20 tasks, multiple open to tasks    */
  /* ------------------------------------------------------------------------------------------ */
  if(1){
    int        *globalranks = NULL;
    int         nlocaltasks = 8;
    int         i,start;

    globalranks = (int *) malloc(nlocaltasks * sizeof(int));
    if (globalranks== NULL) {
      fprintf(stderr,"TEST E: cannot allocate globalranks size %lu, aborting ...\n",
	      (unsigned long) nlocaltasks * sizeof(int));
      return(1);
    }

    /* define access pattern */
    start=rank*4;
    for (i = 0; i < nlocaltasks; i++) {
      globalranks[i] = start+i;  /* overlapping block ordering */
    }

    _read_mappedB("E","test_mappedB.out",aid,rank,size,&gcomm,nlocaltasks,&globalranks);

    SAFE_FREE(globalranks, NULL);
  }

  fflush(stderr);
  fflush(stdout);
  MPI_Barrier(MPI_COMM_WORLD);
  ONRANK printf("on rank %d: END of TEST E multiple files\n",rank);
  MPI_Barrier(MPI_COMM_WORLD);


  /* ------------------------------------------------------------------------------------------ */
  /* TEST F: read from 4 task multiple sion file containing 20 tasks, pre-computed distribution */
  /* ------------------------------------------------------------------------------------------ */
  if(1){
    int        *globalranks = NULL;
    int         nlocaltasks = -1;

    _read_mappedB("F","test_mappedB.out",aid,rank,size,&gcomm,nlocaltasks,&globalranks);

    SAFE_FREE(globalranks, NULL);
  }

  fflush(stderr);
  fflush(stdout);
  MPI_Barrier(MPI_COMM_WORLD);
  ONRANK printf("on rank %d: END of TEST F multiple files\n",rank);
  MPI_Barrier(MPI_COMM_WORLD);


  /* ----------------------------------------------------------------------------------------------------------- */
  /* TEST G: read from 4 task multiple sion file containing 20 tasks, multiple open to tasks, no globalrank = 0  */
  /* ----------------------------------------------------------------------------------------------------------- */
  if(1){
    int        *globalranks = NULL;
    int         nlocaltasks = 8;

    if(rank==0) nlocaltasks=1;
    if(rank==1) nlocaltasks=1;
    if(rank==2) nlocaltasks=1;
    if(rank==3) nlocaltasks=1;

    globalranks = (int *) malloc(nlocaltasks * sizeof(int));
    if (globalranks== NULL) {
      fprintf(stderr,"TEST G: cannot allocate globalranks size %lu, aborting ...\n",
	      (unsigned long) nlocaltasks * sizeof(int));
      return(1);
    }

    /* test scenario: 
       - no rank opens lrank 0 of file 0 and 1  
       - no rank opens lranks of file 2 */
    if(rank==0) {
      globalranks[0]=1;
    }
    if(rank==1) {
      globalranks[0]=8;
    }
    if(rank==2) {
      globalranks[0]=11;
    }
    if(rank==3) {
      globalranks[0]=12;
    }

    _read_mappedB("G","test_mappedB.out",aid,rank,size,&gcomm,nlocaltasks,&globalranks);

    SAFE_FREE(globalranks, NULL);
  }

  fflush(stderr);
  fflush(stdout);
  MPI_Barrier(MPI_COMM_WORLD);
  ONRANK printf("on rank %d: END of TEST G multiple files\n",rank);
  MPI_Barrier(MPI_COMM_WORLD);

  /* ----------------------------------------------------------------------------------------------------------- */
  /* TEST H: read from 4 task multiple sion file containing 20 tasks, no task reads data                         */
  /* ----------------------------------------------------------------------------------------------------------- */
  if(1){
    int        *globalranks = NULL;
    int         nlocaltasks = 0;

    _read_mappedB("H","test_mappedB.out",aid,rank,size,&gcomm,nlocaltasks,&globalranks);

    SAFE_FREE(globalranks, NULL);
  }

  fflush(stderr);
  fflush(stdout);
  MPI_Barrier(MPI_COMM_WORLD);
  ONRANK printf("on rank %d: END of TEST H multiple files\n",rank);
  MPI_Barrier(MPI_COMM_WORLD);


  /* ----------------------------------------------------------------------------------------------------------- */
  /* TEST I: read from 4 task multiple sion file containing 20 tasks, multiple open to tasks, no globalrank = 0  */
  /* ----------------------------------------------------------------------------------------------------------- */
  if(1){
    int        *globalranks = NULL;
    int         nlocaltasks = 8;

    if(rank==0) nlocaltasks=1;
    if(rank==1) nlocaltasks=1;
    if(rank==2) nlocaltasks=1;
    if(rank==3) nlocaltasks=1;

    globalranks = (int *) malloc(nlocaltasks * sizeof(int));
    if (globalranks== NULL) {
      fprintf(stderr,"TEST I: cannot allocate globalranks size %lu, aborting ...\n",
	      (unsigned long) nlocaltasks * sizeof(int));
      return(1);
    }

    /* test scenario: 
       - no rank opens lrank 0 of file 0 and 1  
       - no rank opens lranks of file 2 */
    if(rank==0) {
      globalranks[0]=1;
    }
    if(rank==1) {
      globalranks[0]=8;
    }
    if(rank==2) {
      globalranks[0]=11;
    }
    if(rank==3) {
      globalranks[0]=12;
    }

    _read_mappedB("I","test_mappedC.out",aid,rank,size,&gcomm,nlocaltasks,&globalranks);

    SAFE_FREE(globalranks, NULL);
  }

  fflush(stderr);
  fflush(stdout);
  MPI_Barrier(MPI_COMM_WORLD);
  ONRANK printf("on rank %d: END of TEST I multiple files\n",rank);
  MPI_Barrier(MPI_COMM_WORLD);

  /* ----------------------------------------------------------------------- */
  /* TEST J: read from 4 task multiple sion file containing 20 tasks (dup)   */
  /* ----------------------------------------------------------------------- */
  if(1) {
    int        *globalranks = NULL;
    int         nlocaltasks = 5;
    int         i;

    globalranks = (int *) malloc(nlocaltasks * sizeof(int));
    if (globalranks== NULL) {
      fprintf(stderr,"TEST J: cannot allocate globalranks size %lu, aborting ...\n",
	      (unsigned long) nlocaltasks * sizeof(int));
      return(1);
    }
    /* define access pattern: strided ordering */
    for (i = 0; i < nlocaltasks; i++) {
      globalranks[i] = rank+i*size;
    }
    _read_mappedB_dup("J","test_mappedB.out",aid,rank,size,&gcomm,nlocaltasks,&globalranks);

    SAFE_FREE(globalranks, NULL);
  }

  fflush(stderr);
  fflush(stdout);
  MPI_Barrier(MPI_COMM_WORLD);
  ONRANK printf("on rank %d: END of TEST J multiple files\n",rank);
  MPI_Barrier(MPI_COMM_WORLD);

  sion_generic_free_api(aid);

  /* -------------------------- */
  /* EPILOG */
  /* -------------------------- */
  MPI_Finalize();

  return(0);
}
#undef SAFE_FREE
