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

            string objectPath = Helper.checkFullPath(ProjectVariables.objectPath);
            objectImage.Source = new BitmapImage(new Uri(objectPath));

            string path = Path.GetFullPath("matte.png");
            matteImage.Source = new BitmapImage(new Uri(path));
        }

        //this function reverse the matte colors
        private void reverseMatte(object sender, RoutedEventArgs e)
        {
            string imagePath = "objectImage" + ProjectVariables.imagesCounter.ToString() + ".png";
            Communicator.sendObjectRecognizeReverseMatteMsg(ProjectVariables.objectPath, imagePath);

            string path = Path.GetFullPath("matte2.png");
            matteImage.Source = new BitmapImage(new Uri(path));
  
            ProjectVariables.objectPath = Path.GetFullPath(imagePath); 
        }

        private void closeWindow(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }
}
