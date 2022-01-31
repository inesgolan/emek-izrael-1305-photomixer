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
        private int flag;

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
            if (flag == 0)
            {
                Communicator.resizeObjectBigMsg(objectPath);
            }
        }

        // make the picture size smaller
        private void smallerButton_Click(object sender, RoutedEventArgs e)
        {
            if (flag == 0)
            {
                Communicator.resizeObjectSmallMsg(objectPath);
            }
        }

        // back to upload pathes screen
        private void backButton_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        // show the result of the size change
        private void resultButton_Click(object sender, RoutedEventArgs e)
        {
            ObjectImage.Source = new BitmapImage(new Uri(objectPath));
            string message = "Press on Back button.";
            string caption = "U can't resize the picture anymore!";
            MessageBoxButton buttons = MessageBoxButton.OK;

            // Displays the MessageBox.
            MessageBoxResult result = MessageBox.Show(message, caption, buttons);
            flag = 1;
        }
    }
}
