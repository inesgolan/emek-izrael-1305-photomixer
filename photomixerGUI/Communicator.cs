using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;

namespace photomixerGUI
{
    class Communicator
    {
        // class variables
        // 

        public Communicator()
        {
        }


        public void sendObjectRecognizeMsg(string objectPath, string savePath)
        {
            string exe_params = "100 " + objectPath + " " + savePath;
            string path = Path.GetFullPath("photomixer.exe");
            Process proc = System.Diagnostics.Process.Start(path, exe_params);
        }


        public void sendPasteObjectMsg(string objectPath, string backgroundPath, string savePath, int x, int y)
        {
            string exe_params = "200 " + objectPath + " " + backgroundPath + " " + savePath + " " + Convert.ToChar(x) + " " + Convert.ToChar(y);
            string path = Path.GetFullPath("photomixer.exe");
            Process proc = System.Diagnostics.Process.Start(path, exe_params);
        }
    }
}
