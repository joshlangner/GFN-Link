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
// C / C++ API declarations for GRID Link SDK
//
// ===============================================================================================

#ifndef GRID_LINK_SDK_CAPI_H
#define GRID_LINK_SDK_CAPI_H

#include <stddef.h>

#ifndef __cplusplus
typedef char bool;
#define false 0
#define true 1
#endif

#define GRID_LINK_SDK_VERSION 1.0

#ifdef __cplusplus
namespace GRIDLinkSDK
{
extern "C"
	{
#endif
	// ============================================================================================
	// Constants/Enums
	// ============================================================================================

    // GRIDLink Errors
    // Returned by InitializeGRIDLinkSDK and GRIDLink API methods
    typedef enum GRIDLinkError
    {
        gleSuccess = 0,
        gleGRIDDLLNotPresent,
        gleGRIDComNotEstablished,		// No controller/test application running to connect to.
        gleGRIDComError,
        gleErrorCallingDLLFunction,		// Generic DLL error - possibly due to incompatible DLL.
        gleIncompatibleVersion,
        gleUnableToAllocateMemory,
        gleInvalidParameter,
        gleInternalError
    } GRIDLinkError;

    // All Host Interface methods return a result of this type
    // Note, this must be kept in sync with typedef in IGRIDApplication.cs
    typedef enum ApplicationResult
    {
        arNotImplemented = 0,		// Developers did not implement this method
        arSuccess,					// Operation completed successfully
        arFailure					// General failure result 
    } ApplicationResult;

	// Parameter to RequestKeyboardOverlay method
	// Specifies where to display text input element on screen
	typedef enum GRIDScreenPosition
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
	} GRIDScreenPosition;

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
    // Application -> GRID SDK communication
    // The application should call these methods at the appropriate locations.

    // GRID Link initialization method. 
	// This method must be called before any other GRID Link API calls (even IsGRIDEnabled), 
	// otherwise all API calls will have no effect. 
    GRIDLinkError glInitializeGRIDLinkSDK();

	// GRID Link shutdown method. 
	// This method must be called as part of application shutdown or when GRID Link API is no longer needed.
	// Performs GRID Link shutdown logic and cleans up resources.
    void glShutdownGRIDLinkSDK();

	// Determines if application is running in GRID environment
	bool glIsGRIDEnabled();

	// Called from application when text input is needed to continue
	GRIDLinkError glRequestKeyboardOverlayOpen(GRIDScreenPosition gspPosition);

	// Called from application when necessary text input has been processed and user can continue
	GRIDLinkError glRequestKeyboardOverlayClose();

	// Request to obtain the user's GRID authentication token
	GRIDLinkError glRequestGRIDAccessToken(const char** ppchToken);

	// Provides the designated GRID managed storage location for this application
	GRIDLinkError glGetStorageLocation(const char** ppchStoragePath);

	// Notifies of completed file changes in GRID storage location
	GRIDLinkError glNotifyStorageChange();

#ifdef __cplusplus
	} // extern "C"
}
#endif


#endif GRID_LINK_SDK_CAPI_H


