using System.Windows;
using System.IO;
using System.Windows.Media;
using System;

namespace photomixerGUI
{
    // user enters images pathes and this class checks the paths
    public partial class UploadPathes : Window
    {
        private const int SIZE = 10;
        private const int ENDING = 4;

        private static int imagesCounter;
        private Communicator communicator = new Communicator();
        private static string[] pathesArr;

        public UploadPathes()
        {
            InitializeComponent();
            imagesCounter = 0;
            pathesArr = new string[SIZE];
        }


        private void objectDetection(object sender, RoutedEventArgs e)
        {
            if (!isPathValid(objectPath.Text, "object") || !isPathValid(backgroundPath.Text, "background"))
            {
                ErrorMsg.Text = "Error - wrong path - try again.";
                ErrorMsg.Foreground = Brushes.DarkRed;
            }
            else
            {
                string path = "objectImage" + imagesCounter.ToString() + ".png";
                communicator.sendObjectRecognizeMsg(objectPath.Text, path);
                
                if (Int32.Parse(countOfPathes.Text) == imagesCounter)
                {
                    //checkMatte check = new checkMatte(objectPath.Text);
                    //check.Show();


                    //editImage edit = new editImage();
                    //edit.Show();
                    Close();
                }
            }
        }

        /*
        This function will check if the path is valid
        input:string path
        output: bool
        */
        private bool isPathValid(string path, string trypeOfPicture)
        {
            //C:\Users\משתמש\emek-izrael-1305-photomixer\photomixer\images\rabit.jpg

            string ending = "";
            string localPath = path;

            if (path.Length > ENDING) 
            {

                int startIndex = path.Length - ENDING;
                int finishIndex = path.Length - 1;
                int localPathlen = localPath.Length;

                ending = path.Substring(startIndex, finishIndex - startIndex + 1);

            }
            else
            {
                return false;
            }


            bool fileExist = File.Exists(path);
            if (fileExist && (".jpg" == ending || ".png" == ending)) //can open the file and it's a picture
            {
                if (trypeOfPicture == "object")
                {
                    pathesArr[imagesCounter] = localPath;
                    imagesCounter++;
                }
                return true;
            }

            return false;
        }
    }
}
