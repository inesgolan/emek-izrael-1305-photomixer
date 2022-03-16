#include "CheckObjectImage.h"

#define ENDING 4
#define ALPHA 3
#define OPAQUE 255

//to display object image in GUI
#define MIN_ROWS_IMAGE 80
#define MIN_COLS_IMAGE 80

#define MIN_ROWS_LEN 160
#define MIN_COLS_LEN 160

#define MIN_ROWS_BACKGROUND 1000
#define MIN_COLS_BACKGROUND 1000

#define FALG_OBJECT 1
#define FLAG_BACKGROUND 0

#define TOO_BIG_PICTURE 0.4
#define MEDIOM_PICTURE 0.7
#define SMALL_PICTURE 0.85

using namespace cv;

class Helper
{
public:
	static bool checkImage(Mat image, std::string imagPath);

	static Mat changeImageSize(int rows, int cols, Mat image, std::string path, int flag);

	static std::vector<Mat> splitMat(Mat image);
	static Mat mergeMat(std::vector<Mat> matChannels, Mat objectImage);
};
