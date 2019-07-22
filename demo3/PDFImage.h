#pragma once
#include <hpdf.h>

class PDFImage
{
public:
	PDFImage(void);
	PDFImage(HPDF_Image);
	~PDFImage(void);
private:
	HPDF_Image image_;
public:
	const HPDF_Image handle()const
	{ return image_;}
	bool valid()
	{ return image_ != NULL;}
};

