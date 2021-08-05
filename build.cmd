@echo off
cls
color 0F
echo.
echo --- Blaze Dependency Build Tool ---  
echo -----------------------------------
echo IMPORTANT: This tool MUST be opened in Visual Studio's x64 Native Dev Tools Command Prompt!!!
echo This process may take several minutes depending on how powerful your CPU is.
cd %~dp0
mkdir build
cd build
echo.
echo -- Working at %~dp0
echo.
echo -- Running CMakeLists
echo.
cmake ../ -G "Visual Studio 16 2019"
echo.
echo.
echo -- Starting To Build Projects.
echo.
echo.
echo -------------------- BUILDING ZLIB --------------------
echo.
echo.
cmake --build . --target %~dp0build\zlib\ALL_BUILD
echo.
echo.
echo -------------------- BUILDING LIBPNG --------------------
echo.
echo.
cmake --build . --target %~dp0build\libpng\ALL_BUILD
echo.
echo.
echo -------------------- BUILDING LIBWEBP --------------------
echo.
echo.
cmake --build . --target %~dp0build\libwebp\ALL_BUILD
echo.
echo.
echo -------------------- BUILDING LIBSASS --------------------
echo.
echo.
devenv /Upgrade %~dp0libsass\win\libsass.sln
msbuild -m %~dp0libsass\win\libsass.sln /p:Configuration=Debug /p:Platform=Win64 /p:LIBSASS_STATIC_LIB=1
echo.
echo.
echo.
echo -- Build Finished!
echo.