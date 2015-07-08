#include <stdio.h>
#include <string.h>
#include "GRIDLinkSDK_CAPI.hpp"

extern bool g_MainDone;

void Quit()
{
    printf("Application exiting..\n");
    g_MainDone = true;
}

void Pause()
{
    // Doesn't do anything since our sample isn't doing anything..
    printf("Application paused..\n");
}

void SaveData()
{
    // Doesn't really do much since our sample isn't really saving data, but we will
    // notify GRID that storage has "changed".
    printf("Application saved data.\n");
    GRIDLinkSDK::Instance()->NotifyStorageChange();
}

void LockUserGraphicsOptions()
{
    // Doesn't do anything since our sample isn't doing anything..
    printf("Application locked options menu.\n");
}

bool SetLocale(const char* locale)
{
    // It would be best if this was implemented without having to restart the application, but a restart is possible 
    // to implement by returning arFailure to GRID and restarting the application. GRID will retry once the application
    // restarts.

    // We only support en_US, so anything else returns false which will return "arNotImplemented" to GRID.
    if (strcmp(locale, "en_US") == 0)
    {
        printf("Application changed localization settings.\n");
        return true;
    }
    return false;
}

bool IsCriticalUpdateRequired()
{
    // This sample app has no versioning or updates..
    printf("Application is up to date.\n");
    return false;
}




