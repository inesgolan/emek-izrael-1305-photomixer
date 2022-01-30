using System.Windows;
using System.IO;
using System.Windows.Media;
using System;

namespace photomixerGUI
{
    //this class is in charge of logining in the system
    public partial class Login : Window
    {
        private Communicator communicator = new Communicator();

        public Login()
        {
            InitializeComponent();
        }

        //server returns?
        //this function checks if the username exists
        private void checkUsername(string username)
        {
            communicator.checkIfExistsMsg(username);
            ErrorMsg.Text = "Error: User exist, try again.";

        }

        //how will we know that it works?
        private void login(object sender, RoutedEventArgs e)
        {
            checkUsername(Username.Text);

            communicator.loginMsg(Username.Text, Password.Password);
        }

        //this function open the Register window
        private void register(object sender, RoutedEventArgs e)
        {
            //Register goRegister = new Register(Username.Text, Password.Password);
            //goRegister.Show();
            //Close();
        }
    }
}
