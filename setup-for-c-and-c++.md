## Setup C & C++ Compiler on Windows OS

 1. Download and Install **MSYS2**: MSYS2 is a package manager that sets up an environment to build Windows-based software applications.
	 - Download the MSYS2 installer [[link](https://www.msys2.org/)]
	 - Double-click the executable and accept the default options to install (in `C:\msys64`)
	 - After installation, an **MSYS** shell (terminal) will open.
 2. Update the package database.
	 - Issue the command `pacman -Syu` in the **MSYS** shell.
	 - When prompted, press `Y` to accept
 3. Reopen **MSYS** shell (Start > MSYS2 MSYS) and update the core packages.
	 - Issue the command `pacman -Su`
	 - Note: You may also have to issue `pacman -Sy` if prompted
 4. Install **gcc** (for C) and **g++** (for C++) compilers.
	 - Open **MinGW x64** shell (Start > MSYS2 MinGW x64)
	 - Issue the command `pacman -S mingw-w64-x86_64-gcc` to install the compilers
 5. Install **gdb** debugger.
	 - In the same terminal, issue the command `pacman -S mingw-w64-x86_64-gdb`
 6. Add `bin` directory of MinGW x64 install location (default location is `C:\msys64\mingw64\bin`) to the **Path** Environment Variable
	 - See [here to add a directory to Path](https://www.howtogeek.com/118594/how-to-edit-your-system-path-for-easy-command-line-access/)
 7. Verify installation
	 - Open a new terminal window and issue the following commands:
		```
		gcc --version
		g++ --version
		gdb --version
		```

## Write, Compile, and Test Sample C Code

 1. In any text editor, enter the following code:
	```
	#include  <stdio.h>

	int  main(){
		printf("Hello World in C!");
		return  0;
	}
	```
 2. Save the file as `HelloWorld.c`
 3. Open a terminal in the same directory and issue the following commands:
	```
	gcc HelloWorld.c -o a.out
	a.out
	```
 4. You should see the result as follows:
	`Hello World in C!`

## Write, Compile, and Test Sample C++ Code

 1. In any text editor, enter the following code:
	```
	#include  <iostream>
	using namespace std;

	int  main(){
		cout << "Hello World in C++!";
		return  0;
	}
	```
 2. Save the file as `HelloWorld.cpp`
 3. Open a terminal in the same directory and issue the following commands:
	```
	g++ HelloWorld.cpp -o a.out
	a.out
	```
 4. You should see the result as follows:
	`Hello World in C++!`



*Source: For a complete set of instructions, see [here](https://www.freecodecamp.org/news/how-to-install-c-and-cpp-compiler-on-windows/)* 