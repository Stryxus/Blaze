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
- Visual Studio 2019 with C++ and CMake
- Change NUglify to .netstandard2.1
- [Download FFmpeg 4.3](https://ffmpeg.zeranoe.com/builds/) Dev for Windows x64 and extract the 'include' and 'lib' folders into the 'ffmpeg' folder under the solution directory
- [Download libssh 2.1.9.0](https://www.libssh2.org/) and extract its 'include' folder into the 'libssh' folder under the solution director
- Run ```build.cmd``` once or running it in the Visual Studio x64 Developer Tools Command Line and when strange errors occure.
