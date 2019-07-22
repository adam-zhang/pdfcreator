#include "stdafx.h"
#include "PDFCreator.h"
#include "PDFDocument.h"
#include "PDFPage.h"
#include "PDFFont.h"
#include "VirtualDocument.h"
#include "VirtualColumn.h"
#include "PairColumn.h"
#include "VirtualRow.h"
#include "Trade.h"
#include "CodeConverter.h"
#include "PDFImage.h"
#include "VirtualHeaderRow.h"
#include "Debugger.h"
#include <map>
#include <hpdf.h>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <cmath>
#include <cassert>
#include <memory>
#include <sstream>
#include <Windows.h>
#include "gdi.h"

using namespace std;

PDFCreator::PDFCreator(void)
	: horizonalMargin_(0.0f)
	, verticalMargin_(0.0f)
	, logoHeight_(0.0f)
	, logoWidth_(0.0f)
	, titleHeigh_(0.0f)
	, titleFontSize_(0.0f)
	, rowHeight_(0.0)
{

}


PDFCreator::~PDFCreator(void)
{
}

PDFSize PDFCreator::a4Size()
{
	return PDFSize(595.0f, 841.0f);
}

PDFSize PDFCreator::a5Size()
{
	return PDFSize(595.0f, 420.0f);
}

size_t PDFCreator::a4CoverRowsNumber()
{
	return static_cast<size_t>(floor((a4Size().height() - logoHeight() - titleHeight() - horizonalMargin() * 2) / rowHeight())) - 1;
}

size_t PDFCreator::a4RowsNumber()
{
	auto value = a4Size().height() - horizonalMargin() * 2 - logoHeight();
	value = value / rowHeight();
	return static_cast<size_t>(floor((a4Size().height() - horizonalMargin() * 2 - logoHeight()) / rowHeight())) - 1;
	
	//return static_cast<size_t>(floor((a4Size().height() - horizonalMargin() * 2 - logoHeight()) / rowHeight())) - 1;
}

size_t PDFCreator::a5RowsNumber()
{
	return static_cast<size_t>(floor((a5Size().height() - logoHeight() - titleHeight() - horizonalMargin() * 2) / rowHeight())) - 1;
}



static int calculateNaturalRows(const vector<shared_ptr<Trade>>& data)
{
	int rows = 0;
	for_each(data.begin(), data.end(), [&rows](const shared_ptr<Trade>& trade)
	{
		if (trade->row > rows)
			rows = trade->row;
	});
	return rows;
}

static vector<shared_ptr<Trade>> rowsData(const vector<shared_ptr<Trade>>& data, int rowNumber)
{
	vector<shared_ptr<Trade>> vec;
	for_each(data.begin(), data.end(), [&vec, &rowNumber](const shared_ptr<Trade>& trade)
	{
		if (trade->row == rowNumber)
			vec.push_back(trade);
	});
	return vec;
}

static map<int, vector< shared_ptr<Trade>>> convertRows(const vector<shared_ptr<Trade>>& data, int maxRow)
{
	map<int, vector<shared_ptr<Trade>>> m;
	for(int i = 0; i != maxRow + 1; ++i)
	{
		vector<shared_ptr<Trade>> row = rowsData(data, i);
		m.insert(make_pair(i, row));
	}
	return m;
}

static int maximum(const vector<int>& data)
{
	int maxNumber = 0;
	for_each(data.begin(), data.end(), [&maxNumber](int number)
	{
		if (maxNumber < number)
			maxNumber = number;
	});
	return maxNumber;
}


static string substr(const string& input, size_t index)
{
	std::wstring a1 = CodeConverter::AnsiToUtf16(input);
	auto a2 = a1.substr(index);
	return CodeConverter::Utf16ToAnsi(a2);
}


