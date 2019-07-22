#ifndef __PDFPAGE__H
#define __PDFPAGE__H

#include <hpdf.h>
#include <string>
#include <memory>
#include <iostream>

class PDFImage;
class PDFFont;

class PDFPage
{
public:
	PDFPage();
	PDFPage(const HPDF_Page& page);
	//PDFPage& operator=(const PDFPage& page);
	~PDFPage();
private:
	HPDF_Page page_;
	HPDF_STATUS status_;
public:
	HPDF_STATUS status()
	{ return status_;}
	void setSize(HPDF_PageSizes, HPDF_PageDirection);
	float textWidth(const std::string&);
	float width();
	const float height();
	HPDF_Point currentTextPosition();
	bool drawImage(const PDFImage& image, float x, float y, float width, float height);
	bool setFontAndSize(const PDFFont&, float size);
	bool textOut(const std::string& text, float x, float y);
	bool setRGBFill(float r, float g, float b);
private:
	void assign(const PDFPage&);
};

typedef std::shared_ptr<PDFPage> PDFPagePtr;
#endif//__PDFPAGE__H
