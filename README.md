


# Compiling on Windows
## Installing compiler and libraries
### Download MSys from http://www.msys2.org
Once installed, open a MSys 64-bit terminal window and use the built in package manager to download the required packages. This could take some time.
* `pacman -Syu` - download core packages (you may then need to restart MSys and re-run this command)
* `pacman -S base-devel` - download the basic development tools
* `pacman -S mingw-w64-x86_64-gcc` download the 64 bit gcc toolchain
(Pacman is the package manager program for MSys2 and the -S option means download the specified package.)

### Download the GUI dependencies
* `pacman -S mingw-w64-x86_64-gtk3`

No MSys packages exist for the remaining packages but there are links archives containing compiled libraries and headers. Copy the contents of the archives to the base directory for the 64bit mingw compiler within the msys install directory, e.g. c:\msys64\mingw64. Note the contents of the bin directory in the archive needs to go into the c:\msys64\mingw64\bin, lib into c:\msys64\mingw64\lib, etc.
* [Adwaita Slim](https://www.dropbox.com/s/ax7rfnlzo35yu9h/adwaita-slim.zip?dl=0) (Allow overwriting of the existing settings.ini)


## Install Git and obtain a copy of the source code
* Download git for windows from the [git website](https://git-scm.com/download/win)
* Create a directory somewhere for the source code (e.g. UDP_Forwarder), open a windows terminal and `cd` to it, then clone a copy of the source code to the new directory: 
	`git clone https://github.com/plevans/UDPFwd.git`. 
	
	
## Install CMake and use it to generate build files for Eclipse

* Download and install CMake.
* Create a build directory so that the directory structure looks something like:
~~~~
	 UDP_Forwarder							<- this is the parent directory that you created to contain the source code
		|- UDPFwd 						<- This is the sub-directory cloned from github that contains all the source code
		|- eclipse_build					<- A new, empty sub-directory that will be used to build the software
~~~~
* You'll need to add the compiler bin directory to the system path as CMake needs to find the compiler and other files that were installed. Go to Control Panel->System->Advanced Settings and add `C:\msys64\mingw64\bin` (or equivalent for your install) to the system path variable.
* `C:\msys64\mingw64\bin` should contain mingw32-make.exe. If it doesnt (possible as was downloaded through Msys) get a copy of mingw32-make.exe from [here](https://www.dropbox.com/s/v4h5npv4vo6u3y2/mingw32-make.exe?dl=0) and put in this directory, or use pacman to download.
* Open *CMake GUI*, set the source and build directories to those named above
* Click 'configure' and choose to build for "Eclipse CDT4 - MinGW Makefiles"
* You may get an error message complaining that `sh.exe` is in the path. If this happens, make sure c:\msys64\usr\bin isnt on the system path.
* Hopefully, CMake will locate the compiler you just installed and the required libraries and configure the project. Possible error messages and solutions:
	* *CMake make program not found, you probably need to choose a different build tool* - See comment above about mingw32-make.exe, make sure compiler bin directory is in path and restart CMake. Clear the cache and re-configure. Also see comment below about checking correct MinGW install has been found.
	* Can't find lots of files and libraries such as headers (XXXX.h), glew, graphene, other librarie. Choose advanced options and make sure that CMake has found the correct MinGW install where all of your dependencies have been installed (probably c:\msys64\mingw64). If it has found another install it will be looking in the wrong place for the libraries and headers. Update CMake variables to point to correct MinGW or remove old versions of MinGW, restart CMake. Clear the cache and re-configure.
* Click 'generate' to generate an Eclipse project for your system.


## Eclipse and build
* Download Eclipse IDE for C/C++
* Open Eclipse and choose the base 'UDP_Forwarder' directory as the workspace.
* Import the project you just created in the 'eclipse_build' directory (File->Import->General->Existing Projects into Workspace)
* Build the project (Project->Build All)
* Run the program (you may need to find UDPFwdGUI.exe in the list of executables generated and explicity run this target the first time)

# Packet Formats
The packet formats as they are currently used are given below. These can be adapted easily as needed.
## Triphase System
`|Timestamp[64bits]|Parametervalue1[64bits]|Parametervalue2[64bits]|Parametervalue3[64bits]|Parametervalue4[64bits]|...`

* The first 64bits represent a `uint64_t` which represents a time-stamp indicating the simulation time when the parameter/signal values encoded in the packet are valid.
* Each subsequent 64 bits are a `double` representing a parameter/signal value. The first parameter/signal value maps to the first input/output on the real-time comms block in the Simulink model.
* All numbers are encoded in standard Intel x86/x86_64 format, i.e. Little Endian.

## Internet Comms
`|Timestamp[64bits]|ParameterID1[8bits]|Parametervalue1[64bits]|ParameterID2[8bits]|Parametervalue2[64bits]|ParameterID3[8bits]|Parametervalue3[64bits]|ParameterID4[8bits]|Parametervalue4[64bits]|...`

* The first 64bits are a `uint64_t` which represents a time-stamp indicating the simulation time when the parameter/signal values encoded in the packet are valid.
* Each subsequent variable pairs represent a single parameter/signal:
	* The first 8 bits are a `uint8_t` representing the parameter/signal ID (0-255). Each parameter/signal must have a unique ID that is used consistently across the distributed system.
	* The next 64 bits are a `double` representing the parameter/signal's value
* All numbers are encoded in standard Intel x86/x86_64 format, i.e. Little Endian.

## Translation
At present the Triphase system identifies individual parameter/signals values by their order in the recieved packets whereas the internet packets encode each parameter/signal is encoded with an ID. A mapping between these is needed or the Triphase rx/tx applications on the real time target need modifying the recognise the internet comms style packets (not a big issue to make this change).
	

