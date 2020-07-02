using System;
using System.IO;
using System.Linq;
using System.Diagnostics;
using System.Threading.Tasks;
using System.Collections.Generic;

using BSL;
using BSL.FileSystem;

namespace Blaze
{
    public static class Program
    {
        public static void Main(string[] args) => MainAsync(args).GetAwaiter().GetResult();

        private static async Task MainAsync(string[] args)
        {
            Console.Title = "Web Tools - Setting up...";

            await Logger.Log(LogLevel.Info, "Creating process for optimization processing...");

            Store.ProcessingProcess = new Process();
            Store.ProcessingProcess.StartInfo = new ProcessStartInfo()
            {
                FileName = "cmd.exe",
                WorkingDirectory = FileSystemIO.ApplicationDirectory.FullName,
                CreateNoWindow = true
            };

            await ArgumentHandler.ParseArgumentsFromArray(args, out List<ParsedArgument> arguments);
            DirectoryInfo projectPath = new DirectoryInfo(arguments.Single(c => c.Command.Contains("projectPath")).Value);
            if (await FileSystemIO.Exists(projectPath)) Store.ProjectDirectory = projectPath;
            else throw new ArgumentNullException(nameof(args), "No project path was provided!");
            await Run();
        }

        private static async Task Run()
        {
            Console.Title = "Web Tools - " + Store.ProjectDirectory.FullName;

            Store.WebsiteRootDirectory = Store.ProjectDirectory.Combine("wwwroot");
            Store.CSSDirectory = Store.WebsiteRootDirectory.Combine("css");
            Store.JSDirectory = Store.WebsiteRootDirectory.Combine("js");

            Store.SCSSCoreFile = await ProjectHandler.GetMainProjectMainSCSSFile();
            Store.JSCoreFile = await ProjectHandler.GetMainProjectMainJSFile();
            Store.SCSSOutputFile = ProjectHandler.GetSCSSOutputFile();
            Store.JSOutputFile = ProjectHandler.GetJSOutputFile();
            Store.SCSSSourceMapFile = ProjectHandler.GetSCSSSourceMapFile();

            await Logger.DivideBuffer();
            await Logger.Log(LogLevel.Info, "Using Root Directory -> " + Store.WebsiteRootDirectory.FullName);
            await Logger.Log(LogLevel.Info, "Using CSS Directory -> " + Store.CSSDirectory.FullName);
            await Logger.Log(LogLevel.Info, "Using Core SCSS File -> " + Store.SCSSCoreFile.FullName);
            await Logger.Log(LogLevel.Info, "Using Core JS File -> " + Store.JSCoreFile.FullName);
            await Logger.Log(LogLevel.Info, "Using SCSS Output File -> " + Store.SCSSOutputFile.FullName);
            await Logger.Log(LogLevel.Info, "Using JS Output File -> " + Store.JSOutputFile.FullName);
            await OptimizationTools.RunOptimizationTools(true).ConfigureAwait(false);
            await WaitForCommand();

            static async Task WaitForCommand()
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
                                await WaitForCommand();
                            }
                            else
                            {
                                await Logger.Log(LogLevel.Error, "No file name provided or file does not exist.");
                                await WaitForCommand();
                            }
                        }
                        else
                        {
                            await Logger.Log(LogLevel.Error, "No file name provided.");
                            await WaitForCommand();
                        }
                    }
                    else if (command[0] == "restart")
                    {
                        await Logger.ClearBuffer();
                        await Run();
                    }
                }
                else
                {
                    await Logger.Log(LogLevel.Error, "Please enter a valid command.");
                    await WaitForCommand();
                }
            }
        }
    }
}
