Copyright © 2013-2015 NVIDIA Corporation. All rights reserved.

The GRIDLink SDK package includes the following:

### GRIDLinkSDK\dll:            
* Win32 (x86) and x64 GRID.dlls The dll needs to be placed next to your game executable in order to enable communication with the GRID backend.

### GRIDLinkSDK\include         
* C (.h) and C++ (.hpp) header files your application will need to include in order to access the GRIDLink API.

### GRIDLinkSDK\lib             
* GRIDLink static library files, built with various build configurations. 
* GRIDLinkMD.lib - Uses MultiThreadedDll CRT linkage
* GRIDLinkMT.lib - Uses MultiThreaded CRT linkage

### GRIDLinkSDK\props
* GRIDLink props files to include in your application; Adding this will automatically set up include and lib paths.
* Use GRIDLinkSDK.props if you're using MultiThreadedDll CRT linkage
* Use GRIDLinkSDKMT.props if you're using MultiThreaded CRT linkage

### GRIDLinkSDK\stubs
* Stub files you can add to your application in order to meet the minimal integration requirements.
* You should fill in these stubs with calls into your application in order to implement the required functionality.
* Use C Stubs for C style calls
* Use C++ Stubs for C++ style calls
* Use .NET Stubs for C#/.NET

### Simulator
* The simulator acts as the server for GRID applications (e.g. Samples). It simulates the GRID environment and responds to the request made by GRID.dll. This also includes a sample IDM server for Account Federation Samples. 

### Samples 
* SampleCApplication - illustrates a minimal C implementation
* SampleCPPApplication - illustrates a minimal console-based C++ implementation
* SampleCPPGUIApplication - illustrates a C++ GUI-based implementation with Account Federation 

See https://github.com/camify/GFN-Link/wiki for more details.