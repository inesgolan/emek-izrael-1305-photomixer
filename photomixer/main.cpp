#include "ObjectOnBackground.h"
#include "ObjectDetection.h"

#define OBJECT_DETECTION 100
#define EDIT_IMAGE 200

#define CODE 1
#define OBJECT_PATH 2
#define SAVE_OBJECT_PATH 3
#define BACKGROUND_PATH 3
#define SAVE_IMAGE_PATH 4
#define X_LOCATION 5
#define Y_LOCATION 6

/*
client messages:
100 - object path - save path
200 - object path - background path - save path - x location - y location
*/
int main(int argc, char** argv)
{
	std::string imagePath = "", backgroundPath = "", savePath = "";
	Mat objectImage, backgroundImage, matte;
	ObjectDetection object;
	ClearBackground clearBackground;
	ObjectOnBackground objectOnBackground;

	if (argc >= SAVE_OBJECT_PATH)
	{
		switch (std::stoi(argv[CODE]))
		{
		case OBJECT_DETECTION:
			//get image path
			imagePath = argv[OBJECT_PATH];
			imagePath = Helper::checkPath(imagePath);

			//get image
			objectImage = imread(imagePath);
			objectImage = Helper::checkImage(objectImage, imagePath);

			//get matte
			object.setImage(objectImage);
			object.getImageChannels();
			matte = object.findObject();

			//get object image	
			clearBackground.getObjectImage(objectImage, matte, argv[SAVE_OBJECT_PATH]);
			break;

		case EDIT_IMAGE:
			//get image
			imagePath = argv[OBJECT_PATH];
			imagePath = Helper::checkPath(imagePath);
			objectImage = imread(imagePath, -1);

			//get background
			backgroundPath = argv[BACKGROUND_PATH];
			backgroundPath = Helper::getNewBackground(backgroundPath);
			backgroundImage = imread(backgroundPath);

			//edit the image
			objectOnBackground.setBackground(backgroundImage);
			objectOnBackground.getEditedImage(std::stoi(argv[X_LOCATION]), std::stoi(argv[Y_LOCATION]), objectImage, backgroundImage, argv[SAVE_IMAGE_PATH]);
			break;

		default:
			std::cout << "ERROR" << std::endl;
			break;
		}
	}

	return 0;
}