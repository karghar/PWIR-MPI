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
	// SparseMatrix slice() const;
	// double elem(const uint x, const uint y);
	// const uint getDimm() const;
	// MPI_Datatype getMPI_Type() const;

	double findElem(const uint row, const uint col);
	std::vector<SparseMatrix::dataType> findElemsFixRow(const uint row);
	std::vector<SparseMatrix::dataType> findElemsFixCol(const uint col);
	SparseMatrix extractSparseMatrix(const uint colBegin, const uint colEnd, const uint rowStart, const uint rowEnd);

private:
	//typedef std::tuple<uint, uint, double> dataType;
	// SparseMatrix(const SparseMatrix &other);
	// SparseMatrix& operator=(const SparseMatrix &other) = delete;
	// SparseMatrix(SparseMatrix &&other);
	// SparseMatrix& operator=(SparseMatrix &&other) = delete;
	
	void seek(const uint x, const uint y);

	std::vector<SparseMatrix::dataType> findValueFixColOrRow(const bool fixedRow, const uint cord);
	
	std::tuple<uint, uint, double> *data;	
	uint numValues;
	
};





#endif // SPARSEMATRIX_H