using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;
using System.Windows;
using System.Windows.Media;

namespace photomixerGUI
{
    class Communicator
    {
        public Communicator()
        {
        }

        /*
        This function will send recognize image msg to the server
        input:string objectPath, string savePath
        output: none
        */
        public void sendObjectRecognizeMsg(string objectPath, string savePath)
        {
            string exe_params = "100 " + objectPath + " " + savePath;
            string path = Path.GetFullPath("photomixer.exe");
            Process proc = System.Diagnostics.Process.Start(path, exe_params);
        }


        public void sendObjectRecognizeReverseMatteMsg(string objectPath, string savePath)
        {
            string exe_params = "101 " + objectPath + " " + savePath;
            string path = Path.GetFullPath("photomixer.exe");
            Process proc = System.Diagnostics.Process.Start(path, exe_params);
        }

        /*
        This function will send paste object on image msg to the server
        input:string objectPath, string backgroundPath, string savePath, int x, int y
        output: none
        */
        public void sendPasteObjectMsg(string objectPath, string backgroundPath, string savePath, int x, int y)
        {
            string exe_params = "200 " + objectPath + " " + backgroundPath + " " + savePath + " " + Convert.ToString(x) + " " + Convert.ToString(y);
            string path = Path.GetFullPath("photomixer.exe");
            Process proc = System.Diagnostics.Process.Start(path, exe_params);
        }


        public void resizeObjectBigMsg(string objectPath)
        {
            string exe_params = "300 " + objectPath;
            string path = Path.GetFullPath("photomixer.exe");
            Process proc = System.Diagnostics.Process.Start(path, exe_params);
        }

        public void resizeObjectSmallMsg(string objectPath)
        {
            string exe_params = "400 " + objectPath;
            string path = Path.GetFullPath("photomixer.exe");
            Process proc = System.Diagnostics.Process.Start(path, exe_params);
        }
    }
}
