#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include <tuple>
#include <vector>


#include <mpi.h>



class SparseMatrix {
public:
	SparseMatrix(){}
	~SparseMatrix();
	typedef std::tuple<uint, uint, double> dataType;


	SparseMatrix* createFromFile(const char* filepath);
	
	double findElem(const uint row, const uint col);
	std::vector<SparseMatrix::dataType> findElemsFixRow(const uint row);
	std::vector<SparseMatrix::dataType> findElemsFixCol(const uint col);
	SparseMatrix extractSparseMatrix(const uint colBegin, const uint colEnd, const uint rowStart, const uint rowEnd);

private:
	
	std::vector<SparseMatrix::dataType> findValueFixColOrRow(const bool fixedRow, const uint cord);


	static uint maxInRow;
	static uint maxRows;
	static uint maxColumns; 
	
	std::tuple<uint, uint, double> *data;	
	uint numValues;
	
};





#endif // SPARSEMATRIX_H