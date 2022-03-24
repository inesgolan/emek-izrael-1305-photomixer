using System;
using System.Windows;
using System.Windows.Media.Imaging;
using System.IO;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Media;
using System.Threading;

namespace photomixerGUI
{
    public partial class loading : Window
    {
        static bool flag;
        public loading(bool value)
        {
            InitializeComponent();

            flag = value;
            if (flag)
            {
                type.Content += "ENCRYPT YOUR PICTURE";
            }
            else
            {
                type.Content += "DECRYPT YOUR PICTURE";
            }

            string path = Path.GetFullPath("files\\loading.gif");
            loadingGif.Source = new System.Uri(path);
            loadingGif.LoadedBehavior = MediaState.Manual;
            loadingGif.Play();
        }

        private void encryption()
        {
            string[] pictures = Directory.GetFiles(ProjectVariables.username, "*.png");
            if (File.Exists(ProjectVariables.OUTPUT_FILE_NAME))
            {
                File.Delete("ProjectVariables.OUTPUT_FILE_NAME");
            }
            foreach (string pic in pictures)
            {
                if (!(pic.Split(".")[0].Contains("objectImage")))
                {
                    Communicator.encryptionMsg(pic, ProjectVariables.username);
                }
            }
            pressButton.Visibility = System.Windows.Visibility.Collapsed;
        }

        private void decryption() //only if encrypt
        {
            string[] images = Directory.GetFiles(ProjectVariables.username);

            foreach (string image in images)
            {
                string path = Helper.getImagePath(image);
                Communicator.decryptionMsg(path, ProjectVariables.username);
            }
            pressButton.Visibility = System.Windows.Visibility.Collapsed;
        }

        private void callFunctions(object sender, RoutedEventArgs e)
        {
            if (flag)
            {
                encryption();
            }
            else
            {
                decryption();
            }
        }

        private void exit(object sender, RoutedEventArgs e)
        {
            if (flag) //encryption
            {
                MainWindow gotoMain = new MainWindow();
                gotoMain.Show();
                Close();
            }
            else //decryption
            {
                Menu gotoMenu = new Menu();
                gotoMenu.Show();
                Close();
            }
        }
    }
}