static string caculateWidth(PDFPage& page, const float width, const string& text)
{
	float w = page.textWidth(text);
	if (w < width)
		return text;
	std::wstring wtext = CodeConverter::AnsiToUtf16(text);
	std::wstring ret;
	size_t sub = 0;
	float tempW = 0;
	for(auto i = 0; i != wtext.size(); ++i)
	{
		ret = wtext.substr(0, i);
		tempW =page.textWidth(CodeConverter::Utf16ToAnsi(ret).c_str());
		if (tempW < width)
			++sub;
	}
	return CodeConverter::Utf16ToAnsi(wtext.substr(0, sub - 1));
}


static vector<shared_ptr<VirtualColumn>> outputText( const std::string& text, size_t rowIndex, size_t columnIndex, float width, PDFPage& page)
{
	assert(columnIndex <= 10);
	vector<shared_ptr<VirtualColumn>> columns;
	auto temp = text;
	auto str = caculateWidth(page, width, temp);
	size_t index = 1;
	while(str.size() > 0)
	{
		columns.push_back(make_shared<VirtualColumn>(str, rowIndex + index - 1, columnIndex));
		temp = substr(temp, CodeConverter::AnsiToUtf16(str).size());
		str = caculateWidth(page, width, temp);
		++index;
	}
	return columns;
}


static size_t maximum(const vector<vector<string>>& data)
{
	size_t number = 0;
	for_each(data.begin(), data.end(), [&number](const vector<string>& v)
	{
		if (v.size() > number)
			number = v.size();
	});
	return number;
}

static vector<vector<string>> fillColumns(const vector<vector<string>>& value, int max)
{
	vector<vector<string>> vec;
	for(size_t i = 0; i != value.size(); ++i)
	{
		vector<string> v = value[i];
		if (v.size() < static_cast<size_t>(max))
			v.push_back(string());
		vec.push_back(v);
	}
	return vec;
}

size_t calculateText(const std::string& text)
{
	wstring ws = CodeConverter::AnsiToUtf16(text);
	//for(
	return 0;
}

string insertBlanks(const std::string& text)
{
	size_t number = calculateText(text);
	vector<char> buffer(number);
	fill(buffer.begin(), buffer.end(), ' ');
	return &buffer[0];
}

vector<shared_ptr<PairColumn>> makePairColumns(const vector<shared_ptr<VirtualColumn>>& label,
	const vector<shared_ptr<VirtualColumn>>& value,
	size_t columnIndex)
{
	vector<shared_ptr<PairColumn>> pairs;
	size_t count = max(label.size(), value.size());
	size_t rowIndex = label[0]->rowIndex();
	for(size_t i = 0; i != count; ++i)
	{
		auto p = make_shared<PairColumn>();
		p->setColumnIndex(columnIndex);
		if (label.size() - 1 < i) 
		{
			//p->setLabel(insertBlanks(label[0]));
			p->setLabel(string());
			p->setRowIndex(rowIndex + i);
			p->setValue(value[i]->label());
		}
		else if (value.size() - 1 < i)
		{
			p->setValue(string());
			p->setRowIndex(rowIndex + i);
			p->setLabel(label[i]->label());
		}
		else
		{
			p->setLabel(label[i]->label());
			p->setValue(value[i]->label());
			p->setRowIndex(rowIndex + i);
		}
		pairs.push_back(p);
	}
	return pairs;
}


static vector<shared_ptr<VirtualColumn>> calculateColumn(const shared_ptr<Trade>& trade, size_t rowIndex, size_t columnIndex, float width, PDFPage& page)
{
	vector<shared_ptr<VirtualColumn>> columns;
	static size_t count = 0;
	if (trade->value.empty())
	{
		auto cols = outputText(trade->label, rowIndex + count, columnIndex, width, page);
		copy(cols.begin(), cols.end(), back_inserter(columns));
	}
	else
	{
		auto cols = outputText(trade->label + trade->value, rowIndex + count, columnIndex, width - 10, page);
		copy(cols.begin(), cols.end(), back_inserter(columns));
	}
	return columns;
}

