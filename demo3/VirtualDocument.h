#pragma once
#include <memory>
#include <vector>

class VirtualPage;

class VirtualDocument
{
public:
	enum PAGE_SIZE
	{
		PAGE_SIZE_A5,
		PAGE_SIZE_A4,
	};
public:
	VirtualDocument(void);
	~VirtualDocument(void);
private:
	std::vector<std::shared_ptr<VirtualPage>> pages_;
	PAGE_SIZE pageSize_;
public:
	std::vector<std::shared_ptr<VirtualPage>> pages()
	{ return pages_;}
	void setPageSize(PAGE_SIZE value)
	{ pageSize_ = value;}
	PAGE_SIZE pageSize()
	{ return pageSize_;}
};

