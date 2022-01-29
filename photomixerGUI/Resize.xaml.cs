using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Threading;
namespace photomixerGUI
{
    public partial class Resize
    {
        private Communicator communicator = new Communicator();
        private static string objectPath;

        public Resize()
        {
            InitializeComponent();
        }

        // do a git pull origin develop in develop and in this brunch!!!!!
        public Resize(string ObjectImagePath)
        {
            InitializeComponent();

            // show the object image
            objectPath = Path.GetFullPath(ObjectImagePath);
            //ObjectImage.Source = new BitmapImage(new Uri(objectPath));

            // change here the size of the picture from the xaml according to my object picture ???
        }

        private void biggerButton_Click(object sender, RoutedEventArgs e)
        {
           // Thread.Sleep(5000);
           communicator.resizeObjectBigMsg(objectPath);
            //Thread.Sleep(5000);
            //ObjectImage.Source = new BitmapImage(new Uri(objectPath));
        }

        private void smallerButton_Click(object sender, RoutedEventArgs e)
        {
            communicator.resizeObjectSmallMsg(objectPath);
            //ObjectImage.Source = new BitmapImage(new Uri(objectPath));
        }

        private void backButton_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }
}
