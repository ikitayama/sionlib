
#include "mpi.h"

#include "sion_cxx_mpi.hpp"

namespace sionlib {

  namespace mpi {

    LSIONFile::LSIONFile() {
      std::cerr << "At least name has to be given\n";
      exit (EXIT_FAILURE);
    }

    LSIONFile::LSIONFile(std::string sion_file_name, std::string mode, int num_files,
		       int global_rank, MPI_Comm gComm, MPI_Comm lComm) {

      size_t ncharacter = sion_file_name.length()+1;
      const char * tmp_sion_file_name = sion_file_name.c_str();
      _sion_file_name = new char[ncharacter];

      strncpy(_sion_file_name, tmp_sion_file_name, ncharacter);

      _mode = mode;
      _num_files = num_files;

      _g_comm = gComm;

      _l_comm = lComm;

      _chunk_size = 2097152;
      _fs_blk_size = -1;

      _file_ptr = NULL;
      _new_sion_file_name = new char[255];

    }

    LSIONFile::~LSIONFile() {
      delete [] _sion_file_name;
      _sion_file_name = NULL;
      delete [] _new_sion_file_name;
      _new_sion_file_name = NULL;
      //	lsion_parclose_mpi(_sid);
    }

    //void LSIONFile::setSionFileName(std::string sion_file_name) {
    //	_sion_file_name = sion_file_name;
    //}

    void LSIONFile::setLocalCommunicator(MPI_Comm lComm) {
      _l_comm = lComm;
    }

    MPI_Comm LSIONFile::getLocalCommunicator() const {
      return _l_comm;
    }

    void LSIONFile::setGlobalCommunicator(MPI_Comm gComm) {
      _g_comm = gComm;
    }

    MPI_Comm LSIONFile::getGlobalCommunicator() const {
      return _g_comm;
    }

    void LSIONFile::setGlobalRank(int global_rank) {
      _global_rank = global_rank;
    }

    int LSIONFile::getGlobalRank() const {
      return _global_rank;
    }

    char * LSIONFile::getNewSionFileName() const {
      return _new_sion_file_name;
    }
    //std::ostream* LSIONFile::getSionStream() const {
    //	return _sion_stream;
    //}

    // lsion_paropen_mpi
    //int LSIONFile::open() {
    //
    //	_sid = lsion_paropen_mpi(_sion_file_name,
    //			_mode.c_str(),
    //			&_num_files,
    //			MPI_COMM_WORLD,
    //			&_l_comm,
    //			&_chunk_size,
    //			&_fs_blk_size,
    //			&_global_rank,
    //			&_file_ptr,
    //			&_new_sion_file_name);
    ////	std::cout << "in open() _new_sion_file_name:\t" << _new_sion_file_name << std::endl;
    //	return _sid;
    //
    //}

    void LSIONFile::open() {
      _sid = lsion_paropen_mpi(_sion_file_name, _mode.c_str(), &_num_files,
			      _g_comm, &_l_comm, &_chunk_size, &_fs_blk_size,
			      &_global_rank, NULL, &_new_sion_file_name);
      _return_code = _sid;
    }

    void LSIONFile::close() {
      //	fwrite(void *).
      _return_code = lsion_parclose_mpi (_sid);
    }

    //void LSIONFile::read() {
    ////	char * buffer = new char[8];
    //	double * buffer = new double();
    //	lsion_fread(buffer, 1, 8, _sid);
    //	std::cout << *buffer << std::endl;
    //}

    void LSIONFile::ensureFreeSpace(long numbytes) {
      _return_code = lsion_ensure_free_space(_sid, numbytes);
    }

    void LSIONFile::endOfFile() {
      _return_code = lsion_feof(_sid);
    }

  } /* namespace mpi */
} /* namespace sionlib */
