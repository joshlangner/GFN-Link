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

using System;
using System.Runtime.InteropServices;

namespace GFNLinkSDK.Managed
{
    /*This base class provides the functionality for interfacing with the unmanaged
     * dll to communicate with the GFN network*/
    public abstract class BaseGFNApplication : IDisposable
    {
        #region Public Methods

        /// <summary>
        /// This method disposes of our call backs after the GFN application is done
        /// </summary>
        public void Dispose()
        {
            RemoveCallBacks();
            s_application = null;
            GC.SuppressFinalize(this);

        }

        // GFN Link initialization method. 
        // This method must be called before any other GFN Link API calls (even IsGFNEnabled), 
        // otherwise all API calls will have no effect. 
        // Sets up communication and initializes both the IGFNLink and IGFNApplication objects
        public static GFNLinkError InitializeGFNLinkSDK(BaseGFNApplication application)
        {
            GFNLinkError error = GFNLinkError.gleErrorCallingDLLFunction;

            if (s_application != null)
            {
                s_application.RemoveCallBacks();
            }

            s_application = application;

            try
            {
                error = CallInitializeGFNLinkSDK();

                if (s_application != null)
                {
                    s_application.AddCallBacks();
                }
                
            }
            catch(System.Exception)
            {
                error = GFNLinkError.gleErrorCallingDLLFunction;
            }

            return error;
        }

        // GFN Link shutdown method. 
        // This method must be called as part of application shutdown or when GFN Link is no longer 
        // needed.
        // Performs GFN Link shutdown logic and cleans up resources.
        public static void ShutdownGFNLinkSDK()
        {
            try
            {
                CallShutdownGFNLinkSDK();
                s_application.Dispose();
            }
            catch(System.Exception)
            {
                s_application = null;
            }
        }

        /// <summary>
        /// Query to determine if running in a GFN environment or not
        /// </summary>
        /// <returns>true if running in GFN environment, false otherwise</returns>
        public static bool IsGFNEnabled()
        {
            bool ret = false;

            try
            {
                ret = (CallIsGFNEnabled() != 0);
            }
            catch(System.Exception)
            {

            }

            return ret;
        }

        /// <summary>
        /// Called when text input is desired. Pops up a native keyboard for text entry.
        /// </summary>
        /// <params>gspPosition - screen location for keyboard popup</params>
        /// <returns>gleSuccess on Success, error code otherwise</returns>
        public static GFNLinkError RequestKeyboardOverlayOpen(GFNScreenPosition gspPosition)
        {
            GFNLinkError error = GFNLinkError.gleErrorCallingDLLFunction;

            try
            {
                error = CallRequestKeyboardOverlayOpen(gspPosition);
            }
            catch
            {

            }

            return error;
        }

        /// <summary>
        /// Called when text input is complete. Closes any keyboard popup present. Safe to call in
        /// all cases (regardless of status of keyboard popup).
        /// </summary>
        /// <returns>gleSuccess on Success, error code otherwise</returns>
        public static GFNLinkError RequestKeyboardOverlayClose()
        {
            GFNLinkError error = GFNLinkError.gleErrorCallingDLLFunction;

            try
            {
                error = CallRequestKeyboardOverlayClose();
            }
            catch
            {

            }

            return error;
        }

        /// <summary>
        /// Obtain a user specific GFN authentication token for backend user authentication.
        /// GFNLink manages memory, it is not necessary to preallocate a buffer.
        /// </summary>
        /// <params>ppchToken (out) - pointer to token returned by this method</params>
        /// <returns>gleSuccess on Success, error code otherwise</returns>
        public static GFNLinkError RequestGFNAccessToken(ref string accessToken)
        {
            GFNLinkError error = GFNLinkError.gleErrorCallingDLLFunction;

            var ptr = IntPtr.Zero;

            try
            {
                error = CallRequestGFNAccessToken(ref ptr);
                accessToken = Marshal.PtrToStringAnsi(ptr);
            }
            catch(System.Exception)
            {
                    
            }

            return error;
        }

