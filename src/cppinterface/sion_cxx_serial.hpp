#ifndef SION_CXX_SERIAL_HPP_
#define SION_CXX_SERIAL_HPP_

#include "sion.h"
#include <string>
#include <string.h>
#include "sion_cxx_common.hpp"
#include "sion_cxx_base.hpp"

namespace sionlib {
  namespace serial {
    class LSIONFile : public LSION_Base {
    public:
       LSIONFile(std::string sion_file_name, std::string mode = "wb",
	       int num_tasks = 1, int num_files = 1, sion_int64 * chunk_sizes=NULL, sion_int32 _fs_blk_size=-1, int * global_ranks = NULL);
      ~LSIONFile();

      // Don't copy LSIONFile

      // Class specific methods
      LSIONFile(const LSIONFile& rhs) {
      }

      void open();
      void openRank();
      int close();

      /* HELPER FUNCTIONS */

      /* STATIC MEMBER FUNCTIONS */
      /*   return current endianness (1-> big endian, 0 ->little endian) */
      // static int getEndianness() {
      // 	return lsion_get_endianness();
      // }

      // static bool isBigEndian() {
      // 	return (lsion_get_endianness() ? true : false);
      // }

      /*   return if SIONlib supports PTHREADS (Thread-safe) 1 -> yes, 0 -> no  */
      // static bool isThreadSafe() {
      // 	return (lsion_is_thread_safe() ? true : false);
      // }

      /*   return version numbers */
      // static int GetVersion() {
      // 	return lsion_get_version(&main_version, &sub_version, &patch_level,
      // 				&fileformat_version);
      // }

      /* WRITE */
      template<class T>
      void write(T data) {
    	lsion_fwrite(reinterpret_cast<char*>(&data), 1, sizeof(data), _sid);
      }

      /* Test for writing out arrays of data */
      template<class T>
      void write(T * data) {
    	lsion_fwrite(reinterpret_cast<char*>(data), 1, _chunk_sizes[_rank], _sid);
      }


      template<class T>
      void write(T data, int unit, int length) {
    	lsion_fwrite((void *) data.data(), unit, length, _sid);
      }

      // template<typename T>
      // LSIONFile& operator<<(LSIONFile & sf, const T& rhs) {
      //   sf.write(rhs);
      //   return sf;
      // }

      /* READ */
      template<typename T>
      void read(T * data) {
    	T tmp = *data;
    	_return_code = lsion_fread(data, 1, sizeof(tmp), _sid);
      }

      template<typename T>
      void read(T * data, int unit, int length) {
    	_return_code = lsion_fread(data, unit, length, _sid);
      }

      template<typename T>
      friend LSIONFile& operator<<(LSIONFile & sf, const T& rhs);

    private:
      LSIONFile();

    };
    template<typename T>
    LSIONFile& operator<<(LSIONFile & sf, const T& rhs) {
      sf.write(rhs);
      return sf;
    }
  } /* namespace serial */
} /* namespace sionlib */
#endif /* SION_CXX_SERIAL_HPP_ */
