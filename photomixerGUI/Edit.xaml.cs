using System;
using System.Windows;
using System.Windows.Media.Imaging;
using System.IO;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Media;

namespace photomixerGUI
{
    //this class is in charge of the editing of the image
    public partial class Edit : Window
    {
        private const int SIZE = 11;

        private Communicator communicator = new Communicator();
        private static string[] imagesPathes;
        private static int imagesCounter;
        private static string background;

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
            background = Path.GetFullPath(imagesPathes[imagesCounter]);
            BackgroundImage.Source = new BitmapImage(new Uri(background));

            string path = "";

            //display object images and number them
            for (int i = 0; i < imagesCounter; i++)
            {
                path = Path.GetFullPath(imagesPathes[i]);
                Images.Items.Add(new BitmapImage(new Uri(path)));
                Numbers.Items.Add((i + 1).ToString());
            }
        }

        //drag the object image to the background
        private void dragObject(object sender, MouseButtonEventArgs e)
        {
            Image image = e.Source as Image;
            DataObject data = new DataObject(typeof(ImageSource), image.Source);
            DragDrop.DoDragDrop(image, data, DragDropEffects.All);

            
            Point location = e.GetPosition(this);

            int index = 0;
            //get the image index in the list
            for (int i = 0; i < imagesCounter; i++)
            {
                BitmapImage item = (BitmapImage)Images.Items[i];
                if (image.Source == item)
                {
                    index = i;
                    i = imagesCounter;
                }
            }

            //problem with location
            communicator.sendPasteObjectMsg(imagesPathes[index], imagesPathes[imagesCounter], "edit.png", (int)location.X, (int)location.Y);
            BackgroundImage.Source = new BitmapImage(new Uri(background)); // how to know that the image is ready?
        }

        //put the object image on the background
        private void backgroundDrop(object sender, DragEventArgs e)
        {

        }

        private void save(object sender, RoutedEventArgs e)
        {

        }

        private void resize(object sender, RoutedEventArgs e)
        {

        }
    }
}
