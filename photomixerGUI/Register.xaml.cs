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
    /// <summary>
    /// Interaction logic for Register.xaml
    /// </summary>
    public partial class Register : Window
    {
        public Register()
        {
            InitializeComponent();
        }

        private void backButton_Click(object sender, RoutedEventArgs e)
        {
            MainWindow goToMainWindow = new MainWindow();
            goToMainWindow.Show();
            Close();
        }

        private void signUp_Button(object sender, RoutedEventArgs e)
        {
            Communicator.registerMsg(Username.Text, Password.Password, Mail.Text);
            MainWindow goToMainWindow = new MainWindow();
            goToMainWindow.Show();
            Close();
        }
    }
}
