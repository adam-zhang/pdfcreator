#pragma once
#include <memory>
#include <vector>

class VirtualRow;

class VirtualPage
{
public:
	VirtualPage(void);
	~VirtualPage(void);
private:
	std::vector<std::shared_ptr<VirtualRow>> rows_;
public:
	std::vector<std::shared_ptr<VirtualRow>> rows()
	{ return rows_;}
private:
	float width_;
	float height_;
	float horizonalMargin_;
	float verticalMargin_;
public:
	float horizonalMargin()
	{ return horizonalMargin_;}
	void setHorizonalMargin(float value)
	{ horizonalMargin_ = value;}
	float verticalMargin()
	{ return verticalMargin_;}
	void setVerticalMargin(float value)
	{ verticalMargin_ = value;}
	float width()
	{ return width_;}
	void setWidth(float w)
	{ width_ = w;}
	float height()
	{ return height_;}
	void setHeight(float h)
	{ height_ = h;}
};

