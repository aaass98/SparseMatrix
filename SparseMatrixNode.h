#ifndef __SparseMatrixNode_h
#define __SparseMatrixNode_h

template < typename T>
class SparseMatrixNode 
{
public:
	//TODO
private:
	T value;
	int column, row;
	SparseMatrixNode* nextColumn;
	SparseMatrixNode* nextRow;
};

#endif