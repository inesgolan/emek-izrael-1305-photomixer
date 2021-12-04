#include "Helper.h"

int main()
{
	//get image path
	std::string path = "images/flower.jpg";
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
	Mat objectImage = clearBackground.getObjectImage(image, matte);

	//set background
	std::string backgroundPath = "images/background.jpg";
	backgroundPath = Helper::getNewBackground(backgroundPath);
	Mat backgroundImage = imread(backgroundPath);

	//put object on background
	ObjectOnBackground objectOnBackground(backgroundImage);
	Mat allImage = objectOnBackground.getEditedImage(100, 100, objectImage, backgroundImage);

	//show image
	imshow("image.png", allImage);
	waitKey(0);

	return 0;
}