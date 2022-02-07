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

        //checks the path and if its valid open edit window
        private void checkPath(string path)
        {
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

        private void edit(object sender, RoutedEventArgs e)
        {
            checkPath(imagePath.Text);
        }
    }
}
