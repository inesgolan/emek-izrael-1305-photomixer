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
    class checkPath
    {
        private const int SIZE = 5;
        private const int ENDING = 4;


        // check if the path is valid
        public bool isPathValid(string path, int type)
        {
            string ending = "";

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

            if (type == 1) // upload pathes screen
            {
                if (fileExist && (".jpg" == ending || ".png" == ending)) //can open the file and it's a picture
                {
                    return true;
                }
            }
            else if (type == 2) // save screen 
            {
                if (!fileExist && (".png" == ending)) 
                {
                    return true;
                }
            }


            return false;
        }
    }
}
