#include "StdAfx.h"
#include "PDFSize.h"


PDFSize::PDFSize(void)
	: width_(0.0)
	, height_(0.0)
{
}

PDFSize::PDFSize(float w, float h)
	: width_(w)
	, height_(h)
{
}


PDFSize::~PDFSize(void)
{
}
