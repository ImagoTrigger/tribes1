# Tribes

A project aimed at reconstructing the partial Tribes 1 source code from https://github.com/AltimorTASDK/TribesRebirth.

# Quickstart

1) Open Tribes.sln. This file was created using Visual Studio 2019.
2) Compile the Tribes project under the Debug configuration (x86). This build has been tested to run on a Windows 10 x64 machine.
3) Locate the output folder (~/bin/Debug/Tribes/) and copy an installation of Tribes. Version 1.11 has been tested to work.
4) Locate the output file (~/bin/Debug/Tribes/Tribes.exe) and right-click -> "Properties" -> "Compatibility" tab -> "Change high DPI settings" button -> Ensure "Override high DPI scaling behavior." is checked.
5) Locate the client preferences script (~/bin/Debug/Tribes/config/ClientPrefs.cs) and make sure the variable $pref::VideoFullScreen is assigned to "FALSE". Only windowed mode has been tested.
6) In Visual Studio you should now be able to run Tribes in the debugger.
7) Create an instance of actual Tribes (v1.11), and host a mission locally.
8) In the Debug version of Tribes you may now connect to the real Tribes server using the console (~) by typing:
```
connect("127.0.0.1:28001");
```

Alternatively, instead of steps 6-8, In the Debug instance of Tribes type in the console (~):
```
createServer(Raindance);
```
This will host a Raindance server on the Debug build. As of the time in writing this README, hosting has not been thoroughly tested.
