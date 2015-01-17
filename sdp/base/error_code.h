#ifndef SDP_BASE_ERRORCODE_H
#define SDP_BASE_ERRORCODE_H

#include <sdp/base/cerrno.h>

namespace sdp{

enum Errc {
  SUCCESS = 0,
  ARGUMENT_LIST_TOO_LONG = E2BIG,
  ARGUMENT_OUT_OF_DOMAIN = EDOM,
  DIRECTORY_NOT_EMPTY = ENOTEMPTY,
  FILE_EXISTS = EEXIST,
  FILE_TOO_LARGE = EFBIG,
  FILENAME_TOO_LONG = ENAMETOOLONG,
  INVALID_ARGUMENT = EINVAL,
  INVALID_SEEK = ESPIPE,
  IO_ERROR = EIO,
  IS_A_DIRECTORY = EISDIR,
  NO_MESSAGE_AVAILABLE = ENODATA,
  NO_MESSAGE = ENOMSG,
  NO_SPACE_ON_DEVICE = ENOSPC,
  NO_SUCH_DEVICE_OR_ADDRESS = ENXIO,
  NO_SUCH_FILE_OR_DIRECTORY = ENOENT,
  NOT_A_DIRECTORY = ENOTDIR,
  NOT_ENOUGH_MEMORY = ENOMEM,
  NOT_SUPPORTED = ENOTSUP,
  OPERATION_CANCELED = ECANCELED,
  OPERATION_IN_PROGRESS = EINPROGRESS,
  OPERATION_NOT_PERMITTED = EPERM,
  OPERATION_NOT_SUPPORTED = EOPNOTSUPP,
  PERMISSION_DENIED = EACCES,
  READ_ONLY_FILE_SYSTEM = EROFS,
  RESOURCE_DEADLOCK_WOULD_OCCUR = EDEADLK,
  RESOURCE_UNAVAILABLE_TRY_AGAIN = EAGAIN,
  TOO_MANY_FILES_OPEN_IN_SYSTEM = ENFILE,
  TOO_MANY_FILES_OPEN = EMFILE,
  TOO_MANY_LINKS = EMLINK,
  TOO_MANY_SYMBOLIC_LINK_LEVELS = ELOOP,
  VALUE_TOO_LARGE = EOVERFLOW,
  WRONG_PROTOCOL_TYPE = EPROTOTYPE
};

class ErrorCode{
public:
  ErrorCode() : val_(SUCCESS), msg_("") {}
  
  ErrorCode(Errc val, std::string& msg) :val_(val), msg_(msg) {}

  ~ErrorCode() {}

  inline void assign(Errc val, const std::string& msg) { val_ = val; msg_ = msg; }

  inline void clear() { val_ = SUCCESS; msg_ = ""; }

  inline void operator = (ErrorCode& ec) { val_ = ec.get_val(); msg_ = ec.get_msg(); }

  inline Errc get_val() { return val_;}

  inline const std::string& get_msg() { return msg_;}

private:
  Errc val_;
  std::string msg_;
};
}//end of namespace sdp

#endif //SDP_BASE_ERRORCODE_H
