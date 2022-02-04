using System.Windows;

namespace photomixerGUI
{
    public partial class Menu : Window
    {
        public Menu(string username)
        {
            InitializeComponent();
            userName.Content = username;
        }

        //This function open the window with the info about the project
        private void questionMark(object sender, RoutedEventArgs e)
        {
            ProjectInfo info = new ProjectInfo();
            info.Show();
            Close();
        }

        //This function open the window where the user uploads the images pathes
        private void getPathes(object sender, RoutedEventArgs e)
        {
            UploadPathes pathes = new UploadPathes();
            pathes.Show();
            Close();
        }

        //This function closes the window
        private void exit(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }
}
