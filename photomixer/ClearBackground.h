//it's a class becuse there is a possibility that we will do ourselves the opencv functions
//this class is in charge of the alpha channel and the image transparency

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

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
private:
	static std::vector<Mat> SplitMat(Mat image);
	static Mat mergeMat(std::vector<Mat> matChannels, Mat objectImage);
public:
	Mat getObjectImage(Mat, Mat);
};


