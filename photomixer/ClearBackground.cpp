#include "ClearBackground.h"

Mat ClearBackground::getObjectImage(Mat image, Mat matte)
{
	Mat objectImage = cv::Mat::zeros(image.rows, image.cols, CV_64FC1);
	cv::imwrite("objectImage.png", objectImage);
	objectImage = imread("objectImage.png");






    return objectImage;
}
