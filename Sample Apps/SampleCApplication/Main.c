#include <stdio.h>
#include <tchar.h>
#include <windows.h>            // For GetAsyncKeyState
#include "GRIDLinkSDK_CAPI.h"

bool g_MainDone = false;

// Example Application initialization method with call to GRIDLink SDK initialization
void ApplicationInitialize()
{
    // Initialize GRIDLink using the C calling convention.
    glInitializeGRIDLinkSDK();

    // Application Initialization
}

// Example Application shutdown method with call to GRIDLink SDK shutdown
void ApplicationShutdown()
{
    printf("\n\nApplication: Shutting down...\n");

    // Application Shutdown

    // Shutdown GRIDLink
    // It's safe to call ShutdownGRIDLinkSDK even if the SDK was not initialized.
    glShutdownGRIDLinkSDK();
}

// Example Application Main
int _tmain(int argc, _TCHAR* argv[])
{
    bool bGridEnabled;
    const char* pzCSLocation;

	ApplicationInitialize();

    // Sample C API call
    bGridEnabled = glIsGRIDEnabled();
    printf("GRID Enabled: %s\n", (bGridEnabled == true) ? "true" : "false");

    // Another sample call:

    if (glGetStorageLocation(&pzCSLocation) == 0)
    {
        printf("Grid CloudSave location: %s\n", pzCSLocation);
    }


	printf("\n\nApplication: In main application loop; Press space bar to exit...\n\n");

	// Application Main Loop
	while (!g_MainDone)
	{
		// Do application stuff here..
		if (GetAsyncKeyState(' ') != 0)
		{
			g_MainDone = true;
		}
	}    

    // Application Shutdown
	// It's safe to call ShutdownShieldXLinkSDK even if the SDK was not initialized.
	ApplicationShutdown();

	return 0;
}
