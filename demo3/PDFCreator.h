#pragma once

#include <vector>
#include <memory>
#include <string>
#include <hpdf.h>
#include "PDFSize.h"
#include "PDFDocument.h"

class Trade;
class VirtualRow;

class PDFCreator
{
public:
	PDFCreator(void);
	~PDFCreator(void);
public:
	PDFDocument generateDocument(const std::vector<std::shared_ptr<Trade>>& );
	//void save(const std::string& path);
private:
	float horizonalMargin_;
	float verticalMargin_;
	float logoHeight_;
	float logoWidth_;
	float titleHeigh_;
	float titleFontSize_;
	float rowHeight_;
	std::string title_;
	std::string logoPath_;
	PDFDocument doc_;
public:
	void setTitle(const std::string& value)
	{ title_ = value;}
	const std::string& title()const
	{ return title_;}
	float rowHeight()
	{ return rowHeight_;}
	void setRowHeight(float value)
	{ rowHeight_ = value;}
	void setLogoPath(const std::string& path)
	{ logoPath_ = path;}
	const std::string& logoPath()const
	{ return logoPath_;}
	float horizonalMargin()
	{ return horizonalMargin_;}
	void setHorizonalMargin(float value)
	{ horizonalMargin_ = value;}
	float verticalMargin()
	{ return verticalMargin_;}
	void setVerticalMargin(float value)
	{ verticalMargin_ = value;}
	float logoHeight()
	{  return logoHeight_;}
	void setLogoHeight(float value)
	{ logoHeight_ = value;}
	float logoWidth()
	{ return logoWidth_;}
	void setLogoWidth(float value)
	{ logoWidth_ = value;}
	float titleHeight()
	{ return titleHeigh_;}
	void setTitleHeight(float value)
	{ titleHeigh_ = value;}
	float titleFontSize()
	{ return titleFontSize_;}
	void setTitleFontSize(float value)
	{ titleFontSize_ = value;}
private:
	PDFSize a5Size();
	PDFSize a4Size();
	size_t a5RowsNumber();
	size_t a4CoverRowsNumber();
	size_t a4RowsNumber();
	PDFDocument generateDocument(const std::vector<std::shared_ptr<VirtualRow>>&);
	PDFDocument generateA4Document(const std::vector<std::shared_ptr<VirtualRow>>&);
	PDFDocument generateA5Document(const std::vector<std::shared_ptr<VirtualRow>>&);
	PDFDocument generateSinglepageDocument(const std::vector<std::shared_ptr<VirtualRow>>&);
	PDFDocument generateMultipageDocument(const std::vector<std::shared_ptr<VirtualRow>>&);
	PDFDocument createDocument();
	size_t calculatePages(size_t);
	void drawCover(PDFPage&, const std::vector<std::shared_ptr<VirtualRow>>&);
	void drawPage(PDFPage&,  const std::vector<std::shared_ptr<VirtualRow>>&, size_t);
	std::vector<std::shared_ptr<VirtualRow>> actualRows(const std::vector<std::shared_ptr<VirtualRow>>& rows, size_t pageRowNumber, size_t index);
	void outputContent(PDFPage& page, const std::vector<std::shared_ptr<VirtualRow>>& rows, size_t beginningY);
	void drawVirtualRow(PDFPage& page, const std::shared_ptr<VirtualRow>&, float);
	float calculateWidth(const std::string&);
	float calculateWidth(const std::wstring&);
	void drawLogos(PDFDocument&, const std::string&);
	void drawFooters(PDFDocument&, PDFFont&);
	void drawTitle(PDFPage&, PDFFont&, const std::string& text);
	std::vector<std::shared_ptr<VirtualRow>> PDFCreator::calculateActualRow(const std::vector<std::shared_ptr<Trade>>& rowData, size_t rowIndex, PDFPage& page);
	std::vector<std::shared_ptr<VirtualRow>> calculateRows(const std::vector<std::shared_ptr<Trade>>& data, PDFPage& page);

	bool isLastRow(std::vector<std::shared_ptr<VirtualRow>>& rows);
	void fixNewTable(std::vector<std::shared_ptr<VirtualRow>>& rows);
	std::vector<std::shared_ptr<VirtualRow>> fixTable(const std::vector<std::shared_ptr<VirtualRow>>& rows);
	size_t whichPage(std::shared_ptr<VirtualRow>& row);
	bool isFirstRow(std::shared_ptr<VirtualRow>& row);
	bool crossOnePage(std::vector<std::shared_ptr<VirtualRow>>& rows);
	bool crossMultipages(std::vector<std::shared_ptr<VirtualRow>>& rows);
};

