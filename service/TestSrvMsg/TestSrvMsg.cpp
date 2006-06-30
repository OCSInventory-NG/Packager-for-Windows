#include "stdafx.h"

BOOL APIENTRY DllMain(HANDLE /*hModule*/, DWORD /*ul_reason_for_call*/, LPVOID /*lpReserved*/)
{
  return TRUE;
}

//The following function is provided to ensure that a .lib file
//is generated for TestSrvMsg. This is required as we are using
//the build in Dependency settings in VC to ensure the message
//dll is build before the NT service exe.
void __declspec(dllexport) Dummy()
{
}