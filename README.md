# SW0000_Folder_Template
This project is based on SW0498 branch feature/switch-to-container

Here you should enter some description for your project...

The bootloader s/w PID is SWXXXX.

## Open an existing project you have already opened once
- Make sure Docker is running
- Right-click on Visual Studio
- Find the pinned folder setup the first time you opened the project

## Open an existing project setup with this template for the first time
### Step 1: Software installation
- Install Docker and run it
    - https://www.docker.com/
-	Visual Studio Code
    - https://visualstudio.microsoft.com/
    - Open VS Code and install the following extension
        -	Docker: Make it easy to create, manage, and debug containers
        -	Dev Containers: allow to run VS code directly from inside a Docker container
- Install Ubuntu wsl
    - open a windows command line
    - Type "wsl --install -d Ubuntu"
        - this will take a few minutes...
    - Type "wsl -s Ubuntu"

### Step 2: Open Visual Studio with the dev container
- Make sure Docker Desktop is running
- Open Visual Studio
- Open the dev container
    - ctrl+shift+p
    - "Dev Containers: Clone Repository in Named Container Volume..."
    - select github ("Clone a repository from GitHub in a Container Volume")
    - allow vs code to login if not already allowed
    - select your new repository
    - select the branch you are interested in
    - enter the volume name to a meaningful name (like sw0000-folder-template-volume)
    - enter the target folder name (like SW0000_Folder_Template)
    - let it do its thing ! It will take a few minutes...
- pin this folder to open vs code directly there later
    - right-click on VS code in your task bar
    - locate the folder you just opened
    - pin it
    - now you can easily open it whenever by right-clicking on vs code and clicking on that folder
- setup Git user name and email in your container:
    - open a new terminal in VS Code
    - Type:
        git config --global user.email "you@example.com"
    - Type:
        git config --global user.name "Your Name"
- Test out the build command: .scripts/build.py release

### Open the dev container once initial setup is done
- Method 1 (if pinned): 
    - Right click on VS Code
    - Select the project
- Method 2: 
    - Open VS Code
    - On the left side, select "Remote Explorer"
    - Click on your project to open it

### Debugger setup
To run the code using a JLink debugger:
- ensure your micro is connected to a JLink device
- right-click on the file tools/jlink/JLinkGDBServer.bat, then press download
- in Windows, double click on the downloaded bat file, it should connect to the micro properly
- In VS Code, go to the "Run and Debug" section, then press the "Start Debugging" for the "JLink Debugger" option

## Create new project with MCU Expresso
### Step 1: Software installation
- Install Docker and run it
    - https://www.docker.com/
-	Visual Studio Code
    - https://visualstudio.microsoft.com/
    - Open VS Code and install the following extension
        -	Docker: Make it easy to create, manage, and debug containers
        -	Dev Containers: allow to run VS code directly from inside a Docker container
- Install python 3.10 or up
    - https://www.python.org/downloads/
- Install Ubuntu wsl
    - open a windows command line
    - Type "wsl --install -d Ubuntu"
        - this will take a few minutes...
    - Type "wsl -s Ubuntu"
- Install MCU Expresso
    - https://www.nxp.com/design/software/development-software/mcuxpresso-software-and-tools-/mcuxpresso-integrated-development-environment-ide:MCUXpresso-IDE
        - you will need a login with nxp website


### Step 2: Create repository
- Go to https://github.com/onedometic/SW0000_Folder_Template/tree/master
- click on "Use this template"->"Create a new repository"
- Enter the repository name and description
- click on "Create repository"


### Step 3: Add the sdk files (Using MCU Expresso)
- Clone the new repository on your machine
- Open MCU Expresso
- Click on File->New->New C/C++ Project
- Setup your project as needed and place it inside your new repository.
    - project should not use redlib for its standard as it is a NXP specific library. Use newlib or newlib_nano (smaller footprint) instead
- build.toml:
    - update project name (project_name)
    - update JLink micro (jlink_micro): this is the name of the micro using the JLink tool
    - update pid, boot pid
    - update versions (regular, boot and database)
    - update application address and field flashing buffer address
