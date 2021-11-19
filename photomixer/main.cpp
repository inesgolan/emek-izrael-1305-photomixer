#include <vector> 
#include <fstream>

#include "ObjectDetection.h"
#include "checkObjectImage.h"

#define ENDING 3

using namespace cv;

bool checkPath(std::string path);

int main()
{
	std::string path = "images/dino.jpg";
	while (!checkPath(path)) //path is invalid
	{
		std::cout << "Please enter a valid path (image file): " << std::endl;
		std::cin >> path;	
		getchar();
	}

	Mat image = imread(path);

	checkObjectImage checker = checkObjectImage(image);
	ObjectDetection object = ObjectDetection(image);
		
	if (checker.checkBlackAndWhite() || checker.checkTooDark() || checker.checkTooBright())
	{
		std::cout << "SOME ERROR - WE ARE NOT ABLE TO RECOGNIZE THE OBJECT IN THIS PICTURE" << std::endl;

	}
	else
	{
		object.getImageChannels();
		object.findObject();
	}

	return 0;
}

/*
This function checks the image path
Input: image path
Output: true - the path exist and is an image
		false - the file dosen't exist of isn't an image
*/
bool checkPath(std::string path)
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

	//open file
	std::ifstream ifile;
	ifile.open(path);

	if (ifile && ("jpg" == ending || "png" == ending)) 
	{
		return true;
	}
	return false;
}