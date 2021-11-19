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
	_blueChannel = cv::Mat::zeros(image.rows, image.cols, CV_64FC1);
	cv::imwrite("blue.png", _blueChannel);
	_blueChannel = imread("blue.png");

	_greenChannel = cv::Mat::zeros(image.rows, image.cols, CV_64FC1);
	cv::imwrite("green.png", _greenChannel);
	_greenChannel = imread("green.png");

	_redChannel = cv::Mat::zeros(image.rows, image.cols, CV_64FC1);
	cv::imwrite("red.png", _redChannel);
	_redChannel = imread("red.png");

	//create empty matte 
	_matte = cv::Mat::zeros(image.rows, image.cols, CV_64FC1);
	cv::imwrite("matte.png", _matte);
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
This function get the avg of the darkest pixels in the object image
Input: none
Output: the avg
*/
int ObjectDetection::getDarkestAvg()
{
	int avg = WHITE;
	int pixelAvg = 0;
	Vec3b rgbVector;

	for (int i = 0; i < _image.rows; i++)
	{
		for (int j = 0; j < _image.cols; j++)
		{
			//get the image color channels
			rgbVector = _image.at<Vec3b>(i, j); 
			//get pixel avg
			pixelAvg = (int)rgbVector[RED] + (int)rgbVector[GREEN] + (int)rgbVector[BLUE];
			pixelAvg = pixelAvg / 3;

			if (pixelAvg < avg) 
			{
				avg = pixelAvg;
			}
			pixelAvg = 0;
		}
	}

	std::cout << "dark avg " << avg << std::endl;
	//put a range for the dark pixels - need to change for eash picture
	if (avg == BLACK) 
	{
		avg = 5;
	}
	else 
	{
		avg *= 3;
	}
	std::cout << "chaged dark avg " << avg << std::endl;

	return avg;
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
			_blueChannel.at<Vec3b>(i, j)[0] = _image.at<Vec3b>(i, j)[BLUE];
			_blueChannel.at<Vec3b>(i, j)[1] = _image.at<Vec3b>(i, j)[BLUE];
			_blueChannel.at<Vec3b>(i, j)[2] = _image.at<Vec3b>(i, j)[BLUE];

			// Green
			_greenChannel.at<Vec3b>(i, j)[0] = _image.at<Vec3b>(i, j)[GREEN];
			_greenChannel.at<Vec3b>(i, j)[1] = _image.at<Vec3b>(i, j)[GREEN];
			_greenChannel.at<Vec3b>(i, j)[2] = _image.at<Vec3b>(i, j)[GREEN];

			// Red
			_redChannel.at<Vec3b>(i, j)[0] = _image.at<Vec3b>(i, j)[RED];
			_redChannel.at<Vec3b>(i, j)[1] = _image.at<Vec3b>(i, j)[RED];
			_redChannel.at<Vec3b>(i, j)[2] = _image.at<Vec3b>(i, j)[RED];
		}
	}

	//save the changes in the pictures
	cv::imwrite("blue.png", _blueChannel);
	cv::imwrite("green.png", _greenChannel);
	cv::imwrite("red.png", _redChannel);
}