- tools/jlink/JLinkGDBServer.bat
    - update how the JLink must connect to your micro
        - normally only the device must be updated to the JLink micro
- build the project once
    - in the build directory, find the linker .ld file
    - if there are multiple, combine them into one
        - you may need to change the library used to instead rely on not MCU-Expresso specific library
    - copy it into tools/build
    - rename it to the project name set in the previous step (project_name.ld)
- commit and push the changes to the repository


### Step 4: Open Visual Studio with the dev container
- Make sure Docker Desktop is running
- Open Visual Studio
- Open the dev container
    - ctrl+shift+p
    - "Dev Containers: Clone Repository in Named Container Volume..."
    - select github ("Clone a repository from GitHub in a Container Volume")
    - allow vs code to login if not already allowed
    - select your new repository
    - select the branch you are interested in
    - enter the volume name to a meaningful name (like sw0000-folder-template-volume)
    - enter the target folder name (like SW0000_Folder_Template)
    - let it do its thing ! It will take a few minutes...
- pin this folder to open vs code directly there later
    - right-click on VS code in your task bar
    - locate the folder you just opened
    - pin it
    - now you can easily open it whenever by right-clicking on vs code and clicking on that folder
- setup Git user name and email in your container:
    - open a new terminal in VS Code
    - Type:
        git config --global user.email "you@example.com"
    - Type:
        git config --global user.name "Your Name"


### Step 5: Specify small details to compile your application
-   add CMake files in the folder created by MCU Expresso
    - set their dependency correctly (will depend on SDK version and features provided)
-	ReadME: update to match your system
-	CMakeLists.txt: 
    -	update desired nmea version from library, 
    -	update desired hal port to match your mcu, 
    -	setup driver lib (library from MCU expresso needed for the hal drivers), 
    -	setup drivers include (folders to find those libraries), 
    -	add folders created by MCU expresso, 
    -	add file containing the application main created by MCU expresso, 
    -	add all libraries needed (subfolder created by CMake)
- .VS CODE folder
    -	.vscode/launch.json:
        -	Update "svdFile"
            - In MCU Expresso, this file is an xml file created with the project when the proper option in "Other" is selected
            - the file should be renamed to end with .svd
-	Tools/build folder
    - move the bootloader s19 file in this folder so the post-build can create the combined s19 file
-	Tools/toolchain
    - toolchain_armgnu.cmake: 
        - get the full build options from MCU Expresso>project properties>C/C++ Build>Settings>Tool Settings>MCU C Compiler
            - get both the release and debug build options
        - get the full linker options from MCU Expresso>project properties>C/C++ Build>Settings>Tool Settings>MCU Linker
            - get both the release and debug build options
        - update generic flags CMAKE_C_FLAGS:
            - place there the flags that are the same between the release and the build options
        - update build type specific flags CMAKE_C_FLAGS_RELEASE / CMAKE_C_FLAGS_DEBUG
            - place there the flags that are build type dependant
        - update linker flag CMAKE_EXE_LINKER_FLAGS
            - place there the flags that are the same between the release and the build options
            - Make sure to replace the -Map file by ${LINKER_MAP} and -T file by ${LINKER_FILE}
        - update build type specific linker flags CMAKE_EXE_LINKER_FLAGS_RELEASE / CMAKE_EXE_LINKER_FLAGS_DEBUG
            - place there the flags that are build type dependant

## Build and debug
Here are the commands to clean and build your project:
- .scripts/clean.sh : will clean your build folder
- .scripts/build.sh debug : will create a debug version of your application in /build/debug/
- .scripts/build.sh release : will create a release version of your application in /build/release/

# Todo
- how to do the s19 to sap conversion directly in Linux Docker
    - currently not possible, see last line in following article: https://www.pemicro.com/blog/index.cfm?post_id=253 
    - the task for that will be commented out in the post-build.py
    - for now, it needs to be done manually in Windows

