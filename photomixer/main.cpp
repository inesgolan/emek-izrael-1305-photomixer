#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector> 
#include <fstream>
#include "ObjectDetection.h"

#define ENDING 3

using namespace cv;

bool checkPath(std::string path);

int main()
{
	std::string path = "images/trols.jpg";
	while (!checkPath(path)) //path is invalid
	{
		std::cout << "please enter a valid path (image file): " << std::endl;
		std::cin >> path;	
		std::cout << "check " << path << std::endl;
		//clean buffer
		getchar();
	}

	Mat image = imread(path);

	ObjectDetection object = ObjectDetection(image);

	object.getImageChannels();
	object.findObject();
		
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