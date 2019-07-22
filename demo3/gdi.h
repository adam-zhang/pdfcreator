#ifndef  __GDI__
#define  __GDI__

#include "GdiPlus.h"          //包含DGI+的头文件。 
#include <cassert>

namespace Gdiplus  
{  
	class GdiPlusInitialize  
	{  
		GdiplusStartupInput startupInput;  
		GdiplusStartupOutput startupOutput;  
	public:  
		GdiPlusInitialize()  
		{  
			startupInput.SuppressBackgroundThread = TRUE;  
			GdiplusStartup(&m_Token, &startupInput, &startupOutput);  
			Status stat = startupOutput.NotificationHook(&m_Token);  
			assert(stat == Ok);            
			stat;
		}  

		~GdiPlusInitialize()  
		{  
			startupOutput.NotificationUnhook(m_Token);  
			GdiplusShutdown(m_Token);   
		}  

	protected:  
		ULONG_PTR m_Token;  
		static GdiPlusInitialize m_Initialize;  
	};  
}

#endif