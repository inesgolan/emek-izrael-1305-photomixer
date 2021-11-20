#include "ObjectDetection.h"

/*
This function is the constructor
Input: the object image mat
Output: none
*/
ObjectDetection::ObjectDetection(Mat image)
{
	this->_image = image;

	//create mat for each RGB color channel im the size of the image
	_blueChannel = Mat::zeros(image.rows, image.cols, CV_64FC1);
	imwrite("blue.png", _blueChannel);
	_blueChannel = imread("blue.png");

	_greenChannel = Mat::zeros(image.rows, image.cols, CV_64FC1);
	imwrite("green.png", _greenChannel);
	_greenChannel = imread("green.png");

	_redChannel = Mat::zeros(image.rows, image.cols, CV_64FC1);
	imwrite("red.png", _redChannel);
	_redChannel = imread("red.png");

	//create empty matte 
	_matte = Mat::zeros(image.rows, image.cols, CV_64FC1);
	imwrite("matte.png", _matte);
	_matte = imread("matte.png");
}

/*
This function is the distructor - clears the mat
Input: none
Output: none
*/
ObjectDetection::~ObjectDetection()
{
	this->_image.release();
	this->_redChannel.release();
	this->_blueChannel.release();
	this->_greenChannel.release();
	this->_matte.release();
}

//setters
void ObjectDetection::setImage(Mat image)
{
	_image = image;
}

void ObjectDetection::setRed(Mat red)
{
	_redChannel = red;
}

void ObjectDetection::setBlue(Mat blue)
{
	_blueChannel = blue;
}

void ObjectDetection::setGreen(Mat green)
{
	_greenChannel = green;
}

void ObjectDetection::setMatte(Mat matte)
{
	_matte = matte;
}

void ObjectDetection::setMatteColorChoice(std::string color)
{
	_matteColorChoice = color;
}

//getters
Mat ObjectDetection::getImage()
{
	return _image;
}

Mat ObjectDetection::getRed()
{
	return _redChannel;
}

Mat ObjectDetection::getBlue()
{
	return _blueChannel;
}

Mat ObjectDetection::getGreen()
{
	return _greenChannel;
}

Mat ObjectDetection::getMatte()
{
	return _matte;
}

std::string ObjectDetection::getMatteColorChoice()
{
	return _matteColorChoice;
}

/*
This function make the color mat darker
Input: color mat
Output: none
*/
void ObjectDetection::makeColorDarker(Mat& color)
{
	for (int i = 0; i < color.rows; i++)
	{
		for (int j = 0; j < color.cols; j++)
		{
			makeDarker(color.at<Vec3b>(i, j));
		}
	}
}

/*
This function get the colors channels grayscale mat from the image
Input: none
Output: none
*/
void ObjectDetection::getImageChannels()
{
	for (int i = 0; i < _image.rows; i++)
	{
		for (int j = 0; j < _image.cols; j++)
		{
			// Blue
			_blueChannel.at<Vec3b>(i, j)[BLUE] = _image.at<Vec3b>(i, j)[BLUE];
			_blueChannel.at<Vec3b>(i, j)[GREEN] = _image.at<Vec3b>(i, j)[BLUE];
			_blueChannel.at<Vec3b>(i, j)[RED] = _image.at<Vec3b>(i, j)[BLUE];

			// Green
			_greenChannel.at<Vec3b>(i, j)[BLUE] = _image.at<Vec3b>(i, j)[GREEN];
			_greenChannel.at<Vec3b>(i, j)[GREEN] = _image.at<Vec3b>(i, j)[GREEN];
			_greenChannel.at<Vec3b>(i, j)[RED] = _image.at<Vec3b>(i, j)[GREEN];

			// Red
			_redChannel.at<Vec3b>(i, j)[BLUE] = _image.at<Vec3b>(i, j)[RED];
			_redChannel.at<Vec3b>(i, j)[GREEN] = _image.at<Vec3b>(i, j)[RED];
			_redChannel.at<Vec3b>(i, j)[RED] = _image.at<Vec3b>(i, j)[RED];
		}
	}

	//save the changes in the pictures
    imwrite("blue.png", _blueChannel);
	imwrite("green.png", _greenChannel);
	imwrite("red.png", _redChannel);
}

/*
This function make the colors channels mat darker 
Input: the colors channels vector
Output: none
*/
void ObjectDetection::makeDarker(Vec3b& bgrVector)
{
	if (bgrVector[BLUE] >= DARKER)
	{
		bgrVector[BLUE] -= DARKER;
	}
	if (bgrVector[GREEN] >= DARKER)
	{
		bgrVector[GREEN] -= DARKER;
	}
	if (bgrVector[RED] >= DARKER)
	{
		bgrVector[RED] -= DARKER;
	}

	// if smaller than 50 , change to 0 
	if (bgrVector[BLUE] < DARKER)
	{
		bgrVector[BLUE] = BLACK;
	}
	if (bgrVector[GREEN] < DARKER)
	{
		bgrVector[GREEN] = BLACK;
	}
	if (bgrVector[RED] < DARKER)
	{
		bgrVector[RED] = BLACK;
	}
}

