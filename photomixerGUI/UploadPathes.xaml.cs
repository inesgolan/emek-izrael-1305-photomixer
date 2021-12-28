using System.Windows;

namespace photomixerGUI
{
    // user enters images pathes and this class checks the paths
    public partial class UploadPathes : Window
    {
        private Communicator communicator;
        public UploadPathes()
        {
            InitializeComponent();
            communicator.sendObjectRecognizeMsg("Images", "Images\\questionMark.jpg");
        }
    }
}