        /// <summary>
        /// Provides a storage location for GFN cloud save data (persistant user data)
        /// </summary>
        /// <params>ppchStoragePath (out) - Path to storage directory</params>
        /// <returns>gleSuccess on Success, error code otherwise</returns>
        public static GFNLinkError GetStorageLocation(ref string storagePath)
        {
            GFNLinkError error = GFNLinkError.gleErrorCallingDLLFunction;

            var ptr = IntPtr.Zero;

            try
            {
                error = CallGetStorageLocation(ref ptr);
                storagePath = Marshal.PtrToStringAnsi(ptr);
            }
            catch(System.Exception)
            {
                    
            }

            return error;
        }

        /// <summary>
        /// Notified GFN that saving of data is complete and that data should be uploaded.
        /// </summary>
        /// <returns>gleSuccess on Success, error code otherwise</returns>
        public static GFNLinkError NotifyStorageChange()
        {
            GFNLinkError error = GFNLinkError.gleErrorCallingDLLFunction;

            try
            {
                error = CallNotifyStorageChange();
            }
            catch
            {

            }

            return error;
        }

        #endregion

        #region Setup/Shutdown

        /// <summary>
        /// When this class is finalized remove the callbacks if it hasn't already been done
        /// </summary>
        ~BaseGFNApplication()
        {
            RemoveCallBacks();
            s_application = null;
        }

        /// <summary>
        /// This method adds our call backs to the native side
        /// </summary>
        protected void AddCallBacks()
        {
            try
            {
                SetApplicationPauseCallBack(RequestApplicationPauseCallBack);

                SetRequestApplicationSaveCallBack(RequestApplicationSaveCallBack);

                SetRequestApplicationExitCallBack(RequestApplicationExitCallBack);

                SetLockUserOptionsCallBack(LockUserOptionsCallBack);

                SetSetLocaleCallBack(SetLocaleCallBack);

                SetIsUpdateRequiredCallBack(IsUpdateRequiredCallBack);
            }
            catch
            {
                s_application = null;
            }

        }

        /// <summary>
        /// This method removes our call backs that we have established
        /// </summary>
        protected void RemoveCallBacks()
        {
            if (s_application != null)
            {
                try
                {
                    SetApplicationPauseCallBack(null);

                    SetRequestApplicationSaveCallBack(null);

                    SetRequestApplicationExitCallBack(null);

                    SetLockUserOptionsCallBack(null);

                    SetSetLocaleCallBack(null);

                    SetIsUpdateRequiredCallBack(null);
                }
                catch
                {

                }
            }
        }

        #endregion

        #region Virtual Methods

        /// <summary>
        /// Request to pause application activity
        /// </summary>
        /// <returns>
        /// arSuccess - application activity was successfully paused
        /// arFailure - application activity couldn't be paused
        /// arNotImplemented - application did not implement this method
        /// </returns>
        protected virtual ApplicationResult RequestApplicationPause()
        {
            return ApplicationResult.arNotImplemented;
        }

        /// <summary>
        /// Request to save user progress
        /// </summary>
        /// <returns>
        /// arSuccess - application saved user's progress
        /// arFailure - application couldn't save user's progress
        /// arNotImplemented - not implemented by the developer
        /// </returns>
        protected virtual ApplicationResult RequestApplicationSave()
        {
            return ApplicationResult.arNotImplemented;
        }

        /// <summary>
        /// Request to exit application
        /// </summary>
        /// <returns>
        /// arSuccess - application exited
        /// arFailure - application couldn't exit
        /// arNotImplemented - not implemented by the developer
        /// </returns>
        protected virtual ApplicationResult RequestApplicationExit()
        {
            return ApplicationResult.arNotImplemented;
        }

