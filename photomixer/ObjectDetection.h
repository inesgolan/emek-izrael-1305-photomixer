#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

#define BLUE 0
#define GREEN 1
#define RED 2

#define WHITE 255
#define BLACK 0

#define DARKER 50
#define RANGE 20
#define BRIGHT 200
#define FRAME 8

using namespace cv;

class ObjectDetection
{
private:
	Mat _image;
	Mat _redChannel;
	Mat _blueChannel;
	Mat _greenChannel;
	Mat _matte;
	std::string _matteColorChoice;

	void  makeColorDarker(Mat& color);
	void getChannel(Mat mat, int i, int j, int color);
	void changePixelColor(Mat mat, int color, int i, int j);
	void makeDarkImageMat(Mat mat, String name);
	void checkColorToImprove(Vec3b bgrVector, int color);

public:
	ObjectDetection(); //c'tor
	~ObjectDetection(); //d'tor

	//set
	void setImage(Mat);
	void setRed(Mat);
	void setBlue(Mat);
	void setGreen(Mat);
	void setMatte(Mat);
	void setMatteColorChoice(std::string);

	//get
	Mat getImage();
	Mat getRed();
	Mat getBlue();
	Mat getGreen();
	Mat getMatte();
	std::string getMatteColorChoice();

	void getImageChannels();

	void  makeDarker(Vec3b&);
	void  makeDarkestMatte(int avg, Mat& color, std::string name);
	int getPixelsAvg(Mat);
	Mat getObjectMatte();

	void choseMatte();
	void checkMatte();

	void improvObjectColoring();
	void getPixelFrame(int x, int y, int color);
	bool checkColor(int x, int y, int color);
	void colorAllSquare(int x, int y, int halfRib, int color);
};