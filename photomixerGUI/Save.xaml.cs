using System.Windows;
using System.IO;
using System.Windows.Media;
using System;

namespace photomixerGUI
{
    //this class is in charge of saving the image
    public partial class Save : Window
    {
        public Save()
        {
            InitializeComponent();
        }
        private void edit(object sender, RoutedEventArgs e)
        {
            string path = imagePath.Text;

            if (!Helper.isPathValid(path, ProjectVariables.SAVE_TYPE))
            {
                ErrorMsg.Text = "Error: invalid path, try again.";
                imagePath.Clear();
            }
            else
            {
                ProjectVariables.savePath = path;

                Edit edit = new Edit();
                edit.Show();
                Close();
            }          
        }
    }
}
