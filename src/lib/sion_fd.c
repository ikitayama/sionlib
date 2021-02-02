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
 *
 * @author Th.Eickermann & W.Frings (December 2000)
 *
 */

#define _XOPEN_SOURCE 700

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include "sion_lock.h"
#include "sion_fd.h"

#define sion_assert(expr, args) (assert(expr))

#define SION_FDDATA_INITIALIZER {0,0,-1,NULL}

/************************/
static struct _sion_fddata {
  int size;
  int nfree;
  int last_freed;
  struct _sion_fd *list;
} lsion_fd_data = SION_FDDATA_INITIALIZER;

static char *text;              /* just a temp hack */

/* some abbreviations for fd functions */
/*! Wrapper for _lsion_new_fd() */
int _lsion_newvcd(void *data, int type)
{
  return _lsion_new_fd(&lsion_fd_data, data, type);
}
/*! Wrapper for _lsion_free_fd() */
int _lsion_freevcd(int sid)
{
  return _lsion_free_fd(&lsion_fd_data, sid, text);
}
/*! Wrapper for _lsion_fd2ptr() */
void     *_lsion_vcdtovcon(int sid)
{
  return _lsion_fd2ptr(&lsion_fd_data, sid);
}
/*! Wrapper for _lsion_fd2type() */
int _lsion_vcdtype(int sid)
{
  return _lsion_fd2type(&lsion_fd_data, sid, text);
}
/*! Wrapper for _lsion_reassign_fd() */
int _lsion_reassignvcd(int sid, void *data, int type)
{
  return _lsion_reassign_fd(&lsion_fd_data, sid, data, type, text);
}
/************************/



/*!
 * Get a new descriptor and assign data/type to it.
 *
 * @return The new descriptor or -1 in case of an error.
 */
int _lsion_new_fd(sion_fddata *fdd, void *data, int type)
{
  int       i;

  _lsion_lock();

  /* if we are sure that we have at least 2 free descriptors,
   * we can guarantee, that we don't need to reuse a freed
   * one immediately
   * so enlarge array of descriptors if we have less than 2 free ones
   */
  if (fdd->nfree < 2) {
    int       new_size;

    new_size = fdd->size + SION_FD_CHUNK;

    if (fdd->list) {
      fdd->list = realloc(fdd->list, new_size * sizeof(struct _sion_fd));
    }
    else {
      fdd->list = malloc(new_size * sizeof(struct _sion_fd));
    }
    sion_assert(fdd->list, ("out of memory"));

    for (i = fdd->size; i < new_size; i++) {
      fdd->list[i].state = 0;   /* free */
      fdd->list[i].type = 0;
      fdd->list[i].data = NULL;
    }

    fdd->size = new_size;
    fdd->nfree += SION_FD_CHUNK;
  }

  /* use first 'fresh' index */
  for (i = 0; i < fdd->size; i++) {
    if (fdd->list[i].state == 0) {
      fdd->list[i].data = data;
      fdd->list[i].type = type;
      fdd->list[i].state = 1;
      fdd->nfree--;
      _lsion_unlock();
      return i;
    }
  }

  /* if all have been used before, use a 'closed' one,
   * start seraching a new one AFTER the last freed
   * so this one will not be reused immediately
   */
  for (i = fdd->last_freed + 1; i < fdd->last_freed + 1 + fdd->size; i++) {
    int       imod = i % fdd->size;
    if (fdd->list[imod].state == -1) {
      fdd->list[imod].data = data;
      fdd->list[imod].type = type;
      fdd->list[imod].state = 1;
      fdd->nfree--;
      _lsion_unlock();
      return imod;
    }
  }
  sion_assert(0, ("oops - we should never get here"));
  return -1;
}


/*!
 * Add data/type to the descriptor fd. fd must be non-negative
 * and not be in use
 *
 * @return 1 if successful, 0 otherwise
 */
