//it's a class becuse there is a possibility that we will do ourselves the opencv functions
//this class is in charge of the alpha channel and the image transparency

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

class ClearBackground
{
public:
	Mat getObjectImage(Mat, Mat);
};

