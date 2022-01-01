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
            Console.WriteLine(exe_params);
            string exe_full_path = Path.Combine("C:\\Users\\Ines Noa Golan\\source\\repos\\emek-izrael-1305-photomixer\\photomixer", "photomixer.exe");
            Process proc = System.Diagnostics.Process.Start(exe_full_path, exe_params);
        }


        public void sendPasteObjectMsg(string objectPath, string backgroundPath, string savePath, int x, int y)
        {
            string exe_params = "200 " + objectPath + " " + backgroundPath + " " + savePath + " " + Convert.ToChar(x) + " " + Convert.ToChar(y);
            string exe_full_path = Path.Combine("C:\\Users\\משתמש\\emek-izrael-1305-photomixer\\photomixer\\x64\\Debug", "photomixer.exe");
            Process proc = System.Diagnostics.Process.Start(exe_full_path, exe_params);
        }
    }
}
