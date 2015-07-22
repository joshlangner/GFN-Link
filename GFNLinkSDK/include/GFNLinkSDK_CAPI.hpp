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
// C++ API for Gfn SDK
// This defines the main C++ interface objects. See GFN_LinkSDK_cAPI.h for constants, typedefs 
// and enums.
//
// ===============================================================================================

#ifndef GFN_LINK_SDK_CPPAPI_H
#define GFN_LINK_SDK_CPPAPI_H

#include <stddef.h>
#include "GFNLinkSDK_CAPI.h"

namespace GFNLinkSDK
{
	// ============================================================================================
	// GfnLink C++ API
	// ============================================================================================

	// GFN Link initialization method. 
	// This method must be called before any other GFN Link API calls (even IsGFNEnabled), 
	// otherwise all API calls will have no effect. 
	// Sets up communication and initializes both the IGFNLink and IGFNApplication objects
	GFNLinkError InitializeGFNLinkSDK();

	// GFN Link shutdown method. 
	// This method must be called as part of application shutdown or when GFN Link is no longer 
    // needed.
	// Performs GFN Link shutdown logic and cleans up resources.
	void ShutdownGFNLinkSDK();

	// ============================================================================================
	// Interface object for communication with GFN
	// Application -> GFN communication
	// Application developers should call these methods at the appropriate locations in their code
	class IGFNLink
	{
	public:
		/// <summary>
		/// Query to determine if running in a GFN environment or not
		/// </summary>
		/// <returns>true if running in GFN environment, false otherwise</returns>
		virtual bool IsGFNEnabled() = 0;

		/// <summary>
		/// Called when text input is desired. Pops up a native keyboard for text entry.
		/// </summary>
		/// <params>gspPosition - screen location for keyboard popup</params>
        /// <returns>gleSuccess on Success, error code otherwise</returns>
		virtual GFNLinkError RequestKeyboardOverlayOpen(GFNScreenPosition gspPosition = gspBottom) = 0;

		/// <summary>
		/// Called when text input is complete. Closes any keyboard popup present. Safe to call in
		/// all cases (regardless of status of keyboard popup).
		/// </summary>
        /// <returns>gleSuccess on Success, error code otherwise</returns>
		virtual GFNLinkError RequestKeyboardOverlayClose() = 0;

		/// <summary>
		/// Obtain a user specific GFN authentication token for backend user authentication.
		/// GFNLink manages memory, it is not necessary to preallocate a buffer.
		/// </summary>
		/// <params>ppchToken (out) - pointer to token returned by this method</params>
		/// <returns>gleSuccess on Success, error code otherwise</returns>
        virtual GFNLinkError RequestGFNAccessToken(const char** ppchToken) = 0;

		/// <summary>
		/// Provides a storage location for GFN cloud save data (persistant user data)
		/// </summary>
        /// <params>ppchStoragePath (out) - Path to storage directory</params>
        /// <returns>gleSuccess on Success, error code otherwise</returns>
        virtual GFNLinkError GetStorageLocation(const char** ppchStoragePath) = 0;

		/// <summary>
		/// Notified GFN that saving of data is complete and that data should be uploaded.
		/// </summary>
        /// <returns>gleSuccess on Success, error code otherwise</returns>
		virtual GFNLinkError NotifyStorageChange() = 0;
	};

	// This returns an instantiated IGFNLink object, from which the above methods can be called.
	IGFNLink* Instance();

	// ============================================================================================
	// Interface object for communication with application
	// GFN -> Application communication
	// Application developers must fill in provided GFNApplication class implementation.
    // This object is instantiated when InitializeGFNLinkSDK() is called.
	class IGFNApplication
	{
	public:
		// The application must provide callbacks for any features it plans to implement.
		// The application must implement or stub these methods

		/// <summary>
		/// Request to pause application activity
		/// </summary>
		/// <returns>
		/// arSuccess - application activity was successfully paused
		/// arFailure - application activity couldn't be paused
		/// arNotImplemented
		/// </returns>
		virtual ApplicationResult RequestApplicationPause() { return arNotImplemented; };

		/// <summary>
		/// Request to save user progress
		/// </summary>
		/// <returns>
		/// arSuccess - application saved user's progress
		/// arFailure - application couldn't save user's progress
		/// arNotImplemented
		/// </returns>
		virtual ApplicationResult RequestApplicationSave() { return arNotImplemented; };

		/// <summary>
		/// Request to exit application
		/// </summary>
		/// <returns>
		/// arSuccess - application exited
		/// arFailure - application couldn't exit
		/// arNotImplemented
		/// </returns>
		virtual ApplicationResult RequestApplicationExit() { return arNotImplemented; };

		/// <summary>
		/// Used by GFN to disable certain user options that may impact their GFN experience.
		/// </summary>
		/// <params>uoOptions - flags for which options to disable</params>
		/// <returns>
		/// arSuccess - application successfully disabled specified user options
		/// arFailure - application failed to disable specified user options
		/// arNotImplemented
		/// </returns>
		virtual ApplicationResult LockUserOptions(UserOptions uoOptions) { return arNotImplemented; };

		/// <summary>
		/// Set application's locale according to specified language code.
		/// Follows ISO 639-1 and ISO 3166-1 standards.
		/// </summary>
		/// <params>pchlanguageCode - language code string "<la>-<CO>"</params>
		/// <returns>
		/// arSuccess - application set specified language
		/// arFailure -  application failed to set specified language
		/// arNotImplemented
		/// </returns>
		virtual ApplicationResult SetLocale(const char* pchlanguageCode) { return arNotImplemented; };

		/// <summary>
		/// Determines if application requires an update or patch.
		/// </summary>
		/// <params>pbUpdate (out) - set to true if an update is required, false otherwise</params>
		/// <returns>
		/// arSuccess - successfully determined if an update is required or not
		/// arFailure - failed to determine if updated is required or not
		/// arNotImplemented
		/// </returns>
		virtual ApplicationResult IsUpdateRequired(bool* pbUpdate) { return arNotImplemented; };
	};

	// ===========================================================================================
	// Advanced initialization method
	// This takes an IGFNApplication implementation object, so allows an object defined in developer
	// code to be used as the Application interface object. bApplicationManagedMemory should be set
	// to true if the application plans to delete the object, otherwise it is deleted when 
	// ShutdownGFNLinkSDK() is called.
	GFNLinkError InitializeGFNLinkSDK(IGFNApplication* applicationObj, bool bApplicationManagedMemory = false);
}

#endif GFN_LINK_SDK_CPPAPI_H
