using System;
using System.IO;
using System.Linq;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Text;
using System.Threading.Tasks;
using System.Text.RegularExpressions;

using BSL.FileSystem;

using NUglify;
using NUglify.JavaScript;

using LibSassHost;

namespace Blaze
{
    internal static class OptimizationTools
    {
        private static readonly List<FileSystemWatcher> Watchers = new List<FileSystemWatcher>();

        internal static async Task RunOptimizationTools(bool FirstRun = false)
        {
            if (FirstRun) await Logger.DivideBuffer();
            foreach (FileSystemWatcher w in Watchers) w.Dispose();
            Watchers.Clear();

            foreach (DirectoryInfo inf in Store.ProjectDirectory.GetDirectories("*", SearchOption.AllDirectories))
            {
                if (!inf.ContainsDirectory("bin")
                    && !inf.ContainsDirectory("obj")
                    && inf.ContainsDirectory("wwwroot"))
                {

                    if (inf.ContainsDirectory("css"))
                    {
                        await AddAssetListener(inf,
                              (object sender, FileSystemEventArgs args) => PerformSCSSChecks(args.FullPath)
                            , (object sender, FileSystemEventArgs args) => PerformSCSSChecks(args.FullPath)
                            , (object sender, FileSystemEventArgs args) => { }
                            , (object sender, RenamedEventArgs args) => PerformSCSSChecks(args.FullPath)
                        );
                    }
                    else if (inf.ContainsDirectory("js"))
                    {
                        await AddAssetListener(inf,
                              (object sender, FileSystemEventArgs args) => PerformJSChecks(args.FullPath)
                            , (object sender, FileSystemEventArgs args) => PerformJSChecks(args.FullPath)
                            , (object sender, FileSystemEventArgs args) => { }
                            , (object sender, RenamedEventArgs args) => PerformJSChecks(args.FullPath)
                        );
                    }
                    else if (inf.ContainsAnyDirectory("image", "img"))
                    {
                        await AddAssetListener(inf,
                              (object sender, FileSystemEventArgs args) => PerformImgChecks(args.FullPath)
                            , (object sender, FileSystemEventArgs args) => PerformImgChecks(args.FullPath)
                            , (object sender, FileSystemEventArgs args) => { }
                            , (object sender, RenamedEventArgs args) => PerformImgChecks(args.FullPath)
                        );
                    }
                    else if (inf.ContainsAnyDirectory("video", "vid"))
                    {
                        await AddAssetListener(inf,
                              (object sender, FileSystemEventArgs args) => PerformVidChecks(args.FullPath)
                            , (object sender, FileSystemEventArgs args) => PerformVidChecks(args.FullPath)
                            , (object sender, FileSystemEventArgs args) => { }
                            , (object sender, RenamedEventArgs args) => PerformVidChecks(args.FullPath)
                        );
                    }
                    else if (inf.ContainsDirectory("audio"))
                    {
                        await AddAssetListener(inf,
                              (object sender, FileSystemEventArgs args) => PerformAudioChecks(args.FullPath)
                            , (object sender, FileSystemEventArgs args) => PerformAudioChecks(args.FullPath)
                            , (object sender, FileSystemEventArgs args) => { }
                            , (object sender, RenamedEventArgs args) => PerformAudioChecks(args.FullPath)
                        );
                    }
                }
            }
            if (FirstRun)
            {
                await Logger.DivideBuffer();
                await Logger.Log(LogLevel.Info, "To restart, type 'restart'. To recompile a file manually, type the 're' command followed by the file name with the extension.");
                await Logger.DivideBuffer();
                await Logger.Log(LogLevel.Info, "Waiting for file updates...");
                await Logger.NewLine();

                await OptimizeJS().ConfigureAwait(false);
                await OptimizeSCSS(Store.SCSSCoreFile).ConfigureAwait(false);
                foreach (FileInfo f in Store.WebsiteRootDirectory.GetFiles("*.*", SearchOption.AllDirectories).Where(c => !c.ContainsAnyDirectory("bin", "obj") && c.ContainsDirectory("wwwroot")))
                {
                    await OptimizeImage(f).ConfigureAwait(false);
                    await OptimizeVideo(f).ConfigureAwait(false);
                    await OptimizeAudio(f).ConfigureAwait(false);
                }
            }

            static async Task AddAssetListener(DirectoryInfo directory, FileSystemEventHandler change, FileSystemEventHandler created, FileSystemEventHandler deleted, RenamedEventHandler renamed)
            {
                if (!Watchers.Any(o => o.Path == directory.FullName))
                {
                    FileSystemWatcher watcher = new FileSystemWatcher(directory.FullName)
                    {
                        NotifyFilter = NotifyFilters.Size | NotifyFilters.FileName | NotifyFilters.DirectoryName
                    };
                    watcher.Changed += change;
                    watcher.Created += created;
                    watcher.Deleted += deleted;
                    watcher.Renamed += renamed;
                    watcher.EnableRaisingEvents = true;
                    Watchers.Add(watcher);
                    await Logger.Log(LogLevel.Info, "Added Listener -> " + watcher.Path);
                }
            }
        }

