using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;

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

        public Resize(string ObjectImagePath)
        {
            InitializeComponent();

            // show the object image
            objectPath = Path.GetFullPath(ObjectImagePath);
            ObjectImage.Source = new BitmapImage(new Uri(objectPath));
        }


        private void biggerButton_Click(object sender, RoutedEventArgs e)
        {
            communicator.resizeObjectBigMsg(objectPath);
            ObjectImage.Source = new BitmapImage(new Uri(objectPath));
        }

        private void smallerButton_Click(object sender, RoutedEventArgs e)
        {
            communicator.resizeObjectSmallMsg(objectPath);
            ObjectImage.Source = new BitmapImage(new Uri(objectPath));
        }
    }
}
