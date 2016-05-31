#include "sparsematrix.hpp"
#include <tuple>
#include <vector>
#include <mpi.h>

#include <cstdio>
#include <cstdlib>
#include <cassert>


SparseMatrix* SparseMatrix::createFromFile(const char* filepath)
{
	FILE *f = fopen(filepath, "r");
	if (!f) {
		printf("Error opening file\n");
		return nullptr;
	}

	return nullptr;


}


SparseMatrix::~SparseMatrix() 
{
	
}