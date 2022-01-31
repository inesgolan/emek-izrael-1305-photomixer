﻿using System.Windows;
using System.IO;
using System.Windows.Media;
using System;

namespace photomixerGUI
{
    // user enters images pathes and this class checks the paths
    public partial class UploadPathes : Window
    {
        private const int SIZE = 5;
        private const int ENDING = 4;
        private const int UPLOAD_PATH_TYPE = 1;

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

            if (count < 1 || count > 5)
            {
                ErrorMsg.Text = "Error: wrong pathes count\n try again";
                countOfPathes.Clear();
            }
            else
            {
                ErrorMsg.Text = "Got it!";
                countOfPathes.IsReadOnly = true;
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
                    ErrorMsg.Text = "Error: wrong image path\n try again.";
                }
                else
                {
                    //checkMatte check = new checkMatte(objectPath.Text);
                    //check.Show();

                    imagesCounter++;
                    string savePath = "objectImage" + imagesCounter.ToString() + ".png";
                    Communicator.sendObjectRecognizeMsg(imagePath, savePath);

                    ErrorMsg.Text = "object detected!";

                    //add the save path to the array
                    imagesPathes[imagesCounter-1] = savePath;

                    string fullSavePath = Path.GetFullPath(savePath);
                    Resize resizeScreen = new Resize(fullSavePath);
                    resizeScreen.Show();
                }
            }
            else
            {
                objectPath.IsReadOnly = true;
                ErrorMsg.Text = "Error: you can't enter more pathes";
            }
        }

        //this function check the background path and open the save screen
        private void edit(object sender, RoutedEventArgs e)
        {
            int count = Int32.Parse(countOfPathes.Text);
            string pathBackground = backgroundPath.Text;

            bool checker = isPathValid(pathBackground);

            if (checker == false || (imagesCounter < count))
            { 
                ErrorMsg.Text = "Error: wrong image path or you need\n to enter more pathes\n try again.";
            }
            else
            {
                //put the background path in the last cell in the array
                imagesPathes[imagesCounter] = pathBackground;
                Save saveImage = new Save(imagesPathes, imagesCounter);
                saveImage.Show();
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
            checkPath checker = new checkPath();
            return checker.isPathValid(path, UPLOAD_PATH_TYPE);
        }
    }
}
