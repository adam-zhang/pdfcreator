#include "stdafx.h"
#include "PDFPage.h"
#include "PDFImage.h"
#include "PDFFont.h"
#include "CodeConverter.h"
#include <cassert>
#include <iostream>

using std::cout;
using std::endl;

PDFPage::PDFPage()
	: page_(NULL)
{
}

PDFPage::PDFPage(const HPDF_Page& page)
	: page_(page)
{	
}

//PDFPage& PDFPage::operator=(const PDFPage& page)
//{
//	if (this != &page)
//		page_ = page.page_;
//	return *this;
//}

void PDFPage::assign(const PDFPage& page)
{

}

PDFPage::~PDFPage()
{
}













bool PDFPage::drawImage(const PDFImage& image, float x, float y, float w, float h)
{
	status_ = HPDF_Page_DrawImage(page_, image.handle(), x, y, w, h);
	return status_ == 0;
}

bool PDFPage::setFontAndSize(const PDFFont& font, float size)
{
	assert(page_);
	status_ = HPDF_Page_SetFontAndSize(page_, font.handle(), size);
	assert(status_ == 0);
	return status_ == 0;
}

const float PDFPage::height()
{
	return HPDF_Page_GetHeight(page_);
}

float PDFPage::width()
{
	return HPDF_Page_GetWidth(page_);
}

float PDFPage::textWidth(const std::string& text)
{
	return HPDF_Page_TextWidth(page_, text.c_str());
}

void PDFPage::setSize(HPDF_PageSizes size, HPDF_PageDirection direction)
{
	status_ = HPDF_Page_SetSize(page_, size, direction);
}

HPDF_Point PDFPage::currentTextPosition()
{
	auto p = HPDF_Page_GetCurrentTextPos(page_);
	return p;
}

bool PDFPage::textOut(const std::string& text, float x, float y)
{
	cout << text << endl;
	HPDF_Page_BeginText(page_);
	status_ = HPDF_Page_TextOut(page_, x, y, text.c_str());
	HPDF_Page_EndText(page_);
	return status_ == 0;
}

bool PDFPage::setRGBFill(float r, float g, float b)
{
	status_ = HPDF_Page_SetRGBFill(page_, r, g, b);
	return status_ == 0;
}
