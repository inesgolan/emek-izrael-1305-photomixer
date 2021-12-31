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
            communicator.sendObjectRecognizeMsg("C:\\Users\\משתמש\\emek-izrael-1305-photomixer\\photomixerGUI\\Images\\questionMark.jpg", "C:\\Users\\משתמש\\emek-izrael-1305-photomixer\\photomixerGUI\\Images");
        }
    }
}
