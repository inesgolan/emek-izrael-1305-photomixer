#include "ClearBackground.h"

/*
This function will return the object image with transparent background
Input: image, black and white matte, path to save the result
Output: none 
*/
void ClearBackground::getObjectImage(Mat image, Mat matte, std::string path)
{
	//create new image
	Mat objectImage = Mat::zeros(image.size(), image.type());
	imwrite(path, objectImage);

	//create alpha channel
	std::vector<Mat> matChannels;
	matChannels = Helper::splitMat(image);
	objectImage = Helper::mergeMat(matChannels, image);

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

	//change image size
	objectImage = Helper::changeImageSize(MIN_ROWS_IMAGE, MIN_COLS_IMAGE, objectImage, path, FLAG_BACKGROUND);
}
