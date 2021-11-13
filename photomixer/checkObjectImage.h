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

using namespace cv;

class checkObjectImage
{
private:
	Mat _image;

public:
	checkObjectImage(Mat image); 
	~checkObjectImage();

	bool checkBlackAndWhite();
	bool checkTooDark();
	bool checkTooBright(); // לספןר פיקסלים
};

