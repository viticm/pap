#include "vengine/kernel/base.h"
#include "vgui/stdafx.h"
#include "OgreRoot.h"
#include "vgui/interface.h"

//Magic Code
extern "C" uint32_t DllMagicCode = VENGINE_DLL_MAGIC_CODE | VENGINE_VERSION;

//插件初始化
extern "C" void __stdcall DllInit(vengine_kernel::Base* kernel) {
	VENGINE_ASSERT(kernel);
	g_kernel = kernel;
	kernel->registerclass(VENGINE_KERNEL_GETCLASS());
}

extern VOID InstallUISystem( tKernel* pKernel )
{
	KLAssert(pKernel);
	g_pKernel = pKernel;
	pKernel->ReisgerClass(GETCLASS(CUISystem));
}

// 插件释放
extern "C" VOID __stdcall DllRelease(VOID)
{
}
