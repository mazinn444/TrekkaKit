#!/bin/bash

echo "Starting Trekka SDK setup..."

# Função para verificar comando
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Verifica dependências
deps=(git cmake make)

for d in "${deps[@]}"; do
    if ! command_exists "$d"; then
        echo "Error: $d is not installed. Please install it and try again."
        exit 1
    fi
done

echo "All dependencies are installed."

# Clona o repositório se não existir
if [ ! -d "TrekkaKit" ]; then
    git clone https://github.com/mazinn444/TrekkaKit.git || { echo "Git clone failed"; exit 1; }
else
    echo "TrekkaKit folder already exists, pulling latest changes..."
    cd TrekkaKit && git pull && cd ..
fi

cd TrekkaKit || { echo "Cannot enter TrekkaKit folder"; exit 1; }

mkdir -p build
cd build || exit 1

echo "Running cmake..."
cmake ..

echo "Building Trekka SDK..."
make

echo "Setup complete!"
