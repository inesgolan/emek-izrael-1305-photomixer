#include "objectDetection.h"


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


//get the avg of the darkest pixels in the image
int ObjectDetection::getDarkestAvg()
{
	int avg = 255;
	int pixelAvg = 0;
	Vec3b rgbVector;

	for (int i = 0; i < _image.rows; i++)
	{
		for (int j = 0; j < _image.cols; j++)
		{
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
	if (avg == BLACK) 
	{
		avg = 5;
	}
	else //to put a range for the pixels
	{
		avg *= 3; //change for each pic
	}
	std::cout << "chaged dark avg " << avg << std::endl;

	return avg;
}


//c'tor
ObjectDetection::ObjectDetection(Mat image) 
{
	this->_image = image;

	//create mat for each RGB color channel im the size of the image
	_redChannel = cv::Mat::zeros(image.rows, image.cols, CV_64FC1);
	cv::imwrite("red.png", _redChannel);
	_redChannel = imread("red.png");

	_greenChannel = cv::Mat::zeros(image.rows, image.cols, CV_64FC1);
	cv::imwrite("green.png", _greenChannel);
	_greenChannel = imread("green.png");

	_blueChannel = cv::Mat::zeros(image.rows, image.cols, CV_64FC1);
	cv::imwrite("blue.png", _blueChannel);
	_blueChannel = imread("blue.png");

	//empty matte
	_matte = cv::Mat::zeros(image.rows, image.cols, CV_64FC1);
	cv::imwrite("matte.png", _matte);
	_matte = imread("matte.png");
}

//dtor
ObjectDetection::~ObjectDetection()
{
	this->_image.release();
	this->_redChannel.release();
	this->_blueChannel.release();
	this->_greenChannel.release();
	this->_matte.release();
}


//seters
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

//geters
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


//get color grayscale channels
void ObjectDetection::getImageChannels()
{
	for (int i = 0; i < _image.rows; i++)
	{
		for (int j = 0; j < _image.cols; j++)
		{
			// Red
			_redChannel.at<Vec3b>(i, j)[0] = _image.at<Vec3b>(i, j)[2];
			_redChannel.at<Vec3b>(i, j)[1] = _image.at<Vec3b>(i, j)[2];
			_redChannel.at<Vec3b>(i, j)[2] = _image.at<Vec3b>(i, j)[2];

			// Green
			_greenChannel.at<Vec3b>(i, j)[0] = _image.at<Vec3b>(i, j)[1];
			_greenChannel.at<Vec3b>(i, j)[1] = _image.at<Vec3b>(i, j)[1];
			_greenChannel.at<Vec3b>(i, j)[2] = _image.at<Vec3b>(i, j)[1];

			// Blue
			_blueChannel.at<Vec3b>(i, j)[0] = _image.at<Vec3b>(i, j)[0];
			_blueChannel.at<Vec3b>(i, j)[1] = _image.at<Vec3b>(i, j)[0];
			_blueChannel.at<Vec3b>(i, j)[2] = _image.at<Vec3b>(i, j)[0];
		}
	}

	//save the changes in the pictures
	cv::imwrite("red.png", _redChannel);
	cv::imwrite("green.png", _greenChannel);
	cv::imwrite("blue.png", _blueChannel);
}


void ObjectDetection::makeDarker(Vec3b& rgbVector)
{
	if (rgbVector[RED] >= 50)
	{
		rgbVector[RED] -= 50;
	}
	if (rgbVector[BLUE] >= 50)
	{
		rgbVector[BLUE] -= 50;
	}
	if (rgbVector[GREEN] >= 50)
	{
		rgbVector[GREEN] -= 50;
	}
	// if smaller than 50 , change to 0 
	if (rgbVector[RED] < 50)
	{
		rgbVector[RED] = 0;
	}
	if (rgbVector[BLUE] < 50)
	{
		rgbVector[BLUE] = 0;
	}
	if (rgbVector[GREEN] < 50)
	{
		rgbVector[GREEN] = 0;
	}
}


// make the back and white picture (called matte)
void ObjectDetection::makeDarkestMatte(int avg, Mat& color, std::string name)
{
	Mat new_img(color.rows, color.cols, CV_64FC1);
	cv::imwrite(name, new_img);
	Mat matte = imread(name);

	int pixelAvgGrayScale = 0;
	Vec3b rgbVector;

	int pixelAvgImage = 0;
	Vec3b rgbVectorImage;

	std::cout << name << " avg:" << avg << "\n\n";

	for (int i = 0; i < color.rows; i++)
	{
		for (int j = 0; j < color.cols; j++)
		{
			rgbVector = color.at<Vec3b>(i, j);

			//get pixel avg
			pixelAvgGrayScale = (int)rgbVector[RED] + (int)rgbVector[GREEN] + (int)rgbVector[BLUE];
			pixelAvgGrayScale = pixelAvgGrayScale / 3;

			rgbVectorImage = _image.at<Vec3b>(i, j);

			//get pixel avg
			pixelAvgImage = (int)rgbVectorImage[RED] + (int)rgbVectorImage[GREEN] + (int)rgbVectorImage[BLUE];
			pixelAvgImage = pixelAvgImage / 3;
			
			if (pixelAvgGrayScale >= avg) // lighter pixels - the object
			{
				matte.at<Vec3b>(i, j)[0] = WHITE;
				matte.at<Vec3b>(i, j)[1] = WHITE;
				matte.at<Vec3b>(i, j)[2] = WHITE;
			}
			else // darker pixels
			{
				if (pixelAvgImage < _darkestAvg + 20) //range of darker parts of the object
				{
					matte.at<Vec3b>(i, j)[0] = WHITE;
					matte.at<Vec3b>(i, j)[1] = WHITE;
					matte.at<Vec3b>(i, j)[2] = WHITE;
				}
				else
				{
					matte.at<Vec3b>(i, j)[0] = BLACK;
					matte.at<Vec3b>(i, j)[1] = BLACK;
					matte.at<Vec3b>(i, j)[2] = BLACK;
				}
			}
		}
	}
	cv::imwrite(name, matte); // save the chanes in the picture
}


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


void ObjectDetection::findObject()
{
	int avg = 0;

	avg = getPixelsAvg(_image);
	_darkestAvg = getDarkestAvg();

	std::cout << "image avg " << avg << std::endl;
	if (avg < 200) //the image is darker
	{
		//make image darker to find object
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
		setMatte(_redChannel);
		std::cout << "im redddd\n";
	}
	else if (_matteColorChoice == "blue")
	{
		setMatte(_blueChannel);
		std::cout << "im blueee\n";
	}
	else
	{
		setMatte(_greenChannel);
		std::cout << "im greennnnn\n";
	}


	cv::imwrite("matte.png", _matte);
	_matte = imread("matte.png");
	cv::imshow("matte.png", _matte);
	cv::waitKey(0);
}


void ObjectDetection::choseMatte()
{
	int redAvg = 0, greenAvg = 0, blueAvg = 0;

	redAvg = getPixelsAvg(_redChannel);
	greenAvg = getPixelsAvg(_greenChannel);
	blueAvg = getPixelsAvg(_blueChannel);

	std::cout << "\n\nredAvg: " << redAvg << "\n";
	std::cout << "greenAvg: " << greenAvg << "\n";
	std::cout << "blueAvg: " << blueAvg << "\n";

	if (redAvg > greenAvg && redAvg > blueAvg)
	{
		setMatteColorChoice("red");
		std::cout << "im redddd\n";
	}
	else if (blueAvg > greenAvg && blueAvg > redAvg)
	{
		setMatteColorChoice("blue");
		std::cout << "im blueeee\n";
	}
	else
	{
		setMatteColorChoice("green");
		std::cout << "im greennn\n";
	}


	setRed(imread("red.png"));
	setGreen(imread("green.png"));
	setBlue(imread("blue.png"));
}
