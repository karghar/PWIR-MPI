#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include <tuple>
#include <vector>


#include <mpi.h>



class SparseMatrix {
public:
	SparseMatrix(){}
	~SparseMatrix();
	
	SparseMatrix* createFromFile(const char* filepath);
	// SparseMatrix slice() const;
	// double elem(const uint x, const uint y);
	// const uint getDimm() const;
	// MPI_Datatype getMPI_Type() const;
	
private:
	typedef std::tuple<uint, uint, double> data_type;
	// SparseMatrix(const SparseMatrix &other);
	// SparseMatrix& operator=(const SparseMatrix &other) = delete;
	// SparseMatrix(SparseMatrix &&other);
	// SparseMatrix& operator=(SparseMatrix &&other) = delete;
	
	void seek(const uint x, const uint y);
	
	std::tuple<uint, uint, double> *values;	
	uint num_values;
	
};





#endif // SPARSEMATRIX_H