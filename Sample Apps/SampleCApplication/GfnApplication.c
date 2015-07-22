// ===========================================================================================
//
// Copyright 2013-2015 NVIDIA Corporation.  All rights reserved.
//
// Please refer to the NVIDIA end user license agreement (EULA) associated
// with this source code for terms and conditions that govern your use of
// this software. Any use, reproduction, disclosure, or distribution of
// this software and related documentation outside the terms of the EULA
// is strictly prohibited.
//
// ===========================================================================================
//
// This is the main interface between the Grid dll and the host application.
//
// The application developer should implement as many of these methods as they can or are
// appropriate for their application. Those methods the developer doesn't wish to implement
// should return ApplicationResult::NotImplemented, as they do by default in this file.
//
// ===========================================================================================

#include "GRIDLinkSDK_CAPI.h"
#include "SampleModule.h"

/// <summary>
/// Request to pause application activity
/// </summary>
/// <returns>
/// arSuccess - application activity was successfully paused
/// arFailure - application activity couldn't be paused
/// arNotImplemented
/// </returns>
ApplicationResult glRequestApplicationPause()
{
    Pause();
	return arSuccess;
}

/// <summary>
/// Request to save user progress
/// </summary>
/// <returns>
/// arSuccess - application saved user's progress
/// arFailure - application couldn't save user's progress
/// arNotImplemented
/// </returns>
ApplicationResult glRequestApplicationSave()
{
    SaveData();
	return arSuccess;
}

/// <summary>
/// Request to exit application
/// </summary>
/// <returns>
/// arSuccess - application exited
/// arFailure - application couldn't exit
/// arNotImplemented
/// </returns>
ApplicationResult glRequestApplicationExit()
{
	Quit();
	return arSuccess;
}

/// <summary>
/// Used by GRID to disable certain user options that may impact their GRID experience.
/// </summary>
/// <returns>
/// arSuccess - application successfully disabled specified user options
/// arFailure - application failed to disable specified user options
/// arNotImplemented
/// </returns>
ApplicationResult glLockUserOptions(UserOptions uoOptions)
{
    LockUserGraphicsOptions();
	return arSuccess;
}

/// <summary>
/// Set application's locale according to specified language code.
/// Follows ISO 639-1 and ISO 3166-1 standards.
/// </summary>
/// <returns>
/// arSuccess - application set specified language
/// arFailure -  application failed to set specified language
/// arNotImplemented
/// </returns>
ApplicationResult glSetLocale(const char* pchlanguageCode)
{
    SetLocale(pchlanguageCode);
	return arSuccess;
}

/// <summary>
/// Determines if application requires an update or patch.
/// </summary>
/// <returns>
/// arSuccess - successfully determined if an update is required or not
/// arFailure - failed to determine if updated is required or not
/// arNotImplemented
/// </returns>
ApplicationResult glIsUpdateRequired(bool* pbUpdate)
{
    *pbUpdate = IsCriticalUpdateRequired();
	return arSuccess;
}