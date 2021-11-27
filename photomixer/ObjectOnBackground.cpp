#include "ObjectOnBackground.h"

/*
This function is the constructor
Input: the background image mat
Output: none
*/
ObjectOnBackground::ObjectOnBackground(Mat background)
{
	_background = background;
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

//where check than the size of the object is smller than the background?
/*
This function puts the object on the background where the user choose
Input: the object mat, the background mat
Output: the combined image mat
*/
Mat ObjectOnBackground::getEditedImage(int startX, int startY, Mat object, Mat background)
{
	int x = startX;
	int y = startY;
	int length = object.rows;
	int width = object.cols;

	//create new image
	Mat image = Mat::zeros(background.size(), background.type());
	imwrite("image.png", image);

	//create alpha channel
	std::vector<Mat> matChannels;
	split(background, matChannels); 
	Mat alpha = matChannels.at(BLUE) + matChannels.at(GREEN) + matChannels.at(RED);
	matChannels.push_back(alpha);
	merge(matChannels, image);

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

	//put the object pixels on the background image
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			// if the alpha value is 1 its the object 
			if (object.at<Vec4b>(i, j)[ALPHA] == OPAQUE)
			{
				image.at<Vec4b>(i+x, j+y)[BLUE] = object.at<Vec4b>(i, j)[BLUE];
				image.at<Vec4b>(i+x, j+y)[GREEN] = object.at<Vec4b>(i, j)[GREEN];
				image.at<Vec4b>(i+x, j+y)[RED] = object.at<Vec4b>(i, j)[RED];
				image.at<Vec4b>(i+x, j+y)[ALPHA] = object.at<Vec4b>(i, j)[ALPHA];
			}
		}
	}

	//write changes to image
	imwrite("image.png", image);

	return image;
}