static size_t maximum(const vector<vector<shared_ptr<VirtualRow>>>& data)
{
	size_t max = 0;
	for_each(data.begin(), data.end(), [&max](const vector<shared_ptr<VirtualRow>>& v)
	{
		if (max < v.size())
			max = v.size();
	});
	return max;
}

static void addRows(vector<shared_ptr<VirtualRow>>& data, size_t max)
{
	size_t left = max - data.size();
	for(size_t i = 0; i != max; ++i)
		data.push_back(make_shared<VirtualRow>());
}

static vector<shared_ptr<VirtualRow>> convert(const vector<vector<shared_ptr<VirtualRow>>>& data)
{
	size_t count = data[0].size();
	vector<shared_ptr<VirtualRow>> vec;
	for(size_t i = 0; i != count; ++i)
	{
		shared_ptr<VirtualRow> p;
		for(size_t j = 0; j != data.size(); ++j)
		{
			auto column = data[j][i]->columns()[i];
			p->columns().push_back(column);
		}
		vec.push_back(p);
	}
	return vec;
}

static size_t maxRowNumber(const vector<shared_ptr<VirtualColumn>>& columns)
{
	size_t max = 0;
	for(size_t i = 0; i != columns.size(); ++i)
	{
		if (max < columns[i]->rowIndex())
			max = columns[i]->rowIndex();
	};
	return max + 1;
}

static shared_ptr<VirtualRow> makeVirtualRow(const vector<shared_ptr<VirtualColumn>>& data, size_t index, size_t count)
{
	auto p = make_shared<VirtualRow>();
	p->setColumnCount(count);
	for(size_t i = 0; i != data.size(); ++i)
	{
		if (data[i]->rowIndex() == index)
			p->columns().push_back(data[i]);
	};
	return p;
}

size_t maxColumnNumber(const vector<shared_ptr<VirtualColumn>>& data)
{
	size_t max = 0;
	for(size_t i = 0; i != data.size(); ++i)
		if (max < data[i]->columnIndex())
			max = data[i]->columnIndex();
	return max;
}

static vector<shared_ptr<VirtualRow>> toRows(const vector<shared_ptr<VirtualColumn>>& data, size_t rowIndex, size_t count)
{
	vector<shared_ptr<VirtualRow>> rows;
	if (data.size() == 0)
		return rows;
	size_t max = maxRowNumber(data) - rowIndex;
	size_t columnNumber = maxColumnNumber(data);
	for(size_t i = 0; i != max; ++i)
	{
		rows.push_back(makeVirtualRow(data, rowIndex + i, count));
	};
	return rows;
}

size_t columnCount(const vector<shared_ptr<Trade>>& row)
{
	if (row[0]->colTotal == 0)
		return 3;
	else
		return row[0]->colTotal;
}

shared_ptr<Trade> find(const vector<shared_ptr<Trade>>& data, size_t index)
{
	for(size_t i = 0; i != data.size(); ++i)
	{
		if (data[i]->col == index)
			return data[i];
	}
	return shared_ptr<Trade>();
}

vector<shared_ptr<Trade>> fixRowData(const vector<shared_ptr<Trade>>& rowData, size_t count)
{
	if (rowData.size() == count)
		return rowData;
	vector<shared_ptr<Trade>> data; // rowData;
	for(size_t i = 0; i != count; ++i)
	{
		auto p = find(rowData, i);
		if (p)
			data.push_back(p);
		else
		{
			auto p = make_shared<Trade>();
			p->col = i;
			p->row = data[0]->row;
			data.push_back(p);
		}
	}
	return data;
}

static float successorWidth(const vector<shared_ptr<Trade>>& data, size_t index, float w)
{
	size_t count = 0;
	for(size_t i = index; i != data.size(); ++i)
	{
		auto s = data[i]->label + data[i]->value;
		if (s.empty())
			++count;
		else
			break;
	}
	return count * w;
}

