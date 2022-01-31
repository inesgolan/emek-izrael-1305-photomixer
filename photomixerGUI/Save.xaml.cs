using System.Windows;
using System.IO;
using System.Windows.Media;
using System;

namespace photomixerGUI
{
    //this class is in charge of saving the image
    public partial class Save : Window
    {
        private const int SIZE = 5;
        private const int ENDING = 4;
        private Communicator communicator = new Communicator();
        private static int imagesCounter;
        private static string[] imagesPathes;

        public Save(string[] pathes, int count)
        {
            InitializeComponent();

            imagesPathes = new string[SIZE];
            pathes.CopyTo(imagesPathes, 0);
            
            imagesCounter = count;
        }

        //checks the path and if its valid open edit window
        private void checkPath(string path)
        {
            checkPath checker = new checkPath();
            if (!checker.isPathValid(path, 2))
            {
                ErrorMsg.Text = "Error: invalid path, try again.";
                imagePath.Clear();
            }
            else
            {
                Edit edit = new Edit(imagesPathes, imagesCounter, imagePath.Text);
                edit.Show();
                Close();
            }
        }

        private void edit(object sender, RoutedEventArgs e)
        {
            checkPath(imagePath.Text);
        }
    }
}
