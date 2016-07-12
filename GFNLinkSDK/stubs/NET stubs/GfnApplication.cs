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


namespace GFNLinkSDK.Managed
{
    class GFNApplication : BaseGFNApplication
    {
        #region Overrides

        /// <summary>
        /// Request to pause application activity
        /// </summary>
        /// <returns>
        /// arSuccess - application activity was successfully paused
        /// arFailure - application activity couldn't be paused
        /// arNotImplemented - application did not implement this method
        /// </returns>
        protected override ApplicationResult RequestApplicationPause()
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
        protected override ApplicationResult RequestApplicationSave()
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
        protected override ApplicationResult RequestApplicationExit()
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
        protected override ApplicationResult SetLocale(string pchlanguageCode)
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
        protected override ApplicationResult IsUpdateRequired(ref bool bUpdate)
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
        protected override ApplicationResult LockUserOptions(UserOptions uoOptions)
        {
            return ApplicationResult.arNotImplemented;
        }

        #endregion
    }
}
