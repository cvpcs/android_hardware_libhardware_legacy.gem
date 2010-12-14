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
#include <hardware_legacy/ITelephonyService.h>
#include <sys/time.h>

namespace android {

/* Specifies the function id that has to be remotely invoked */

enum {
	endCall = IBinder::FIRST_CALL_TRANSACTION + 4,
};

/* Stub class for Telephony service */

class BpTelephonyService : public BpInterface<ITelephonyService>
{

public:
	BpTelephonyService(const sp<IBinder>& impl): BpInterface<ITelephonyService>(impl)
	{
	}

    virtual bool endCurrentCall() {
    	Parcel data, reply;
	    data.writeInterfaceToken(ITelephonyService::getInterfaceDescriptor());
    	remote()->transact(endCall, data, &reply);  //RPC call
    	reply.readInt32();          //Deserialize the exception response
    	return reply.readInt32();   //returns 1 if success
    }
};

IMPLEMENT_META_INTERFACE(TelephonyService, "com.android.internal.telephony.ITelephony")

};
