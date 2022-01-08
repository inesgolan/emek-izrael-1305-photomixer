using System.Windows;
using System.IO;
using System.Windows.Media;

namespace photomixerGUI
{
    // user enters images pathes and this class checks the paths
    public partial class UploadPathes : Window
    {
        private const int ENDING = 4;
        private Communicator communicator = new Communicator();

        public UploadPathes()
        {
            InitializeComponent();
            this.communicator = communicator;
        }


        private void objectDetection(object sender, RoutedEventArgs e)
        {
            if (!isPathValid(objectPath.Text) || !isPathValid(backgroundPath.Text))
            {
                ErrorMsg.Text = "Error - wrong path - try again.";
                ErrorMsg.Width = 60;
                ErrorMsg.Height = 60;
                ErrorMsg.Foreground = Brushes.DarkRed;
                ErrorMsg.HorizontalAlignment = HorizontalAlignment.Left;
                ErrorMsg.TextWrapping = TextWrapping.Wrap;
            }
            else
            {
                communicator.sendObjectRecognizeMsg(objectPath.Text, backgroundPath.Text);

                checkMatte check = new checkMatte(objectPath.Text);
                check.Show();
                Close();
            }
        }

        /*
        This function will check if the path is valid
        input:string path
        output: bool
        */
        private bool isPathValid(string path)
        {
            string ending = "";
            string localPath = path;

            if (path.Length > ENDING) 
            {
                //C:\Users\משתמש\emek-izrael-1305-photomixer\photomixer\images/bear2.jpg
                //C:\Users\משתמש\emek-izrael-1305-photomixer\photomixer\images/background.jpg

                int startIndex = path.Length - ENDING;
                int finishIndex = path.Length - 1;
                int localPathlen = localPath.Length;

                ending = path.Substring(startIndex, finishIndex - startIndex + 1);

            }
            else
            {
                return false;
            }


            bool fileExist = File.Exists(path);
            if (fileExist && (".jpg" == ending || ".png" == ending)) //can open the file and it's a picture
            {
                return true;
            }

            return false;
        }
    }
}
