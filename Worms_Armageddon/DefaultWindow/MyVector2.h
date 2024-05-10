#pragma once
#include <cmath>

class CMyVector2
{



public:
	CMyVector2() : fX(0.0f), fY(0.0f) {};
	CMyVector2(const float& _fX, const float& _fY) : fX(_fX), fY(_fY) {}
	CMyVector2(const int& _iX, const int& _iY) : fX(float(_iX)), fY(float(_iY)) {}
	~CMyVector2() {};


	CMyVector2			operator -	(const CMyVector2& _v) const { return CMyVector2{ fX - _v.fX, fY - _v.fY }; };
	CMyVector2			operator +	(const CMyVector2& _v) const { return CMyVector2{ fX + _v.fX, fY + _v.fY }; };
	CMyVector2			operator *	(const float& _f) const { return CMyVector2{ fX * _f, fY * _f }; };
	CMyVector2			operator /	(const float& _f) const { return CMyVector2{ fX / _f, fY / _f }; };
	const CMyVector2&	operator += (const CMyVector2& _v) { fX += _v.fX; fY += _v.fY; return *this; };
	const CMyVector2&	operator -= (const CMyVector2& _v) { fX -= _v.fX; fY -= _v.fY; return *this; };
	const CMyVector2&	operator -= (const float& _f) { fX -= _f; fY -= _f; return *this; };
	const CMyVector2&	operator *= (const float& _f) { fX *= _f;	fY *= _f; return *this; };
	const CMyVector2&	operator /= (const float& _f) { fX /= _f;	fY /= _f; return *this; };
	bool					operator != (const CMyVector2& _v) { return(fX != _v.fX || fY != _v.fY); }
	bool					operator == (const CMyVector2& _v) { return(fX == _v.fX && fY == _v.fY); }

	const float				Get_Magnitude()	const { return sqrt(pow(fX, 2) + pow(fY, 2)); }
	const CMyVector2		Get_Normalized() const { return CMyVector2(fX / Get_Magnitude(), fY / Get_Magnitude()); }
	void					Normalize() { fX /= Get_Magnitude(); fY /= Get_Magnitude(); }
	void                    Zero() { fX = 0.f; fY = 0.f; }


	float					Get_fX(void) { return fX; }
	float					Get_fY(void) { return fY; }
	void					Set_fX(float _fX) { fX = _fX; }


	void					Set_fY(float _fY) 
	{ 
		fY = _fY; 
	}

	float					Get_fCX(void) { return fCX; }
	float					Get_fCY(void) { return fCY; }
	void					Set_fCX(float _fCX) { fCX = _fCX; }
	void					Set_fCY(float _fCY) { fCY = _fCY; }

public:
	float fX;
	float fY;

	float fCX;
	float fCY;
};