static float calculateWidth(const vector<shared_ptr<Trade>>& data, size_t index, float w)
{
	if (data.size() == index)
		return 0;
	auto s = data[index]->label + data[index]->value;
	if (!s.empty())
		return 0;
	return successorWidth(data, index, w);
}

vector<shared_ptr<VirtualRow>> PDFCreator::calculateActualRow(const vector<shared_ptr<Trade>>& rowData, size_t rowIndex, PDFPage& page)
{
	vector<shared_ptr<VirtualRow>> rows;
	vector<shared_ptr<VirtualColumn>> temp;
	size_t count = columnCount(rowData);
	float w = (page.width() - verticalMargin()) / count;
	auto data = fixRowData(rowData, count);	
	for(size_t i = 0; i != count; ++i)
	{
		auto width = ::calculateWidth(data, i + 1, w);
		auto ret = calculateColumn(data[i], rowIndex , i, w + width, page  );
		copy(ret.begin(), ret.end(), back_inserter(temp));
	};
	auto ret = toRows(temp, rowIndex, data.size());
	return ret;
}



void changeRowType(vector<shared_ptr<VirtualRow>>& rows)
{
	for_each(rows.begin(), rows.end(), [](shared_ptr<VirtualRow>& row)
	{
		row->setRowType(VirtualRow::HEADER);	
	});
}

vector<shared_ptr<VirtualRow>> PDFCreator::calculateRows(const vector<shared_ptr<Trade>>& data, PDFPage& page)
{
	vector<shared_ptr<VirtualRow>> retRows;
	int rows = calculateNaturalRows(data);	
	auto rowsData = convertRows(data, rows);
	for(size_t i = 0; i != rows + 1; ++i)
	{
		if (rowsData[i].size() == 0)
		{
			retRows.push_back(make_shared<VirtualRow>());
			continue;
		}
		auto virtualRows = calculateActualRow(rowsData[i] , i, page);
		if (rowsData[i][0]->keyword == 0)
		{
			Debugger::write("header", rowsData[i][0]->label);
			changeRowType(virtualRows);
		}
		copy(virtualRows.begin(), virtualRows.end(), back_inserter(retRows));
	}
	return retRows;
}


void output(const vector<shared_ptr<VirtualRow>>& rows)
{
	for(auto i = 0; i != rows.size(); ++i)
	{
		cout << i << " " << "size:" << rows[i]->columns().size() << " ";
		for(auto j = 0; j != rows[i]->columns().size(); ++j)
			cout << "col:" << j << " " << rows[i]->columns()[j]->text() << " ";	
		cout << endl;
	}
}

PDFFont getFontFrom(PDFDocument& doc)
{
	return doc.getFont("SimSun", "GB-EUC-H");
}

void addIndics(vector<shared_ptr<VirtualRow>>& rows)
{
	for(size_t i = 0; i != rows.size(); ++i)
		rows[i]->setIndex(i);
}

PDFDocument PDFCreator::generateDocument(const vector<shared_ptr<Trade>>& data)
{
	PDFDocument doc;
	doc.initiate();
	doc.useCNSEncoding();//"SimSun", "GB-EUC-H"
	auto page = doc.addPage();
	auto font = getFontFrom(doc);
	page.setFontAndSize(font, 12);
	auto rows = calculateRows(data, page);
	addIndics(rows);
	output(rows);
	doc.destroy();
	doc = generateDocument(rows);
	font = getFontFrom(doc);
	drawLogos(doc, logoPath());
	drawFooters(doc, font);
	drawTitle(doc.pages()[0], font, title());
	return doc;
}

PDFDocument PDFCreator::generateDocument(const vector<shared_ptr<VirtualRow>>& rows)
{
	auto number = a5RowsNumber();
	if (rows.size() < number)
		return generateA5Document(rows);
	else
		return generateA4Document(rows);
}

PDFDocument PDFCreator::generateA4Document(const vector<shared_ptr<VirtualRow>>& rows)
{
	if (rows.size() <= a4CoverRowsNumber())
		return generateSinglepageDocument(rows);
	else
		return generateMultipageDocument(rows);
}

