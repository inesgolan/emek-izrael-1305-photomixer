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

            objectImage.Source = new BitmapImage(new Uri(ProjectVariables.objectPath));
           // System.Threading.Thread.Sleep(50 * 2);
            string path = Path.GetFullPath("matte.png");
            matteImage.Source = new BitmapImage(new Uri(path));
        }

        //this function reverse the matte colors
        private void reverseMatte(object sender, RoutedEventArgs e)
        {
            Communicator.sendObjectRecognizeReverseMatteMsg(ProjectVariables.objectPath, ProjectVariables.imagesPathes[ProjectVariables.imagesCounter]);
            //System.Threading.Thread.Sleep(50*2); //it takes time to reverse the matte
            string path = Path.GetFullPath("matte2.png");
            matteImage.Source = new BitmapImage(new Uri(path));
        }

        //opens edit window
        private void edit(object sender, RoutedEventArgs e)
        {
            Edit edit = new Edit();
            edit.Show();
            Close();
        }
    }
}
