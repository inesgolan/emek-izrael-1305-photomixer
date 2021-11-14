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
	Mat image = imread("images/bunny.jpg");

	checkObjectImage checker = checkObjectImage(image);
	ObjectDetection object = ObjectDetection(image);

	if (checker.checkBlackAndWhite() || checker.checkTooDark() || checker.checkTooBright())
	{
		std::cout << "SOME ERROR\n";

	}
	else
	{
		object.getImageChannels();
		object.findObject();
	}

	return 0;
}