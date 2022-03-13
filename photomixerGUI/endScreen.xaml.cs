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
        }

        private void sendMail(object sender, RoutedEventArgs e)
        {
            string path = Helper.getImagePath(ProjectVariables.backgroundPath);
            Communicator.sendImageMail(path, ProjectVariables.username);
        }

        private void goBack(object sender, RoutedEventArgs e)
        {
            Menu gotoMenu = new Menu();
            gotoMenu.Show();
            Close();
        }

        private void Encrypt(object sender, RoutedEventArgs e)
        {
            loading loadScreen = new loading(true);
            loadScreen.Show();
            Close();
        }
    }
}
