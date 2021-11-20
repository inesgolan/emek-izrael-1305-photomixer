#include <vector> 
#include <fstream>

#include "ObjectDetection.h"
#include "CheckObjectImage.h"
#include "ClearBackground.h"

#define ENDING 3

using namespace cv;

std::string checkPath(std::string path);
bool isPathValid(std::string path);
Mat checkImage(Mat image);

int main()
{
	std::string path = "images/dino.jpg";
	path = checkPath(path);

	Mat image = imread(path);
	image = checkImage(image);

	ObjectDetection object = ObjectDetection(image);
	object.getImageChannels();
	Mat matte = object.findObject();

	ClearBackground clearBackground;
	clearBackground.getObjectImage(image, matte);

	return 0;
}

/*
This function gets a path from the user until it's valid
Input: image path
Output: the valid path
*/
std::string checkPath(std::string path)
{
	std::string newPath = path;

	while (!isPathValid(newPath)) 
	{
		std::cout << "PLEASE ENTER A VALID PATH (OF AN IMAGE FILE): " << std::endl;
		std::cin >> newPath;
		getchar();
	}

	return newPath;
}

/*
This function checks the image path
Input: image path
Output: true - the path exist and is an image
		false - the file dosen't exist of isn't an image
*/
bool isPathValid(std::string path)
{
	std::string ending = "";

	if (path.size() > ENDING)
	{
		ending = path.substr(path.size() - ENDING, path.size() - 1);
	}
	else
	{
		return false;
	}

	std::ifstream ifile;
	ifile.open(path);

	if (ifile && ("jpg" == ending || "png" == ending)) //can open the file and it's a picture
	{
		return true;
	}
	return false;
}

/*
This function gets an image from the user until it's valid
Input: image 
Output: the new image
*/
Mat checkImage(Mat image)
{
	std::string path = "";
	Mat newImage = image;
	checkObjectImage checker = checkObjectImage(image);

	while (checker.checkBlackAndWhite() || checker.checkTooDark() || checker.checkTooBright()) 
	{
		std::cout << "SOME ERROR - WE ARE NOT ABLE TO RECOGNIZE THE OBJECT IN THIS PICTURE" << std::endl;

		//get new path
		std::cout << "PLEASE ENTER A VALID PATH (OF AN IMAGE FILE): " << std::endl;
		std::cin >> path;
		getchar();
		path = checkPath(path);

		//get the new image
		newImage = imread(path);
		checker.setImage(newImage);
		checker.setCount();
	}

	return newImage;
}
