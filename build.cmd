@echo off
cls
color 0F
echo.
echo --- Blaze Dependency Build Tool ---  
echo -----------------------------------
echo This process may take several minutes depending on how powerful your CPU is.
echo Entering the Visual Studio year version will delete the current build folder and begin the build process.
echo.
echo.
set /p id= -- Enter your Visual Studio year version (2019 etc): 
cd %~dp0
rd /s /q build
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
cmake --build . --target %~dp0\build\zlib\ALL_BUILD --config Debug
echo.
echo.
echo.
cmake --build . --target %~dp0\build\libpng\ALL_BUILD --config Debug
echo.
echo.
echo.
cmake --build . --target %~dp0build\libwebp\ALL_BUILD --config Debug
echo.
echo.
echo.
msbuild %~dp0libsass\win\libsass.sln /p:Configuration=Release /p:Platform=Win64
echo.
echo.
echo.
echo Build Finished!
echo.
PAUSE