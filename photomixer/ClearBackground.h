//it's a class becuse there is a possibility that we will do ourselves the opencv functions
//this class is in charge of the alpha channel and the image transparency

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

// BGR
#define BLUE 0
#define GREEN 1
#define RED 2
#define ALPHA 3

#define WHITE 255
#define BLACK 0

#define OPAQUE 255
#define CLEAR 0

using namespace cv;

class ClearBackground
{
public:
	Mat getObjectImage(Mat, Mat);
};


