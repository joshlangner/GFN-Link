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
#include <string.h>
#include "GFNLinkSDK_CAPI.h"

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
    glNotifyStorageChange();
}

void LockUserGraphicsOptions()
{
    // Doesn't do anything since our sample isn't doing anything..
    printf("Application locked options menu.\n");
}

bool SetLocale(const char* locale)
{
    // We only support en_US, so anything else returns false which will return "arNotImplemented" to GRID.
    if (strcmp(locale,"en_US") == 0)
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




