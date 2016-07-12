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


namespace SampleCSharpApplication
{
    class Program
    {
        static void Main(string[] args)
        {
            GFNApplication.InitializeGFNLinkSDK(new GFNApplication());

            // Sample call into the GFNLink interface object:
            bool bGfnEnabled = GFNApplication.IsGFNEnabled();
            Console.WriteLine("GFN Enabled: {0}", bGfnEnabled);

            // Another sample call:
            string storageLocation = null;

            if (GFNApplication.GetStorageLocation(ref storageLocation) == GFNLinkSDK.Managed.GFNLinkError.gleSuccess)
            {
                Console.WriteLine("Gfn CloudSave location: {0}", storageLocation);
            }

            GFNApplication.NotifyStorageChange();

            string accessToken = null;

            if (GFNApplication.RequestGFNAccessToken(ref accessToken) == GFNLinkSDK.Managed.GFNLinkError.gleSuccess)
            {
                Console.WriteLine("Gfn Access Token: {0}", accessToken);
            }

            Console.WriteLine("\n\nC# Application: In main application loop; Press space bar to exit...\n");

            // Application Main Loop
            while (!mainDone)
            {
                var keyInfo = Console.ReadKey();

                // Do application stuff here..
                if (keyInfo.Key == ConsoleKey.Spacebar)
                {
                    mainDone = true;
                }
            }

            Console.WriteLine("Shuting down Gfn Link.");

            GFNApplication.ShutdownGFNLinkSDK();

        }

        static bool mainDone = false;
    }
}
