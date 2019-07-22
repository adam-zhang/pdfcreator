#include "StdAfx.h"
#include "PDFImage.h"


PDFImage::PDFImage(void)
	: image_(NULL)
{
}

PDFImage::PDFImage(HPDF_Image image)
	: image_(image)
{
	
}


PDFImage::~PDFImage(void)
{
}
