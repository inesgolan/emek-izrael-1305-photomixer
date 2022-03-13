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
        static bool values;
        public loading(bool flag)
        {
            InitializeComponent();

            values = flag;

            string path = Path.GetFullPath("files\\loading.webp");
            loadingImage.Source = new BitmapImage(new Uri(path));         
        }

        private void encryption()
        {
            type.Content += "encrypt";

            string path = Helper.getImagePath(ProjectVariables.imagesPathes[ProjectVariables.imagesCounter]);
            Communicator.encryptionMsg(path, ProjectVariables.username);

            endScreen end = new endScreen();
            end.Show();
            Close();
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

            Menu gotoMenu = new Menu();
            gotoMenu.Show();
            Close();
        }

        private void callFunctions(object sender, RoutedEventArgs e)
        {
            if (values)
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
