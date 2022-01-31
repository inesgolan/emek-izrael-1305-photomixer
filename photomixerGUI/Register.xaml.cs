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
        public static string OUTPUT_FILE_NAME = "Output.txt";
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

            string text;
            File.OpenRead(OUTPUT_FILE_NAME);
            text = File.ReadAllText(OUTPUT_FILE_NAME);

            if (text == "False")
            {
                ErrorMsg.Text = "Your own problem. go get new friends.";
                Username.Clear();
                Password.Clear();
                Mail.Clear();
            }
            else
            {
                MainWindow goToMainWindow = new MainWindow();
                goToMainWindow.Show();
                Close();
            }
        }
    }
}
