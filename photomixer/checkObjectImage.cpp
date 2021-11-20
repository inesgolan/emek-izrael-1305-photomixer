#include "CheckObjectImage.h"

// Ctor
checkObjectImage::checkObjectImage(Mat image)
{
	this->_image = image;

	int count = 0;

	for (int i = 0; i < this->_image.rows; i++)
	{
		for (int j = 0; j < this->_image.cols; j++)
		{
			count++;
		}
	}

	this->_countOfPixels = count;
}


//Dtor
checkObjectImage::~checkObjectImage()
{
	this->_image.release();
}

void checkObjectImage::setImage(Mat image)
{
	_image = image;
}

void checkObjectImage::setCount()
{
	int count = 0;

	for (int i = 0; i < this->_image.rows; i++)
	{
		for (int j = 0; j < this->_image.cols; j++)
		{
			count++;
		}
	}

	this->_countOfPixels = count;
}

Mat checkObjectImage::getImage()
{
	return _image;
}

int checkObjectImage::getCount()
{
	return _countOfPixels;
}


/*
This function will check if the picture is only black and white
Input: none
Output: true - the picture is only black and white
		false - the picture is not only black and white
*/
bool checkObjectImage::checkBlackAndWhite()
{
	bool check = false;
	Vec3b rgbVector;

	for (int i = 0; i < this->_image.rows; i++)
	{
		for (int j = 0; j < this->_image.cols; j++)
		{
			rgbVector = _image.at<Vec3b>(i, j);

			if ((rgbVector[BLUE] == WHITE && rgbVector[RED] == WHITE && rgbVector[GREEN] == WHITE)
				|| (rgbVector[BLUE] == BLACK && rgbVector[RED] == BLACK && rgbVector[GREEN] == BLACK)
				|| (rgbVector[BLUE] <= DARKEST_GRAY && rgbVector[RED] <= DARKEST_GRAY && rgbVector[GREEN] <= DARKEST_GRAY)
				|| (rgbVector[BLUE] >= BRIGHTEST_GRAY && rgbVector[RED] >= BRIGHTEST_GRAY && rgbVector[GREEN] >= BRIGHTEST_GRAY))
			{
				check = true;
			}
			else
			{
				check = false;
			}
		}
	}

	return check;
}


/*
This function will check if most of the pixels in the picture are too dark 
Input: none
Output: true - the picture is too dark to recognize the object
		false - the picture is not too dark to recognize the object
*/
bool checkObjectImage::checkTooDark()
{
	Vec3b rgbVector;
	int count = 0;

	for (int i = 0; i < this->_image.rows; i++)
	{
		for (int j = 0; j < this->_image.cols; j++)
		{
			rgbVector = _image.at<Vec3b>(i, j);

			if (rgbVector[BLUE] <= DARKEST_GRAY && rgbVector[RED] <= DARKEST_GRAY && rgbVector[GREEN] <= DARKEST_GRAY)
			{
				count++;
			}
		}
	}

	if (this->_countOfPixels * MOST_OF_THE_PIXELS <= count) // check if most of the pixels are too dark
	{
		return true;
	}
	return false;
}


/*
This function will check if most of the pixels in the picture are too bright
Input: none
Output: true - the picture is too bright to recognize the object
		false - the picture is not too bright to recognize the object
*/
bool checkObjectImage::checkTooBright()
{
	Vec3b rgbVector;
	int count = 0;

	for (int i = 0; i < this->_image.rows; i++)
	{
		for (int j = 0; j < this->_image.cols; j++)
		{
			rgbVector = _image.at<Vec3b>(i, j);

			if (rgbVector[BLUE] >= BRIGHTEST_GRAY && rgbVector[RED] >= BRIGHTEST_GRAY && rgbVector[GREEN] >= BRIGHTEST_GRAY)
			{
				count++;
			}
		}
	}

	if (this->_countOfPixels * MOST_OF_THE_PIXELS <= count)
	{
		return true;
	}
	return false;
}

