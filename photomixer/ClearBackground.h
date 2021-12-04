//It's a class becuse there is a possibility that we will do ourselves the opencv functions
//This class is in charge of the alpha channel and the image transparency

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#define WHITE 255
#define BLACK 0

#define BLUE 0
#define GREEN 1
#define RED 2
#define ALPHA 3
#define RGB_CHANNELS_LEN 3

#define OPAQUE 255
#define CLEAR 0

using namespace cv;

class ClearBackground
{
public:
	Mat getObjectImage(Mat, Mat);

	static std::vector<Mat> splitMat(Mat image);
	static Mat mergeMat(std::vector<Mat> matChannels, Mat objectImage);
};


