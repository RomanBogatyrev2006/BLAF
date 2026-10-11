#!/bin/bash

cd ..
echo "Generating project..."

cmake -S . -B build

if [ $? -ne 0 ]; then
    echo "Generation failed"
	cd scripts
    exit 1
fi

echo "Done!"
cd scripts