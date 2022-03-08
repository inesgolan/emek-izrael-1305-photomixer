using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;
using System.Windows;
using System.Windows.Media;
using System.Threading;

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
        public static void sendObjectRecognizeMsg(string objectPath, string savePath)
        {
            string exe_params = "100 " + objectPath + " " + savePath;
            string path = Path.GetFullPath("photomixer.exe");
            Process proc = System.Diagnostics.Process.Start(path, exe_params);
            proc.WaitForExit();
        }


        public static void sendObjectRecognizeReverseMatteMsg(string objectPath, string savePath)
        {
            string exe_params = "101 " + objectPath + " " + savePath;
            string path = Path.GetFullPath("photomixer.exe");
            Process proc = System.Diagnostics.Process.Start(path, exe_params);
            proc.WaitForExit();
        }

        /*
        This function will send paste object on image msg to the server
        input:string objectPath, string backgroundPath, string savePath, int x, int y
        output: none
        */
        public static void sendPasteObjectMsg(string objectPath, string backgroundPath, string savePath, int x, int y)
        {
            string exe_params = "200 " + objectPath + " " + backgroundPath + " " + savePath + " " + Convert.ToString(x) + " " + Convert.ToString(y);
            string path = Path.GetFullPath("photomixer.exe");
            Process proc = System.Diagnostics.Process.Start(path, exe_params);
            proc.WaitForExit();
        }


        public static void resizeObjectBigMsg(string objectPath)
        {
            string exe_params = "300 " + objectPath;
            string path = Path.GetFullPath("photomixer.exe");
            Process proc = System.Diagnostics.Process.Start(path, exe_params);
            proc.WaitForExit();
        }

        public static void resizeObjectSmallMsg(string objectPath)
        {
            string exe_params = "400 " + objectPath;
            string path = Path.GetFullPath("photomixer.exe");
            Process proc = System.Diagnostics.Process.Start(path, exe_params);
            proc.WaitForExit();
        }

        /*
        This function will send login message to the server
        Input: username, password
        Output: none
        */
        public static void loginMsg(string username, string password)
        {
            string exe_params = "500 " + username + " " + password;
            string path = Path.GetFullPath("photomixer.exe");
            Process proc = System.Diagnostics.Process.Start(path, exe_params);
            proc.WaitForExit();
        }

        /*
        This function will send register message to the server
        Input: username, password, mail
        Output: none
        */
        public static void registerMsg(string username, string password, string mail)
        {
            string exe_params = "600 " + username + " " + password + " " + mail;
            string path = Path.GetFullPath("photomixer.exe");
            Process proc = System.Diagnostics.Process.Start(path, exe_params);
            proc.WaitForExit();
        }

        /*
        This function will send encryption message to the server
        Input: image path, key
        Output: none
        */
        public static void encryptionMsg(string imagePath, string key)
        {
            string exe_params = "700 " + imagePath + " " + key;
            string path = Path.GetFullPath("photomixer.exe");
            Process proc = System.Diagnostics.Process.Start(path, exe_params);
            proc.WaitForExit();
        }

    }
}
