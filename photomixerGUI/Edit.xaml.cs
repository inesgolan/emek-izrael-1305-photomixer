using System;
using System.Windows;
using System.Windows.Media.Imaging;
using System.IO;

namespace photomixerGUI
{
    //this class is in charge of the editing of the image
    public partial class Edit : Window
    {
        private const int SIZE = 11;

        private Communicator communicator = new Communicator();
        private static string[] imagesPathes;
        private static int imagesCounter;

        public Edit(string[] pathes, int count)
        {
            InitializeComponent();

            //get the pathes array
            imagesPathes = new string[SIZE];
            pathes.CopyTo(imagesPathes, 0);

            imagesCounter = count;

            displayImages();
        }

        //this function display the object images and the background image
        private void displayImages()
        {
            //display background image
            string backgroundPath = Path.GetFullPath(imagesPathes[imagesCounter]);
            BackgroundImage.Source = new BitmapImage(new Uri(backgroundPath));

            string path = "";

            //display object images and number them
            for (int i = 0; i < imagesCounter; i++)
            {
                path = Path.GetFullPath(imagesPathes[i]);
                Images.Items.Add(new BitmapImage(new Uri(path)));
                Numbers.Items.Add((i+1).ToString());
            }
        }

        private void save(object sender, RoutedEventArgs e)
        {

        }

        private void resize(object sender, RoutedEventArgs e)
        {

        }
    }
}
