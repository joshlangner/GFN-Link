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
// This is the main interface between the Grid dll and the host application.
//
// The application developer should implement as many of these methods as they can or are
// appropriate for their application. Those methods the developer doesn't wish to implement
// should return GridHostResult::NotImplemented, as they do by default in this file.
//
// ===========================================================================================

#include "GRID_LinkSDK_CAPI.h"

/// <summary>
/// Returns the version of the application currently installed on the client machine.
/// </summary>
/// <output>
/// string representation of the application's version.
/// </output>
/// <returns>
/// Success if version known, NotImplemented if not implemented
/// </returns>
GridHostResult gsdkGetInstalledVersion(wchar_t* versionStr, int bufferLen)
{
    return GridHostResult::NotImplemented;
}

/// <summary>
/// Returns the version of the newest version available for download/patching
/// </summary>
/// <output>
/// string representation of the newest available version.
/// </output>
/// <returns>
/// Success if version found, Failure if not. NotImplemented if not implemented
/// </returns>
GridHostResult gsdkGetNewestVersion(wchar_t* versionStr, int bufferLen)
{
    return GridHostResult::NotImplemented;
}

/// <summary>
/// Initiates a patch update.
/// </summary>
/// <remarks>
/// This is an asynchronous call. The application should trigger a patch update when 
/// this call is made. When the update is complete, the application should call
/// GridApplication.SDKInterface.PatchingDone();
/// Note that it isn't necessary that the same process calls the return method,
/// so if an application needs to restart as part of the patch process, it can
/// call this one it initializes the grid SDK.
/// </remarks>
/// <returns>
/// Success if patching was started. NotImplemented if not implemented
/// </returns>
GridHostResult gsdkStartPatching()
{
    return GridHostResult::NotImplemented;
}

/// <summary>
/// Initiates a user login request
/// </summary>
/// <remarks>
/// Initiates either a native login or grid login request. 
/// This is an asynchronous call so does not need to wait until login has completed.
/// </remarks>
/// <param name="gridLogin">True if logging in through grid, false if native</param>
/// <param name="username">Username registered with native app</param>
/// <param name="authToken">Grid auth token if grid login, password if native login</param>
/// <returns>
/// Success if login is supported. NotImplemented if not implemented
/// </returns>
GridHostResult gsdkRequestUserLogin(bool gridLogin, const wchar_t* username, const wchar_t* authToken)
{
    return GridHostResult::NotImplemented;
}

/// <summary>
/// Attempts to create a new user account native for this application
/// </summary>
/// <remarks>
/// This is an asynchronous call so does not need to wait until registration has completed.
/// Only supports login through grid. The username passed will be the requested 
/// username, which will default to the grid username. For best results the app
/// should enforce unique user names only within the grid namespace.
/// The application should call
/// </remarks>
/// <param name="requestedUsername">Desired username</param>
/// <param name="authToken">Grid supplied authentication token</param>
/// <returns>
/// Success if registration is supported. NotImplemented if not implemented
/// </returns>
GridHostResult gsdkRequestUserRegistration(const wchar_t* requestedUsername, const wchar_t* authToken)
{
    return GridHostResult::NotImplemented;
}

/// <summary>
/// Requests application save data and shut down.
/// </summary>
/// <remarks>
/// If a user disconnects from Grid while using an application, the application will have 
/// no way to know this, as it will continue to run on the virtual machine. Without this,
/// Grid is forced to kill the application in order to shut it down, which is not always
/// a good idea. Implement this if you want your application to do anything special before
/// shutting down, such as saving off user data. The application should then exit.
/// </remarks>
/// <returns>
/// Success if external shutdown is supported. NotImplemented if not.
/// </returns>
GridHostResult gsdkRequestApplicationExit()
{
    return GridHostResult::NotImplemented;
}