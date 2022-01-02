using System.Windows;

namespace photomixerGUI
{
    // user enters images pathes and this class checks the paths
    public partial class UploadPathes : Window
    {
        private Communicator communicator = new Communicator();
        public UploadPathes()
        {
            InitializeComponent();
            string imagePath = "\"C:/Users/Ines Noa Golan/source/repos/emek-izrael-1305-photomixer/photomixer/images/flower.jpg\"";
            string savePath = "\"C:/Users/Ines Noa Golan/source/repos/emek-izrael-1305-photomixer/photomixer/images/here.png\"";
            communicator.sendObjectRecognizeMsg(imagePath, savePath);
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
