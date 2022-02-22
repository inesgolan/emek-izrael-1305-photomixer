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
	Vec3b bgrVector;

	for (int i = 0; i < this->_image.rows; i++)
	{
		for (int j = 0; j < this->_image.cols; j++)
		{
			bgrVector = _image.at<Vec3b>(i, j);

			if ((bgrVector[BLUE] == WHITE && bgrVector[RED] == WHITE && bgrVector[GREEN] == WHITE)
				|| (bgrVector[BLUE] == BLACK && bgrVector[RED] == BLACK && bgrVector[GREEN] == BLACK)
				|| (bgrVector[BLUE] <= DARKEST_GRAY && bgrVector[RED] <= DARKEST_GRAY && bgrVector[GREEN] <= DARKEST_GRAY)
				|| (bgrVector[BLUE] >= BRIGHTEST_GRAY && bgrVector[RED] >= BRIGHTEST_GRAY && bgrVector[GREEN] >= BRIGHTEST_GRAY))
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
	Vec3b bgrVector;
	int count = 0;

	for (int i = 0; i < this->_image.rows; i++)
	{
		for (int j = 0; j < this->_image.cols; j++)
		{
			bgrVector = _image.at<Vec3b>(i, j);

			if (bgrVector[BLUE] <= DARKEST_GRAY && bgrVector[RED] <= DARKEST_GRAY && bgrVector[GREEN] <= DARKEST_GRAY)
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
	Vec3b bgrVector;
	int count = 0;

	for (int i = 0; i < this->_image.rows; i++)
	{
		for (int j = 0; j < this->_image.cols; j++)
		{
			bgrVector = _image.at<Vec3b>(i, j);

			if (bgrVector[BLUE] >= BRIGHTEST_GRAY && bgrVector[RED] >= BRIGHTEST_GRAY && bgrVector[GREEN] >= BRIGHTEST_GRAY)
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
