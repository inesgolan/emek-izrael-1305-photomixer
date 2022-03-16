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
        public UploadPathes()
        {
            InitializeComponent();
        }

        //this function detect the object in the given pathes from the user and get the background path 
        private void objectDetection()
        {
           //if the path is valid detect the object in the image
           if (!isPathValid(ProjectVariables.objectPath))
           {
               ErrorMsg.Text = "Error: wrong file type\n try again.";
           }
           else
           {
                ProjectVariables.imagesCounter++;
                string savePath = ProjectVariables.username + "\\objectImage" + ProjectVariables.imagesCounter.ToString() + ".png";
                Communicator.sendObjectRecognizeMsg(Helper.checkFullPath(ProjectVariables.objectPath), savePath);

                string text;
                File.OpenRead(ProjectVariables.OUTPUT_FILE_NAME);
                text = File.ReadAllText(ProjectVariables.OUTPUT_FILE_NAME);

                if (text == "False")
                {
                    ProjectVariables.imagesCounter--;

                    ErrorMsg.Text = "Try another picture pls :(";
                }
                else
                {
                    ErrorMsg.Text = "object detected!";

                    //add the save path to the array
                    ProjectVariables.imagesPathes[ProjectVariables.imagesCounter - 1] = savePath;

                    string fullSavePath = Path.GetFullPath(savePath);
                    Resize resizeScreen = new Resize(fullSavePath);
                    resizeScreen.Show();
                }
           }
        }

        //this function check the background path and open the save screen
        private void edit(object sender, RoutedEventArgs e)
        {
            bool checker = isPathValid(ProjectVariables.backgroundPath);

            if (checker == false)
            {
                ErrorMsg.Text = "Error: wrong image path or you need\n to enter more pathes\n try again.";
            }
            else
            {
                //put the background path in the last cell in the array
                ProjectVariables.imagesPathes[ProjectVariables.imagesCounter] = ProjectVariables.backgroundPath;
                Save saveImage = new Save();
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
            return Helper.isPathValid(path, ProjectVariables.UPLOAD_PATH_TYPE);
        }


        // upload images
        private void uploadImgae_click(object sender, RoutedEventArgs e)
        {
            if (ProjectVariables.imagesCounter == 4)
            {
                ErrorMsg.Text = "U can't add more than 4 pictures :(";
                return;
            }
            Microsoft.Win32.OpenFileDialog temp = new Microsoft.Win32.OpenFileDialog();
            bool? res = temp.ShowDialog();
            if (res == true)
            {
                ProjectVariables.objectPath = temp.FileName;
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
                ProjectVariables.backgroundPath = temp.FileName;
            }

            if (isPathValid(ProjectVariables.backgroundPath) == false)
            {
                ErrorMsg.Text = "Error: wrong image path or you need\n to enter more pathes\n try again.";
            }
            else
            {
                ErrorMsg.Text = "Got the path!";
            }
        }

        //ask the user if we detected the object
        private void checkObjectDetction(object sender, RoutedEventArgs e)
        {
            checkMatte check = new checkMatte();
            check.Show();
        }
    }
}
