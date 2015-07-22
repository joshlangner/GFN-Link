// ===============================================================================================
//
// Copyright 2013-2015 NVIDIA Corporation.  All rights reserved.
//
// Please refer to the NVIDIA end user license agreement (EULA) associated with this source code 
// for terms and conditions that govern your use of this software. Any use, reproduction, 
// disclosure, or distribution of this software and related documentation outside the terms of the
// EULA is strictly prohibited.
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
        gleGFNDLLNotPresent,
        gleGFNComNotEstablished,		// No controller/test application running to connect to.
        gleGFNComError,
        gleErrorCallingDLLFunction,		// Generic DLL error - possibly due to incompatible DLL.
        gleIncompatibleVersion,
        gleUnableToAllocateMemory,
        gleInvalidParameter,
        gleInternalError
    } GFNLinkError;

    // All Host Interface methods return a result of this type
    // Note, this must be kept in sync with typedef in IGFNApplication.cs
    typedef enum ApplicationResult
    {
        arNotImplemented = 0,		// Developers did not implement this method
        arSuccess,					// Operation completed successfully
        arFailure					// General failure result 
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
		uoNone				= 0,
		uoGraphicsSettings	= 0 << 1
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

	// Provides the designated GFN managed storage location for this application
	GFNLinkError glGetStorageLocation(const char** ppchStoragePath);

	// Notifies of completed file changes in GFN storage location
	GFNLinkError glNotifyStorageChange();

#ifdef __cplusplus
	} // extern "C"
}
#endif


#endif GFN_LINK_SDK_CAPI_H


