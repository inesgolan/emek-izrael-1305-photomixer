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
        static bool flagg;
        public loading(bool flag)
        {
            InitializeComponent();

            string path = Path.GetFullPath("loading.webp");
            loadingImage.Source = new BitmapImage(new Uri(path));         
            flagg = flag;
        }

        private void encryption()
        {
            type.Content = "encrypt";
 
            string[] splitPath = ProjectVariables.imagesPathes[ProjectVariables.imagesCounter].Split("\\");
            string path = splitPath[splitPath.Length - 2] + "\\" + splitPath[splitPath.Length - 1];
            Communicator.encryptionMsg(path, ProjectVariables.username);

            Menu gotoMenu = new Menu();
            gotoMenu.Show();
            Close();
        }

        private void decryption()
        {
            type.Content = "decrypt";

            string[] images = Directory.GetFiles(ProjectVariables.username);
            foreach (string image in images)
            {
                string[] splitPath = image.Split("\\");
                string path = splitPath[splitPath.Length - 2] + "\\" + splitPath[splitPath.Length - 1];
                Communicator.decryptionMsg(path, ProjectVariables.username);
            }

            Menu gotoMenu = new Menu();
            gotoMenu.Show();
            Close();
        }

        private void callFunctions(object sender, RoutedEventArgs e)
        {
            if (flagg)
            {
                encryption();
            }
            else
            {
                decryption();
            }
            type.Content += " your picture...";
        }
    }
}
