/* Copyright (c) 2009, Code Aurora Forum. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Code Aurora nor
 *       the names of its contributors may be used to endorse or promote
 *       products derived from this software without specific prior written
 *       permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <stdint.h>
#include <sys/types.h>
#include <binder/Parcel.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <utils/String16.h>
#include <hardware_legacy/IWindowManagerService.h>
#include <sys/time.h>



namespace android {

/* Specifies the function id that has to be remotely invoked */
enum {
    injectKeyEvent = IBinder::FIRST_CALL_TRANSACTION + 5,
};

/* Stub class for WindowManager service */
class BpWindowManagerService : public BpInterface<IWindowManagerService>
{
public:
    BpWindowManagerService(const sp<IBinder>& impl)
        : BpInterface<IWindowManagerService>(impl)
    {
    }

/*===========================================================================
  FUNCTION  pressKey
===========================================================================*/
/*!
@brief
  Bundles the parameters required for injectKeyEvent function into a parcel
  and invokes it

@return
  Returns 0 if the key press is successful

@note


*/
/*=========================================================================*/
    virtual bool pressKey(int keycode, bool down)
    {
        struct timeval tv_current;
        uint32_t n = keycode;
        Parcel data, reply;

        gettimeofday(&tv_current, NULL);

        data.writeInterfaceToken(IWindowManagerService::getInterfaceDescriptor());
        data.writeInt32(1);                 //specify there is an input parameter
        data.writeInt32(down ? 0 : 1);      //specify if it's key up or key down
        data.writeInt32(n);                 //specify the key code
        data.writeInt32(0);                 //repeat count
        data.writeInt32(0);                 //meta state
        data.writeInt32(0);                 //device id
        data.writeInt32(0);                 //scan code
        data.writeInt32(0);                 //flags
        data.writeInt32(tv_current.tv_sec); //Down time
        data.writeInt32(tv_current.tv_sec); //Event time
        data.writeInt32(1);                 //end of parameter

        remote()->transact(injectKeyEvent, data, &reply);//RPC call
        return reply.readInt32();  //returns 0 if success
    }
};  // class BpWindowManagerService

IMPLEMENT_META_INTERFACE(WindowManagerService, "android.view.IWindowManager")

};  // namespace android

