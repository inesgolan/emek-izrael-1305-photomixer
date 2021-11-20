#include "ObjectDetection.h"
#include "CheckObjectImage.h"
#include "ClearBackground.h"
#include "Helper.h"

using namespace cv;

int main()
{
	//get image path
	std::string path = "images/dino.jpg";
	path = Helper::checkPath(path);

	//get image
	Mat image = imread(path);
	image = Helper::checkImage(image);

	//get object
	ObjectDetection object = ObjectDetection(image);
	object.getImageChannels();
	Mat matte = object.findObject();

	//get object image
	ClearBackground clearBackground;
	clearBackground.getObjectImage(image, matte);

	return 0;
}
