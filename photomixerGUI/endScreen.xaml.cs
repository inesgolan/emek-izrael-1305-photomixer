using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace photomixerGUI
{

    public partial class endScreen : Window
    {
        public endScreen()
        {
            InitializeComponent();

            //display background image
            ProjectVariables.backgroundPath = ProjectVariables.imagesPathes[ProjectVariables.imagesCounter];
            BackgroundImage.Source = new BitmapImage(new Uri(ProjectVariables.backgroundPath));
        }

        private void sendMail(object sender, RoutedEventArgs e)
        {
            string[] splitPath = ProjectVariables.backgroundPath.Split("\\");
            string path = splitPath[splitPath.Length-2] + "\\" +splitPath[splitPath.Length - 1];
            Communicator.sendImageMail(path, ProjectVariables.username);
        }

        private void goBack(object sender, RoutedEventArgs e)
        {
            loading loadScreen = new loading(true);
            loadScreen.Show();
            Close();

        }
    }
}
