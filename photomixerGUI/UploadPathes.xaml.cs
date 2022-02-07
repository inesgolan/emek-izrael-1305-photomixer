using System.Windows;
using System.IO;
using System.Windows.Media;
using System;
using System.Linq;

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

        public static string objectPath;
        public static string backgroundPath;

        public UploadPathes()
        {
            InitializeComponent();

            imagesCounter = 0;
            imagesPathes = new string[SIZE];
        }

        //this function detect the object in the given pathes from the user and get the background path 
        private void objectDetection()
        {
           //if the path is valid detect the object in the image
           if (!isPathValid(objectPath))
           {
               ErrorMsg.Text = "Error: wrong file type\n try again.";
           }
           else
           {
                imagesCounter++;
                string savePath = "objectImage" + imagesCounter.ToString() + ".png";
                objectPath = Helper.checkFullPath(objectPath);
                Communicator.sendObjectRecognizeMsg(objectPath, savePath);

                ErrorMsg.Text = "object detected!";

                //add the save path to the array
                imagesPathes[imagesCounter - 1] = savePath;

                string fullSavePath = Path.GetFullPath(savePath);
                Resize resizeScreen = new Resize(fullSavePath);
                resizeScreen.Show();
           }
        }

        //this function check the background path and open the save screen
        private void edit(object sender, RoutedEventArgs e)
        {
            bool checker = isPathValid(backgroundPath);

            if (checker == false)
            {
                ErrorMsg.Text = "Error: wrong image path or you need\n to enter more pathes\n try again.";
            }
            else
            {
                //put the background path in the last cell in the array
                imagesPathes[imagesCounter] = backgroundPath;
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
            return Helper.isPathValid(path, UPLOAD_PATH_TYPE);
        }


        // upload images
        private void uploadImgae_click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog temp = new Microsoft.Win32.OpenFileDialog();
            bool? res = temp.ShowDialog();
            if (res == true)
            {
                objectPath = temp.FileName;
            }
            objectDetection();
        }


        // upload background image
        private void uploadBackground_click(object sender, RoutedEventArgs e)
        {
            ErrorMsg.Text = " ";
            Microsoft.Win32.OpenFileDialog temp = new Microsoft.Win32.OpenFileDialog();
            bool? res = temp.ShowDialog();

            if (res == true)
            {
                backgroundPath = temp.FileName;
            }

            if (isPathValid(backgroundPath) == false)
            {
                ErrorMsg.Text = "Error: wrong image path or you need\n to enter more pathes\n try again.";
            }
            else
            {
                ErrorMsg.Text = "Got the path!";
            }
        }

    }
}
