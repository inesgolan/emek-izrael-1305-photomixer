#include "ObjectOnBackground.h"
#include "ObjectDetection.h"
#include "DataBase.h"

#define OBJECT_DETECTION 100
#define REVERSE_MATTE 101
#define EDIT_IMAGE 200
#define RESIZE_BIGGER 300
#define RESIZE_SMALLER 400
#define LOGIN 500
#define REGISTER 600
#define ENCRYPTION 700
#define DECRYPTION 800
#define SEND_IMAGE_MAIL 900
#define SEND_FORGETPASSWORD_MAIL 901

#define CODE 1
#define OBJECT_PATH 2
#define IMAGE_PATH 2
#define USER 2
#define PASSWORD 3
#define KEY 3
#define USERS 3
#define SAVE_OBJECT_PATH 3
#define BACKGROUND_PATH 3
#define SAVE_IMAGE_PATH 4
#define X_LOCATION 5
#define Y_LOCATION 6

#define USERNAME 2
#define PASSWORD 3
#define MAIL 4

#define ADD 20
#define REMOVE -20

int main(int argc, char** argv)
{
	std::string imagePath = "", backgroundPath = "", savePath = "", command = "python ", fileName = "", mail = "", password ="";
	Mat objectImage, backgroundImage, matte;
	ObjectDetection object;
	ClearBackground clearBackground;
	ObjectOnBackground objectOnBackground;
	bool var = false;

	DataBase db;
	bool returnVal = false;

	if (argc > 1)
	{
		switch (std::stoi(argv[CODE]))
		{
		case OBJECT_DETECTION:
			//get image path
			imagePath = argv[OBJECT_PATH];
			imagePath = Helper::checkPath(imagePath);

			//get image
			objectImage = imread(imagePath);
			var = Helper::checkImage(objectImage, imagePath); 
			if (var)
			{
				//get matte
				object.setImage(objectImage);
				object.getImageChannels();
				matte = object.getObjectMatte();

				//get object image	
				clearBackground.getObjectImage(objectImage, matte, argv[SAVE_OBJECT_PATH]);
			}

			std::cout << "100 ok" << std::endl;
			break;

		case REVERSE_MATTE:
			//get image path
			imagePath = argv[OBJECT_PATH];
			imagePath = Helper::checkPath(imagePath);

			//get image
			objectImage = imread(imagePath);
			var = Helper::checkImage(objectImage, imagePath); //
			if (var)
			{
				//get matte
				object.setImage(objectImage);
				object.getImageChannels();
				matte = object.getObjectMatte();
				matte = object.reverseMatte();
				imwrite("matte2.png", matte);

				//get object image	
				clearBackground.getObjectImage(objectImage, matte, argv[SAVE_OBJECT_PATH]);
			}
			objectImage = Helper::checkImage(objectImage, imagePath);

			std::cout << "101 ok" << std::endl;
			break;

		case EDIT_IMAGE:
			//get image
			imagePath = argv[OBJECT_PATH];
			imagePath = Helper::checkPath(imagePath);
			objectImage = imread(imagePath, -1); //read alpha channel

			//get background
			backgroundPath = argv[BACKGROUND_PATH];
			backgroundImage = imread(backgroundPath);

			//edit the image
			objectOnBackground.setBackground(backgroundImage);
			objectOnBackground.getEditedImage(std::stoi(argv[X_LOCATION]), std::stoi(argv[Y_LOCATION]), objectImage, backgroundImage, argv[SAVE_IMAGE_PATH]);

			std::cout << "200 ok" << std::endl;
			break;

		case RESIZE_BIGGER:
			imagePath = argv[OBJECT_PATH];
			objectImage = imread(imagePath, -1);
			objectImage = Helper::changeImageSize(objectImage.rows + ADD , objectImage.cols + ADD, objectImage, argv[OBJECT_PATH], FLAG_BACKGROUND);

			std::cout << "300 ok" << std::endl;
			break;

		case RESIZE_SMALLER:
			imagePath = argv[OBJECT_PATH];
			objectImage = imread(imagePath, -1);

			objectImage = Helper::changeImageSize(objectImage.rows + REMOVE, objectImage.cols + REMOVE, objectImage, argv[OBJECT_PATH], FLAG_BACKGROUND);

			std::cout << "400 ok" << std::endl;
			break;

		case LOGIN:
			returnVal = db.doesPasswordMatch(argv[USERNAME], argv[PASSWORD]);

			std::cout << "500 ok" << std::endl;
			break;

		case REGISTER:
			returnVal = db.addNewUser(argv[USERNAME], argv[PASSWORD], argv[MAIL]);

			std::cout << "600 ok" << std::endl;
			break;

		case ENCRYPTION:
			fileName = "encryption.py";
			system((command + fileName + " " + argv[2] + " " + argv[3] + " " + argv[4]).c_str()); //key path username
			getchar();

			std::cout << "700 ok" << std::endl;
			break;

		case DECRYPTION:
			fileName = "decryption.py";
			system((command + fileName + " " + argv[2] + " " + argv[3] + " " + argv[4]).c_str()); //key path username
			getchar();

			std::cout << "800 ok" << std::endl;
			break;

		case SEND_IMAGE_MAIL:
			fileName = "sendMail.py";
			imagePath = argv[IMAGE_PATH];
			mail = db.getUserMail(argv[USERS]);

			std::cout << "imagePath: " << imagePath << " mail: " << mail;

			system((command + fileName + " " + argv[IMAGE_PATH] + " " + mail + " 1").c_str());
			getchar();

			std::cout << "900 ok" << std::endl;
			break;

		case SEND_FORGETPASSWORD_MAIL:
			fileName = "sendMail.py";
			mail = db.getUserMail(argv[USER]);
			password = db.getUserPassword(argv[USER]);

			system((command + fileName + " " + mail + " " + password + " 2").c_str());
			getchar();

			std::cout << "901 ok" << std::endl;
			break;

		default:
			std::cout << "error" << std::endl;
			break;
		}
	}

	return 0;
}