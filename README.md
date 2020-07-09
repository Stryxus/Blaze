# Blaze
The optimization and delivery tool for Star Athenaeum's Blazor projects.
## Distribution
There will be distribution of Blaze through this repository on the releases page eventually.
## Contributing
Everyone is welcome to contribute if interested. There are no instructions but there are requirements, obviously.
#### Code Style
There is no set code style, everyone can contribute in their own prefered ways as long as it isnt complicated enough that it isnt universally understood across all contributors.

Memory management is dealt with by coding freely, then afterwards doing a 'memory management pass' to deal with all the leaks and optimizations and so forth.
#### Requirements
- Windows 10 1909 or later
- Visual Studio 2019 with C++
- Change NUglify to .netstandard2.1
- Download FFmpeg Dev for Windows x64 and extract the 'include' and 'lib' folders into the 'ffmpeg' folder under the solution directory
- Build libwebp through the 'build_webp.cmd' file through the [Visual Studio Developer Command Prompt](https://docs.microsoft.com/en-us/dotnet/framework/tools/developer-command-prompt-for-vs)
