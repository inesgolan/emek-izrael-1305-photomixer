#include "CheckObjectImage.h"

#define ENDING 3
#define ALPHA 3
#define OPAQUE 255

using namespace cv;

class Helper
{
public:
	static std::string checkPath(std::string path);
	static bool isPathValid(std::string path);
	static Mat checkImage(Mat image, std::string imagPath);

	static std::string getNewBackground(std::string backgroundPath);

	static std::vector<Mat> splitMat(Mat image);
	static Mat mergeMat(std::vector<Mat> matChannels, Mat objectImage);
};
