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
	Mat image = imread("images/black.jpg");

	checkObjectImage checker = checkObjectImage(image);
	ObjectDetection object = ObjectDetection(image);

	if (checker.checkBlackAndWhite())
	{
		std::cout << "BLACK AND WHITE ERROR\n";

	}
	else
	{
		object.getImageChannels();
		object.findObject();
	}

	return 0;
}