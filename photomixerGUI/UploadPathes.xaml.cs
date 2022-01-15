using System.Windows;
using System.IO;
using System.Windows.Media;
using System;

namespace photomixerGUI
{
    // user enters images pathes and this class checks the paths
    public partial class UploadPathes : Window
    {
        private const int SIZE = 11;
        private const int ENDING = 4;

        private Communicator communicator = new Communicator();
        private static int imagesCounter;
        private static string[] imagesPathes;

        public UploadPathes()
        {
            InitializeComponent();

            imagesCounter = 0;
            imagesPathes = new string[SIZE];
        }

        //this function check is the count of the pathes that the user enters is 1-10
        private void checkCount(object sender, RoutedEventArgs e)
        {
            int count = Int32.Parse(countOfPathes.Text);

            if (count < 1 || count > 10)
            {
                ErrorMsg.Text = "Error - wrong pathes count - try again.";
                countOfPathes.Clear();
            }
            else
            {
                ErrorMsg.Text = "ok";
            }

        }

        //this function detect the object in the given pathes from the user and get the background path 
        private void objectDetection(object sender, RoutedEventArgs e)
        {
            string imagePath = "";
            int count = Int32.Parse(countOfPathes.Text);

            if (imagesCounter < count)
            {
                //get the object path
                imagePath = objectPath.Text;
                objectPath.Clear();

                //if the path is valid detect the object in the image
                if (!isPathValid(imagePath))
                {
                    ErrorMsg.Text = "Error - wrong object image path - try again.";
                }
                else
                {
                    ErrorMsg.Text = "ok";

                    //checkMatte check = new checkMatte(objectPath.Text);
                    //check.Show();

                    imagesCounter++;
                    string savePath = "objectImage" + imagesCounter.ToString() + ".png";
                    communicator.sendObjectRecognizeMsg(imagePath, savePath);

                    //add the save path to the array
                    imagesPathes[imagesCounter-1] = savePath;

                }
            }
        }

        //this function check the background path and open the edit screen
        private void edit(object sender, RoutedEventArgs e)
        {
            string pathBackground = backgroundPath.Text;

            if (!isPathValid(pathBackground))
            {
                ErrorMsg.Text = "Error - wrong background path - try again.";
            }
            else
            {
                ErrorMsg.Text = "ok";

                //put the background path in the last cell in the array
                imagesPathes[imagesCounter] = pathBackground;

                Edit edit = new Edit(imagesPathes, imagesCounter);
                edit.Show();
                Close();
            }
        }

        /*
        This function will check if the path is valid
        input:string path
        output: bool
        */
        private bool isPathValid(string path)
        {
            //C:\Users\משתמש\emek-izrael-1305-photomixer\photomixer\images\rabit.jpg

            string ending = "";

            if (path.Length > ENDING) 
            {

                int startIndex = path.Length - ENDING;
                int finishIndex = path.Length - 1;

                ending = path.Substring(startIndex, finishIndex - startIndex + 1);

            }
            else
            {
                return false;
            }


            bool fileExist = File.Exists(path);
            if (fileExist && (".jpg" == ending || ".png" == ending)) //can open the file and it's a picture
            {
                return true;
            }

            return false;
        }
    }
}
