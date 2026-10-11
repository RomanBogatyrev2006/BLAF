#!/bin/bash

cd ..
echo "Building project..."

cmake --build build

if [ $? -ne 0 ]; then
    echo "Build failed"
	cd scripts
    exit 1
fi

echo "Done!"
cd scripts