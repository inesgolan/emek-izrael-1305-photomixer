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

        private void login(object sender, RoutedEventArgs e)
        {
            string username = Helper.switchSpaces(Username.Text);
            Communicator.loginMsg(username, Password.Password);

            File.OpenRead(ProjectVariables.OUTPUT_FILE_NAME);
            string text = File.ReadAllText(ProjectVariables.OUTPUT_FILE_NAME);

            if (text == "False")
            {
                ErrorMsg.Text = "Your own problem. go get new friends.";
                Username.Clear();
                usernameText.Text = "Enter username";
                Password.Clear();
                passwordText.Text = "Enter password";
            }
            else
            {
                ProjectVariables.username = Username.Text;

                if (ProjectVariables.username != "guest")
                {
                    Directory.CreateDirectory(ProjectVariables.username);
                    string[] images = Directory.GetFiles(ProjectVariables.username);

                    if (images.Length > 0)
                    {


                        loading loadScreen = new loading(false);
                        loadScreen.Show();
                        Close();
                    }
                    else
                    {
                        Menu gotoMenu = new Menu();
                        gotoMenu.Show();
                        Close();
                    }
                }
                else
                {
                    Menu gotoMenu = new Menu();
                    gotoMenu.Show();
                    Close();
                }
            }
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
            ProjectVariables.username = "guest";
            Directory.CreateDirectory(ProjectVariables.username);

            Menu gotoMenu = new Menu();
            gotoMenu.Show();
            Close();
        }

        private void forgotPassword(object sender, RoutedEventArgs e)
        {
            Communicator.sendForgetPasswordMail(Username.Text);
        }

        private void exit(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void usernameGotFocus(object sender, RoutedEventArgs e)
        {
            usernameText.Clear();
        }

        private void passwordGotFocus(object sender, RoutedEventArgs e)
        {
            passwordText.Clear();
        }
    }
}