        public static void CompileFile(FileInfo inf)
        {
            if (!inf.ContainsDirectory("bin")
                && !inf.ContainsDirectory("obj")
                && inf.ContainsDirectory("wwwroot"))
            {
                if (inf.ContainsDirectory("css")) PerformSCSSChecks(inf.FullName);
                else if (inf.ContainsDirectory("js")) PerformJSChecks(inf.FullName);
                else if (inf.ContainsAnyDirectory("image", "img")) PerformImgChecks(inf.FullName);
                else if (inf.ContainsAnyDirectory("video", "vid")) PerformVidChecks(inf.FullName);
                else if (inf.ContainsDirectory("audio")) PerformAudioChecks(inf.FullName);
            }
        }

        private static async void PerformSCSSChecks(string path)
        {
            try
            {
                if (File.GetAttributes(path).HasFlag(FileAttributes.Directory)) await RunOptimizationTools().ConfigureAwait(false);
                else await OptimizeSCSS(new FileInfo(path));
            }
            catch (FileNotFoundException) { }
            catch (DirectoryNotFoundException) { }
        }

        private static async void PerformJSChecks(string path)
        {
            try
            {
                if (File.GetAttributes(path).HasFlag(FileAttributes.Directory)) await RunOptimizationTools().ConfigureAwait(false);
                else await OptimizeJS(new FileInfo(path));
            }
            catch (FileNotFoundException) { }
            catch (DirectoryNotFoundException) { }
        }

        private static async void PerformImgChecks(string path)
        {
            try
            {
                if (File.GetAttributes(path).HasFlag(FileAttributes.Directory)) await RunOptimizationTools().ConfigureAwait(false);
                else await OptimizeImage(new FileInfo(path));
            }
            catch (FileNotFoundException) { }
            catch (DirectoryNotFoundException) { }
        }

        private static async void PerformVidChecks(string path)
        {
            try
            {
                if (File.GetAttributes(path).HasFlag(FileAttributes.Directory)) await RunOptimizationTools().ConfigureAwait(false);
                else await OptimizeVideo(new FileInfo(path));
            }
            catch (FileNotFoundException) { }
            catch (DirectoryNotFoundException) { }
        }

        private static async void PerformAudioChecks(string path)
        {
            try
            {
                if (File.GetAttributes(path).HasFlag(FileAttributes.Directory)) await RunOptimizationTools().ConfigureAwait(false);
                else await OptimizeAudio(new FileInfo(path));
            } 
            catch (FileNotFoundException) { }
            catch (DirectoryNotFoundException) { }
        }

        private static async Task OptimizeImage(FileInfo info)
        {
            if (info.Extension.EndsWithAny(Store.compilableImageContainers))
            {
                await Logger.Log(LogLevel.Info, "Processing Asset: " + info.FullName);
                byte[] rawWebP;
                FileInfo output = new FileInfo(info.FullName.Replace(info.Extension, ".webp"));
                using (Bitmap bitmap = (Bitmap)Image.FromFile(info.FullName))
                {
                    using WebP webp = new WebP();
                    rawWebP = webp.Encode(bitmap);
                }
                if (!await FileSystemIO.Exists(output)) await FileSystemIO.Create(output);
                else await FileIO.NullifyFile(output);
                await File.WriteAllBytesAsync(output.FullName, rawWebP);
            }
        }

        private static async Task OptimizeVideo(FileInfo info)
        {
            if (Store.compilableVideoContainers.Contains(info.Extension))
            {
                await Logger.Log(LogLevel.Info, "Processing Asset: " + info.FullName);
                await Store.ProcessingProcess.StartThenWaitRefreshAsync(Path.Combine(FileSystemIO.ApplicationDirectory.FullName, "ffmpeg") +
                    " -y -i \"" + info.FullName + "\" -c:v libvpx-vp9 -crf 10 -b:v 6000k -maxrate 10000k \"" + info.FullName.Replace(info.Extension, ".webm") + "\"");
            }
        }

        private static async Task OptimizeAudio(FileInfo info)
        {
            if (Store.compilableAudioContainers.Contains(info.Extension))
            {
                await Logger.Log(LogLevel.Info, "Processing Asset: " + info.FullName);
                await Store.ProcessingProcess.StartThenWaitRefreshAsync(Path.Combine(FileSystemIO.ApplicationDirectory.FullName, "ffmpeg") +
                    " -y -i\"" + info.FullName + "\" \"" + info.FullName.Replace(info.Extension, ".aac") + "\"");
            }
        }

