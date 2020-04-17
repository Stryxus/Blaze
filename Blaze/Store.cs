using System;
using System.IO;
using System.Diagnostics;
using System.Collections.Generic;

namespace Blaze
{
    internal static class Store
    {
        public static Process ProcessingProcess = null;

        public static DirectoryInfo ProjectDirectory = null;
        public static DirectoryInfo WebsiteRootDirectory = null;

        public static DirectoryInfo CSSDirectory = null;
        public static DirectoryInfo JSDirectory = null;

        public static FileInfo SCSSCoreFile = null;
        public static FileInfo JSCoreFile = null;
        public static FileInfo SCSSOutputFile = null;
        public static FileInfo JSOutputFile = null;
        public static FileInfo SCSSSourceMapFile = null;
        public static FileInfo JSSourceMapFile = null;

        public static int FileAccessRetries = 200;

        public static List<string> compilableImageContainers = new List<string>(new string[] { ".png", ".apng" });
        public static List<string> compilableVideoContainers = new List<string>(new string[] { ".mp4", ".avi" });
        public static List<string> compilableAudioContainers = new List<string>(new string[] { ".mp3", ".ogg", ".wav", ".flac" });
    }
}
