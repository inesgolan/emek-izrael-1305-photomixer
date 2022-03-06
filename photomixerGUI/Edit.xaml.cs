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
            DataObject data = new DataObject(typeof(ImageSource), image.Source);
            DragDrop.DoDragDrop(image, data, DragDropEffects.All);

            //get the image index in the list and remove the item from the list
            for (int i = 0; i < ProjectVariables.imagesCounter; i++)
            {
                BitmapImage item = (BitmapImage)Images.Items[i];
                if (image.Source == item)
                {
                    Images.Items.Remove(item);
                    i = ProjectVariables.imagesCounter;
                }
            }
        }

        private void dropObject(object sender, DragEventArgs e)
        {
            string save;
            ProjectVariables.countOfEdits++;
            ProjectVariables.countOfClicks = ProjectVariables.countOfEdits;

            Point location = e.GetPosition(this); //get image location relative to the screen

            //save the edited images in a folder
            if (ProjectVariables.username == "guest")
            {
                if (ProjectVariables.countOfEdits == ProjectVariables.imagesCounter)
                {
                    save = ProjectVariables.savePath;
                }
                else
                {
                    save = "edit" + ProjectVariables.countOfEdits.ToString() + ".png";
                }
            }
            else
            {
 
                if (ProjectVariables.countOfEdits == ProjectVariables.imagesCounter)
                {
                    save = ProjectVariables.username + "/" + ProjectVariables.savePath;
                }
                else
                {
                    save = ProjectVariables.username + "/edit" + ProjectVariables.countOfEdits.ToString() + ".png";
                }
            }

            ProjectVariables.imagesPathes[ProjectVariables.imagesCounter] = Helper.checkFullPath(ProjectVariables.imagesPathes[ProjectVariables.imagesCounter]);
            Communicator.sendPasteObjectMsg(ProjectVariables.imagesPathes[ProjectVariables.countOfEdits - 1], ProjectVariables.imagesPathes[ProjectVariables.imagesCounter], save, (int)location.X, (int)location.Y);

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
            ProjectVariables.imagesPathes[ProjectVariables.imagesCounter] = Path.GetFullPath(save);
            BackgroundImage.Source = new BitmapImage(new Uri(ProjectVariables.imagesPathes[ProjectVariables.imagesCounter]));
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
                    File.Delete(ProjectVariables.OUTPUT_FILE_NAME);
                }
            }
            else
            {
                Close();
                File.Delete(ProjectVariables.OUTPUT_FILE_NAME);
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
                if (ProjectVariables.username == "guest")
                {
                    lastEdit = "edit" + (ProjectVariables.countOfClicks - 1).ToString() + ".png";                  
                }
                else
                {
                    lastEdit = ProjectVariables.username + "/edit" + (ProjectVariables.countOfClicks - 1).ToString() + ".png";
                }        
            }

            //update the image showen on the screen
            if (ProjectVariables.countOfClicks > 0)
            {
                ProjectVariables.imagesPathes[ProjectVariables.imagesCounter] = Path.GetFullPath(lastEdit);
                BackgroundImage.Source = new BitmapImage(new Uri(ProjectVariables.imagesPathes[ProjectVariables.imagesCounter]));

                ProjectVariables.countOfClicks--;
            }
            //if we move the second image it moves the first one
        }

        //go to the next edited image
        private void goToNextEdit(object sender, RoutedEventArgs e)
        {
            string lastEdit = "";

            ProjectVariables.countOfClicks++;

            if (ProjectVariables.countOfClicks == ProjectVariables.imagesCounter)
            {
                if (ProjectVariables.username == "guest")
                {
                    lastEdit = ProjectVariables.savePath;
                }
                else
                {
                    lastEdit = ProjectVariables.username + "/" + ProjectVariables.savePath;
                }
            }
            else
            {
                if (ProjectVariables.username == "guest")
                {
                    lastEdit = "edit" + ProjectVariables.countOfClicks.ToString() + ".png";
                }
                else
                {
                    lastEdit = ProjectVariables.username + "/edit" + ProjectVariables.countOfClicks.ToString() + ".png";
                }
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
