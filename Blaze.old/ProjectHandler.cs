using System;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using System.Collections.Generic;

using BSL.FileSystem;

namespace Blaze
{
    internal static class ProjectHandler
    {
        internal static DirectoryInfo GetWebsiteRootDirectory()
        {
            foreach (DirectoryInfo inf in Store.ProjectDirectory.GetDirectories("*", SearchOption.AllDirectories).Where(o => o.ContainsDirectory("css")))
            {
                List<FileInfo> infs = new List<FileInfo>(inf.GetFiles("*", SearchOption.TopDirectoryOnly));
                if (infs.Contains("appsettings.json") && infs.Contains("appsettings.Development.json") && infs.Contains("_Imports.razor")) return inf;
            }
            throw new FileNotFoundException("Main project not found in the selected solution!");
        }

        internal static async Task<FileInfo> GetMainProjectMainSCSSFile()
        {
            FileInfo inf = new FileInfo(Path.Combine(Store.ProjectDirectory.FullName, "wwwroot", "css", "bundle.scss"));
            if (await FileSystemIO.Exists(inf)) return inf;
            throw new FileNotFoundException("No bundle.scss was found in " + Store.CSSDirectory.FullName);
        }

        internal static async Task<FileInfo> GetMainProjectMainJSFile()
        {
            FileInfo inf = new FileInfo(Path.Combine(Store.ProjectDirectory.FullName, "wwwroot", "js", "bundle.js"));
            if (await FileSystemIO.Exists(inf)) return inf;
            throw new FileNotFoundException("No bundle.js was found in " + Store.JSDirectory.FullName);
        }

        internal static FileInfo GetSCSSOutputFile()
        {
            return new FileInfo(Path.Combine(Store.ProjectDirectory.FullName, "wwwroot", "bundle.min.css"));
        }

        internal static FileInfo GetJSOutputFile()
        {
            return new FileInfo(Path.Combine(Store.ProjectDirectory.FullName, "wwwroot", "bundle.min.js"));
        }

        internal static FileInfo GetSCSSSourceMapFile()
        {
            return new FileInfo(Path.Combine(Store.ProjectDirectory.FullName, "wwwroot", "bundle.css.map"));
        }

        internal static FileInfo GetJSSourceMapFile()
        {
            return new FileInfo(Path.Combine(Store.ProjectDirectory.FullName, "wwwroot", "bundle.js.map"));
        }

        public static bool FindFile(string filename, out FileInfo file)
        {
            foreach (FileInfo i in Store.WebsiteRootDirectory.GetFiles("*.*", SearchOption.AllDirectories))
            {
                if (i.Name == filename)
                {
                    file = i;
                    return true;
                }
            }
            file = null;
            return false;
        }
    }
}
