#ifndef __SparseMatrix_h
#define __SparseMatrix_h

template <typename T> class Matrix;
template <typename T> class Vector;

template < typename T>
class SparseMatrix
{
public:
//	~SparseMatrix();

//	SparseMatrix();
//	SparseMatrix(int, int);
//	SparseMatrix(const Matrix<T>&);

//	SparseMatrix(const SparseMatrix<T>&);
//	SparseMatrix<T>& operator =(const SparseMatrix<T>&);
//	SparseMatrix<T> operator +(const SparseMatrix<T>&) const;
//	SparseMatrix<T> operator -(const SparseMatrix<T>&) const;
//	SparseMatrix<T> operator *(const SparseMatrix<T>&) const;
//	SparseMatrix<T> operator *(const Vector<T>&) const;
//	SparseMatrix<T> operator *(const T&) const;

//	int nrows() const;
//	int ncols() const;
	auto size() const
	{
		return nrows() * ncols();
	}

//	T operator ()(int, int) const;
	void set(int, int, const T&);
//	operator Matrix<T>() const;
	SparseMatrix<T> transpose() const;
//	void print(const char*, FILE* = stdout) const;
private:
	// TODO
};
#endif

template <typename T>
class SparseMatrixNode
{
public:

private:
	T value;
	int column, row;
	SparseMatrixNode* nextColumn;
	SparseMatrixNode* nextRow;
};

template <typename T>
class SparseMatrixBody
{
public:
	//TODO
private:
	
};