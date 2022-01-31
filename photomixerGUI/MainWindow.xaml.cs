using System.Windows;
using System.IO;
using System.Windows.Media;
using System;

namespace photomixerGUI
{
    //this class is in charge of logining in the system
    public partial class MainWindow : Window
    {
        public static string OUTPUT_FILE_NAME = "Output.txt";
        public MainWindow()
        {
            InitializeComponent();
        }

        private void login(object sender, RoutedEventArgs e)
        {
            Communicator.loginMsg(Username.Text, Password.Password);

            string text;
            File.OpenRead(OUTPUT_FILE_NAME);
            text = File.ReadAllText(OUTPUT_FILE_NAME);

            if (text == "False")
            {
                ErrorMsg.Text = "Your own problem. go get new friends.";
                Username.Clear();
                Password.Clear();
            }
            else
            {
                Menu gotoMenu = new Menu();
                gotoMenu.Show();
                Close();
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
            Menu gotoMenu = new Menu();
            gotoMenu.Show();
            Close();
        }
    }
}
