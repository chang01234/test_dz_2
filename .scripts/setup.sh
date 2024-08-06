#!/bin/sh

echo SETUP SYSTEM !!!

# Find all files of extension .sh or .py and give execution permission
find . -type f \( -name "*.sh" -o -name "*.py" \) -exec chmod +x {} \;
chmod +x ./tools/build/edb-conv

# init all submodules
git submodule update --init

# clone code-gen, checkout tag, pip install, rm code-gen
python -m venv .venv
./.venv/bin/pip install -r requirements.txt
git clone https://github.com/onedometic/Code-Database-Generation-Tool.git code-gen
cd code-gen && git checkout origin/feature/embed-enum-in-xml
cd .. && ./.venv/bin/pip install ./code-gen
git config --global --add safe.directory .
rm -rf code-gen

# setup the project name environment variable in bash and zsh so it is available for all subsequent shell
COMMAND="export PROJECT_NAME="$(./.venv/bin/python3 ./tools/build/get-env-var.py project-name)
echo $COMMAND >> ~/.bashrc
echo $COMMAND >> ~/.zshrc

# setup the mcu environment variable in bash and zsh so it is available for all subsequent shell
COMMAND="export JLINK_MICRO="$(./.venv/bin/python3 ./tools/build/get-env-var.py jlink-micro)
echo $COMMAND >> ~/.bashrc
echo $COMMAND >> ~/.zshrc
