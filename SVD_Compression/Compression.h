#pragma once
#include <sal.h>
#include <vector>
#include <string>
#include <Eigen/Dense>
#include <iostream>

#define DEFAULT_COMPRESSION_AMOUNT 50

struct CompressedImage
{
	unsigned char vRows, vCols, uRows, uCols, numVals;
	Eigen::MatrixXf V;
	Eigen::MatrixXf U;
	Eigen::VectorXf singularValues;
	int compressionAmount;

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
	friend std::istream& operator >> (std::istream& is, CompressedImage& c)
	{
		// need to input carefully
		// value by value
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