int _lsion_set_fd(sion_fddata *fdd, int fd, void *data, int type, char *text)
{

  if (text && (!*text))
    text = "_lsion_set_fd";

  if (fd < 0) {
    if (text) {
      fprintf(stderr, "%s: trying to set an invalid descriptor fd=%d.\n", text, fd);
    }
    return 0;
  }

  _lsion_lock();

  if (fd >= fdd->size) {
    /*
     * enlarge descriptor array if neccessary
     *
     */
    int       i, new_size;

    new_size = fdd->size + SION_FD_CHUNK;
    while (fd >= new_size) {
      new_size += SION_FD_CHUNK;
    }

    if (fdd->list) {
      fdd->list = realloc(fdd->list, new_size * sizeof(struct _sion_fd));
    }
    else {
      fdd->list = malloc(new_size * sizeof(struct _sion_fd));
    }
    sion_assert(fdd->list, ("out of memory"));

    for (i = fdd->size; i < new_size; i++) {
      fdd->list[i].state = 0;   /* free */
      fdd->list[i].type = 0;
      fdd->list[i].data = NULL;
    }

    fdd->nfree += new_size - fdd->size;
    fdd->size = new_size;
  }
  else if (fdd->list[fd].state == 1) {
    if (text) {
      fprintf(stderr, "%s: trying to set a descriptor that is in use fd=%d.\n", text, fd);
    }
    _lsion_unlock();
    return 0;
  }

  fdd->list[fd].data = data;
  fdd->list[fd].type = type;
  fdd->list[fd].state = 1;
  fdd->nfree--;

  _lsion_unlock();
  return 1;
}


/*!
 * free a descriptor
 */
int _lsion_free_fd(sion_fddata *fdd, int fd, char *text)
{

  _lsion_lock();
  if ((fd < fdd->size) && (fd >= 0) && (fdd->list) && (fdd->list[fd].state == 1)) {
    fdd->list[fd].state = -1;
    fdd->nfree++;
    fdd->last_freed = fd;       /* remember this one to avoid immediate reuse */

    if (fdd->nfree == fdd->size) {
      free(fdd->list);
      fdd->list = NULL;
      fdd->nfree = 0;
      fdd->size = 0;
    }

    _lsion_unlock();
    return 1;
  }
  else {
    if (text) {
      if (!*text)
        text = "_lsion_free_fd";
      fprintf(stderr, "%s: trying to free an invalid descriptor fd=%d.\n", text, fd);
    }
    _lsion_unlock();
    return 0;
  }
}


/*!
 * @return The data associated with a descriptor
 */
void     *_lsion_fd2ptr(sion_fddata *fdd, int fd)
{
  _lsion_lock();
  if ((fd < fdd->size) && (fd >= 0) && (fdd->list[fd].state == 1)) {
    void *ptr = fdd->list[fd].data;
    _lsion_unlock();
    return ptr;
  }
  else {
    _lsion_unlock();
    return NULL;
  }
}


/*!
 * @return The type (of data) associated with a descriptor
 */
int _lsion_fd2type(sion_fddata *fdd, int fd, char *text)
{
  _lsion_lock();
  if ((fd < fdd->size) && (fd >= 0) && (fdd->list[fd].state == 1)) {
    int type = fdd->list[fd].type;
    _lsion_unlock();
    return type;
  }
  else {
    if (text) {
      if (!*text)
        text = "_lsion_fd2type";
      fprintf(stderr, "%s: invalid descriptor fd=%d.\n", text, fd);
    }
    _lsion_unlock();
    return -1;
  }
}


/*!
 * @return The smallest valid descriptor, that has 'data' associated to
 * or -1 if there is none
 */
int _lsion_ptr2fd(sion_fddata *fdd, void *ptr, char *text)
{
  int       i;

  _lsion_lock();
  for (i = 0; i < fdd->size; i++) {
    if ((fdd->list[i].state == 1) && (fdd->list[i].data == ptr)) {
      _lsion_unlock();
      return i;
    }
  }
  if (text) {
    if (!*text)
      text = "_lsion_ptr2fd";
    fprintf(stderr, "%s: invalid pointer ptr=%x.\n", text, (unsigned) (size_t) ptr);
  }
  _lsion_unlock();
  return -1;
}


/*!
 * Assign new data/type to descriptor fd, where fd must be in use
 *
 * @return 1 if successful, 0 otherwise
 */
int _lsion_reassign_fd(sion_fddata *fdd, int fd, void *data, int type, char *text)
{
  _lsion_lock();
  if ((fd < fdd->size) && (fd >= 0) && (fdd->list[fd].state == 1)) {
    fdd->list[fd].data = data;
    fdd->list[fd].type = type;
    _lsion_unlock();
    return 1;
  }
  else {
    if (text) {
      if (!*text)
        text = "_lsion_reassign_fd";
      fprintf(stderr, "%s: invalid descriptor fd=%d.\n", text, fd);
    }
    _lsion_unlock();
    return 0;
  }
}


/*!
 * @return The size of the descriptor array.
 */
int _lsion_fd_size(sion_fddata *fdd)
{
  /* should be atomic */
  return fdd->size;
}
