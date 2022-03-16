using System;
using System.Windows;
using System.Windows.Media.Imaging;
using System.IO;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Media;

namespace photomixerGUI
{
    public partial class loading : Window
    {
        static bool flag;
        public loading(bool value)
        {
            InitializeComponent();

            flag = value;

            string path = Path.GetFullPath("files\\loading.webp");
            loadingImage.Source = new BitmapImage(new Uri(path));         
        }

        private void encryption()
        {
            type.Content += "encrypt";

            string[] pictures = Directory.GetFiles(ProjectVariables.username, "*.png");

            foreach (string pic in pictures)
            {
                if (!(pic.Split(".")[0].Contains("objectImage")))
                {
                    Communicator.encryptionMsg(pic, ProjectVariables.username);
                }
            }
            pressButton.Visibility = System.Windows.Visibility.Collapsed;
        }

        private void decryption()
        {
            type.Content += "decrypt";

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
            type.Content += " your picture...";
        }

        private void back(object sender, RoutedEventArgs e)
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
