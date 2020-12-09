#ifndef __Vector_h
#define __Vector_h

#include "MatrixException.h"
#include <cstdio>

template <typename T>
class Vector
{
private:
  int n;
  T* data;

public:
  Vector();

  Vector(int n);

  Vector(const Vector<T>& other);

  ~Vector();

  Vector<T>& operator =(const Vector<T>& other);

  Vector<T> operator +(const Vector<T>&) const;
  Vector<T> operator -(const Vector<T>&) const;
  Vector<T> operator *(const T&) const;

  auto size() const
  {
    return n;
  }

  const T& operator [](int) const;
  T& operator [](int);

  void print(const char*, FILE* = stdout) const;

}; // Vector

#endif // !__Vector_h