PDFDocument PDFCreator::generateSinglepageDocument(const vector<shared_ptr<VirtualRow>>& rows)
{
	auto doc = createDocument();
	auto page = doc.addPage();
	auto font = getFontFrom(doc);
	page.setFontAndSize(font, 12);
	page.setSize(HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
	drawCover(page, rows);
	return doc;
}

size_t PDFCreator::calculatePages(size_t size)
{
	size_t count = static_cast<size_t>(ceilf((static_cast<float>(size) - a4CoverRowsNumber()) / a4RowsNumber()));
	return count + 1;
}

float PDFCreator::calculateWidth(const std::wstring& path)
{
	unique_ptr<Gdiplus::Image> image(Gdiplus::Image::FromFile(path.c_str()));
	auto ratio = static_cast<float>(image->GetWidth()) / image->GetHeight();
	auto width = logoHeight() * ratio;
	return width;
}

float PDFCreator::calculateWidth(const std::string& path)
{
	return calculateWidth(CodeConverter::AnsiToUtf16(path));
}

void PDFCreator::drawLogos(PDFDocument& doc, const std::string& logoPath)
{
	auto image = doc.loadImageFromFile(logoPath);
	auto width = calculateWidth(logoPath);
	for(size_t i = 0; i != doc.pages().size(); ++i)
	{
		auto y = doc.pages()[i].height() - verticalMargin() - logoHeight();
		doc.pages()[i].drawImage(image, horizonalMargin(), y, width, logoHeight());
	}
}

size_t getTableHeader(const vector<shared_ptr<VirtualRow>>& rows)
{
	size_t index = -1;
	for(size_t i = 0; i != rows.size(); ++i)
		if (rows[i]->rowType() == VirtualRow::HEADER)
			return i;
	return index;
}

vector<shared_ptr<VirtualRow>> getTable(const vector<shared_ptr<VirtualRow>>& rows, size_t index)
{
	vector<shared_ptr<VirtualRow>> table;
	for(size_t i = index; i != rows.size(); ++i)
	{
		if (rows[i]->columns().size() == 0)
			break;
		table.push_back(rows[i]);
	}
	return table;
}

vector<vector<shared_ptr<VirtualRow>>> getTables(const vector<shared_ptr<VirtualRow>>& rows)
{
	vector<vector<shared_ptr<VirtualRow>>> tables;
	for(size_t i = 0; i != rows.size(); ++i)
	{
		Debugger::write("i", i);
		if (rows[i]->rowType() == VirtualRow::HEADER)
		{
			auto table = getTable(rows, i);
			i += table.size() - 1;
			tables.push_back(table);
		}
	}
	return tables;
}

bool PDFCreator::isLastRow(vector<shared_ptr<VirtualRow>>& rows)
{
	size_t count = 0;
	while(true)
	{
		if (count == 0)
		{
			if (rows[0]->index() <= a4CoverRowsNumber())
				return rows[0]->index() == a4CoverRowsNumber();
		}
		else
		{
			if (rows[0]->index() <= a4CoverRowsNumber() + a4RowsNumber() * count)
				return rows[0]->index() == a4CoverRowsNumber() + a4RowsNumber() * count;
		}
		++count;
	}
	return false;
}

void addRowNumber(vector<shared_ptr<VirtualRow>>& rows, size_t index)
{
	for(size_t i = index; i != rows.size(); ++i)
		rows[i]->setIndex(rows[i]->index() + 1);
}

size_t PDFCreator::whichPage(shared_ptr<VirtualRow>& row)
{
	size_t count = 1;
	bool stop = false;
	while(!stop)
	{
		if (row->index() > a4CoverRowsNumber() && row->index() < a4CoverRowsNumber()  + a4RowsNumber() * count)
			return count;
		++count;
	}
	return -1;
}

bool PDFCreator::isFirstRow(shared_ptr<VirtualRow>& row)
{
	size_t pageNumber = whichPage(row);
	if (row->index() ==  a4CoverRowsNumber() + 1)
		return true;
	return false;
}

bool PDFCreator::crossOnePage(vector<shared_ptr<VirtualRow>>& rows)
{
	for(size_t i = 2; i != rows.size(); ++i)
	{
		if (isFirstRow(rows[i]))
			return true;
	}
	return false;
}

void addHeader(vector<shared_ptr<VirtualRow>>& rows)
{

}



bool PDFCreator::crossMultipages(vector<shared_ptr<VirtualRow>>& rows)
{
	size_t beginning = whichPage(rows[0]);
	size_t ending = whichPage(rows[rows.size() - 1]);
	return (beginning - ending)  > 2;
}

vector<shared_ptr<VirtualRow>> getHeaders(vector<shared_ptr<VirtualRow>>& rows)
{
	vector<shared_ptr<VirtualRow>> vec;
	for(size_t i = 0; i != rows.size(); ++i)
	{
		if (rows[i]->rowType() == VirtualRow::HEADER)
		{
			vec.push_back(rows[i]);
			continue;
		}
	}
	return vec;
}

size_t getNextPage(vector<shared_ptr<VirtualRow>>& rows)
{
	return 0;
}

void addHeader(vector<shared_ptr<VirtualRow>>& headers, vector<shared_ptr<VirtualRow>>& table, size_t i)
{
	
}


void addHeaders(vector<shared_ptr<VirtualRow>>& rows, vector<shared_ptr<VirtualRow>>& table)
{
	auto headers = getHeaders(table);	
	while(auto i = getNextPage(table))		
		addHeader(headers, table, i);
}

void PDFCreator::fixNewTable(vector<shared_ptr<VirtualRow>>& rows)
{
	auto tables = getTables(rows);
	for(size_t i = 0; i != tables.size(); ++i)
	{
		if (isLastRow(tables[i]))
		{
			addRowNumber(rows, tables[i][0]->index());
			continue;
		}
		auto crossed = crossMultipages(tables[i]);
		Debugger::write("crossed", crossed);
		//else if (crossMultipages(tables[i]))
		//	addHeaders(rows, tables[i]);
		//else if (crossOnePage(tables[i]))
		//	addHeader(tables[i]);
	}
}

vector<shared_ptr<VirtualRow>> PDFCreator::fixTable(const vector<shared_ptr<VirtualRow>>& rows)
{
	vector<shared_ptr<VirtualRow>> newRows = rows;
	fixNewTable(newRows);
	return newRows;
}

PDFDocument PDFCreator::generateMultipageDocument(const vector<shared_ptr<VirtualRow>>& rows)
{
	auto doc = createDocument();
	auto font = getFontFrom(doc);
	fixTable(rows);
	auto count = calculatePages(rows.size());
	for(size_t i = 0; i != count; ++i)
	{
		auto page = doc.addPage();
		page.setFontAndSize(font, 12);
		if ( i == 0)
			drawCover(page, rows);
		else
			drawPage(page, rows, i);
	}
	return doc;
}

void PDFCreator::drawTitle(PDFPage& page, PDFFont& font, const std::string& title)
{
	auto x = (page.width() - page.textWidth(title)) / 2 - 25;
	auto y = page.height() - logoHeight() - titleHeight();
	page.setFontAndSize(font, 18);
	page.textOut(title, x, y);
}

static string footer(size_t index, size_t count)
{
	stringstream ss;
	ss << "本笔业务共 " << count << "页，第 " << index << " 页";
	return ss.str();
}


void PDFCreator::drawFooters(PDFDocument& doc, PDFFont& font)
{
	for(size_t i = 0; i != doc.pages().size(); ++i)
	{
		auto page = doc.pages()[i];
		page.setFontAndSize(font, 10);
		auto text = footer(i + 1, doc.pages().size());
		auto width = doc.pages()[i].textWidth(text);
		auto x = (doc.pages()[i].width() - width) / 2;
		auto y = verticalMargin();
		doc.pages()[i].textOut(text, x, y);
	}
}

vector<shared_ptr<VirtualRow>> actualRows(const vector<shared_ptr<VirtualRow>>& rows, size_t pageRowNumber)
{
	if (rows.size() <= pageRowNumber)
		return rows;
	vector<shared_ptr<VirtualRow>> actual;
	copy(rows.begin(), rows.begin() + pageRowNumber, back_inserter(actual));
	return actual;
}

vector<shared_ptr<VirtualRow>> PDFCreator::actualRows(const vector<shared_ptr<VirtualRow>>& rows, size_t pageRowNumber, size_t index)
{
	size_t beginning = a4CoverRowsNumber() + a4RowsNumber() * (index - 1);
	size_t ending = 0;
	size_t left = rows.size() - beginning;
	vector<shared_ptr<VirtualRow>> vec;
	if (left >= a4RowsNumber())
	{
		auto ending = beginning + a4RowsNumber();
		copy(rows.begin() + beginning, rows.begin() + ending, back_inserter(vec));
	}
	else
		copy(rows.begin() + beginning, rows.end(), back_inserter(vec));
	return vec;
}

void drawPairColumn(PDFPage& page, const shared_ptr<VirtualColumn>& column, float x, float y, float w)
{
	float width = w / 2;
}

void PDFCreator::outputContent(PDFPage& page, const vector<shared_ptr<VirtualRow>>& rows, size_t beginningY)
{
	for(size_t i = 0; i != rows.size(); ++i)
	{
		float y = page.height() - beginningY - rowHeight() - i * rowHeight();
	}
}

void PDFCreator::drawVirtualRow(PDFPage& page, const shared_ptr<VirtualRow>& row, float y)
{
	for(size_t j = 0; j != row->columns().size(); ++j)
	{
		assert(row->columns()[j]->columnIndex() < 10);
		auto w = page.width() / row->columnCount();
		float x = horizonalMargin() + w * row->columns()[j]->columnIndex();
		auto s = row->columns()[j]->text();
		page.textOut(s, x, y);
	}
}

void PDFCreator::drawCover(PDFPage& page, const vector<shared_ptr<VirtualRow>>& rows)
{
	auto actual = ::actualRows(rows, a4CoverRowsNumber());
	for(size_t i = 0; i != actual.size(); ++i)
	{
		auto h = page.height();
		auto w = page.width();
		float y = page.height() - verticalMargin() - logoHeight() - titleHeight() - rowHeight() - i * rowHeight();
		drawVirtualRow(page, actual[i], y);
	}
}

void PDFCreator::drawPage(PDFPage& page, const vector<shared_ptr<VirtualRow>>& rows, size_t index)
{
	auto actual = actualRows(rows, a4RowsNumber(), index);
	for(size_t i = 0; i != actual.size(); ++i)
	{
		auto y = page.height() - verticalMargin() - logoHeight() - rowHeight() - i * rowHeight();
		drawVirtualRow(page, actual[i], y);
	}
}


PDFDocument PDFCreator::generateA5Document(const vector<shared_ptr<VirtualRow>>& rows)
{
	auto doc = createDocument();
	auto page = doc.addPage();
	page.setSize(HPDF_PAGE_SIZE_A5, HPDF_PAGE_LANDSCAPE);
	auto w = page.width();
	auto h = page.height();
	page.setFontAndSize(getFontFrom(doc), 12);
	for(size_t i = 0; i != rows.size(); ++i)
	{
		auto y = page.height() - verticalMargin() - logoHeight() - titleHeight() - rowHeight() - i * rowHeight();
		drawVirtualRow(page, rows[i], y);
	}
	return doc;
}

PDFDocument PDFCreator::createDocument()
{
	PDFDocument doc;
	doc.initiate();
	doc.useCNSEncoding();
	return doc;
}