/*
This function make the colors channels mat darker 
Input: the colors channels vector
Output: none
*/
void ObjectDetection::makeDarker(Vec3b& rgbVector)
{
	if (rgbVector[BLUE] >= DARKER)
	{
		rgbVector[BLUE] -= DARKER;
	}
	if (rgbVector[GREEN] >= DARKER)
	{
		rgbVector[GREEN] -= DARKER;
	}
	if (rgbVector[RED] >= DARKER)
	{
		rgbVector[RED] -= DARKER;
	}

	// if smaller than 50 , change to 0 
	if (rgbVector[BLUE] < DARKER)
	{
		rgbVector[BLUE] = BLACK;
	}
	if (rgbVector[GREEN] < DARKER)
	{
		rgbVector[GREEN] = BLACK;
	}
	if (rgbVector[RED] < DARKER)
	{
		rgbVector[RED] = BLACK;
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
	cv::imwrite(name, tempMatte);
	Mat matte = imread(name);

	int pixelAvgGrayScale = 0;
	Vec3b rgbVectorGrayScale;

	int pixelAvgImage = 0;
	Vec3b rgbVectorImage;

	std::cout << name << " avg:" << avg << "\n\n";

	for (int i = 0; i < color.rows; i++)
	{
		for (int j = 0; j < color.cols; j++)
		{
			rgbVectorGrayScale = color.at<Vec3b>(i, j);

			//get pixel avg
			pixelAvgGrayScale = (int)rgbVectorGrayScale[RED] + (int)rgbVectorGrayScale[GREEN] + (int)rgbVectorGrayScale[BLUE];
			pixelAvgGrayScale = pixelAvgGrayScale / 3;

			rgbVectorImage = _image.at<Vec3b>(i, j);

			//get pixel avg
			pixelAvgImage = (int)rgbVectorImage[RED] + (int)rgbVectorImage[GREEN] + (int)rgbVectorImage[BLUE];
			pixelAvgImage = pixelAvgImage / 3;
			
			if (pixelAvgGrayScale >= avg) // lighter pixels - the object
			{
				matte.at<Vec3b>(i, j)[BLUE] = WHITE;
				matte.at<Vec3b>(i, j)[GREEN] = WHITE;
				matte.at<Vec3b>(i, j)[RED] = WHITE;
			}
			else // darker pixels
			{
				if (pixelAvgImage < _darkestAvg + RANGE) //need to check when we don't need to color the object
				{
					matte.at<Vec3b>(i, j)[BLUE] = WHITE;
					matte.at<Vec3b>(i, j)[GREEN] = WHITE;
					matte.at<Vec3b>(i, j)[RED] = WHITE;
				}
				else
				{
					matte.at<Vec3b>(i, j)[BLUE] = BLACK;
					matte.at<Vec3b>(i, j)[GREEN] = BLACK;
					matte.at<Vec3b>(i, j)[RED] = BLACK;
				}
			}
		}
	}

	// save the chanes in the picture
	cv::imwrite(name, matte); 
}

/*
This function gets the pixels average in given mat
Input:  color - the color channel mat
Output: the aveage
*/
int ObjectDetection::getPixelsAvg(Mat color)
{
	int pixelAvg = 0, avg = 0, count = 0;
	Vec3b rgbVector;

	for (int i = 0; i < color.rows; i++)
	{
		for (int j = 0; j < color.cols; j++)
		{
			rgbVector = color.at<Vec3b>(i, j);
			//get pixel avg
			pixelAvg = (int)rgbVector[RED] + (int)rgbVector[GREEN] + (int)rgbVector[BLUE];
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
Output: none
*/
void ObjectDetection::findObject()
{
	int avg = 0;

	avg = getPixelsAvg(_image);
	_darkestAvg = getDarkestAvg();

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

	//save changes to matte picture and show it
	cv::imwrite("matte.png", _matte);
	_matte = imread("matte.png");
	//cv::imshow("matte.png", _matte);
	//cv::waitKey(0);

	improvObjectColoring();
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
	//cv::imshow("matte.png", _matte);
	//cv::waitKey(0);

	Vec3b rgbVector;

	for (int i = 0; i < _matte.rows; i++)
	{
		for (int j = 0; j < _matte.cols; j++)
		{
			rgbVector = _image.at<Vec3b>(i, j);

			if (rgbVector[RED] == BLACK || rgbVector[GREEN] == BLACK || rgbVector[BLUE] == BLACK)
			{
				if (getPixelFrame(i, j)) //color all pixels or just one?
				{
					_matte.at<Vec3b>(i, j)[BLUE] = WHITE;
					_matte.at<Vec3b>(i, j)[GREEN] = WHITE;
					_matte.at<Vec3b>(i, j)[RED] = WHITE;
					std::cout << "WHITE ";
				}
			}
		}
	}
	cv::imshow("matte.png", _matte);
	cv::waitKey(0);
}

/*
This function will check the square that some pixel is exist in is in the middle of white area (in the middle of the object)
Input: int x, int y
Output: bool - true - the pixel is in the middle of white area (the object area)
			   false - the pixel is not in the middle of white area (the object area)
*/
bool ObjectDetection::getPixelFrame(int x, int y)
{
	int halfRib = 0, count = 0;
	bool isAllWhite = true;
	int const max_squre_size = (this->_matte.size().width * this->_matte.size().height) * 0.15; // 0.15 because it can't be all of the picture

	// check if the squere is still in the picture
	// 4 because its 0.5*0.5
	while ((halfRib * halfRib * 4 < max_squre_size) 
		&& (x + halfRib < _matte.rows && y + halfRib < _matte.cols && x - halfRib > _matte.rows && y - halfRib > _matte.cols)) // need to check if the square is too big
	{
		while (isAllWhite)
		{
			//  top line
			for (int k = 0; k < halfRib; k++) // right
			{
				if (_matte.at<Vec3b>(x + k, y + halfRib)[BLUE] == BLACK || _matte.at<Vec3b>(x + k, y + halfRib)[GREEN] == BLACK || _matte.at<Vec3b>(x + k, y + halfRib)[RED] == BLACK)
				{
					isAllWhite = false;
				}
				else
				{
					isAllWhite = true;
				}
			}

			for (int k = 0; k < halfRib; k++) // left 
			{
				if (_matte.at<Vec3b>(x - k, y + halfRib)[BLUE] == BLACK || _matte.at<Vec3b>(x - k, y + halfRib)[GREEN] == BLACK || _matte.at<Vec3b>(x - k, y + halfRib)[RED] == BLACK)
				{
					isAllWhite = false;
				}
				else
				{
					isAllWhite = true;
				}
			}


			// bottom line

			for (int k = 0; k < halfRib; k++) // right
			{
				if (_matte.at<Vec3b>(x + k, y - halfRib)[BLUE] == BLACK || _matte.at<Vec3b>(x + k, y - halfRib)[GREEN] == BLACK || _matte.at<Vec3b>(x + k, y - halfRib)[RED] == BLACK)
				{
					isAllWhite = false;
				}
				else
				{
					isAllWhite = true;
				}
			}

			for (int k = 0; k < halfRib; k++) // left 
			{
				if (_matte.at<Vec3b>(x - k, y - halfRib)[BLUE] == BLACK || _matte.at<Vec3b>(x - k, y - halfRib)[GREEN] == BLACK || _matte.at<Vec3b>(x - k, y - halfRib)[RED] == BLACK)
				{
					isAllWhite = false;
				}
				else
				{
					isAllWhite = true;
				}
			}

			// right col

			for (int k = 0; k < halfRib; k++) // up
			{
				if (_matte.at<Vec3b>(x + halfRib, y + k)[BLUE] == BLACK || _matte.at<Vec3b>(x + halfRib, y + k)[GREEN] == BLACK || _matte.at<Vec3b>(x + halfRib, y + k)[RED] == BLACK)
				{
					isAllWhite = false;
				}
				else
				{
					isAllWhite = true;
				}
			}

			for (int k = 0; k < halfRib; k++) // down
			{
				if (_matte.at<Vec3b>(x + halfRib, y - k)[BLUE] == BLACK || _matte.at<Vec3b>(x + halfRib, y - k)[GREEN] == BLACK || _matte.at<Vec3b>(x + halfRib, y - k)[RED] == BLACK)
				{
					isAllWhite = false;
				}
				else
				{
					isAllWhite = true;
				}
			}

			// left col

			for (int k = 0; k < halfRib; k++) // up
			{
				if (_matte.at<Vec3b>(x - halfRib, y + k)[BLUE] == BLACK || _matte.at<Vec3b>(x - halfRib, y + k)[GREEN] == BLACK || _matte.at<Vec3b>(x - halfRib, y + k)[RED] == BLACK)
				{
					isAllWhite = false;
				}
				else
				{
					isAllWhite = true;
				}
			}

			for (int k = 0; k < halfRib; k++) // down
			{
				if (_matte.at<Vec3b>(x - halfRib, y - k)[BLUE] == BLACK || _matte.at<Vec3b>(x - halfRib, y - k)[GREEN] == BLACK || _matte.at<Vec3b>(x - halfRib, y - k)[RED] == BLACK)
				{
					isAllWhite = false;
				}
				else
				{
					isAllWhite = true;
				}
			}
		}


		halfRib++;
	}


	return isAllWhite;
}

//bool ObjectDetection::checkPixelColor(int x, int y, int num)
//{
//	for (int k = 0; k < num; k++) 
//	{
//		if (_image.at<Vec3b>(x,y)[BLUE] == BLACK || _image.at<Vec3b>(x, y)[GREEN] == BLACK || _image.at<Vec3b>(x, y)[RED] == BLACK)
//		{
//			return false;
//		}
//	}
//	return true;
//}
