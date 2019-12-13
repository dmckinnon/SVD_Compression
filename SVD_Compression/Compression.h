#pragma once
#include <sal.h>
#include <vector>
#include <string>
#include <Eigen/Dense>
#include <iostream>

#define DEFAULT_COMPRESSION_AMOUNT 50

struct CompressedImage
{
	short vRows, vCols, uRows, uCols, numVals;
	Eigen::MatrixXf V;
	Eigen::MatrixXf U;
	Eigen::VectorXf singularValues;
	short compressionAmount;

	// IO operators
	friend std::ostream& operator << (std::ostream& os, const CompressedImage& c)
	{
		os << c.vRows << " " << c.vCols << " ";
		os << c.uRows << " " << c.uCols << " " << c.numVals << " ";
		os << c.V << " ";
		os << c.U << " ";
		os << c.singularValues;
		return os;
	}
	friend std::istream& operator >> (std::istream& is, CompressedImage& C)
	{
		is >> C.vRows >> C.vCols >> C.uRows >> C.uCols >> C.numVals;
		// Now read the next values in one at a time
		for (int r = 0; r < C.vRows; ++r)
		{
			for (int c = 0; c < C.vCols; ++c)
			{
				is >> C.V(r, c);
			}
		}
		for (int r = 0; r < C.uRows; ++r)
		{
			for (int c = 0; c < C.uCols; ++c)
			{
				is >> C.U(r, c);
			}
		}
		for (int v = 0; v < C.numVals; ++v)
		{
			is >> C.singularValues(v, 0);
		}
		return is;
	}
};

/*
	Functions for compression
*/

bool CompressImage(
	_In_ const std::string& workingDir,
	_In_ const std::string& imageFilename,
	_In_ int& compressionAmount);

bool DecompressToImage(
	_In_ const std::string& workingDir,
	_In_ const std::string& compressFilename);
