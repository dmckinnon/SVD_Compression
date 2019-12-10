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
*/
bool CompressImage(
	_In_ const std::string& workingDir,
	_In_ const std::string& imageFilename,
	_In_ const int& compressionAmount)
{
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