#include <stdio.h>
#include <tchar.h>
#include <windows.h>            // For GetAsyncKeyState
#include "GRIDLinkSDK_CAPI.hpp"

bool g_MainDone = false;

// Example Application initialization method with call to GRIDLink SDK initialization
void ApplicationInitialize()
{
    // Initialize GRIDLink using the CPP calling convention.
    GRIDLinkSDK::InitializeGRIDLinkSDK();

    // Application Initialization
}

// Example Application shutdown method with call to GRIDLink SDK shutdown
void ApplicationShutdown()
{
    printf("\n\nApplication: Shutting down...\n");

    // Application Shutdown

    // Shutdown GRIDLink
    // It's safe to call ShutdownGRIDLinkSDK even if the SDK was not initialized.
    GRIDLinkSDK::ShutdownGRIDLinkSDK();
}

// Example Application main
int _tmain(int argc, _TCHAR* argv[])
{
    ApplicationInitialize();

	// Sample call into the GRIDLink interface object:
	bool bGridEnabled = GRIDLinkSDK::Instance()->IsGRIDEnabled();
	printf("GRID Enabled: %s\n", (bGridEnabled == true) ? "true" : "false");

	// Another sample call:
	const char* pzCSLocation;
	if (GRIDLinkSDK::Instance()->GetStorageLocation(&pzCSLocation) == 0)
	{
		printf("Grid CloudSave location: %s\n", pzCSLocation);
	}

    printf("\n\nApplication: In main application loop; Press space bar to exit...\n");

    // Application Main Loop
    while (!g_MainDone)
    {
        // Do application stuff here..
        if (GetAsyncKeyState(' ') != 0)
        {
            g_MainDone = true;
        }
    }    

    ApplicationShutdown();

    return 0;
}

