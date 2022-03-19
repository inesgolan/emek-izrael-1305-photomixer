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
using System.IO;


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
            if (ProjectVariables.username != "guest")
            {
                string path = Helper.getImagePath(ProjectVariables.imagesPathes[ProjectVariables.imagesCounter]);
                Communicator.sendImageMail(path, ProjectVariables.username);
            }
        }

        private void goBack(object sender, RoutedEventArgs e)
        {
            Menu gotoMenu = new Menu();
            gotoMenu.Show();
            Close();
        }

        private void exit(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }
}
