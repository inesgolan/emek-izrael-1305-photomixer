using System.Windows;

namespace photomixerGUI
{
    // user enters images pathes and this class checks the paths
    public partial class UploadPathes : Window
    {
        public UploadPathes()
        {
            InitializeComponent();
        }

        private void objectDetection(object sender, RoutedEventArgs e)
        {
            Close();
            //send pathes to the server
            checkMatte check = new checkMatte();
            check.Show();
        }
    }
}
