#include "CheckObjectImage.h"

#define ENDING 4
#define ALPHA 3
#define OPAQUE 255

#define OBJECT_SIZE 80
#define BACKGROUND_ROWS 535
#define BACKGROUND_COLS 800

using namespace cv;

class Helper
{
public:
	static bool checkImage(Mat image, std::string imagPath);

	static Mat changeImageSize(int rows, int cols, Mat image, std::string path);

	static std::vector<Mat> splitMat(Mat image);
	static Mat mergeMat(std::vector<Mat> matChannels, Mat objectImage);
};
