using System;
using System.Windows;
using System.Windows.Media.Imaging;

namespace photomixerGUI
{
    //asks the user if we found the object
    public partial class checkMatte : Window
    {
        private Communicator communicator = new Communicator();
        public checkMatte(string imagePath)
        {
            InitializeComponent();

            objectImage.Source = new BitmapImage(new Uri(imagePath));
            matteImage.Source = new BitmapImage(new Uri("C:/Users/Ines Noa Golan/source/repos/emek-izrael-1305-photomixer/photomixerGUI/bin/Debug/net5.0-windows/matte.png"));
        }

        //this function reverse the matte colors
        private void reverseMatte(object sender, RoutedEventArgs e)
        {
            string imagePath = "\"C:/Users/Ines Noa Golan/source/repos/emek-izrael-1305-photomixer/photomixer/images/bear2.jpg\"";
            string savePath = "\"C:/Users/Ines Noa Golan/source/repos/emek-izrael-1305-photomixer/photomixer/images/here2.png\"";
            communicator.sendObjectRecognizeReverseMatteMsg(imagePath, savePath);
            System.Threading.Thread.Sleep(50); //it takes time to reverse the matte
            matteImage.Source = new BitmapImage(new Uri("C:/Users/Ines Noa Golan/source/repos/emek-izrael-1305-photomixer/photomixerGUI/bin/Debug/net5.0-windows/matte2.png"));
        }

        //opens edit window
        private void edit(object sender, RoutedEventArgs e)
        {
            Close();
            //editImage edit = new editImage();
            //edit.Show();
        }
    }
}
