#include "pch.h"
#include "StdAfx.h"
#include "Graphic.h"

Graphic::Graphic(HDC hdc)
{
	m_hDC=hdc;

	m_hpenOld=NULL;
	//当前画笔
	m_hpenCur=NULL;
	//旧的画刷
	m_hbrOld=NULL;
	//当前画刷
	m_hbrCur=NULL;
	//旧的字体
	m_hfontOld=NULL;
	//当前字体
	m_hfontCur=NULL;
	//
	m_clrText=0;
}

Graphic::~Graphic(void)
{
	if(m_hpenOld!=NULL) ::SelectObject(m_hDC,m_hpenOld);
	if(m_hpenCur!=NULL) ::DeleteObject(m_hpenCur);

	if(m_hbrOld!=NULL) ::SelectObject(m_hDC,m_hbrOld);
	if(m_hbrCur!=NULL) ::DeleteObject(m_hbrCur);

	if(m_hfontOld!=NULL) ::SelectObject(m_hDC,m_hfontOld);
	if(m_hfontCur!=NULL) ::DeleteObject(m_hfontCur);
}
// 选择一种画笔
void Graphic::SelectAPen(HPEN hpen)
{
	HPEN hpold;
	hpold=(HPEN)::SelectObject(m_hDC,hpen);
	if(m_hpenOld==NULL) m_hpenOld=hpold;
	if(m_hpenCur!=NULL) ::DeleteObject(m_hpenCur);
	m_hpenCur=hpen;
}
// 生成并选择一种画笔
void Graphic::SelectAPen(int npstyle, int nwidth, COLORREF color)
{
	HPEN hpen=::CreatePen(npstyle,nwidth,color);
	SelectAPen(hpen);;
}

// 生成并选择一种画刷
void Graphic::SelectABrush(HBRUSH hbrush)
{
	HBRUSH hbrold;
	hbrold=(HBRUSH)::SelectObject(m_hDC,hbrush);
	if(m_hbrOld==NULL) m_hbrOld=hbrold;
	if(m_hbrCur!=NULL) ::DeleteObject(m_hbrCur);
	m_hbrCur=hbrush;
}
// 生成并选择一种画刷
void Graphic::SelectABrush(COLORREF color)
{
	HBRUSH hbr=::CreateSolidBrush(color);
	SelectABrush(hbr);;
}
// 采用当前画笔，绘制一条直线
void Graphic::DrawLine(int x1, int y1, int x2, int y2)
{
	::MoveToEx(m_hDC,x1,y1,NULL);
	::LineTo(m_hDC,x2,y2);
}
// 绘制一个矩形
void Graphic::DrawRect(RECT rect,bool bfill)
{
	if(bfill) 
		::Rectangle(m_hDC,rect.left,rect.top,rect.right,rect.bottom);
	else
	{
		::MoveToEx(m_hDC,rect.left,rect.top,NULL);
		::LineTo(m_hDC,rect.right,rect.top);
		::LineTo(m_hDC,rect.right,rect.bottom);
		::LineTo(m_hDC,rect.left,rect.bottom);
		::LineTo(m_hDC,rect.left,rect.top);
	}
}
// 绘制一个矩形
void Graphic::DrawRect(int x1, int y1, int wx, int hy,bool bfill)
{
	RECT rc={x1,y1,x1+wx,y1+hy};
	DrawRect(rc,bfill);
}

// 用颜色填充一个矩形
void Graphic::FillRect(RECT rect, COLORREF color)
{	//利用API函数实现矩形填充
	HBRUSH hbr=::CreateSolidBrush(color);
	::FillRect(m_hDC,&rect,hbr);
	::DeleteObject(hbr);
}
// 用颜色填充一个矩形
void Graphic::FillRect(int x, int y, int wx, int hy, COLORREF color)
{
	RECT rect;
	rect.left=x;
	rect.right=x+wx;
	rect.top=y;
	rect.bottom=y+hy;
	//调用重载函数实现矩形填充
	FillRect(rect,color);
}

// 绘制一个圆形
void Graphic::DrawCircle(int x, int y, int radius)
{	//调用API函数绘制圆
	::Ellipse(m_hDC,x-radius,y-radius,x+radius,y+radius);
}
// 生成一种字体
HFONT Graphic::CreateAFont(TCHAR *sfontname,int nfontsize,bool bbold,bool bitalic)
{
	int nWeight=bbold?700:400;
	DWORD dwItalic=bitalic?1:0;
	HFONT  hfont;
	hfont=::CreateFont(
		-::MulDiv(nfontsize, GetDeviceCaps(m_hDC, LOGPIXELSY), 72),		//字体高度
		0,					//平均字体宽度，默认为0
		0,					//字体显示的角度，默认为0
		0,					//字体基线的角度，默认为0
		nWeight,			//字体的粗细
		dwItalic,			//斜体字属性开关，可以选择1和0，默认为0
		0,					//下划线属性开关，可以选择1和0，默认为0
		0,					//带删除线的属性开关，可以选择1和0，默认为0
		DEFAULT_CHARSET,	//所需的字符集，默认为DEFAULT_CHARSET
		0,					//输出的精度，默认为0
		0,					//剪裁的精度，默认为0
		0,					//逻辑字体与输出设备的实际字体之间的精度，默认为0
		0,					//字体间距和字体集，默认为0
		sfontname			//字体名称
	);
	return hfont;
}
// 生成并选择一种字体
void Graphic::SelectAFont(TCHAR *sfontname,int nfontsize,bool bbold,bool bitalic)
{
	HFONT  hfont,hfold;
	hfont=CreateAFont(sfontname,nfontsize,bbold,bitalic);
	hfold=(HFONT)::SelectObject(m_hDC,hfont);
	if(m_hfontOld==NULL) m_hfontOld=hfold;
	if(m_hfontCur!=NULL) ::DeleteObject(m_hfontCur);
	m_hfontCur=hfont;
}
//在指定矩形内绘制文字
void Graphic::DrawText(TCHAR *stext,RECT rect)
{
	::SetTextColor(m_hDC,m_clrText);
	::SetBkMode(m_hDC,TRANSPARENT);
	::DrawText(m_hDC,stext,-1,&rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_NOCLIP);
}

//-------------------------------------------------------
// VER1.1,新增绘制图片功能
void Graphic::DrawBitmap(HBITMAP hbmp, int x, int y)
{
	BITMAP	bminfo;
	HDC memdc = CreateCompatibleDC(m_hDC);  //内存DC
	GetObject(hbmp, sizeof(bminfo), &bminfo);  //获取图片大小信息
	SelectObject(memdc, hbmp);        //将g_bg_bmp选入内存DC
	BitBlt(m_hDC, x, y, bminfo.bmWidth, bminfo.bmHeight, memdc, 0, 0, SRCCOPY);  //贴图到目标DC 
	DeleteDC(memdc);
}