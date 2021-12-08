#include "CheckObjectImage.h"

#define ENDING 4

using namespace cv;

class Helper
{
public:
	static std::string checkPath(std::string path);
	static bool isPathValid(std::string path);
	static Mat checkImage(Mat image);

	static std::string getNewBackground(std::string backgroundPath);
};
