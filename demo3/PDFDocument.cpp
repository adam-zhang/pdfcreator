#include "StdAfx.h"
#include "PDFDocument.h"
#include "PDFPage.h"
#include "PDFImage.h"
#include "PDFFont.h"
#include <cassert>

using namespace std;

PDFDocument::PDFDocument(void)
	: doc_(NULL)
	, status_(-1)
{
	//assert(doc_);
}

PDFDocument::PDFDocument(const PDFDocument& doc)
	: doc_(doc.doc_)
	, pages_(doc.pages_)
	, status_(doc.status_)
{
}

static jmp_buf env;

static void error_handler(HPDF_STATUS   error_no, HPDF_STATUS   detail_no, void         *user_data)
{
	printf("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
		(HPDF_UINT)detail_no);
	longjmp(env, 1);
}

bool PDFDocument::initiate()
{
	doc_ = HPDF_New(error_handler, NULL);
	HPDF_SetCompressionMode(doc_, HPDF_COMP_ALL);
	setjmp(env);
	return doc_ != NULL;
}

void PDFDocument::destroy()
{
	HPDF_Free(doc_);
}


PDFDocument::~PDFDocument(void)
{
}

PDFPage PDFDocument::addPage()
{
	assert(doc_);
	auto page = HPDF_AddPage(doc_);
	assert(page);
	pages_.push_back(page);
	return page;
}

bool PDFDocument::saveToFile(const string& fileName)
{
	assert(doc_);
	assert(fileName.size() > 0);
	status_ = HPDF_SaveToFile(doc_, fileName.c_str());
	return status_ == 0;
}

PDFImage PDFDocument::loadImageFromFile(const std::string& path)
{
	auto handle = HPDF_LoadJpegImageFromFile(doc_, path.c_str());
	if (!handle)
		return PDFImage();
	PDFImage image(handle);
	assert(image.valid());
	return image;
}

PDFFont PDFDocument::getFont(const string& fontName, const string& encodingName)
{
	auto handle = HPDF_GetFont(doc_, fontName.c_str(), encodingName.c_str());
	auto font = PDFFont(handle);
	return font;
}

bool PDFDocument::useCNSEncoding()
{
	status_ = HPDF_UseCNSEncodings(doc_);
	if (status_ != 0)
		return false;
	status_ = HPDF_UseCNSFonts(doc_);
	return status_ == 0;
}