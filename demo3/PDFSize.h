#pragma once


class PDFSize
{
public:
	PDFSize(void);
	PDFSize(float width, float height);
	~PDFSize(void);
private:
	float width_;
	float height_;
public:
	float width()
	{return width_;}
	void setWidth(float value)
	{ width_ =value;}
	float height()
	{ return height_;}
	void setHeight(float value)
	{ height_ = value;}
};


//PDFSize A4Size()
//{
//	return PDFSize(210, 297);
//}

//PDFSize A5Size()
//{
//	return PDFSize(210, 148);
//}