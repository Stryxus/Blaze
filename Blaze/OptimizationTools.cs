using System;
using System.IO;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Drawing.Imaging;
using System.Text.RegularExpressions;

using Stryxus.IO;
using Stryxus.Formats;

using ImageProcessor;
using ImageProcessor.Imaging.Formats;
using ImageProcessor.Plugins.WebP.Imaging.Formats;

using NUglify;
using NUglify.Css;
using NUglify.Helpers;
using NUglify.Html;
using NUglify.JavaScript;

using LibSassHost;

namespace Blaze
{
    internal static class OptimizationTools
    {
        private static List<FileSystemWatcher> Watchers = new List<FileSystemWatcher>();

        internal static async Task RunOptimizationTools(bool FirstRun = false)
        {
            if (FirstRun) Logger.DivideBuffer();
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
                        AddAssetListener(inf,
                              (object sender, FileSystemEventArgs args) => PerformSCSSChecks(args.FullPath)
                            , (object sender, FileSystemEventArgs args) => PerformSCSSChecks(args.FullPath)
                            , (object sender, FileSystemEventArgs args) => { }
                            , (object sender, RenamedEventArgs args) => PerformSCSSChecks(args.FullPath)
                        );
                    }
                    else if (inf.ContainsDirectory("js"))
                    {
                        AddAssetListener(inf,
                              (object sender, FileSystemEventArgs args) => PerformJSChecks(args.FullPath)
                            , (object sender, FileSystemEventArgs args) => PerformJSChecks(args.FullPath)
                            , (object sender, FileSystemEventArgs args) => { }
                            , (object sender, RenamedEventArgs args) => PerformJSChecks(args.FullPath)
                        );
                    }
                    else if (inf.ContainsAnyDirectory("image", "img"))
                    {
                        AddAssetListener(inf,
                              (object sender, FileSystemEventArgs args) => PerformImgChecks(args.FullPath)
                            , (object sender, FileSystemEventArgs args) => PerformImgChecks(args.FullPath)
                            , (object sender, FileSystemEventArgs args) => { }
                            , (object sender, RenamedEventArgs args) => PerformImgChecks(args.FullPath)
                        );
                    }
                    else if (inf.ContainsAnyDirectory("video", "vid"))
                    {
                        AddAssetListener(inf,
                              (object sender, FileSystemEventArgs args) => PerformVidChecks(args.FullPath)
                            , (object sender, FileSystemEventArgs args) => PerformVidChecks(args.FullPath)
                            , (object sender, FileSystemEventArgs args) => { }
                            , (object sender, RenamedEventArgs args) => PerformVidChecks(args.FullPath)
                        );
                    }
                    else if (inf.ContainsDirectory("audio"))
                    {
                        AddAssetListener(inf,
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
                Logger.DivideBuffer();
                Logger.SetForegroundColor(ConsoleColor.DarkGreen);
                Logger.LogInfo("To restart, type 'restart'. To recompile a file manually, type the 're' command followed by the file name with the extension.");
                Logger.SetForegroundColor(ConsoleColor.White);
                Logger.DivideBuffer();
                Logger.LogInfo("Waiting for file updates...", false, false);
                Logger.NewLine();

                await OptimizeJS().ConfigureAwait(false);
                await OptimizeSCSS(Store.SCSSCoreFile).ConfigureAwait(false);
                foreach (FileInfo f in Store.WebsiteRootDirectory.GetFiles("*.*", SearchOption.AllDirectories).Where(c => !c.ContainsAnyDirectory("bin", "obj") && c.ContainsDirectory("wwwroot")))
                {
                    await OptimizeImage(f).ConfigureAwait(false);
                    await OptimizeVideo(f).ConfigureAwait(false);
                    await OptimizeAudio(f).ConfigureAwait(false);
                }
            }

            static void AddAssetListener(DirectoryInfo directory, FileSystemEventHandler change, FileSystemEventHandler created, FileSystemEventHandler deleted, RenamedEventHandler renamed)
            {
                if (!Watchers.Any(o => o.Path == directory.FullName))
                {
                    FileSystemWatcher watcher = new FileSystemWatcher(directory.FullName);
                    watcher.NotifyFilter = NotifyFilters.Size | NotifyFilters.FileName | NotifyFilters.DirectoryName;
                    watcher.Changed += change;
                    watcher.Created += created;
                    watcher.Deleted += deleted;
                    watcher.Renamed += renamed;
                    watcher.EnableRaisingEvents = true;
                    Watchers.Add(watcher);
                    Logger.SetForegroundColor(ConsoleColor.Cyan);
                    Logger.LogInfo("Added Listener -> " + watcher.Path);
                    Logger.SetForegroundColor(ConsoleColor.White);
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
            if (FileSystem.IsPathDirectory(path)) await RunOptimizationTools().ConfigureAwait(false);
            else await OptimizeSCSS(new FileInfo(path)).ConfigureAwait(false);
        }

        private static async void PerformJSChecks(string path)
        {
            if (FileSystem.IsPathDirectory(path)) await RunOptimizationTools().ConfigureAwait(false);
            else await OptimizeJS(new FileInfo(path)).ConfigureAwait(false);
        }

        private static async void PerformImgChecks(string path)
        {
            if (FileSystem.IsPathDirectory(path)) await RunOptimizationTools().ConfigureAwait(false);
            else await OptimizeImage(new FileInfo(path)).ConfigureAwait(false);
        }

        private static async void PerformVidChecks(string path)
        {
            if (FileSystem.IsPathDirectory(path)) await RunOptimizationTools().ConfigureAwait(false);
            else await OptimizeVideo(new FileInfo(path)).ConfigureAwait(false);
        }

        private static async void PerformAudioChecks(string path)
        {
            if (FileSystem.IsPathDirectory(path)) await RunOptimizationTools().ConfigureAwait(false);
            else await OptimizeAudio(new FileInfo(path)).ConfigureAwait(false);
        }

        private static async Task OptimizeImage(FileInfo info)
        {
            if (Store.compilableImageContainers.Contains(info.Extension))
            {
                Logger.LogInfo("Processing Asset: " + info.FullName);
                List<byte> photoBytes = FileSystem.ReadBytesSync(info);

                ISupportedImageFormat format = new WebPFormat { Quality = 75 };
                using (MemoryStream inStream = new MemoryStream(photoBytes.ToArray()))
                {
                    using (MemoryStream outStream = new MemoryStream())
                    {
                        try
                        {
                            LoadAndWriteImage();
                        }
                        catch (IOException)
                        {
                            Logger.LogError("Processing image from file " + info.FullName + " failed. Attempting again...");
                            for (int i = 0; i < Store.FileAccessRetries; i++) LoadAndWriteImage();
                        }

                        void LoadAndWriteImage()
                        {
                            using (ImageFactory imageFactory = new ImageFactory(preserveExifData: false)) imageFactory.Load(inStream)
                                    .BitDepth((long)PixelFormat.Format16bppRgb555).Format(format).Save(outStream);
                            FileInfo outFile = new FileInfo(info.FullName.Replace(info.Extension, string.Empty) + ".webp");
                            if (!FileSystem.Exists(outFile)) FileSystem.Create(outFile);
                            FileSystem.WriteBytesSync(outStream, outFile);
                        }
                    }
                }
            }
        }

        private static async Task OptimizeVideo(FileInfo info)
        {
            if (Store.compilableVideoContainers.Contains(info.Extension))
            {
                Logger.LogInfo("Processing Asset: " + info.FullName);
                // Needs re-implementing
                throw new NotImplementedException();
            }
        }

        private static async Task OptimizeAudio(FileInfo info)
        {
            if (Store.compilableAudioContainers.Contains(info.Extension))
            {
                Logger.LogInfo("Processing Asset: " + info.FullName);
                // Needs re-implementing
                throw new NotImplementedException();
            }
        }

        private static async Task OptimizeSCSS(FileInfo actualFile)
        {
            if (actualFile != Store.SCSSOutputFile && actualFile.Extension == ".scss")
            {
                Logger.LogInfo("Processing CSS...");
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
                    string cssContent = ReadCSSContent();
                    if (!cssContent.IsEmpty() && cssContent != null) resultThirdParty = SassCompiler.Compile(cssContent, compilation);
                    result = SassCompiler.CompileFile(Store.SCSSCoreFile.FullName, null, null, compilation);
                }
                catch (SassException e)
                {
                    Logger.LogError(e.Description);
                }
                catch (IOException)
                {
                    Logger.LogError("Processing SCSS from file " + Store.SCSSCoreFile.FullName + " failed. Attempting again...");
                    for (int i = 0; i < Store.FileAccessRetries; i++)
                    {
                        await Task.Delay(TimeSpan.FromSeconds(1)).ConfigureAwait(false);
                        result = SassCompiler.CompileFile(Store.SCSSCoreFile.FullName, null, null, compilation);
                    }
                }
                catch (ArgumentException e)
                {
                    Logger.LogError(e.Message);
                }
                if (result != null)
                {
                    try
                    {
                        WriteCSSAndMap();
                    }
                    catch (IOException e)
                    {
                        Logger.LogError("Saving CSS from " + Store.SCSSCoreFile.FullName + " failed. Attempting again...");
                        for (int i = 0; i < Store.FileAccessRetries; i++)
                        {
                            await Task.Delay(TimeSpan.FromSeconds(1)).ConfigureAwait(false);
                            WriteCSSAndMap();
                        }
                    }
                    void WriteCSSAndMap()
                    {
                        if (!Store.SCSSOutputFile.Exists) Store.SCSSOutputFile.Create();
                        else FileSystem.NullifyFileSync(Store.SCSSOutputFile);
                        FileSystem.WriteSync(Regex.Replace(resultThirdParty != null ? resultThirdParty.CompiledContent + result.CompiledContent : result.CompiledContent, @"/\*.+?\*/", string.Empty, RegexOptions.Singleline), Store.SCSSOutputFile, Encoding.UTF8);
                        if (!Store.SCSSSourceMapFile.Exists) Store.SCSSSourceMapFile.Create();
                        else FileSystem.NullifyFileSync(Store.SCSSSourceMapFile);
                        FileSystem.WriteSync(result.SourceMap, Store.SCSSSourceMapFile, Encoding.UTF8);
                    }
                }
            }

            string ReadCSSContent()
            {
                string content = string.Empty;
                foreach (FileInfo s in Store.CSSDirectory.GetFiles("*.*", SearchOption.AllDirectories)
                    .Where(o => o.FullName.EndsWith(".css") && !o.FullName.EndsWith(".min.css"))) content += FileSystem.ReadSync(s, Encoding.UTF8);
                return content;
            }
        }

        private static async Task OptimizeJS(FileInfo actualFile = null)
        {
            if (actualFile == null || (actualFile != Store.JSOutputFile && actualFile.Extension == ".js"))
            {
                Logger.LogInfo("Processing Javascript...");
                string jsContent = string.Empty;
                foreach (FileInfo jsFile in Store.JSDirectory.GetFiles("*.*", SearchOption.AllDirectories)
                    .Where(o => o.FullName.EndsWith(".third.js")))
                {
                    if (jsFile == Store.JSOutputFile) continue;
                    jsContent += FileSystem.ReadSync(jsFile, Encoding.UTF8);
                }
                foreach (FileInfo jsFile in Store.JSDirectory.GetFiles("*.*", SearchOption.AllDirectories)
                    .Where(o => o.FullName.EndsWith(".js") && !o.FullName.EndsWith(".third.js") && !o.FullName.EndsWith(".min.js")))
                {
                    if (jsFile == Store.JSOutputFile) continue;
                    jsContent += FileSystem.ReadSync(jsFile, Encoding.UTF8);
                }
                FileSystem.NullifyFileSync(Store.JSOutputFile);
                FileSystem.WriteSync(Uglify.Js(jsContent, new CodeSettings
                {
                    ScriptVersion = ScriptVersion.EcmaScript6,
                    PreserveImportantComments = false
                }).Code, Store.JSOutputFile, Encoding.UTF8);
            }

            string ReadJSContent()
            {
                string content = string.Empty;
                foreach (FileInfo s in Store.JSDirectory.GetFiles("*.*", SearchOption.AllDirectories)
                    .Where(o => o.FullName.EndsWith(".min.js"))) content += FileSystem.ReadSync(s, Encoding.UTF8);
                return content;
            }
        }
    }
}