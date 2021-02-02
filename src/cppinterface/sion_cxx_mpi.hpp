
#ifndef SION_CXX_MPI_HPP_
#define SION_CXX_MPI_HPP_

#ifdef MPI_VERSION

#include <mpi.h>
#include "sion.h"
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include "sion_cxx_base.hpp"

namespace sionlib {
  namespace mpi {

    class LSIONFile : public LSION_Base {
    public:
    
      LSIONFile();
      LSIONFile(std::string sion_file_name, std::string mode = "bw",
	       int num_files = 1, int global_rank = 0, MPI_Comm gComm=MPI_COMM_WORLD, MPI_Comm lComm=MPI_COMM_WORLD);
      virtual ~LSIONFile();

      // Don't copy LSIONFile
      LSIONFile(const LSIONFile& rhs) {
      }

      char * getNewSionFileName() const;

      //	std::ostream* getSionStream() const;

      //	template<class T>
      //	LSIONFile& LSIONFile::operator<<(T rhs);

      //	int open();

      void setLocalCommunicator(MPI_Comm lComm);
      MPI_Comm getLocalCommunicator() const;

      void setGlobalCommunicator(MPI_Comm gComm);
      MPI_Comm getGlobalCommunicator() const;

      void setGlobalRank(int global_rank);
      int getGlobalRank() const;



      // Wrapper for SION functions
      void open();
      void close();

      template<class T>
      void write(T data);

      template<typename dataT>
      void read(dataT * data);

      //	Nur zu Versuchszwecken
      template<typename dataT>
      void read(dataT * data, int unit, int length);

      //	Nur zu Versuchszwecken
      template<class T>
      void write(T & data, int unit, int length);

       template<typename outT>
      friend LSIONFile& operator<<(LSIONFile & sf, const outT& rhs);

      template<typename inT>
      friend LSIONFile& operator>>(LSIONFile & sf, inT& rhs);

      void ensureFreeSpace(long numbytes);
      void endOfFile();
 
    private:
      char * _new_sion_file_name;
      MPI_Comm _g_comm;
      MPI_Comm _l_comm;
      int _global_rank;
    };

    template<class T>
    void LSIONFile::write(T data) {
      //      lsion_fwrite(reinterpret_cast<char*>(data), 1, _chunk_size, _sid);
      //      lsion_fwrite(reinterpret_cast<char*>(&data), 1, sizeof(data), _sid);
      lsion_fwrite(reinterpret_cast<char*>(&data), sizeof(data), 1, _sid);
      //lsion_coll_fwrite_mpi(reinterpret_cast<char*>(&data), 1, sizeof(data), _sid);
      //	lsion_coll_fwrite_mpi(reinterpret_cast<char*>(&data), 1, sizeof(data), _sid);
    }

    template<class T>
    void LSIONFile::write(T & data, int unit, int length) {
      //	fwrite(reinterpret_cast<char*>(&data), 1, sizeof(data), _file_ptr);
      //	lsion_fwrite(reinterpret_cast<char*>(&data), unit, length, _sid);
      //	std::cout << "write() from mpi namespace" << std::endl;
      lsion_coll_fwrite_mpi((void *) data.data(), unit, length, _sid);
    }

    template<typename outT>
    LSIONFile& operator<<(LSIONFile & sf, const outT& rhs) {
      sf.write(rhs);
      return sf;
    }

    template<typename dataT>
    void LSIONFile::read(dataT * data) {
      dataT tmp = *data;
      //	std::cout << "size of T:\t" << sizeof(tmp) << std::endl;
      //      _return_code = lsion_fread(data, 1, sizeof(tmp), _sid);
      _return_code = lsion_fread(data, sizeof(tmp), 1, _sid);
      //   lsion_coll_fread_mpi(data, 1, sizeof(tmp), _sid);
    }

    template<typename dataT>
    void LSIONFile::read(dataT * data, int unit, int length) {
      lsion_coll_fread_mpi(data, unit, length, _sid);
    }

    template<typename inT>
    LSIONFile& operator>>(LSIONFile & sf, inT & rhs) {
      sf.read(&rhs);
      return sf;
    }
  } /* namespace mpi */

} /* namespace sionlib */

#endif /* MPI_VERSION */

#endif /* SION_CXX_MPI_HPP_ */
