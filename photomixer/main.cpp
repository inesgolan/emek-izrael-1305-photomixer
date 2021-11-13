//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//#include <iostream>
#include <vector> 

#include "ObjectDetection.h"
#include "checkObjectImage.h"

using namespace cv;

int main()
{
	Mat image = imread("images/trols.jpg");

	ObjectDetection object = ObjectDetection(image);

	object.getImageChannels();
	object.findObject();

	return 0;
}