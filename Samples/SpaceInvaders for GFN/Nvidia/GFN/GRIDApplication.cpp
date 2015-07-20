/*
Author: Mohammad Mottaghi mamad@cs.duke.edu (mmottaghi@nvidia.com)
Date: July 14, 2015
*/

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
// This is the main C++ interface between the GRID DLL and the host application.
//
// The application developer should implement as many of these methods as they can or are
// appropriate for their application. Those methods the developer doesn't wish to implement
// should return ApplicationResult::NotImplemented, as they do by default in this file.
//
// A fresh stub file that you can use in your application can be found under:
// GRIDLinkSDK\stubs\C++ stubs\
//
// ===========================================================================================

#include "GRIDLinkSDK_CAPI.hpp"

//NVIDIA 
extern bool			gfn_game_paused;
extern bool			gfn_game_quit;
extern bool			gfn_game_save;

namespace GRIDLinkSDK
{
	class GRIDApplication : public IGRIDApplication
	{
		/// <summary>
		/// Request to pause application activity
		/// </summary>
		/// <returns>
		/// arSuccess - application activity was successfully paused
		/// arFailure - application activity couldn't be paused
		/// arNotImplemented
		/// </returns>
		ApplicationResult GRIDApplication::RequestApplicationPause()
		{
			gfn_game_paused = !gfn_game_paused;
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
		ApplicationResult GRIDApplication::RequestApplicationSave()
		{
			gfn_game_save = true;
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
		ApplicationResult GRIDApplication::RequestApplicationExit()
		{
			gfn_game_quit = true;
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
		ApplicationResult GRIDApplication::LockUserOptions(UserOptions uoOptions)
		{
			ApplicationResult res = arNotImplemented;
			return res;
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
		ApplicationResult GRIDApplication::SetLocale(const char* pchlanguageCode)
		{
			ApplicationResult res = arFailure;
			return res;
		}

		/// <summary>
		/// Determines if application requires an update or patch.
		/// </summary>
		/// <returns>
		/// arSuccess - successfully determined if an update is required or not
		/// arFailure - failed to determine if updated is required or not
		/// arNotImplemented
		/// </returns>
		ApplicationResult GRIDApplication::IsUpdateRequired(bool* pbUpdate)
		{
			*pbUpdate = false;
			ApplicationResult res = arSuccess;
			return res;
		}
	};

	// Application wrapper for Grid initialization. This calls the advanced GRID initialization 
	// method with a newly constructed GRIDApplication object. The signature for this is declared
	// in GRIDLinkSDK_CAPI.hpp, but it is defined here due to the scoping of GRIDApplication.
	// If you want to manage your own GRIDApplication object memory, you should call 
	// InitializeGRIDLinkSDK directly and pass true for bApplicationManagedMemory.
	GRIDLinkError InitializeGRIDLinkSDK()
	{
		return InitializeGRIDLinkSDK(new GRIDApplication(), false);
	}
}