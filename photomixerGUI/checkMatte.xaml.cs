using System;
using System.Windows;
using System.Windows.Media.Imaging;
using System.IO;

namespace photomixerGUI
{
    //asks the user if we found the object
    public partial class checkMatte : Window
    {
        public checkMatte()
        {
            InitializeComponent();

            string objectPath = "";

            if (ProjectVariables.objectPath.Contains(" "))
            {
                objectPath = (ProjectVariables.objectPath).Substring(1, ProjectVariables.objectPath.Length - 2);
            }
            else
            {
                objectPath = ProjectVariables.objectPath;
            }

            objectImage.Source = new BitmapImage(new Uri(objectPath));

            string path = Path.GetFullPath("matte.png");
            matteImage.Source = new BitmapImage(new Uri(path));
        }

        //this function reverse the matte colors
        private void reverseMatte(object sender, RoutedEventArgs e)
        {
            File.Delete("matte.png");
            string imagePath = "objectImage" + ProjectVariables.imagesCounter.ToString() + ".png";
            File.Delete(imagePath);
            Communicator.sendObjectRecognizeReverseMatteMsg(ProjectVariables.objectPath, ProjectVariables.imagesPathes[ProjectVariables.imagesCounter]);

            string path = Path.GetFullPath("matte.png");
            matteImage.Source = new BitmapImage(new Uri(path));
  
            ProjectVariables.objectPath = Path.GetFullPath(imagePath); //problem with the image of the object after we reverse the matte
        }

        private void closeWindow(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }
}
