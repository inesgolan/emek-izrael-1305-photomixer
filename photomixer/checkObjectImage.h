#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

#define BLUE 0
#define GREEN 1
#define RED 2

#define WHITE 255
#define BLACK 0

#define DARKEST_GRAY 35
#define BRIGHTEST_GRAY 220
#define MOST_OF_THE_PIXELS 0.8

using namespace cv;

class checkObjectImage
{
private:
	Mat _image;
	int countOfPixels;

public:
	checkObjectImage(Mat image); 
	~checkObjectImage();

	bool checkBlackAndWhite();
	bool checkTooDark();
	bool checkTooBright(); 
};