/*
This function make a matte for the given color channel mat
Input: avg - the pixels average in the mat
		color - the color channel mat
		name - the name of the color channel picture
Output: none
*/
void ObjectDetection::makeDarkestMatte(int avg, Mat& color, std::string name)
{
	//create the matte
	Mat tempMatte(color.rows, color.cols, CV_64FC1);
	imwrite(name, tempMatte);
	Mat matte = imread(name);

	int pixelAvgGrayScale = 0;
	Vec3b bgrVectorGrayScale;

	int pixelAvgImage = 0;
	Vec3b bgrVectorImage;

	std::cout << name << " avg:" << avg << "\n\n";

	for (int i = 0; i < color.rows; i++)
	{
		for (int j = 0; j < color.cols; j++)
		{
			bgrVectorGrayScale = color.at<Vec3b>(i, j);

			//get pixel avg
			pixelAvgGrayScale = (int)bgrVectorGrayScale[RED] + (int)bgrVectorGrayScale[GREEN] + (int)bgrVectorGrayScale[BLUE];
			pixelAvgGrayScale = pixelAvgGrayScale / 3;

			bgrVectorImage = _image.at<Vec3b>(i, j);

			//get pixel avg
			pixelAvgImage = (int)bgrVectorImage[RED] + (int)bgrVectorImage[GREEN] + (int)bgrVectorImage[BLUE];
			pixelAvgImage = pixelAvgImage / 3;
			
			if (pixelAvgGrayScale >= avg) // lighter pixels - the object
			{
				matte.at<Vec3b>(i, j)[BLUE] = WHITE;
				matte.at<Vec3b>(i, j)[GREEN] = WHITE;
				matte.at<Vec3b>(i, j)[RED] = WHITE;
			}
			else // darker pixels
			{
				matte.at<Vec3b>(i, j)[BLUE] = BLACK;
				matte.at<Vec3b>(i, j)[GREEN] = BLACK;
				matte.at<Vec3b>(i, j)[RED] = BLACK;
			}
		}
	}

	// save the chanes in the picture
	imwrite(name, matte); 
}

/*
This function gets the pixels average in given mat
Input:  color - the color channel mat
Output: the aveage
*/
int ObjectDetection::getPixelsAvg(Mat color)
{
	int pixelAvg = 0, avg = 0, count = 0;
	Vec3b bgrVector;

	for (int i = 0; i < color.rows; i++)
	{
		for (int j = 0; j < color.cols; j++)
		{
			bgrVector = color.at<Vec3b>(i, j);
			//get pixel avg
			pixelAvg = (int)bgrVector[RED] + (int)bgrVector[GREEN] + (int)bgrVector[BLUE];
			pixelAvg = pixelAvg / 3;
			//add pixel avg to avg
			avg += pixelAvg;

			pixelAvg = 0;
			count++;
		}
	}
	avg = avg / count;

	return avg;
}

/*
This function find the object in the image and show the matte
Input: none
Output: the matte
*/
Mat ObjectDetection::findObject()
{
	int avg = 0;

	avg = getPixelsAvg(_image);

	std::cout << "image avg " << avg << std::endl;
	if (avg < BRIGHT) //the image is darker
	{
		//make image darker in each color channel to find object

		makeColorDarker(_redChannel);
		avg = getPixelsAvg(_redChannel);
		makeDarkestMatte(avg,_redChannel, "red.png");

		makeColorDarker(_greenChannel);
		avg = getPixelsAvg(_greenChannel);
		makeDarkestMatte(avg, _greenChannel, "green.png");

		makeColorDarker(_blueChannel);
		avg = getPixelsAvg(_blueChannel);
		makeDarkestMatte(avg, _blueChannel, "blue.png");
	}

	choseMatte();
	//set new matte
	if (_matteColorChoice == "red")
	{
		_matte = _redChannel;
	}
	else if (_matteColorChoice == "blue")
	{
		_matte = _blueChannel;
	}
	else
	{
		_matte = _greenChannel;
	}

	improvObjectColoring();

	return _matte;
}

/*
This function chose the matte that identify the object the best
Input: none
Output: none
*/
void ObjectDetection::choseMatte()
{
	int redAvg = 0, greenAvg = 0, blueAvg = 0;

	//check which color is more in the image
	redAvg = getPixelsAvg(_redChannel);
	greenAvg = getPixelsAvg(_greenChannel);
	blueAvg = getPixelsAvg(_blueChannel);
	std::cout << "\n\nredAvg: " << redAvg << "\n";
	std::cout << "greenAvg: " << greenAvg << "\n";
	std::cout << "blueAvg: " << blueAvg << "\n";

	if (redAvg > greenAvg && redAvg > blueAvg) //chose the highet avg
	{
		_matteColorChoice = "red";
	}
	else if (blueAvg > greenAvg && blueAvg > redAvg)
	{
		_matteColorChoice = "blue";
	}
	else
	{
		_matteColorChoice = "green";
	}

	std::cout << "chosen matte: " << _matteColorChoice << std::endl;

	_redChannel = imread("red.png");
	_greenChannel = imread("green.png");
	_blueChannel = imread("blue.png");
}


