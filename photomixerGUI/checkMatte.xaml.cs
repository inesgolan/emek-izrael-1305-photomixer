using System.Windows;

namespace photomixerGUI
{
    //asks the user if we found the object
    public partial class checkMatte : Window
    {
        public checkMatte()
        {
            InitializeComponent();
        }

        //this function reverse the matte colors
        private void reverseMatte(object sender, RoutedEventArgs e)
        {
            string msg = "101";
            //send to server to reverse colors of the matte
        }

        //opens edit window
        private void edit(object sender, RoutedEventArgs e)
        {
            Close();
            //editImage edit = new editImage();
            //edit.Show();
        }
    }
}
