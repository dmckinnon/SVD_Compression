#pragma once
#include <sal.h>
#include <string>

#define DEFAULT_COMPRESSION_AMOUNT 50

/*
	Functions for compression
*/

bool CompressImage(
	_In_ const std::string& workingDir,
	_In_ const std::string& imageFilename,
	_In_ const int& compressionAmount);

bool DecompressToImage(
	_In_ const std::string& workingDir,
	_In_ const std::string& compressFilename);
