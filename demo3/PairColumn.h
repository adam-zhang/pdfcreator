#pragma once
#include "virtualcolumn.h"
#include <vector>
#include <memory>

class PairColumn : public VirtualColumn
{
public:
	PairColumn(void);
	~PairColumn(void);
private:
	std::string value_;
public:
	void setValue(const std::string& value)
	{ value_ = value;}
	const std::string& value()const
	{ return value_;}
public:
	const std::string text()const
	{ return label() + value();}
};

