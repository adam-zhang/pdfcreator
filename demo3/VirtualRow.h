#pragma once
#include <memory>
#include <vector>

class VirtualColumn;
class VirtualPage;


class VirtualRow
{
public:
	enum RowType
	{
		NORMAL,
		HEADER,
		NEWHEADER,
	};
public:
	VirtualRow(void);
	~VirtualRow(void);
private:
	std::vector<std::shared_ptr<VirtualColumn>> columns_;
	size_t columnCount_;
	RowType rowType_;
	size_t index_;
public:
	size_t index()const
	{ return index_;}
	void setIndex(size_t value)
	{ index_ = value;}
	RowType rowType()
	{ return rowType_;}
	void setRowType(RowType value)
	{ rowType_ = value;}
	std::vector<std::shared_ptr<VirtualColumn>>& columns()
	{ return columns_;}
	size_t columnCount()
	{ return columnCount_;}
	void setColumnCount(size_t value)
	{ columnCount_ = value;}
};

