IF NOT EXIST build (
mkdir build 
)

REM Change this to the correct Visual Studio version
cmake -G "Visual Studio 16 2019" -A x64 -S . -B build

cd build

REM Change this to the appropriate directory
SET MSBUILD=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe
IF NOT EXIST "%MSBUILD%" GOTO NOMSB

"%MSBUILD%" InMemoryDb.sln /t:rebuild /p:Configuration=Debug /p:Platform="x64" /m
GOTO :EOF

:NOMSB
echo. 
echo MSBUILD not found 
echo. 
GOTO :EOF 
