#pragma once

#include <hpdf.h>
#include <vector>
#include <memory>
#include <string>

class PDFPage;
class PDFImage;
class PDFFont;

class PDFDocument
{
public:
	PDFDocument(void);
	PDFDocument(const PDFDocument&);
	~PDFDocument(void);
private:
	HPDF_Doc doc_;
	HPDF_STATUS status_;
	int* count_;
	std::vector<PDFPage> pages_;	
public:
	bool valid()
	{ return doc_ != 0;}
	HPDF_STATUS status()
	{ return status_;}
	bool saveToFile(const std::string& fileName);
	PDFImage loadImageFromFile(const std::string& fileName);
	PDFPage addPage();
	PDFFont getFont(const std::string& fontName, const std::string& encodingName);
	bool initiate();
	void destroy();
	bool useCNSEncoding();
	std::vector<PDFPage>& pages()
	{ return pages_;}
};

