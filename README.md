[![Total alerts](https://img.shields.io/lgtm/alerts/g/Stryxus/Blaze.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/Stryxus/Blaze/alerts/)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/Stryxus/Blaze.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/Stryxus/Blaze/alerts/)
# Blaze
The optimization and delivery tool for many different types of assets in many different types of projects.
## Contributing
Everyone is welcome to contribute if interested. Follow the requirements and instructions below!
#### Code Style
There is no set code style, everyone can contribute in their own prefered ways as long as it isnt complicated enough that it isnt universally understood across all contributors.
#### Requirements & Instructions
- The latest version of Windows 10 and preferably other OS's like Android and have Windows SubSystem For Linux with a distro setup.
- Visual Studio 2019 with .NET 5, C++, CMake & CLR.
- Change NUglify & FFMpegCore targetframework to net5.0, this is found inside the csproj for each project.
- [Download FFmpeg 4.3 x64](https://ffmpeg.zeranoe.com/builds/) & extract the 'include' & 'lib' folders into 'Blaze/ffmpeg/include' & 'Blaze/ffmpeg/lib'.
- [Download curl 7.74 x64](https://curl.se/windows/) & extract the 'include' & 'lib' folders into 'Blaze/curl/include' & 'Blaze/curl/lib' & 'Blaze/curl/bin/libcurl-x64.dll'.
- [Download OpenSSL 1.1.1i x64](https://curl.se/windows/) & extract the 'libssl-1_1-x64.dll' & 'libcrypto-1_1-x64.dll' files into the 'Blaze/curl/bin' folder.
- Run ```./build.cmd``` in the View -> Terminal window just once unless the dependencies break.
