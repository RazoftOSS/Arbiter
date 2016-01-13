#ifndef LIB_LIBARBITER_UTIL_H_
#define LIB_LIBARBITER_UTIL_H_

#include <stdexcept>
#include <sstream>
#include <string>

namespace libarbiter {

class FileNotFoundException : public std::runtime_error {
 public:
  FileNotFoundException(std::string path)
      : std::runtime_error("file not found"), path_(path) {}

  virtual const char* what() const throw() {
    std::ostringstream out;
    out << std::runtime_error::what() << ": " << path_.c_str();
    return out.str().c_str();
  }

 private:
  std::string path_;
};

class InvalidJSONException : public std::runtime_error {
 public:
  InvalidJSONException() : std::runtime_error("invalid JSON given") {}
};

}  // namespace libarbiter

#endif
