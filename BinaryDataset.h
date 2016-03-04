/**
 *  Generate a binary format dataset of images for the 
 *  convolutional neural network(CNN) based on tensorflow.
 *
 *  dataform: 
 *    - data: a nx3072 array of uint8s. Each row of the 
 *        array stores a 32x32 colour image. The first 1024 
 *        entries contain the red channel values, the next 1024
 *        the green, and the final 1024 the blue. The image is 
 *        stored in row-major order, so that the first 32 entries
 *        of the array are the red channel values of the first 
 *        row of the image.
 *    - labels: a list of n numbers in the range 0-9. The 
 *        number at index i indicates the label of the ith image
 *        in the array data.
 *   Each file contains n such 3073-byte.
 *  
 *    Editor: Yahui Liu.
 *    Data:   2016-03-03
 *    Email:  yahui.cvrs@gmail.com
 *    Address: Computer Vision and Remote Sensing(CVRS) Lab， Wuhan University.
 */

#ifndef BINARY_DATASET_H
#define BINARY_DATASET_H
#pragma once

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "cv.h"
#include "highgui.h"

using namespace std;
using namespace cv;

class BinaDataset
{
public:
	BinaDataset()
	{
		_iHeight = 32;
		_iWidth  = 32;
	}
	~CrackBinaDataset(){}

public:
	void images2BinaryFile( std::string filefolder, std::vector<std::string>& img_list, 
		std::vector<int>& img_labels, std::string filename );
	
	void mat2Binary( std::string& image_file, int label, FILE*& fp );

	void convertMat2Bin( cv::Mat& image, int label, FILE*& fp );

//	cv::Mat imageReshape( cv::Mat& input );

	std::string getFileName( std::string & filename );

	std::vector<std::string> getFileLists( std::string file_folder );

public:
	int _iHeight;
	int _iWidth;
};
#endif // BINARY_DATASET_H
