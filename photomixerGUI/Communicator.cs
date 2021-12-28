using System;
using System.Collections.Generic;
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
            string exe_full_path = Path.Combine(exe_folder, "photomixer.exe");
            Process proc = System.Diagnostics.Process.Start(exe_full_path, exe_params);
        }


        public void sendPasteObjectMsg(string objectPath, string backgroundPath, string savePath, int x, int y)
        {
            string exe_params = "200 " + objectPath + " " + backgroundPath + " " + savePath + " " + Convert.toChar(x) + " " + Convert.toChar(y);
            string exe_full_path = Path.Combine(exe_folder, "photomixer.exe");
            Process proc = System.Diagnostics.Process.Start(exe_full_path, exe_params);
        }
    }
}
