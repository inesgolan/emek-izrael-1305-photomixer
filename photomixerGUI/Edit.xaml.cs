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
        private static string savePath;

        public Edit(string[] pathes, int count, string save)
        {
            InitializeComponent();

            //get the pathes array
            imagesPathes = new string[SIZE];
            pathes.CopyTo(imagesPathes, 0);
            
            imagesCounter = count;
            savePath = save;

            displayImages();
        }

        //this function display the object images and the background image
        private void displayImages()
        {
            //display background image
            background =imagesPathes[imagesCounter];
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

        private void dropObject(object sender, DragEventArgs e)
        {
            string save = "";
            countOfEdits++;

            Point location = e.GetPosition(this); //get image location relative to the screen

            if (countOfEdits == imagesCounter)
            {
                save = savePath;
            }
            else
            {
                save = "edit" + countOfEdits.ToString() + ".png";
            }

            imagesPathes[imagesCounter] = Helper.checkFullPath(imagesPathes[imagesCounter]);
            Communicator.sendPasteObjectMsg(imagesPathes[countOfEdits - 1], imagesPathes[imagesCounter], save, (int)location.X, (int)location.Y);

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

        //delete the images we don't need anymore and go back to main screen
        private void deleteImages(object sender, RoutedEventArgs e)
        {
            if (Images.Items.Count > 0)
            {
                // Initializes the variables to pass to the MessageBox.Show method.
                string message = "Are you sure?";
                string caption = "Error Detected in Input";
                MessageBoxButton buttons = MessageBoxButton.YesNo;

                // Displays the MessageBox.
                MessageBoxResult result = MessageBox.Show(message, caption, buttons);
                if (result == MessageBoxResult.Yes)
                {
                    Close();
                }
            }
            else
            {
                Close();
            }

        }
    }
}
