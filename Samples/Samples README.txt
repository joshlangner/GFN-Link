Compiling:
All samples can be compiled using any version of Visual Studio between 2010 and 2015.

Running:
Samples can be run with or without the GFN.DLL installed. By default the dll installs as part 
of building the sample.
The DLL can be installed or removed from within Visual Studio by compiling the "InstallDll.bat" 
or "RemoveDll.bat" scripts.
This can also be done through the command line as follows:
InstallDll.bat <Platform> <Configuration>
RemoveDll.bat <Platform> <Configuration>
i.e: 
	InstallDll.bat x64 Release

Note that after compiling the RemoveDll.bat file and running the sample through Visual Studio 
you will be asked to rebuild the project. Ignore this otherwise the DLL will be installed 
again as part of the build.
