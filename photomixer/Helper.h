#include "CheckObjectImage.h"

#define ENDING 4
#define ALPHA 3
#define OPAQUE 255

//to display object image in GUI
#define MIN_ROWS_IMAGE 80
#define MIN_COLS_IMAGE 80

#define MIN_ROWS_LEN 160
#define MIN_COLS_LEN 160

#define MIN_ROWS_BACKGROUND 1000
#define MIN_COLS_BACKGROUND 1000

using namespace cv;

class Helper
{
public:
	static std::string checkPath(std::string path);
	static bool isPathValid(std::string path);
	static Mat checkImage(Mat image, std::string imagPath);

	static std::string getNewBackground(std::string backgroundPath);
	static Mat changeImageSize(int rows, int cols, Mat image, std::string path);

	static std::vector<Mat> splitMat(Mat image);
	static Mat mergeMat(std::vector<Mat> matChannels, Mat objectImage);
};
