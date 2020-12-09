#ifndef __Matrix_h
#define __Matrix_h

#include "Vector.h"
#include <memory>

template <typename T> class Matrix;

template <typename T>
class MatrixBody
{
public:
  ~MatrixBody()
  {
    delete[] _data;
  }

private:
  int _refCount = 1;
  int _m;
  int _n;
  T* _data;

  MatrixBody()
  {
    _m = _n = 0;
    _data = nullptr;
  }

  MatrixBody(int, int);

  auto makeUse()
  {
    ++_refCount;
    return this;
  }

  void release()
  {
    if (--_refCount == 0)
      delete this;
  }

  static MatrixBody<T>* null();

  friend Matrix<T>;

}; // MatrixBody

template <typename T>
MatrixBody<T>*
MatrixBody<T>::null()
{
  static MatrixBody<T> _null;
  return &_null;
}

template <typename T>
MatrixBody<T>::MatrixBody(int m, int n)
{
#if _DEBUG
  if (m <= 0)
    throw BadDimensionException(m);
  if (n <= 0)
    throw BadDimensionException(n);
#endif // _DEBUG
  _m = m;
  _n = n;

  auto s = m * n;

  _data = new T[s];
  memset(_data, 0, s * sizeof(T));
}

template <typename T>
class Matrix
{
private:
  MatrixBody<T>* _body;

public:
  Matrix():
    _body(MatrixBody<T>::null()->makeUse())
  {
    // do nothing
  }

  Matrix(int m, int n):
    _body(new MatrixBody<T>(m, n))
  {
    // do nothing
  }

  Matrix(const Matrix<T>& other):
    _body(other._body->makeUse())
  {
    // do nothing
  }

  ~Matrix()
  {
    _body->release();
  }

  Matrix<T>& operator =(const Matrix<T>& other)
  {
    if (_body != other._body)
    {
      _body->release();
      _body = other._body->makeUse();
    }
    return *this;
  }

  Matrix<T> operator +(const Matrix<T>&) const;
  Matrix<T> operator -(const Matrix<T>&) const; 
  Matrix<T> operator *(const Vector<T>&) const;
 // Matrix<T> operator *(const Matrix<T>&) const;
  Matrix<T> operator *(const T&) const;

 // Matrix<T> transpose() const;

  auto nrows() const
  {
    return _body->_m;
  }

  auto ncols() const
  {
    return _body->_n;
  }

  auto size() const
  {
    return _body->_m * _body->_n;
  }

  const T& operator ()(int i, int j) const
  {
#if _DEBUG
    if (i < 0 || i > _body->_m)
      throw BadIndexException(i);
    if (j < 0 || j > _body->_n)
      throw BadIndexException(j);
#endif // _DEBUG
    return _body->_data[i * _body->_n + j];
  }

  T& operator ()(int i, int j)
  {
#if _DEBUG
    if (i < 0 || i > _body->_m)
      throw BadIndexException(i);
    if (j < 0 || j > _body->_n)
      throw BadIndexException(j);
#endif // _DEBUG
    return _body->_data[i * _body->_n + j];
  }

  const T& operator [](int i) const
  {
#if _DEBUG
    if (i < 0 || i > size())
      throw BadIndexException(i);
#endif // _DEBUG
    return _body->_data[i];
  }

  T& operator [](int i)
  {
#if _DEBUG
    if (i < 0 || i > size())
      throw BadIndexException(i);
#endif // _DEBUG
    return _body->_data[i];
  }

  void print(const char*, FILE* = stdout) const;

}; // Matrix

template <typename T>
Matrix<T>
Matrix<T>::operator +(const Matrix<T>& m) const
{
  Matrix<T> c(_body->_m, _body->_n);
  if (_body->_m==m._body->_m && _body->_n==m._body->_n) {
      for (int i = 0; i < size(); ++i)
          c._body->_data[i] = _body->_data[i] + m._body->_data[i];
  }
  return c;
}

template <typename T>
Matrix<T>
Matrix<T>::operator -(const Matrix<T>& m) const
{
    Matrix<T> c(_body->_m, _body->_n);
    if (_body->_m == m._body->_m && _body->_n == m._body->_n) {
        for (int i = 0; i < size(); ++i)
            c._body->_data[i] = _body->_data[i] - m._body->_data[i];
    }
    return c;
}

template <typename T>
Matrix<T> 
Matrix<T>::operator *(const T& t) const
{
    Matrix<T> c(_body->_m, _body->_n);
    for (int i = 0; i < size(); ++i)
        c._body->_data[i] = _body->_data[i] + t;
    return c;
}

template <typename T>
Matrix<T> 
Matrix<T>::operator *(const Vector<T>&) const
{

}

template <typename T>
inline Matrix<T>
operator *(const T& s, const Matrix<T>& m)
{
  return m * s;
}

inline FILE&
operator <<(FILE& out, char c)
{
  fputc(c, &out);
  return out;
}

template <typename T>
void
Matrix<T>::print(const char* s, FILE* out) const
{
  fprintf(out, "%s\n", s);
  if (size() == 0)
  {
    fprintf(out, "0x0 matrix\n");
    return;
  }
  for (int k = 0, i = 0; i < _body->_m; ++i)
  {
    for (int j = 0; j < _body->_n; ++j, ++k)
      *out << _body->_data[k] << ' ';
    *out << '\n';
  }
}

#endif // !__Matrix_h
