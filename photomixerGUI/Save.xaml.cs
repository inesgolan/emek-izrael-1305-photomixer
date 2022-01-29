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
            string ending = "";

            if (path.Length > ENDING)
            {

                int startIndex = path.Length - ENDING;
                int finishIndex = path.Length - 1;

                ending = path.Substring(startIndex, finishIndex - startIndex + 1);

            }
            else
            {
                ErrorMsg.Text = "Error: path too short, try again.";
                imagePath.Clear();
            }

            bool fileExist = File.Exists(path);
            if (fileExist || (".png" != ending)) //can't open the file and it's a picture type png
            {
                ErrorMsg.Text = "Error: path exist or image type isn't png, try again.";
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
