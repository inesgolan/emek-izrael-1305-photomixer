using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.IO;
using System.Windows.Media;

namespace photomixerGUI
{
    class Helper
    {
        private const int SIZE = 5;
        private const int ENDING = 4;
        private const int UPLOAD_PATH_TYPE = 1;
        private const int SAVE_TYPE = 2;

        // check if the path is valid
        public static bool isPathValid(string path, int type)
        {
            string ending = "";

            // check if the user did not choose path yet
            if (path == null)
            {
                return false;
            }

            if (path.Length > ENDING)
            {

                int startIndex = path.Length - ENDING;
                int finishIndex = path.Length - 1;

                ending = path.Substring(startIndex, finishIndex - startIndex + 1);

            }
            else
            {
                return false;
            }


            bool fileExist = File.Exists(path);

            if (type == UPLOAD_PATH_TYPE) // upload pathes screen
            {
                if (fileExist && (".jpg" == ending || ".png" == ending)) //can open the file and it's a picture
                {
                    return true;
                }
            }
            else if (type == SAVE_TYPE) // save screen 
            {
                if (!fileExist && (".png" == ending)) 
                {
                    return true;
                }
            }


            return false;
        }

        //if the path has space we add ""
        public static string checkFullPath(string path)
        {
            string newPath = "";
            string temp = "\"";

            bool hasSpace = path.Any(Char.IsWhiteSpace);
            if (hasSpace)
            {
                newPath = temp + path + temp;
                //string savePath = "\"C:/Users/Ines Noa Golan/source/repos/emek-izrael-1305-photomixer/photomixer/images/new.png\""
            }
            else
            {
                newPath = path;
            }

            return newPath;
        }
    }
}
