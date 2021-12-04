#include "ClearBackground.h"

/*
This function will return the object image with transparent background
Input: image, black and white matte
Output: object image 
*/
Mat ClearBackground::getObjectImage(Mat image, Mat matte)
{
	//create new image
	Mat objectImage = Mat::zeros(image.size(), image.type());
	imwrite("objectImage.png", objectImage);

	//create alpha channel
	std::vector<Mat> matChannels;
	matChannels = splitMat(image);
	objectImage = mergeMat(matChannels, image);

	//change the backgroung alpha value to 0
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			if (matte.at<Vec3b>(i, j)[RED] == BLACK) 
			{
				objectImage.at<Vec4b>(i, j)[ALPHA] = CLEAR;
			}
			else 
			{
				objectImage.at<Vec4b>(i, j)[ALPHA] = OPAQUE;
			}
		}
	}

	//write changes to image
	imwrite("objectImage.png", objectImage);

	return objectImage;
}


/*
This function will split the 3 existed channels from picture's mat
input: Mat image
output: std::vector<Mat>
*/
std::vector<Mat> ClearBackground::splitMat(Mat image)
{
	std::vector<Mat> matChannels;

	for (int k = 0; k < RGB_CHANNELS_LEN; k++) // go throgh all RGB channels
	{
		cv::Mat temp = Mat::zeros(image.size(), image.type()); // create temp mat to push into the vector
		for (int i = 0; i < image.rows; i++) // go throgh the picture and put all the data from each RGB channel every time
		{
			for (int j = 0; j < image.cols; j++)
			{
				temp.at<Vec3b>(i, j)[k] = image.at<Vec3b>(i, j)[k]; //k = BLUE -> GREEN -> RED
			}
		}
		matChannels.push_back(temp);
	}

	return matChannels;
}


/*
This function will merge the 3 channels of some RGB picture + will add alpha channel
input: std::vector<Mat> matChannels, Mat image
output: Mat
*/
Mat ClearBackground::mergeMat(std::vector<Mat> matChannels, Mat image)
{
	cv::Mat_ <Vec4b> matt(image.size());

	for (int i = 1; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			// put the channels back to the mat + add the alpha channel to the mat
			matt.at<Vec4b>(i, j)[BLUE] = matChannels[BLUE].at<Vec3b>(i, j)[BLUE];
			matt.at<Vec4b>(i, j)[GREEN] = matChannels[GREEN].at<Vec3b>(i, j)[GREEN];
			matt.at<Vec4b>(i, j)[RED] = matChannels[RED].at<Vec3b>(i, j)[RED];
			matt.at<Vec4b>(i, j)[ALPHA] = OPAQUE;
		}
	}

	return matt;
}
