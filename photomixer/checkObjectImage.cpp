#include "checkObjectImage.h"

// Ctor
checkObjectImage::checkObjectImage(Mat image)
{
	this->_image = image;
}


//Dtor
checkObjectImage::~checkObjectImage()
{
	this->_image.release();
}


/*
This function will check if the picture is only black and white
Input: none
Output: true - the picture is not only black and white
		false - the picture is only black and white
*/
bool checkObjectImage::checkBlackAndWhite()
{
	bool check = false;
	Vec3b rgbVector;
	int temp = 0;

	for (int i = 0; i < this->_image.rows; i++)
	{
		for (int j = 0; j < this->_image.cols; j++)
		{
			rgbVector = _image.at<Vec3b>(i, j);

			if ((rgbVector[BLUE] == WHITE && rgbVector[RED] == WHITE && rgbVector[GREEN] == WHITE)
				|| (rgbVector[BLUE] == BLACK && rgbVector[RED] == BLACK && rgbVector[GREEN] == BLACK)
				|| (rgbVector[BLUE] <= DARKEST_GRAY && rgbVector[RED] <= DARKEST_GRAY && rgbVector[GREEN] <= DARKEST_GRAY))
			{
				temp = 0;
			}
			else
			{
				temp = 1;
			}
		}
	}

	if (temp == 0)
	{
		return true;
	}
	return false;
}


/*
This function will
Input:
Output:
*/
bool checkObjectImage::checkTooDark()
{
	return false;
}


/*
This function will
Input:
Output:
*/
bool checkObjectImage::checkTooBright()
{
	return false;
}
