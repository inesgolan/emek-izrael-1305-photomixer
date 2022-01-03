using System.Windows;

namespace photomixerGUI
{
    // user enters images pathes and this class checks the paths
    public partial class UploadPathes : Window
    {
        private Communicator communicator = new Communicator();
        public string imagePath { get; set; }
        public string savePath { get; set; }

        public UploadPathes()
        {
            InitializeComponent();
            imagePath = "\"C:/Users/Ines Noa Golan/source/repos/emek-izrael-1305-photomixer/photomixer/images/bear2.jpg\"";
            savePath = "\"C:/Users/Ines Noa Golan/source/repos/emek-izrael-1305-photomixer/photomixer/images/here.png\"";
            communicator.sendObjectRecognizeMsg(imagePath, savePath);
        }

        private void objectDetection(object sender, RoutedEventArgs e)
        {
            checkMatte check = new checkMatte("C:/Users/Ines Noa Golan/source/repos/emek-izrael-1305-photomixer/photomixer/images/bear2.jpg");
            check.Show();
            Close();
        }
    }
}
