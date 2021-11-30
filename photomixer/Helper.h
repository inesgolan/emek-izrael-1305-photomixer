#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <fstream>

#include "ObjectDetection.h"
#include "CheckObjectImage.h"
#include "ClearBackground.h"
#include "ObjectOnBackground.h"

#define ENDING 3

using namespace cv;

class Helper
{
public:
	static std::string checkPath(std::string path);
	static bool isPathValid(std::string path);
	static Mat checkImage(Mat image);

	static std::string getNewBackground(std::string backgroundPath);
};
