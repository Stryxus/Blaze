using System;
using System.IO;
using System.Linq;
using System.Diagnostics;

using Stryxus.IO;

namespace Blaze
{
    public static class Program
    {
        private static bool ShutdownTrigger = true;

        public static void Main(string[] args)
        {
            if (args != null)
            {
                Setup();
                while (ShutdownTrigger)
                {
                    if (!args[args.Length - 1].StartsWith("--"))
                    {
                        for (int i = 0; i < args.Length; i++)
                        {
                            if (args[i].StartsWith("--") &&
                                (args[i + 1].StartsWith("-") ||
                                args[i + 1].StartsWith("--")))
                            {
                                ArgumentNullException e = new ArgumentNullException("Argument " + args[i] + "does not have a value! Can not continue! Closing...");
                                Logger.LogError(ref e);
                                throw e;
                            }
                        }
                    }
                    else
                    {
                        ArgumentException e = new ArgumentException("Last argument is a value requestor with no value! Cannot continue!");
                        Logger.LogError(ref e);
                        throw e;
                    }

                    string projectPathArg = "--projectPath";
                    if (args.Contains(projectPathArg))
                    {
                        Store.ProjectDirectory = new DirectoryInfo(args[Array.IndexOf(args, projectPathArg) + 1]);
                        if (!FileSystem.Exists(Store.ProjectDirectory.FullName))
                        {
                            Logger.LogError("Argument for " + projectPathArg  + " does not exist! Can not coninue! Closing...");
                            throw new DirectoryNotFoundException("Argument for " + projectPathArg + " does not exist! Can not coninue! Closing...");
                        }
                    }
                    else RequiredArgumentDoesntExist(projectPathArg);
                    Run();

                    void RequiredArgumentDoesntExist(string argument)
                    {
                        ArgumentNullException e = new ArgumentNullException("Required argument '" + argument + "' does not exist and therefore can not continue! Closing...");
                        Logger.LogError(ref e);
                        throw e;
                    }
                }
            }
            else
            {
                ArgumentNullException e = new ArgumentNullException(nameof(args));
                Logger.LogError(ref e);
                throw e;
            }
        }

        private static void Setup()
        {
            Logger.SetForegroundColor(ConsoleColor.Yellow);
            Console.Title = "Web Tools - Setting up...";

            Logger.LogInfo("Creating process for optimization processing...");

            Store.ProcessingProcess = new Process();
            Store.ProcessingProcess.StartInfo = new ProcessStartInfo()
            {
                FileName = "cmd.exe",
                WorkingDirectory = FileSystem.ApplicationDirectory.FullName,
                CreateNoWindow = false
            };

            Logger.NewLine();
            Logger.SetForegroundColor(ConsoleColor.White);
        }

        private static async void Run()
        {
            Console.Title = "Web Tools - " + Store.ProjectDirectory.FullName;

            Store.WebsiteRootDirectory = Store.ProjectDirectory.Combine("wwwroot");
            Store.CSSDirectory = Store.WebsiteRootDirectory.Combine("css");
            Store.JSDirectory = Store.WebsiteRootDirectory.Combine("js");

            Store.SCSSCoreFile = ProjectHandler.GetMainProjectMainSCSSFile();
            Store.JSCoreFile = ProjectHandler.GetMainProjectMainJSFile();
            Store.SCSSOutputFile = ProjectHandler.GetSCSSOutputFile();
            Store.JSOutputFile = ProjectHandler.GetJSOutputFile();
            Store.SCSSSourceMapFile = ProjectHandler.GetSCSSSourceMapFile();


            Logger.DivideBuffer();
            Logger.LogInfo("Using Root Directory -> " + Store.WebsiteRootDirectory.FullName);
            Logger.LogInfo("Using CSS Directory -> " + Store.CSSDirectory.FullName);
            Logger.LogInfo("Using Core SCSS File -> " + Store.SCSSCoreFile.FullName);
            Logger.LogInfo("Using Core JS File -> " + Store.JSCoreFile.FullName);
            Logger.LogInfo("Using SCSS Output File -> " + Store.SCSSOutputFile.FullName);
            Logger.LogInfo("Using JS Output File -> " + Store.JSOutputFile.FullName);
            await OptimizationTools.RunOptimizationTools(true).ConfigureAwait(false);
            WaitForCommand();

            void WaitForCommand()
            {
                string[] command = Console.ReadLine().Split(" ");
                if (command != null && command.Length > 0)
                {
                    if (command[0] == "re")
                    {
                        if (command.Length == 2)
                        {
                            if (ProjectHandler.FindFile(command[1], out FileInfo file) != false)
                            {
                                OptimizationTools.CompileFile(file);
                                WaitForCommand();
                            }
                            else
                            {
                                Logger.LogError("No file name provided or file does not exist.");
                                WaitForCommand();
                            }
                        }
                        else
                        {
                            Logger.LogError("No file name provided.");
                            WaitForCommand();
                        }
                    }
                    else if (command[0] == "restart")
                    {
                        Logger.ClearBuffer();
                        Run();
                    }
                }
                else
                {
                    Logger.LogError("Please enter a valid command.");
                    WaitForCommand();
                }
            }
        }
    }
}
