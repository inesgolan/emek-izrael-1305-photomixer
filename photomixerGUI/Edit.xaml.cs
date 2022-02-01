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
        private const int SIZE = 6;

        private Communicator communicator = new Communicator();
        private static string[] imagesPathes;
        private static int imagesCounter;
        private static string background;
        private static int countOfEdits;
        private static int height;
        private static int width;

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

            //display object images and number them
            for (int i = 0; i < imagesCounter; i++)
            {
                string path = Path.GetFullPath(imagesPathes[i]);
                Images.Items.Add(new BitmapImage(new Uri(path)));
            }
        }

        //drag the object image to the background
        private void dragObject(object sender, MouseEventArgs e)
        {
            Image image = e.Source as Image;
            DataObject data = new DataObject(typeof(ImageSource), image.Source);
            DragDrop.DoDragDrop(image, data, DragDropEffects.All);

            //get the image index in the list and remove the item from the list
            for (int i = 0; i < imagesCounter; i++)
            {
                BitmapImage item = (BitmapImage)Images.Items[i];
                if (image.Source == item)
                {
                    Images.Items.Remove(item);
                    i = imagesCounter;
                }
            }
        }

        private void save(object sender, RoutedEventArgs e)
        {

        }

        private void resize(object sender, RoutedEventArgs e)
        {

        }

        private void getLocation(object sender, DragEventArgs e)
        {
            Image image = e.Source as Image;
            height = (int)image.Source.Height;
            width = (int)image.Source.Width;

            //location not right
            MouseLocation.Text = Mouse.GetPosition(BackgroundImage).ToString();
            Point location = Mouse.GetPosition(BackgroundImage);

            int x = (int)(location.X);
            int y = (int)(location.Y);

            countOfEdits++;
            string save = "edit" + countOfEdits.ToString() + ".png";
            communicator.sendPasteObjectMsg(imagesPathes[countOfEdits - 1], imagesPathes[imagesCounter], save, x, y);

            //wait till the image is created to update the background image
            bool flag = false;
            while (!flag)
            {
                bool fileExist = File.Exists(save);
                if (fileExist)
                {
                    try
                    {
                        if (File.OpenRead(save).CanRead)
                        {
                            flag = true;
                        }
                    }
                    catch (IOException)
                    {

                    }
                }
            }

            imagesPathes[imagesCounter] = save;
            background = Path.GetFullPath(save);
            BackgroundImage.Source = new BitmapImage(new Uri(background));
        }
    }
}
