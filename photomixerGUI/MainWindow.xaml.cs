using System.Windows;

namespace photomixerGUI
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        //this function open the window with the info about the project
        private void getProjectInfo(object sender, RoutedEventArgs e)
        {
            ProjectInfo info = new ProjectInfo();
            info.Show();
            Close();
        }

        //this function open the window where the user uploads the images pathes
        private void getPathes(object sender, RoutedEventArgs e)
        {
            UploadPathes pathes = new UploadPathes();
            pathes.Show();
            Close();
        }

        //This function closes the window
        private void exit(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}
