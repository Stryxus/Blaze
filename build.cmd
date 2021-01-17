@echo off
cls
color 0F
echo.
echo --- Blaze Dependency Build Tool ---  
echo -----------------------------------
echo IMPORTANT: This tool MUST be opened in Visual Studio's x64 Native Dev Tools Command Prompt!!!
echo This process may take several minutes depending on how powerful your CPU is.
echo Entering the Visual Studio year version will delete the current build folder and begin the build process.
echo.
echo.
set /p id= -- Enter your Visual Studio year version (2019 etc): 
cd %~dp0
rd /s /q build
rd /s /q %~dp0\libsass\win\bin
mkdir build
cd build
echo.
echo -- Working at %~dp0
echo.
echo.
echo Running CMakeLists
echo.
echo.
cmake ../
echo.
echo.
echo Starting to build projects.
echo.
echo.
echo.
cmake --build . --target %~dp0\build\zlib\ALL_BUILD
echo.
echo.
echo.
cmake --build . --target %~dp0\build\libpng\ALL_BUILD
echo.
echo.
echo.
cmake --build . --target %~dp0\build\libwebp\ALL_BUILD
echo.
echo.
echo.
cmake --build . --target %~dp0\build\curl\ALL_BUILD
echo.
echo.
echo.
msbuild %~dp0libsass\win\libsass.sln /p:Configuration=Debug /p:Platform=Win64 /p:LIBSASS_STATIC_LIB=1
echo.
echo.
echo.
echo Build Finished!
echo.
PAUSE