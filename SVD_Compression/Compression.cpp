#include "Compression.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;
using namespace Eigen;

/*
	Compress an image using Singular-Value Decomposition.

	The way this works is that we treat the image like a mxn matrix. 
	Then, as a matrix, we can get the singular values and vectors and
	isolate those that cause the most contribution to the image - say, the
	top 50. Using these, each row becomes a linear combination of these vectors
	and we can recreate the image to as much or as little detail as we please.
*/
bool CompressImage(
	_In_ const std::string& workingDir,
	_In_ const std::string& imageFilename,
	_In_ const int& compressionAmount)
{
	// First, open the image
	Mat img = imread(workingDir + imageFilename, IMREAD_GRAYSCALE);

	// Now create the matrix of the image and fill it
	MatrixXd imgMatrix(img.rows, img.cols);
	// There's probably a way to do this more efficiently
	for (int r = 0; r < img.rows; ++r)
	{
		for (int c = 0; c < img.cols; ++c)
		{
			imgMatrix(r, c) = img.at<uchar>(r,c);
		}
	}

	// Now compute the singular values

	// Take the top <compressionAmount> of the singular values and vectors

#ifdef DEBUG_SHOW_COMPRESSION
	// reconstruct the image and display it
#endif

	// save the compression

	return true;
}

/*
	Decompress an image that was compressed with Singular-Value Decomposition.
*/
bool DecompressToImage(
	_In_ const std::string& workingDir,
	_In_ const std::string& compressFilename)
{
	return true;
}