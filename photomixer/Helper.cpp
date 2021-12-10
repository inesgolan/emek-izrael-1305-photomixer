#include "Helper.h"

/*
This function gets a path from the user until it's valid
Input: image path
Output: the valid path
*/
std::string Helper::checkPath(std::string path)
{
	std::string newPath = path;

	while (!isPathValid(newPath))
	{
		std::cout << "PLEASE ENTER A VALID PATH (OF AN IMAGE FILE): " << std::endl;
		std::cin >> newPath;
		getchar();
	}

	return newPath;
}

/*
This function checks the image path
Input: image path
Output: true - the path exist and is an image
		false - the file dosen't exist of isn't an image
*/
bool Helper::isPathValid(std::string path)
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

	std::ifstream ifile;
	ifile.open(path);

	if (ifile && (".jpg" == ending || ".png" == ending)) //can open the file and it's a picture
	{
		return true;
	}
	return false;
}


/*
This function gets an image from the user until it's valid
Input: image
Output: the new image
*/
Mat Helper::checkImage(Mat image, std::string imagePath)
{
	Mat newImage = image;
	checkObjectImage checker = checkObjectImage(image);

	while (checker.checkBlackAndWhite() || checker.checkTooDark() || checker.checkTooBright())
	{
		std::cout << "SOME ERROR - WE ARE NOT ABLE TO RECOGNIZE THE OBJECT IN THIS PICTURE" << std::endl;

		//get new path
		std::cout << "PLEASE ENTER A VALID PATH (OF AN IMAGE FILE): " << std::endl;
		std::cin >> imagePath;
		getchar();
		imagePath = checkPath(imagePath);

		//get the new image
		newImage = imread(imagePath);
		checker.setImage(newImage);
		checker.setCount();
	}

	if (image.cols > MIN_COLS_IMAGE || image.rows > MIN_ROWS_IMAGE) //change image size if its too big
	{
		newImage = Helper::changeImageSize(MIN_ROWS_IMAGE, MIN_COLS_IMAGE, newImage, imagePath);
	}

	return newImage;
}

/*
This function gets a new background image from the user
Input: current background path
Output: the new background path
*/
std::string Helper::getNewBackground(std::string backgroundPath)
{
	std::string choice = "";
	std::string newPath = backgroundPath;

	std::cout << "want to change the background image? (yes/no)" << std::endl;
	std::cin >> choice;
	getchar();

	if (choice == "yes") //user wants to change the background
	{
		std::cout << "enter new path: " << std::endl;
		std::cin >> newPath;
		getchar();
	}

	newPath = checkPath(newPath);

	Mat image = imread(newPath);
	std::cout << "background size: " << image.cols << " " << image.rows << std::endl;
	if (image.cols > MIN_COLS_BACKGROUND || image.rows > MIN_ROWS_BACKGROUND) //change image size if its too big
	{
		image = Helper::changeImageSize(MIN_ROWS_BACKGROUND, MIN_COLS_BACKGROUND, image, newPath);
	}


	return newPath;
}

/*
This function will change the size of an image
input: rows, cols, image, std::string path
output: Mat
*/
Mat Helper::changeImageSize(int rows, int cols, Mat image, std::string path)
{
	Mat newMat;
	resize(image, newMat, Size(rows, cols), INTER_LINEAR);
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


