// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// demo.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

// TODO: �� STDAFX.H ��
// �����κ�����ĸ���ͷ�ļ����������ڴ��ļ�������
#pragma comment(lib, "ws2_32.lib")

#ifdef _DEBUG
#pragma comment(lib, "libhpdfsd.lib")
#else
#pragma comment(lib, "libhpdfs.lib")
#endif
