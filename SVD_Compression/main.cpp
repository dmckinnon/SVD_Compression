#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include "Compression.h"

using namespace std;

/*
	This is an exercise in SVD and lossy image compression.

	If we treat an image as a mxn matrix, we can compute the singular values of
	this image. These values and the corresponding vectors are the values and 
	vectors that contribute to the 'transform' that the matrix, or image, is.
	Therefore, we can recreate that with a subset of those - and these should be
	more space-efficient to store than individual pixel values. 

	Input:
	- a grayscale image (can work with colour, but let's start simple)
	- the amount of compression

	Output:
	- a compressed file of that image

	Alternatively,

	Input:
	- a compression file

	Output:
	- the corresponding image

	I'm mostly doing this as an example of SVD's practical uses, but I may extend
	this in future to include an implementation of SVD. I'm hesitant, since such
	an algorithm is nontrivial, and prone to error and finickiness. 

	The 'amount of compression' currently corresponds to an amount of the 
	singular values and vectors used, but at some point I need to convert this 
	to 'amount of image that is error vs true' and give a number from 1 - 100

	TODO:
	- command line arg for compression amount
	- convert compression amount to percentage error or something
	- test image error
	- compile with O3 for speed
	- store in an actual compressed format lol

	The problem currently is we generate a whole lotta floats, not unsigned chars.
	And then these are stored as text, not as raw binary, which means they take up
	way more memory than they should. 
	If we store everything as 16 bit floats, and then save as raw binary, it is
	considerably more compressed and we end up saving memory

	Otherwise this is an exercise in futility, and learning SVD. 
	Which would be fun. Still gotta write an SVD algo
*/

int main(int argc, char** argv)
{
	string workingDir = "";
	string imageFilename = "img.jpg";
	string compressFilename = "compress.svd";
	bool compressInput = true;
	int compressionAmount = 25;// DEFAULT_COMPRESSION_AMOUNT;
	// Default compression

	// Parse args
	if (argc < 2 || strcmp(argv[1], "-h") == 0)
	{
		cout << "Usage:" << endl;
		cout << "-h                     Display this message." << endl;
		cout << "-dir <directory>       The directory where the input is. No trailing slashes. Required." << endl;
		cout << "-image <filename>      The image file to be compressed. Default is img.jpg. Optional." << endl;
		cout << "-compressed <filename> The compressed file to be decompressed. Default is compress.svd. Optional." << endl;
		cout << "-decompress            Flag stating to decompress. If not set, default is to compress. Optional." << endl;
		exit(1);
	}
	else
	{
		for (int i = 1; i < argc; i ++)
		{
			if (strcmp(argv[i], "-dir") == 0)
			{
				i++;
				workingDir = string(argv[i]) + string("\\");
			}
			else if (strcmp(argv[i], "-image") == 0)
			{
				i++;
				imageFilename = string(argv[i]);
			}
			else if (strcmp(argv[i], "-compressed") == 0)
			{
				i++;
				compressFilename = string(argv[i]);
			}
			else if (strcmp(argv[i], "-decompress") == 0)
			{
				compressInput = false;
			}
		}
	}

	// Need a working dir
	if (workingDir.empty())
	{
		cout << "No working directory given!" << endl;
		exit(1);
	}

	// now compress or decompress
	if (compressInput)
	{
		if (!CompressImage(workingDir, imageFilename, compressionAmount))
		{
			cout << "Compression failed." << endl;
			exit(1);
		}
		else
		{
			cout << "Compression succeeded! See the file " << workingDir << "compress.svd." << endl;
		}
	}
	else
	{
		DecompressToImage(workingDir, compressFilename);
	}

	return 0;
}