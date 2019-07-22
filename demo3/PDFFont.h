#pragma once
#include <hpdf.h>

class PDFFont
{
public:
	PDFFont(){}
	//PDFFont(const std::string& fontName, const std::string& encodingName);
	PDFFont(HPDF_Font);
	~PDFFont(void);
private:
	HPDF_Font font_;
public:
	const HPDF_Font handle()const
	{ return font_;}
	bool valid()
	{ return font_ != 0; }
};

