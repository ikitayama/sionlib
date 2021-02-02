
#include <iostream>
#include "sion_cxx_base.hpp"

// Common functions
char* LSION_Base::getSionFileName() const {
  return _sion_file_name;
}

void LSION_Base::setMode(std::string mode) {
  _mode = mode;
}

std::string LSION_Base::getMode() const {
  return _mode;
}


void LSION_Base::setNumberOfFiles(int num_files) {
  _num_files = num_files;
}

int LSION_Base::getNumberOfFiles() const {
  return _num_files;
}

void LSION_Base::setNumberOfTasks(int num_tasks) {
  _num_tasks = num_tasks;
}

int LSION_Base::getNumberOfTasks() const {
  return _num_tasks;
}

void LSION_Base::setRank(int rank) {
  _rank = rank;
}

int LSION_Base::getRank() const {
  return _rank;
}

void LSION_Base::setChunkSize(sion_int64 chunk_size) {
  _chunk_size = chunk_size;
}

sion_int64 LSION_Base::getChunkSize() const {
  return _chunk_size;
}

void LSION_Base::setChunkSizes(sion_int64 * chunk_sizes) {
  _chunk_sizes = chunk_sizes;
}

sion_int64 * LSION_Base::getChunkSizes() const {
  return _chunk_sizes;
}

void LSION_Base::setGlobalRanks(int * global_ranks) {
  _global_ranks = global_ranks;
}

int * LSION_Base::getGlobalRanks() const {
  return _global_ranks;
}

void LSION_Base::setFileSystemBlockSize(sion_int32 fs_blk_size) {
  _fs_blk_size = fs_blk_size;
}

sion_int32 LSION_Base::getFileSystemBlockSize() const {
  return _fs_blk_size;
}

int LSION_Base::getNumberOfSuccessfulReadElements() const {
  return _number_of_elements_sucessfully_read;
}

int LSION_Base::getReturnCode() const {
  return _return_code;
}

int LSION_Base::getSid() const {
  return _sid;
}


/* get information (with sion datatypes) */
int LSION_Base::getFileEndianness() const {
  return lsion_get_file_endianness(_sid);
}

sion_int64 LSION_Base::getBytesWritten() const {
  return lsion_get_bytes_written(_sid);
}

sion_int64 LSION_Base::getBytesRead() const {
  return lsion_get_bytes_read(_sid);
}

sion_int64 LSION_Base::getBytesAvailInBlock() const {
  return lsion_bytes_avail_in_block(_sid);
}

sion_int64 LSION_Base::getBytesAvailInChunk() const {
  return lsion_bytes_avail_in_chunk(_sid);
}

sion_int64 LSION_Base::getPosition() const {
  return lsion_get_position(_sid);
}


/* Seeking */
void LSION_Base::seek() {
  _return_code = lsion_seek(_sid,SION_CURRENT_RANK,SION_CURRENT_BLK,SION_CURRENT_POS);
}

// void LSION_Base::seekFp() {
//   _return_code = lsion_seek_fp(_sid, _rank, SION_CURRENT_BLK,SION_CURRENT_POS,&_file_ptr);

