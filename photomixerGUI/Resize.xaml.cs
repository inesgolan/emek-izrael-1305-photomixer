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
        private static string objectPath;

        // c'tors
        public Resize()
        {
            InitializeComponent();
        }

        public Resize(string ObjectImagePath)
        {
            InitializeComponent();

            objectPath = Path.GetFullPath(ObjectImagePath);
        }

        // make the picture size larger
        private void biggerButton_Click(object sender, RoutedEventArgs e)
        {
            Communicator.resizeObjectBigMsg(objectPath);  
        }

        // make the picture size smaller
        private void smallerButton_Click(object sender, RoutedEventArgs e)
        {
            Communicator.resizeObjectSmallMsg(objectPath);
        }

        // back to upload pathes screen
        private void backButton_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        // show the result of the size change
        private void resultButton_Click(object sender, RoutedEventArgs e)
        {
            showPicture g = new showPicture(objectPath);
            g.Show();
        }
    }
}
