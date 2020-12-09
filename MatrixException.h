#ifndef __MatrixException_h
#define __MatrixException_h

#include <string>

class MatrixException
{
public:
  MatrixException(const std::string& message):
    _message(message)
  {
    // do nothing
  }

  auto message() const
  {
    return _message.c_str();
  }

private:
  std::string _message;

}; // MatrixException

class BadDimensionException: public MatrixException
{
public:
  BadDimensionException():
    MatrixException("Bad dimension")
  {
    // do nothing
  }

  BadDimensionException(int n):
    MatrixException("Bad dimension: " + std::to_string(n))
  {
    // do nothing
  }

}; // BadDimensionException

class BadIndexException: public MatrixException
{
public:
  BadIndexException():
    MatrixException("Bad index")
  {
    // do nothing
  }

  BadIndexException(int i):
    MatrixException("Bad index: " + std::to_string(i))
  {
    // do nothing
  }

}; // BadIndexException

#endif // !__MatrixException_h
