@echo off
echo Starting Trekka SDK setup...

REM Função para verificar se comando existe
where git >nul 2>&1
if errorlevel 1 (
    echo Error: git is not installed or not in PATH.
    pause
    exit /b 1
)

where cmake >nul 2>&1
if errorlevel 1 (
    echo Error: cmake is not installed or not in PATH.
    pause
    exit /b 1
)

echo All dependencies are installed.

IF NOT EXIST TrekkaKit (
    git clone https://github.com/mazinn444/TrekkaKit.git
) ELSE (
    echo TrekkaKit folder already exists, pulling latest changes...
    cd TrekkaKit
    git pull
    cd ..
)

cd TrekkaKit || (
    echo Cannot enter TrekkaKit folder
    pause
    exit /b 1
)

if not exist build (
    mkdir build
)

cd build

echo Running cmake...
cmake ..

echo Building Trekka SDK...
cmake --build .

echo Setup complete!
pause
