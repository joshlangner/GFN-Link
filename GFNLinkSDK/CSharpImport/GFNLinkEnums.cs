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
    // GFNLink Errors
    // Returned by InitializeGFNLinkSDK and GFNLink API methods
    public enum GFNLinkError
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
    };

    // All Host Interface methods return a result of this type
    // Note, this must be kept in sync with typedef in IGFNApplication.cs
    public enum ApplicationResult
    {
        arNotImplemented = 0,		// Developers did not implement this method
        arSuccess,					// Operation completed successfully
        arFailure					// General failure result 
    };

	// Parameter to RequestKeyboardOverlay method
	// Specifies where to display text input element on screen
	public enum GFNScreenPosition
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
	};

	// Parameter to LockUserOptions
	// Flags indicating user's options in the application
	public enum UserOptions
	{
		uoNone				= 0,
		uoGraphicsSettings	= 0 << 1
	};
}