        /// <summary>
        /// Used by GFN to disable certain user options that may impact their GFN experience.
        /// </summary>
        /// <returns>
        /// arSuccess - application successfully disabled specified user options
        /// arFailure - application failed to disable specified user options
        /// arNotImplemented - not implemented by the developer
        /// </returns>
        protected virtual ApplicationResult LockUserOptions(UserOptions uoOptions)
        {
            return ApplicationResult.arNotImplemented;
        }

        /// <summary>
        /// Set application's locale according to specified language code.
        /// Follows ISO 639-1 and ISO 3166-1 standards.
        /// </summary>
        /// <returns>
        /// arSuccess - application set specified language
        /// arFailure -  application failed to set specified language
        /// arNotImplemented - not implemented by the developer
        /// </returns>
        protected virtual ApplicationResult SetLocale(string pchlanguageCode)
        {
            return ApplicationResult.arNotImplemented;
        }

        /// <summary>
        /// Determines if application requires an update or patch.
        /// </summary>
        /// <returns>
        /// arSuccess - successfully determined if an update is required or not
        /// arFailure - failed to determine if updated is required or not
        /// arNotImplemented - not implemented by the developer
        /// </returns>
        protected virtual ApplicationResult IsUpdateRequired(ref bool pbUpdate)
        {
            return ApplicationResult.arNotImplemented;
        }

        #endregion

        #region Delegates

        //These delegates are also referenced in the unmanaged C++ dll.  If changing here ensure changes match there
        protected delegate ApplicationResult ApplicationStatusDelegate();

        protected delegate ApplicationResult LockUserOptionsDelegate(UserOptions uoOptions);

        protected delegate ApplicationResult SetLocaleDelegate([In, MarshalAs(UnmanagedType.LPStr)]string pchlanguageCode);

        protected delegate ApplicationResult IsUpdateRequiredDelegate(ref int pUpdate);

        #endregion

        #region CallBacks

        /// <summary>
        /// This call back is call by the native side when GFN wants to pause the game
        /// </summary>
        /// <returns>
        /// arSuccess - application activity was successfully paused
        /// arFailure - application activity couldn't be paused
        /// arNotImplemented - application did not implement this method
        /// </returns>
        private static ApplicationResult RequestApplicationPauseCallBack()
        {
            ApplicationResult result = ApplicationResult.arNotImplemented;

            if(s_application != null)
            {
                result = s_application.RequestApplicationPause();
            }

            return result;
        }

        /// <summary>
        /// This call back is call by the native side when GFN wants to save the game
        /// </summary>
        /// arSuccess - application saved user's progress
        /// arFailure - application couldn't save user's progress
        /// arNotImplemented - not implemented by the developer
        /// </returns>
        private static ApplicationResult RequestApplicationSaveCallBack()
        {
            ApplicationResult result = ApplicationResult.arNotImplemented;

            if(s_application != null)
            {
                result = s_application.RequestApplicationSave();
            }

            return result;
        }

        /// <summary>
        /// This call back is called by the native side when GFN wants to exit the game
        /// </summary>
        /// <returns>
        /// arSuccess - application exited
        /// arFailure - application couldn't exit
        /// arNotImplemented - not implemented by the developer
        /// </returns>
        private static ApplicationResult RequestApplicationExitCallBack()
        {
            ApplicationResult result = ApplicationResult.arNotImplemented;

            if(s_application != null)
            {
                result = s_application.RequestApplicationExit();
            }

            return result;
        }

        /// <summary>
        /// Used by GFN to disable certain user options that may impact their GFN experience.
        /// </summary>
        /// <returns>
        /// arSuccess - application successfully disabled specified user options
        /// arFailure - application failed to disable specified user options
        /// arNotImplemented - not implemented by the developer
        /// </returns>
        private static ApplicationResult LockUserOptionsCallBack(UserOptions uoOptions)
        {
            ApplicationResult result = ApplicationResult.arNotImplemented;

            if(s_application != null)
            {
                result = s_application.LockUserOptions(uoOptions);
            }

            return result;
        }

