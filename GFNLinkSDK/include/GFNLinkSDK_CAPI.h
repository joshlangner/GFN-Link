// ===============================================================================================
//
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
//
// ===============================================================================================
//
// C / C++ API declarations for GFN Link SDK
//
// ===============================================================================================

#ifndef GFN_LINK_SDK_CAPI_H
#define GFN_LINK_SDK_CAPI_H

#include <stddef.h>

#ifndef __cplusplus
typedef char bool;
#define false 0
#define true 1
#endif

#define GFN_LINK_SDK_VERSION 1.0

#ifdef __cplusplus
namespace GFNLinkSDK
{
    extern "C"
    {
#endif
        // ============================================================================================
        // Constants/Enums
        // ============================================================================================

        // GFNLink Errors
        // Returned by InitializeGFNLinkSDK and GFNLink API methods
        typedef enum GFNLinkError
        {
            gleSuccess = 0,
            gleGFNDLLNotPresent = 1,
            gleGFNComNotEstablished = 2,    // No controller/test application running to connect to.
            gleGFNComError = 3,
            gleErrorCallingDLLFunction = 4, // Generic DLL error - possibly due to incompatible DLL.
            gleIncompatibleVersion = 5,
            gleUnableToAllocateMemory = 6,
            gleInvalidParameter = 7,
            gleInternalError = 8,           // Generic error on controller side, treat as unsupported
            gleUnsupportedAPICall = 9,
            gleInvalidToken = 10,
        } GFNLinkError;

        // All Host Interface methods return a result of this type
        // Note, this must be kept in sync with typedef in IGFNApplication.cs
        typedef enum ApplicationResult
        {
            arNotImplemented = 0,       // Developers did not implement this method
            arSuccess,                  // Operation completed successfully
            arFailure                   // General failure result 
        } ApplicationResult;

        // Parameter to RequestKeyboardOverlay method
        // Specifies where to display text input element on screen
        typedef enum GFNScreenPosition
        {
            gspBottom = 0,
            gspTop,
            gspLeft,
            gspRight,
            gspCenter,
            gspTopLeft,
            gspTopRight,
            gspBottomLeft,
            gspBottomRight
        } GFNScreenPosition;

        // Parameter to LockUserOptions
        // Flags indicating user's options in the application
        typedef enum UserOptions
        {
            uoNone = 0,
            uoGraphicsSettings = 0 << 1
        } UserOptions;

        // ============================================================================================
        // C API
        // ============================================================================================

        // ============================================================================================
        // Application -> GFN SDK communication
        // The application should call these methods at the appropriate locations.

        // GFN Link initialization method. 
        // This method must be called before any other GFN Link API calls (even IsGFNEnabled),
        // otherwise all API calls will have no effect. 
        GFNLinkError glInitializeGFNLinkSDK();

        // GFN Link shutdown method. 
        // This method must be called as part of application shutdown or when GFN Link API is no longer needed.
        // Performs GFN Link shutdown logic and cleans up resources.
        void glShutdownGFNLinkSDK();

        // Determines if application is running in GFN environment
        bool glIsGFNEnabled();

        // Called from application when text input is needed to continue
        GFNLinkError glRequestKeyboardOverlayOpen(GFNScreenPosition gspPosition);

        // Called from application when necessary text input has been processed and user can continue
        GFNLinkError glRequestKeyboardOverlayClose();

        // Request to obtain the user's GFN authentication token
        GFNLinkError glRequestGFNAccessToken(const char** ppchToken);

        // Request to obtain a 3rd party token
        GFNLinkError glRequest3rdPartyToken(const char* pchProviderId, const char** ppchToken);

        // Sets a 3rd party token
        GFNLinkError glSet3rdPartyToken(const char* pchProviderId, const char* pchToken);

        // Provides the designated GFN managed storage location for this application
        GFNLinkError glGetStorageLocation(const char** ppchStoragePath);

        // Notifies of completed file changes in GFN storage location
        GFNLinkError glNotifyStorageChange();

#ifdef __cplusplus
    } // extern "C"
}
#endif


#endif GFN_LINK_SDK_CAPI_H
