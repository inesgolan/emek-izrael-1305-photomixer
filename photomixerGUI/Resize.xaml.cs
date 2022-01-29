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
        private int flag;

        public Resize()
        {
            InitializeComponent();
        }

        // do a git pull origin develop in develop and in this brunch!!!!!
        public Resize(string ObjectImagePath)
        {
            InitializeComponent();

            objectPath = Path.GetFullPath(ObjectImagePath);
            //ObjectImage.Source = new BitmapImage();
        }

        private void biggerButton_Click(object sender, RoutedEventArgs e)
        {
            if (flag == 0)
            {
                communicator.resizeObjectBigMsg(objectPath);
            }
        }

        private void smallerButton_Click(object sender, RoutedEventArgs e)
        {
            if (flag == 0)
            {
                communicator.resizeObjectSmallMsg(objectPath);
            }
        }

        private void backButton_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

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
