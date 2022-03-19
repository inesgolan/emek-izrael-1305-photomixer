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
            ProjectVariables.key = checkKey(keyBotton.Text);

            string username = Helper.switchSpaces(Username.Text);

            Communicator.registerMsg(username, Password.Password, Mail.Text, ProjectVariables.key);

            string text;
            File.OpenRead(ProjectVariables.OUTPUT_FILE_NAME);
            text = File.ReadAllText(ProjectVariables.OUTPUT_FILE_NAME);

            if (text == "False")
            {
                ErrorMsg.Text = "Your own problem. go get new friends.";
                Username.Clear();
                usernameText.Text = "Enter username";
                Password.Clear();
                passwordText.Text = "Enter password";
                Mail.Clear();
                mailText.Text = "Enter mail";
                keyBotton.Clear();
                keyText.Text = "Enter key (16 chars)";
            }
            else
            {
                MainWindow goToMainWindow = new MainWindow();
                goToMainWindow.Show();
                Close();
            }
        }

        //this function check the key length
        private string checkKey(string key)
        {
            string newKey = key;

            while (newKey.Length != ProjectVariables.LENGTH)
            {
                ErrorMsg.Text = "please enter 16 chars";
                keyBotton.Clear();
                keyText.Text = "Enter key (16 chars)";
            }

            newKey = Helper.switchSpaces(newKey);

            return newKey;
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

        private void mailGotFocus(object sender, RoutedEventArgs e)
        {
            mailText.Clear();
        }

        private void keyGotFocus(object sender, RoutedEventArgs e)
        {
            keyText.Clear();
        }
    }
}
