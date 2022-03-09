using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace photomixerGUI
{
    static class ProjectVariables
    {
        public const int SIZE = 5;
        public const int ENDING = 4;
        public const int UPLOAD_PATH_TYPE = 1;
        public const int SAVE_TYPE = 2;
        public const string OUTPUT_FILE_NAME = "Output.txt";

        public static string username;

        public static int imagesCounter = 0;
        public static string[] imagesPathes = new string[SIZE];

        public static string objectPath;
        public static string backgroundPath;
        public static string key;

        public static Communicator communicator = new Communicator();

        public static int countOfEdits;
        public static string savePath;
        public static int countOfClicks;
        public static int index;
    }
}
