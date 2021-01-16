# Blaze
The optimization and delivery tool for Blazor projects and anything which has a wwwroot for assets.
## Distribution
There will be distribution of Blaze through this repository on the releases page eventually.
## Contributing
Everyone is welcome to contribute if interested. There are no instructions but there are requirements, obviously.
#### Code Style
There is no set code style, everyone can contribute in their own prefered ways as long as it isnt complicated enough that it isnt universally understood across all contributors.

Memory management is dealt with by coding freely, then afterwards doing a 'memory management pass' to deal with all the leaks and optimizations and so forth.
#### Requirements
- Windows 10 1909 or later
- Visual Studio 2019
- C++ with Cmake, Clang and CLR
- .NET 5 SDK
- Change NUglify and FFMpegCore targetframework to net5.0, this is found inside the csproj for each project.
- [Download FFmpeg 4.3](https://ffmpeg.zeranoe.com/builds/) Dev for Windows x64 and extract the 'include' and 'lib' folders into the 'ffmpeg' folder under the solution directory
- Run ```build.cmd``` once in the Visual Studio x64 Developer Tools Command Line and when strange errors occure.
