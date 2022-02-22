#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <fstream>

#define BLUE 0
#define GREEN 1
#define RED 2

#define WHITE 255
#define BLACK 0

#define DARKEST_GRAY 35
#define BRIGHTEST_GRAY 220
#define MOST_OF_THE_PIXELS 0.8

using namespace cv;

class checkObjectImage
{
private:
	Mat _image;
	int _countOfPixels;
	std::ofstream _outputFile;

public:
	checkObjectImage(Mat); //c'tor
	~checkObjectImage(); //d'tor

	//set
	void setImage(Mat);
	void setCount();

	//get
	Mat getImage();
	int getCount();

	bool checkBlackAndWhite();
	bool checkTooDark();
	bool checkTooBright(); 
};

