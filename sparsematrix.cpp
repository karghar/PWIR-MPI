#include "sparsematrix.hpp"
#include <tuple>
#include <vector>
#include <mpi.h>

#include <cstdio>
#include <cstdlib>
#include <cassert>

#define ROW 0
#define COL 1
#define VALUE 2

//STATICS
uint SparseMatrix::maxInRow;
uint SparseMatrix::maxRows;
uint SparseMatrix::maxColumns;

//METHODS

SparseMatrix* SparseMatrix::createFromFile(const char* filepath)
{
	FILE *f = fopen(filepath, "r");
	if (!f) 
	{
		printf("Error opening file\n");
		return nullptr;
	}

	uint rows, cols, elems, maxElems;

	fscanf(f, "%u%u%u%u", &rows, &cols, &elems, &maxElems);

	SparseMatrix::maxInRow = maxElems;
	SparseMatrix::maxRows = rows;
	SparseMatrix::maxColumns = cols;

	std::vector<double> a(elems);
	std::vector<uint>  ia(rows + 1);
	std::vector<uint> ja(elems);

	for (auto &aElem : a) 
	{
		fscanf(f, "%lf", &aElem);
	}


	for (auto &iaElem : ia) 
	{
		fscanf(f, "%u", &iaElem);
	}

	for (auto &jaElem : ja) 
	{
		fscanf(f, "%u", &jaElem);
	}

	fclose(f);

	//now we create matrix
	data = new SparseMatrix::dataType[a.size()];

	uint row, amountInRow, col;

	col = 1; // we start from 1 columns of matrix

	for (size_t  i = 0; i < a.size(); i++)
	{
		if(amountInRow >= ia[col])
		{
			col++;
			amountInRow = 0;
			row++;
		}

		data[i] = std::make_tuple(ja[i], row, a[i]);
	}

	numValues = a.size();

	return this;
}

double SparseMatrix::findElem(const uint row, const uint col)
{
	double result = 0.0;
	for(size_t index = 0; index < numValues; index++)
	{
		if (std::get<ROW>(data[index]) == row && std::get<COL>(data[index]) == col)
		{
			result = std::get<VALUE>(data[index]);
			index = numValues;
		}
	}
	return result;
}

std::vector<SparseMatrix::dataType> SparseMatrix::findElemsFixCol(const uint col)
{
	return this->findValueFixColOrRow(false, col);
}

std::vector<SparseMatrix::dataType> SparseMatrix::findElemsFixRow(const uint row)
{
	return this->findValueFixColOrRow(true, row);
}

SparseMatrix SparseMatrix::extractSparseMatrix(const uint colBegin, const uint colEnd, const uint rowBegin, const uint rowEnd)
{
	std::vector<SparseMatrix::dataType> valueHolder;
	
	for(size_t index = 0; index < numValues; index++)
	{
		//check ROW
		if(std::get<ROW>(data[index]) >= rowBegin && std::get<ROW>(data[index]) <= rowEnd)
		{
			//check COL
			if(std::get<COL>(data[index]) >= colBegin && std::get<COL>(data[index]) <= colEnd)
			{
				valueHolder.push_back(data[index]);
			}
		}
	}
	SparseMatrix* result = new SparseMatrix();

	//FIXME pointer issues maybe? maybe i should copy it
	result->data = valueHolder.data();
	result->numValues = valueHolder.size();

	return *result;
}


std::vector<SparseMatrix::dataType> SparseMatrix::findValueFixColOrRow(const bool fixedRow, const uint cord)
{
	std::vector<SparseMatrix::dataType> result;
	uint dummy;

	for(size_t index = 0; index < numValues; index++)
	{
		//here we decide whether it should be row or col to be checked
		dummy = fixedRow ?  std::get<ROW>(data[index]) : std::get<COL>(data[index]);

		if (dummy == cord)
		{
			result.push_back(data[index]);
		}
	}
	return result;
}

SparseMatrix::~SparseMatrix() 
{
	delete [] data;
}

