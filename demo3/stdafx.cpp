// stdafx.cpp : 只包括标准包含文件的源文件
// demo.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO: 在 STDAFX.H 中
// 引用任何所需的附加头文件，而不是在此文件中引用
#pragma comment(lib, "ws2_32.lib")

#ifdef _DEBUG
#pragma comment(lib, "libhpdfsd.lib")
#else
#pragma comment(lib, "libhpdfs.lib")
#endif
