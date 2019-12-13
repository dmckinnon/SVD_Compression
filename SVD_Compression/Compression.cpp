#include "Compression.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;
using namespace Eigen;

#define DEBUG_SHOW_COMPRESSION

/*
	Given a CompressedImage structure, create the image
*/
void CreateImageFromCompression(
	_In_ const CompressedImage& c,
	_Inout_ Mat& img)
{
	MatrixXf sigma = c.singularValues.asDiagonal();
	MatrixXf compressedMatrix = c.U * sigma * c.V.transpose();
	img = Mat(compressedMatrix.rows(), compressedMatrix.cols(), 0);

	for (int r = 0; r < img.rows; ++r)
	{
		for (int c = 0; c < img.cols; ++c)
		{
			img.at<uchar>(r, c) = (uchar)compressedMatrix(r, c);
		}
	}
}

/*
	Given a filename, open the compressed image
*/
CompressedImage OpenCompressionFile(_In_ const string& file)
{
	ifstream compressedFile;
	compressedFile.open(file);
	CompressedImage c;
	if (compressedFile.is_open())
	{
		compressedFile >> c;
		compressedFile.close();
	}
	return c;
}

/*
	Take a CompressedImage structure and write it to a file
	Filename is compress.svd
*/
void WriteCompressedFile(
	_In_ const string& workingDir,
	_In_ CompressedImage& c)
{
	ofstream compressedFile;
	compressedFile.open(workingDir + "compress.svd");
	if (compressedFile.is_open())
	{
		c.uCols = c.U.cols();
		c.uRows = c.U.rows();
		c.vCols = c.V.cols();
		c.vRows = c.U.rows();
		c.numVals = c.singularValues.rows();
		compressedFile << c;
		compressedFile.close();
	}
}

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
	_In_ int& compressionAmount)
{
	// First, open the image
	Mat img = imread(workingDir + imageFilename, IMREAD_GRAYSCALE);

	// Now create the matrix of the image and fill it
	MatrixXf imgMatrix(img.rows, img.cols);
	// There's probably a way to do this more efficiently
	for (int r = 0; r < img.rows; ++r)
	{
		for (int c = 0; c < img.cols; ++c)
		{
			imgMatrix(r, c) = (float)img.at<uchar>(r,c);
		}
	}

	// Now compute the singular values
	// TODO: write this algorithm myself
	BDCSVD<MatrixXf> svd(imgMatrix, ComputeFullU | ComputeFullV);
	if (!svd.computeV())
		return false;
	if (!svd.computeU())
		return false;
	MatrixXf V = svd.matrixV();
	MatrixXf U = svd.matrixU();
	VectorXf singularValues = svd.singularValues();

	if (compressionAmount > singularValues.size())
	{
		compressionAmount = (int)singularValues.rows();
	}

	// Take the top <compressionAmount> of the singular values and vectors
	CompressedImage c;
	c.singularValues = VectorXf(compressionAmount);
	for (int i = 0; i < compressionAmount; ++i)
	{
		c.singularValues(i) = singularValues(i);
	}
	c.U = U.block(0, 0, U.rows(), compressionAmount);
	c.V = V.block(0, 0, V.rows(), compressionAmount);
	
	// Create the compressed image
	Mat imgCompressed(img.size(), CV_8U);
	CreateImageFromCompression(c, imgCompressed);

	// Compression stats
	cout << "Number of bytes in the image: " << img.rows * img.cols << std::endl;
	cout << "Number of values in the reduced SVD model: " << c.U.rows() * c.U.cols() << " + " << c.singularValues.rows() << " + ";
	cout << c.V.rows() * c.V.cols();
	cout << " = " << c.U.rows() * c.U.cols() + c.singularValues.rows() + c.V.rows() * c.V.cols() << endl;

#ifdef DEBUG_SHOW_COMPRESSION
	imshow("Compressed Image", imgCompressed);
	waitKey(0);
#endif

	// save both the compression file and the compressed image
	imwrite(workingDir + "compressed.bmp", imgCompressed);
	WriteCompressedFile(workingDir, c);

	// Compute image error and print out statistics:
	Mat errorImage;
	absdiff(img, imgCompressed, errorImage);
	Scalar error = sum(errorImage);
#ifdef DEBUG_SHOW_COMPRESSION
	cout << "Total compression error in terms of pixel difference is " << error[0] << endl;
	imshow("Error image", errorImage);
	waitKey(0);
#endif

	return true;
}

/*
	Decompress an image that was compressed with Singular-Value Decomposition.
*/
bool DecompressToImage(
	_In_ const std::string& workingDir,
	_In_ const std::string& compressFilename)
{
	// Open the compression file
	CompressedImage c = OpenCompressionFile(workingDir + compressFilename);

	// Compute the SVD
	Mat imgCompressed;
	CreateImageFromCompression(c, imgCompressed);

#ifdef DEBUG_SHOW_COMPRESSION
	imshow("Compressed Image", imgCompressed);
	waitKey(0);
#endif

	imwrite(workingDir + "compressed.bmp", imgCompressed);

	return true;
}