using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;
using System.Windows;
using System.Windows.Media;
using System.Threading;
using System.Windows.Navigation;

namespace photomixerGUI
{
    // this window display info about the project
    public partial class ProjectInfo : Window
    {
        public ProjectInfo()
        {
            InitializeComponent();
        }

        //open link
        private void guide(object sender, System.Windows.Navigation.RequestNavigateEventArgs e)
        {
            Process.Start(new ProcessStartInfo(e.Uri.AbsoluteUri) { UseShellExecute = true });
        }

        private void Hyperlink_RequestNavigate(object sender, RequestNavigateEventArgs e)
        {

        }
    }
}
