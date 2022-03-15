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
        public Edit()
        {
            InitializeComponent();

            displayImages();
        }

        //this function display the object images and the background image
        private void displayImages()
        {
            //display background image
            ProjectVariables.backgroundPath = ProjectVariables.imagesPathes[ProjectVariables.imagesCounter];
            BackgroundImage.Source = new BitmapImage(new Uri(ProjectVariables.backgroundPath));

            //display object images and number them
            for (int i = 0; i < ProjectVariables.imagesCounter; i++)
            {
                string path = Path.GetFullPath(ProjectVariables.imagesPathes[i]);
                Images.Items.Add(new BitmapImage(new Uri(path)));
            }
        }

        //drag the object image to the background
        private void dragObject(object sender, MouseEventArgs e)
        {
            Image image = e.Source as Image;

            //get the image index in the list
            for (int i = 0; i < ProjectVariables.imagesCounter; i++)
            {
                BitmapImage item = (BitmapImage)Images.Items[i];
                if (image.Source == item)
                {
                    ProjectVariables.index = i;
                    i = ProjectVariables.imagesCounter;
                }
            }

            DataObject data = new DataObject(typeof(ImageSource), image.Source);
            DragDrop.DoDragDrop(image, data, DragDropEffects.All);
        }

        private void dropObject(object sender, DragEventArgs e)
        {
            string save;
            ProjectVariables.countOfEdits++;
            ProjectVariables.countOfClicks = ProjectVariables.countOfEdits;

            Point location = e.GetPosition(this); //get image location relative to the screen

            //save the edited images in a folder
            if (ProjectVariables.countOfEdits == ProjectVariables.imagesCounter)
            {
                save = ProjectVariables.username + "/" + ProjectVariables.savePath;
            }
            else
            {
                save = ProjectVariables.username + "/edit" + ProjectVariables.countOfEdits.ToString() + ".png";
            }

            ProjectVariables.imagesPathes[ProjectVariables.imagesCounter] = Helper.checkFullPath(ProjectVariables.imagesPathes[ProjectVariables.imagesCounter]);
            Communicator.sendPasteObjectMsg(ProjectVariables.imagesPathes[ProjectVariables.index], ProjectVariables.imagesPathes[ProjectVariables.imagesCounter], save, (int)location.X, (int)location.Y);

            ProjectVariables.imagesPathes[ProjectVariables.imagesCounter] = Path.GetFullPath(save);
            BackgroundImage.Source = new BitmapImage(new Uri(ProjectVariables.imagesPathes[ProjectVariables.imagesCounter]));
        }

        //delete the images we don't need anymore and go back to main screen
        private void done(object sender, RoutedEventArgs e)
        {
           string message = "Are you sure?";
           string caption = "Error Detected in Input";
           MessageBoxButton buttons = MessageBoxButton.YesNo;

           // Displays the MessageBox.
           MessageBoxResult result = MessageBox.Show(message, caption, buttons);
           if (result == MessageBoxResult.Yes)
           {

                BackgroundImage.Source = null;

                if (ProjectVariables.username != "guest")
                {
                    endScreen end = new endScreen();
                    end.Show();
                    Close();
                }
                else
                {
                    Menu gotoMenu = new Menu();
                    gotoMenu.Show();
                    Close();
                }
            }

        }

        //change the background to the last edited image
        private void returnToLastEdit(object sender, RoutedEventArgs e)
        {
            string lastEdit = "";

            if (ProjectVariables.countOfClicks == 1)
            {
                lastEdit = ProjectVariables.backgroundPath;
            }
            else if (ProjectVariables.countOfClicks > 1)
            {
                lastEdit = ProjectVariables.username + "/edit" + (ProjectVariables.countOfClicks - 1).ToString() + ".png";   
            }

            //update the image showen on the screen
            if (ProjectVariables.countOfClicks > 0)
            {
                ProjectVariables.imagesPathes[ProjectVariables.imagesCounter] = Path.GetFullPath(lastEdit);
                BackgroundImage.Source = new BitmapImage(new Uri(ProjectVariables.imagesPathes[ProjectVariables.imagesCounter]));

                ProjectVariables.countOfClicks--;
            }
        }

        //go to the next edited image
        private void goToNextEdit(object sender, RoutedEventArgs e)
        {
            string lastEdit = "";

            ProjectVariables.countOfClicks++;

            if (ProjectVariables.countOfClicks == ProjectVariables.imagesCounter)
            {
                lastEdit = ProjectVariables.username + "/" + ProjectVariables.savePath;
            }
            else
            {
                lastEdit = ProjectVariables.username + "/edit" + ProjectVariables.countOfClicks.ToString() + ".png";
            }

            //update the image showen on the screen
            if (File.Exists(lastEdit))
            {
                ProjectVariables.imagesPathes[ProjectVariables.imagesCounter] = Path.GetFullPath(lastEdit);
                BackgroundImage.Source = new BitmapImage(new Uri(ProjectVariables.imagesPathes[ProjectVariables.imagesCounter]));
            }
        }
    }
}
