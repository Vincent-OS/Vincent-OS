@ stdcall CsrAllocateCaptureBuffer(long long)
@ stdcall CsrAllocateMessagePointer(ptr long ptr)
@ stdcall CsrCaptureMessageBuffer(ptr ptr long ptr)
@ stdcall CsrCaptureMessageMultiUnicodeStringsInPlace(ptr long ptr)
@ stdcall CsrCaptureMessageString(ptr str long long ptr)
@ stdcall CsrCaptureTimeout(long ptr)
@ stdcall CsrClientCallServer(ptr ptr long long)
@ stdcall CsrClientConnectToServer(str long ptr ptr ptr)
@ stdcall CsrFreeCaptureBuffer(ptr)
@ stdcall CsrGetProcessId()
@ stdcall CsrIdentifyAlertableThread()
@ stdcall -version=0x502 CsrNewThread()
@ stdcall -version=0x502 CsrProbeForRead(ptr long long)
@ stdcall -version=0x502 CsrProbeForWrite(ptr long long)
@ stdcall CsrSetPriorityClass(ptr ptr)
@ stdcall -stub -version=0x600+ CsrVerifyRegion(ptr long)
@ stdcall -stub -version=0x600+ RtlRegisterThreadWithCsrss()
