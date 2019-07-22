#pragma once
#include <string>
#include <vector>
#include <memory>

typedef struct TRADE_st
{
	int row;
	int col;
	int style;//0 default 1 red 2 bold 3 redbold
	int colTotal;
	std::string label;
	std::string value;
	int keyword;
	TRADE_st()
	{
		row = 0;
		col = 0;
		colTotal = 0;
		label = "";
		value = "";
		keyword = 0;
	}
}TRADE,*PTRADE;


class Trade
{
public:
	Trade(void)
	{
		initialize();
	}
	explicit Trade(const TRADE& value)
		: row(value.row)
		, col(value.col)
		, colTotal(value.colTotal)
		, label(value.label)
		, value(value.value)
		, keyword(value.keyword)
	{
	}
	~Trade(void);


	int row;
	int col;
	int style;//0 default 1 red 2 bold 3 redbold
	int colTotal;
	std::string label;
	std::string value;
	int keyword;

private:
	void initialize()
	{
		row = 0;
		col = 0;
		colTotal = 0;
		//label = "";
		//value = "";
		keyword = -1;
	}
};

//class Transaction
//{
//public:
//	std::string title_;
//	std::vector<std::shared_ptr<Trade>> trades_;
//public:
//	void setTitle(const std::string& title)
//	{ title_ = title;}
//	const std::string& title()const
//	{ return title_;}
//	std::vector<std::shared_ptr<Trade>> trades()
//	{ return trades_;}
//};
