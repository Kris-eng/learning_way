#pragma once
#ifndef GRAPHIC_H
#define GRAPHIC_H



//
//  本程序版权归 程磊、李爱华 所有
//
//图形工具类
class Graphic
{
private:
	HDC  m_hDC;			//设备环境句柄
	HPEN m_hpenOld;		//旧的画笔
	HPEN m_hpenCur;		//当前画笔
	HBRUSH m_hbrOld;	//旧的画刷
	HBRUSH m_hbrCur;	//当前画刷
	HFONT  m_hfontOld;	//旧的字体
	HFONT  m_hfontCur;	//当前的字体
	COLORREF m_clrText;	//文本的颜色
public:
	//构造函数
	Graphic(HDC hdc=NULL);
	//析构函数
	~Graphic(void);
public:
	//设置环境句柄
	void SetHDC(HDC hdc);
	// 生成并选择一种画笔
	void SelectAPen(HPEN hpen);
	// 生成并选择一种画笔
	void SelectAPen(int npstyle, int nwidth, COLORREF color);
	// 生成并选择一种画刷
	void SelectABrush(HBRUSH hbrush);
	// 生成并选择一种画刷
	void SelectABrush(COLORREF color);
	// 生成一种字体
	HFONT CreateAFont(TCHAR *sfontname,int nfontsize,bool bbold=false,bool bitalic=false);
	// 生成并选择一种字体
	void SelectAFont(TCHAR *sfontname,int nfontsize,bool bbold=false,bool bitalic=false);
	// 采用当前画笔，绘制一条直线
	void DrawLine(int x1, int y1, int x2, int y2);
	// 绘制一个矩形
	void DrawRect(RECT rect,bool bfill=true);
	// 绘制一个矩形
	void DrawRect(int x1, int y1, int wx, int hy,bool bfill=true);
	// 用颜色填充一个矩形
	void FillRect(RECT rect, COLORREF color);
	// 用颜色填充一个矩形
	void FillRect(int x, int y, int wx, int hy, COLORREF color);
	// 绘制一个圆形
	void DrawCircle(int x, int y, int radius);
	//在指定矩形内绘制文字
	void DrawText(TCHAR *stext,RECT rect);
	//-------------------------------------------------------
	// VER1.1,新增绘制图片功能
	void DrawBitmap(HBITMAP hbmp,int x,int y);

public:
	//设置文本颜色属性
	void SetTextColor(COLORREF color)
	{ m_clrText=color;}
	//返回当前画笔
	HPEN GetCurPen(){return m_hpenCur;}
	//返回当前画刷
	HBRUSH GetCurBrush(){return m_hbrCur;}
	//返回当前字体
	HFONT GetCurFont(){return m_hfontCur;}
	//得到一种随机颜色，静态成员函数
	static COLORREF GetRandColor()
	{ return RGB(rand()%256,rand()%256,rand()%256);}
};
#endif // !GRAPHIC_H