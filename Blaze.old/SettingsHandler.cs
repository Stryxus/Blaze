using System;
using System.IO;
using System.Threading.Tasks;
using System.Collections.Generic;

using BSL.FileSystem;

namespace Blaze
{
    internal static class SettingsHandler
    {
        /*
        internal static Task SaveSettings()
        {
            JSON.WriteJSON<>();
        }

        internal static Task LoadSettings()
        {

        }
        */
    }

    internal class SolutionSettings
    {
        public Dictionary<string, ProjectSettings> RelativeProjectDirectoriesToBuild { get; set; }
    }

    internal class ProjectSettings
    {
        public bool Enabled { get; set; }
        public List<string> FilePathsToIgnore { get; set; }
        public List<string> DirectoryPathsToIgnore { get; set; }
        public List<string> FileTypesToAllow { get; set; }
        public List<SCSSSettings> SCSSFileSettings { get; set; }
        public List<JSSettings> JSFileSettings { get; set; }
        public List<ImageSettings> ImageFileSettings { get; set; }
        public List<VideoSettings> VideoFileSettings { get; set; }
        public List<AudioSettings> AudioFileSettings { get; set; }
    }

    public class SCSSSettings
    {
        public int FloatingPointPrecision { get; set; } = 3;
    }

    public class JSSettings
    {
        public int CompilationOrder { get; set; }
    }

    public class ImageSettings
    {
        public int MaxFileSizeKb { get; set; }
    }

    public class VideoSettings
    {
        public int MaxBitrate { get; set; }
        public int TargetBitrate { get; set; }
        public int MinimumBitrate { get; set; }
    }

    public class AudioSettings
    {

    }
}
