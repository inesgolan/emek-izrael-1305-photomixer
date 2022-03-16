#include "Helper.h"

#define OUTPUT_FILE_NAME "files/Output.txt"
std::mutex mtxCheck;


/*
This function gets an image from the user until it's valid
Input: image
Output: the new image
*/
bool Helper::checkImage(Mat image, std::string imagePath)
{
	Mat newImage = image;
	checkObjectImage* checker = new checkObjectImage(image);
	std::ofstream _outputFile;
	_outputFile.open(OUTPUT_FILE_NAME);
	bool var = false;

	if (checker->checkBlackAndWhite() || checker->checkTooDark() || checker->checkTooBright())
	{
		mtxCheck.lock();
		_outputFile << "False";
		mtxCheck.unlock();
	}
	else
	{
		mtxCheck.lock();
		_outputFile << "True";
		mtxCheck.unlock();
		var = true;
	}
	_outputFile.close();
	return var;
}

/*
This function will change the size of an image
input: rows, cols, image, std::string path
output: Mat
*/
Mat Helper::changeImageSize(int rows, int cols, Mat image, std::string path, int flag)
{
	Mat newMat;

	if (flag == FALG_OBJECT)
	{
		if (rows > 500 && cols > 500)
		{
			resize(image, newMat, Size(rows * TOO_BIG_PICTURE, cols * TOO_BIG_PICTURE), INTER_LINEAR);
		}

		else if (rows > 300 && cols > 300)
		{
			resize(image, newMat, Size(rows * MEDIOM_PICTURE, cols * MEDIOM_PICTURE), INTER_LINEAR);
		}

		else if (rows > 200 && cols > 200)
		{
			resize(image, newMat, Size(rows * SMALL_PICTURE, cols * SMALL_PICTURE), INTER_LINEAR);
		}
	}
	else
	{
		resize(image, newMat, Size(rows, cols), INTER_LINEAR);
	}
	
	imwrite(path, newMat);
	return newMat;
}

/*
This function will split the 3 existed channels from picture's mat
input: Mat image
output: std::vector<Mat>
*/
std::vector<Mat> Helper::splitMat(Mat image)
{
	std::vector<Mat> matChannels;

	for (int k = 0; k < 3; k++) // go throgh all RGB channels
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
Mat Helper::mergeMat(std::vector<Mat> matChannels, Mat image)
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


