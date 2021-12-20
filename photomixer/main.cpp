#include "ObjectOnBackground.h"
#include "ObjectDetection.h"

#define IMAGE_PATH 1
#define BACKGROUND_PATH 2
#define OBJECT_X_LOCATION 3
#define OBJECT_Y_LOCATION 4

/* NOTE:
You pass all the command line arguments separated by a space, but if argument itself has a space
then you can pass such arguments by putting them inside double quotes “” or single quotes ”
client message: image path, background path, object x location, object y location
*/
int main(int argc, char** argv)
{
	std::string path = "", backgroundPath = "";
	Mat image, matte, objectImage, backgroundImage, allImage;

	//get image path
	path = argv[IMAGE_PATH];
	path = Helper::checkPath(path);

	//get image
	image = imread(path);
	image = Helper::checkImage(image, path);

	//get object
	ObjectDetection object = ObjectDetection(image);
	object.getImageChannels();
	matte = object.findObject();

	//get object image
	ClearBackground clearBackground;
	objectImage = clearBackground.getObjectImage(image, matte);

	backgroundPath = argv[BACKGROUND_PATH];
	backgroundPath = Helper::getNewBackground(backgroundPath);
	backgroundImage = imread(backgroundPath);

	ObjectOnBackground objectOnBackground =ObjectOnBackground(backgroundImage);
	allImage = objectOnBackground.getEditedImage(std::stoi(argv[OBJECT_X_LOCATION]), std::stoi(argv[OBJECT_Y_LOCATION]), objectImage, backgroundImage);

	return 0;
}