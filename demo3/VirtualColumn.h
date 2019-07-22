#pragma once
#include <string>
#include <memory>
#include <vector>

//class VirtualRow;

class VirtualColumn
{
public:
	VirtualColumn(void);
	VirtualColumn(const std::string& label, size_t rowIndex, size_t columnIndex)
		: label_(label)
		, rowIndex_(rowIndex)
		, columnIndex_(columnIndex)
		, empty_(false)
	{}
	~VirtualColumn(void);
public:
	const std::string& label()const
	{ return label_;}
	void setLabel(const std::string& label)
	{ label_ = label;}
	size_t rowIndex()const
	{ return rowIndex_;}
	void setRowIndex(size_t value)
	{ rowIndex_ = value;}
	size_t columnIndex()
	{ return columnIndex_;}
	void setColumnIndex(size_t value)
	{ columnIndex_ = value;}
	virtual const std::string text()const
	{ return label();}
	bool empty()
	{ return empty_;}
private:
	std::string label_;
	size_t rowIndex_;
	size_t columnIndex_;
	bool empty_;
};