/*
This function will go throgh all the black pixels in a picture and will check if they are in the middle of white area
Input: none
Output: none
*/
void ObjectDetection::improvObjectColoring()
{
	Vec3b bgrVector;

	// check for black pixels
	for (int i = 0; i < _matte.rows; i++)
	{
		for (int j = 0; j < _matte.cols; j++)
		{
			bgrVector = _matte.at<Vec3b>(i, j);

			if (bgrVector[RED] == BLACK)
			{
				getPixelFrame(i, j, BLACK);
			}
		}
	}

	// check for white pixels
	for (int i = 0; i < _matte.rows; i++)
	{
		for (int j = 0; j < _matte.cols; j++)
		{
			bgrVector = _matte.at<Vec3b>(i, j);

			if (bgrVector[RED] == WHITE)
			{
				getPixelFrame(i, j, WHITE);
			}
		}
	}

	//save changes to matte picture
	imwrite("matte.png", _matte);
	_matte = imread("matte.png");
}

/*
This function will check the square that some pixel is exist in is in the middle of the not type area 
(in the middle of the object or background - it depends on the type)
Input: int x, int y
Output: none
*/
void ObjectDetection::getPixelFrame(int x, int y, int color)
{
	int halfRib = 1, flag = 0;
	bool isAllTheSame = true;
	int const max_squre_size = (this->_matte.rows * this->_matte.cols) * 0.3; // 0.3 because it can't be all of the picture
	

	// check if the squere is still in the picture
	while ((halfRib * halfRib * 4 < max_squre_size) 
		&& (x + halfRib < _matte.rows && y + halfRib < _matte.cols && x - halfRib > 0 && y - halfRib > 0 )
		&& flag == 0) 
	{
		while (isAllTheSame)
		{
			for (int k = 0; k < halfRib; k++)
			{
				// check what is the color of the pixel that is checking now
				if (color == BLACK)
				{
					if (!checkColor(x + k, y + halfRib, BLACK) || !checkColor(x - k, y + halfRib, BLACK) || !checkColor(x + k, y - halfRib, BLACK) || !checkColor(x - k, y - halfRib, BLACK) ||
						!checkColor(x + halfRib, y + k, BLACK) || !checkColor(x + halfRib, y - k, BLACK) || !checkColor(x - halfRib, y + k, BLACK) || !checkColor(x - halfRib, y - k, BLACK))
					{
						isAllTheSame = false;
					}
				}
				else
				{
					if (!checkColor(x + k, y + halfRib, WHITE) || !checkColor(x - k, y + halfRib, WHITE) || !checkColor(x + k, y - halfRib, WHITE) || !checkColor(x - k, y - halfRib, WHITE) ||
						!checkColor(x + halfRib, y + k, WHITE) || !checkColor(x + halfRib, y - k, WHITE) || !checkColor(x - halfRib, y + k, WHITE) || !checkColor(x - halfRib, y - k, WHITE))
					{
						isAllTheSame = false;
					}
				}
			}

			//finish the loop
			if (isAllTheSame) 
			{
				flag = 1;
			}

			isAllTheSame = false;
		}


		if (flag == 1 && color == BLACK) // white square exist outside of black pixel
		{
			colorAllSquare(x, y, halfRib, BLACK);
		}
		else if (flag == 1 && color == WHITE) // black square exist outside of white pixel
		{
			colorAllSquare(x, y, halfRib, WHITE);
		}
		else // no valid square 
		{
			isAllTheSame = true;
			flag = 0;
			halfRib++;
		}
	}
}

/*
This function will check if some pixel is black or white
input: int x, int y
output: bool - true - white
				false - black
*/
bool ObjectDetection::checkColor(int x, int y, int color)
{
	if (_matte.at<Vec3b>(x, y)[RED] == color)
	{
		return false;
	}
	return true;
}

/*
This function will color all the pixels inside the square area according to the type of pixel that is currently checking
input: int x, int y, int halfRib
output: none
*/
void ObjectDetection::colorAllSquare(int x, int y, int halfRib, int color)
{
	int startX = x - halfRib;
	int startY = y + halfRib;

	for (int i = 0; i < 2 * halfRib; i++)
	{		
		for (int j = 0; j < 2 * halfRib; j++)
		{
			// check what is the color of the pixel that is checking now
			if (color == BLACK) 
			{
				_matte.at<Vec3b>(startX, startY - j)[BLUE] = WHITE;
				_matte.at<Vec3b>(startX, startY - j)[GREEN] = WHITE;
				_matte.at<Vec3b>(startX, startY - j)[RED] = WHITE;
			}
			else
			{
				_matte.at<Vec3b>(startX, startY - j)[BLUE] = BLACK;
				_matte.at<Vec3b>(startX, startY - j)[GREEN] = BLACK;
				_matte.at<Vec3b>(startX, startY - j)[RED] = BLACK;
			}
		}
		startX++;
	}
}