#include "includes.h"

int main(int argc, char** argv)
{
	std::string imagePath = "", backgroundPath = "", savePath = "", command = "python ", fileName = "", mail = "", password ="", key = "";
	bool check = false;
	Mat objectImage, backgroundImage, matte;
	ObjectDetection object;
	ClearBackground clearBackground;
	ObjectOnBackground objectOnBackground;
	DataBase db;

	if (argc > 1)
	{
		switch (std::stoi(argv[CODE]))
		{
		case OBJECT_DETECTION:
			//get image path
			imagePath = argv[IMAGE_PATH];
			objectImage = imread(imagePath); //get image

			objectImage = Helper::changeImageSize(OBJECT_SIZE, OBJECT_SIZE, objectImage, imagePath);
			
			
			check = Helper::checkImage(objectImage, imagePath); 
			if (check)
			{
				//get matte
				object.setImage(objectImage);
				object.getImageChannels();
				matte = object.getObjectMatte();

				//get object image	
				clearBackground.getObjectImage(objectImage, matte, argv[SAVE_OBJECT_PATH]);
			}

			break;

		case REVERSE_MATTE:
			//get image path
			imagePath = argv[IMAGE_PATH];

			//get image
			objectImage = imread(imagePath);
			check = Helper::checkImage(objectImage, imagePath); 
			if (check)
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

			break;

		case EDIT_IMAGE:
			//get image
			imagePath = argv[IMAGE_PATH];
			objectImage = imread(imagePath, -1); //read alpha channel

			//get background
			backgroundPath = argv[BACKGROUND_PATH];
			backgroundImage = imread(backgroundPath);

			//edit the image
			objectOnBackground.setBackground(backgroundImage);
			objectOnBackground.getEditedImage(std::stoi(argv[X_LOCATION]), std::stoi(argv[Y_LOCATION]), objectImage, backgroundImage, argv[SAVE_IMAGE_PATH]);

			break;

		case RESIZE_BIGGER:
			imagePath = argv[IMAGE_PATH];
			objectImage = imread(imagePath, -1); //read with alpha channel

			objectImage = Helper::changeImageSize(objectImage.rows + ADD , objectImage.cols + ADD, objectImage, argv[IMAGE_PATH]);

			break;

		case RESIZE_BACKGROUND:
			imagePath = argv[IMAGE_PATH];
			objectImage = imread(imagePath);

			objectImage = Helper::changeImageSize(BACKGROUND_ROWS, BACKGROUND_COLS , objectImage, argv[IMAGE_PATH]);

			break;

		case RESIZE_SMALLER:
			imagePath = argv[IMAGE_PATH];
			objectImage = imread(imagePath, -1); //read with alpha channel

			objectImage = Helper::changeImageSize(objectImage.rows + REMOVE, objectImage.cols + REMOVE, objectImage, argv[IMAGE_PATH]);

			break;

		case LOGIN:
			db.doesPasswordMatch(argv[USERNAME], argv[PASSWORD]); //check the password

			break;

		case REGISTER:
			db.addNewUser(argv[USERNAME], argv[PASSWORD], argv[MAIL], argv[KEY]);

			break;

		case ENCRYPTION:
			fileName = "files\\encryption.py";
			key = db.getUserKey(argv[USER]);

			//run python file
			system((command + fileName + " " + key + " " + argv[PATH] + " " + argv[USER]).c_str()); 
			
			break;

		case DECRYPTION:
			fileName = "files\\decryption.py";
			key = db.getUserKey(argv[USER]);
			
			//run python file
			system((command + fileName + " " + key + " " + argv[PATH] + " " + argv[USER]).c_str()); 

			break;

		case SEND_IMAGE_MAIL:
			fileName = "files\\sendMail.py";
			imagePath = argv[IMAGE_PATH];
			mail = db.getUserMail(argv[USER]);

			//run python file
			system((command + fileName + " " + argv[IMAGE_PATH] + " " + mail + " 1").c_str());

			break;

		case SEND_FORGETPASSWORD_MAIL:
			fileName = "files\\sendMail.py";
			mail = db.getUserMail(argv[USERNAME]);
			password = db.getUserPassword(argv[USERNAME]);

			//run python file
			system((command + fileName + " " + mail + " " + password + " 2").c_str());

			break;

		default:
			break;
		}
	}

	return 0;
}