        /// <summary>
        /// Set application's locale according to specified language code.
        /// Follows ISO 639-1 and ISO 3166-1 standards.
        /// </summary>
        /// <returns>
        /// arSuccess - application set specified language
        /// arFailure -  application failed to set specified language
        /// arNotImplemented - not implemented by the developer
        /// </returns>
        private static ApplicationResult SetLocaleCallBack(string pchlanguageCode)
        {
            ApplicationResult result = ApplicationResult.arNotImplemented;

            if(s_application != null)
            {
                result = s_application.SetLocale(pchlanguageCode);
            }

            return result;
        }

        /// <summary>
        /// Determines if application requires an update or patch.
        /// </summary>
        /// <returns>
        /// arSuccess - successfully determined if an update is required or not
        /// arFailure - failed to determine if updated is required or not
        /// arNotImplemented - not implemented by the developer
        /// </returns>
        private static ApplicationResult IsUpdateRequiredCallBack(ref int update)
        {
            ApplicationResult result = ApplicationResult.arNotImplemented;

            if(s_application != null)
            {
                bool localUpdate = false;

                result = s_application.IsUpdateRequired(ref localUpdate);

                update = localUpdate ? 1 : 0;
            }

            return result;
        }

        #endregion

        #region PInvokes

        [DllImport("GFNLinkNativeWrapper.dll")]
        private static extern GFNLinkError CallInitializeGFNLinkSDK();

        [DllImport("GFNLinkNativeWrapper.dll")]
        private static extern void CallShutdownGFNLinkSDK();

        [DllImport("GFNLinkNativeWrapper.dll")]
        private static extern int CallIsGFNEnabled();

        [DllImport("GFNLinkNativeWrapper.dll")]
        private static extern GFNLinkError CallRequestKeyboardOverlayOpen(GFNScreenPosition gspPosition);

        [DllImport("GFNLinkNativeWrapper.dll")]
        private static extern GFNLinkError CallRequestKeyboardOverlayClose();

        [DllImport("GFNLinkNativeWrapper.dll")]
        private static extern GFNLinkError CallRequestGFNAccessToken(ref IntPtr ppchToken);

        [DllImport("GFNLinkNativeWrapper.dll")]
        private static extern GFNLinkError CallGetStorageLocation(ref IntPtr ppchStoragePath);

        [DllImport("GFNLinkNativeWrapper.dll")]
        private static extern GFNLinkError CallNotifyStorageChange();

        [DllImport("GFNLinkNativeWrapper.dll")]
        private static extern void SetApplicationPauseCallBack([MarshalAs(UnmanagedType.FunctionPtr)]ApplicationStatusDelegate applicationPause);

        [DllImport("GFNLinkNativeWrapper.dll")]
        private static extern void SetRequestApplicationSaveCallBack([MarshalAs(UnmanagedType.FunctionPtr)]ApplicationStatusDelegate applicationSave);

        [DllImport("GFNLinkNativeWrapper.dll")]
        private static extern void SetRequestApplicationExitCallBack([MarshalAs(UnmanagedType.FunctionPtr)]ApplicationStatusDelegate applicationExit);

        [DllImport("GFNLinkNativeWrapper.dll")]
        private static extern void SetLockUserOptionsCallBack([MarshalAs(UnmanagedType.FunctionPtr)]LockUserOptionsDelegate lockUserOption);

        [DllImport("GFNLinkNativeWrapper.dll")]
        private static extern void SetSetLocaleCallBack([MarshalAs(UnmanagedType.FunctionPtr)]SetLocaleDelegate setLocale);

        [DllImport("GFNLinkNativeWrapper.dll")]
        private static extern void SetIsUpdateRequiredCallBack([MarshalAs(UnmanagedType.FunctionPtr)]IsUpdateRequiredDelegate updateRequired);

        #endregion

        #region Variables

        static BaseGFNApplication s_application = null;

        #endregion

    }
}
