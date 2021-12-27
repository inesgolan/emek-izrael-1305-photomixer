#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "ClearBackground.h"

#define BLUE 0
#define GREEN 1
#define RED 2
#define ALPHA 3

#define WHITE 255
#define BLACK 0

#define OPAQUE 255
#define CLEAR 0

using namespace cv;

class ObjectOnBackground 
{
private: 
	Mat _background;
public:
	ObjectOnBackground(); //c'tor
	~ObjectOnBackground(); //d'tor

	//set and get
	void setBackground(Mat); 
	Mat getBackground();

	void getEditedImage(int, int, Mat, Mat, std::string);

	void deleteImages();
};

