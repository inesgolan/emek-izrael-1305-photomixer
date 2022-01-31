using System.Windows;
using System.IO;
using System.Windows.Media;
using System;

namespace photomixerGUI
{
    //this class is in charge of logining in the system
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        //server returns?
        //this function checks if the username exists
        private void checkUsername(string username)
        {
            Communicator.checkIfExistsMsg(username);
            ErrorMsg.Text = "Error: User exist, try again.";

        }

        //how will we know that it works?
        private void login(object sender, RoutedEventArgs e)
        {
            checkUsername(Username.Text);

            Communicator.loginMsg(Username.Text, Password.Password);
        }

        // This function open the Register window
        private void register(object sender, RoutedEventArgs e)
        {
            Register goRegister = new Register();
            goRegister.Show();
            Close();
        }

        // This function enter to the app as a guest
        private void guestButton_click(object sender, RoutedEventArgs e)
        {
            Menu gotoMenu = new Menu();
            gotoMenu.Show();
            Close();
        }
    }
}
