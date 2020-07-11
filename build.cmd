@echo off
cls
setlocal
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
set executionPath="C:\Program Files (x86)\Microsoft Visual Studio\%id%\Preview\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"
echo.
echo -- Working at %~dp0
echo -- Using CMake at %executionPath%
echo.
echo.
echo Running CMakeLists
echo.
echo.
%executionPath% ../
echo.
echo.
echo Starting to build projects.
echo.
echo.
echo.
%executionPath% --build . --target %~dp0\build\zlib\ALL_BUILD
echo.
echo.
echo.
%executionPath% --build . --target %~dp0\build\libpng\ALL_BUILD
echo.
echo.
echo.
%executionPath% --build . --target %~dp0build\libwebp\ALL_BUILD
echo.
echo.
echo.
echo Build Finished!
echo.
PAUSE
endlocal
goto :eof

:dequote
setlocal
set thestring=%~1
endlocal&set ret=%thestring%
goto :eof