        private static async Task OptimizeSCSS(FileInfo actualFile)
        {
            if (actualFile == null || (actualFile != Store.SCSSOutputFile && actualFile.FullName.EndsWith(".scss") && actualFile.Extension == ".scss"))
            {
                await Logger.Log(LogLevel.Info, "Processing CSS...");
                CompilationResult resultThirdParty = null;
                CompilationResult result = null;
                CompilationOptions compilation = null;
                try
                {
                    compilation = new CompilationOptions
                    {
                        SourceMap = true,
                        IncludePaths = new List<string>(new[] { Store.CSSDirectory.FullName }),
                        Precision = 3,
                        SourceComments = false,
                        OutputStyle = OutputStyle.Compressed
                    };
                    string cssContent = await ReadCSSContent();
                    if (!string.IsNullOrEmpty(cssContent) && cssContent != null) resultThirdParty = SassCompiler.Compile(cssContent, compilation);
                    result = SassCompiler.CompileFile(Store.SCSSCoreFile.FullName, null, null, compilation);
                }
                catch (SassException e)
                {
                    await Logger.Log(LogLevel.Error, e.Description);
                }
                catch (IOException)
                {
                    await Logger.Log(LogLevel.Info, "Processing SCSS from file " + Store.SCSSCoreFile.FullName + " failed. Attempting again...");
                    for (int i = 0; i < Store.FileAccessRetries; i++)
                    {
                        await Task.Delay(TimeSpan.FromSeconds(1)).ConfigureAwait(false);
                        result = SassCompiler.CompileFile(Store.SCSSCoreFile.FullName, null, null, compilation);
                    }
                }
                catch (ArgumentException e)
                {
                    await Logger.Log(LogLevel.Error, e.Message);
                }
                if (result != null)
                {
                    try
                    {
                        if (!Store.SCSSOutputFile.Exists) Store.SCSSOutputFile.Create();
                        else await FileIO.NullifyFile(Store.SCSSOutputFile);
                        await FileIO.WriteText(Store.SCSSOutputFile, Regex.Replace(resultThirdParty != null ? resultThirdParty.CompiledContent + result.CompiledContent : result.CompiledContent, @"/\*.+?\*/", string.Empty, RegexOptions.Singleline), Encoding.UTF8);
                        if (!Store.SCSSSourceMapFile.Exists) Store.SCSSSourceMapFile.Create();
                        else await FileIO.NullifyFile(Store.SCSSSourceMapFile);
                        await FileIO.WriteText(Store.SCSSSourceMapFile, result.SourceMap, Encoding.UTF8);
                    }
                    catch (IOException)
                    {
                        await Logger.Log(LogLevel.Error, "Saving CSS from " + Store.SCSSCoreFile.FullName + " failed. Will attempt again on change...");
                    }
                }
            }

            static async Task<string> ReadCSSContent()
            {
                string content = string.Empty;
                foreach (FileInfo s in Store.CSSDirectory.GetFiles("*.*", SearchOption.AllDirectories)
                    .Where(o => o.FullName.EndsWith(".css") && !o.FullName.EndsWith(".min.css"))) content += await FileIO.ReadText(s);
                return content;
            }
        }

        private static async Task OptimizeJS(FileInfo actualFile = null)
        {
            if (actualFile == null || (actualFile != Store.JSOutputFile && actualFile.FullName.EndsWith(".js") && actualFile.Extension == ".js"))
            {
                await Logger.Log(LogLevel.Info, "Processing Javascript...");
                string jsContent = string.Empty;
                foreach (FileInfo jsFile in Store.JSDirectory.GetFiles("*.*", SearchOption.AllDirectories)
                    .Where(o => o.FullName.EndsWith(".third.js")))
                {
                    if (jsFile == Store.JSOutputFile) continue;
                    jsContent += await FileIO.ReadText(jsFile);
                }
                foreach (FileInfo jsFile in Store.JSDirectory.GetFiles("*.*", SearchOption.AllDirectories)
                    .Where(o => o.FullName.EndsWith(".js") && !o.FullName.EndsWith(".third.js") && !o.FullName.EndsWith(".min.js")))
                {
                    if (jsFile == Store.JSOutputFile) continue;
                    jsContent += await FileIO.ReadText(jsFile);
                }
                await FileIO.NullifyFile(Store.JSOutputFile);
                await FileIO.WriteText(Store.JSOutputFile, Uglify.Js(jsContent, new CodeSettings
                {
                    ScriptVersion = ScriptVersion.EcmaScript6,
                    PreserveImportantComments = false,
                    AmdSupport = false
                }).Code, Encoding.UTF8);
            }
        }
    }
}