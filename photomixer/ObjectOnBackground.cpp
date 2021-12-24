#include "ObjectOnBackground.h"

/*
This function is the constructor
Input: none
Output: none
*/
ObjectOnBackground::ObjectOnBackground()
{
}

/*
This function is the distructor - clears the mat
Input: none
Output: none
*/
ObjectOnBackground::~ObjectOnBackground()
{
	_background.release();
}

/*
This function sets a new background
Input: the new background mat
Output: none
*/
void ObjectOnBackground::setBackground(Mat newBackground)
{
	_background = newBackground;
}

/*
This function returns the background
Input: none
Output:the background mat
*/
Mat ObjectOnBackground::getBackground()
{
	return _background;
}

/*
This function puts the object on the background where the user choose
Input: the object mat, the background mat, path to save the result
Output: none
*/
void ObjectOnBackground::getEditedImage(int startX, int startY, Mat object, Mat background, std::string path)
{
	int x = startX;
	int y = startY;
	int length = object.rows;
	int width = object.cols;

	//create new image
	Mat image = Mat::zeros(background.size(), background.type());

	//create alpha channel
	std::vector<Mat> matChannels;
	matChannels = Helper::splitMat(background);
	image = Helper::mergeMat(matChannels, background);

	//check if the object image exits the background
	while (x + length > background.rows || y + width > background.cols || x < 0 || y < 0)
	{
		std::cout << "ERROR! OBJECT IS OUT OF THE BACKGROUD FRAME" << std::endl;
		std::cout << "PLEASE ENTER NEW X: " << std::endl;
		std::cin >> x;
		getchar();
		std::cout << "PLEASE ENTER NEW Y: " << std::endl;
		std::cin >> y;
		getchar();
	}

	//add alpha channel
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			image.at<Vec4b>(i, j)[ALPHA] = OPAQUE;
		}
	}

	//put the object pixels on the background image
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			// if the alpha value is 255 its the object 
			if (object.at<Vec4b>(i, j)[ALPHA] == OPAQUE)
			{
				image.at<Vec4b>(i+x, j+y)[BLUE] = object.at<Vec4b>(i, j)[BLUE];
				image.at<Vec4b>(i+x, j+y)[GREEN] = object.at<Vec4b>(i, j)[GREEN];
				image.at<Vec4b>(i+x, j+y)[RED] = object.at<Vec4b>(i, j)[RED];
			}
		}
	}

	//write changes to image
	imwrite(path, image);

	deleteImages();
}

/*
This function delete the color channels and matte images
Input: none
Output: none
*/
void ObjectOnBackground::deleteImages()
{
	std::remove("red.png"); 
	std::remove("blue.png");
	std::remove("green.png");
	std::remove("matte.png");
}
