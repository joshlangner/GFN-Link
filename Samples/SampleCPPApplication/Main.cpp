/* Copyright (c) 2015, NVIDIA CORPORATION. All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   * Neither the name of NVIDIA CORPORATION nor the names of its
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.
 
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS "AS IS" AND ANY
  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
  PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
  OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

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
	if (GFNLinkSDK::Instance()->GetStorageLocation(&pzCSLocation) == GFNLinkSDK::gleSuccess)
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

