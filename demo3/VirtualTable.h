#pragma once
#include <vector>
#include <memory>

class VirtualHeaders;
class VirtualRow;

class VirtualTable
{
public:
	VirtualTable(void);
	~VirtualTable(void);
public:
	const std::shared_ptr<VirtualHeaders>& headers()
	{ return headers_;}
	void setHeaders(const std::shared_ptr<VirtualHeaders>& value)
	{ headers_ = value;}
	std::vector<std::shared_ptr<VirtualRow>>& rows()
	{ return rows_;}

private:
	std::shared_ptr<VirtualHeaders> headers_;
	std::vector<std::shared_ptr<VirtualRow>> rows_;
};

