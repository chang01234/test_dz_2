#!/bin/sh

echo "Generating code..."
cd tools/build
python3 code_gen.py
cd ../..