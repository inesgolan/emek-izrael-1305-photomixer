#include "ObjectOnBackground.h"
#include "ObjectDetection.h"
#include "DataBase.h"

//message codes
#define OBJECT_DETECTION 100
#define REVERSE_MATTE 101
#define EDIT_IMAGE 200
#define RESIZE_BIGGER 300
#define RESIZE_BACKGROUND 350
#define RESIZE_SMALLER 400
#define LOGIN 500
#define REGISTER 600
#define ENCRYPTION 700
#define DECRYPTION 800
#define SEND_IMAGE_MAIL 900
#define SEND_FORGETPASSWORD_MAIL 901

//object detection
#define CODE 1
#define IMAGE_PATH 2
#define SAVE_OBJECT_PATH 3

//put object on background
//CODE
//IMAGE_PATH
#define BACKGROUND_PATH 3
#define SAVE_IMAGE_PATH 4
#define X_LOCATION 5
#define Y_LOCATION 6

//resize
//CODE
//IMAGE_PATH
#define ADD 20
#define REMOVE -20

//sign in and register
//CODE
#define USERNAME 2
#define PASSWORD 3
#define MAIL 4
#define KEY 5

//encryption and decryption
//CODE
#define PATH 2
#define USER 3
