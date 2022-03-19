using System.IO;
using System.Windows;

namespace photomixerGUI
{
    public partial class Menu : Window
    {
        public Menu()
        {
            InitializeComponent();

            userName.Content += " " + ProjectVariables.username;
        }

        //This function open the window with the info about the project
        private void questionMark(object sender, RoutedEventArgs e)
        {
            ProjectInfo info = new ProjectInfo();
            info.Show();
        }

        //This function open the window where the user uploads the images pathes
        private void getPathes(object sender, RoutedEventArgs e)
        {
            UploadPathes pathes = new UploadPathes();
            pathes.Show();
            Close();
        }

        private void logout(object sender, RoutedEventArgs e)
        {
            File.Delete(ProjectVariables.OUTPUT_FILE_NAME);

            if (File.Exists("matte2.png"))
            {
                File.Delete("matte2.png");
            }

            if (ProjectVariables.username == "guest")
            {
                string[] pictures = Directory.GetFiles(ProjectVariables.username);

                foreach (string pic in pictures)
                {
                    if (pic != Helper.getImagePath(ProjectVariables.imagesPathes[ProjectVariables.imagesCounter]) && !pic.Contains("objectImage"))
                    {
                        File.Delete(pic);
                    }
                }

                MainWindow gotoMain = new MainWindow(); 
                gotoMain.Show();
                Close();
            }
            else
            {
                loading pathes = new loading(true); // encryption
                pathes.Show();
                Close();

                // initialize all project variables
                ProjectVariables.imagesCounter = 0;
                ProjectVariables.imagesPathes = new string[ProjectVariables.SIZE];
                ProjectVariables.countOfEdits = 0;
                ProjectVariables.countOfClicks = 0;
                ProjectVariables.index = 0;
            }
        }
    }
}
