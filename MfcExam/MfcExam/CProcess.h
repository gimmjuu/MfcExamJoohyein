﻿#pragma once

// CProcess 명령 대상

class CProcess : public CObject
{
public:
	CProcess();
	virtual ~CProcess();

	int GetStarInfo(CImage* pImage, int nTh = 100);
};


