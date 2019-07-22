#include "StdAfx.h"
#include "PDFFont.h"

using namespace std;

PDFFont::PDFFont(HPDF_Font font)
	: font_(font)
{
}

PDFFont::~PDFFont(void)
{
}

//PDFFont::PDFFont(const string& fontName, const string& encodingName)
//{
//	font_ = HPDF_GetFont(fontName.c_str(), encodingName.c_str());
//}