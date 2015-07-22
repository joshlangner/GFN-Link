#include <stdio.h>
#include <tchar.h>
#include <windows.h>            // For GetAsyncKeyState
#include "GFNLinkSDK_CAPI.hpp"

bool g_MainDone = false;

// Example Application initialization method with call to GFNLink SDK initialization
void ApplicationInitialize()
{
    // Initialize GFNLink using the CPP calling convention.
    GFNLinkSDK::InitializeGFNLinkSDK();

    // Application Initialization
}

// Example Application shutdown method with call to GFNLink SDK shutdown
void ApplicationShutdown()
{
    printf("\n\nApplication: Shutting down...\n");

    // Application Shutdown

    // Shutdown GFNLink
    // It's safe to call ShutdownGFNLinkSDK even if the SDK was not initialized.
    GFNLinkSDK::ShutdownGFNLinkSDK();
}

// Example Application main
int _tmain(int argc, _TCHAR* argv[])
{
    ApplicationInitialize();

	// Sample call into the GFNLink interface object:
	bool bGfnEnabled = GFNLinkSDK::Instance()->IsGFNEnabled();
	printf("GFN Enabled: %s\n", (bGfnEnabled == true) ? "true" : "false");

	// Another sample call:
	const char* pzCSLocation;
	if (GFNLinkSDK::Instance()->GetStorageLocation(&pzCSLocation) == 0)
	{
		printf("Gfn CloudSave location: %s\n", pzCSLocation);
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

