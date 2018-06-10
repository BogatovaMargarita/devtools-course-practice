#pragma once
class TDatValue;
typedef TDatValue * PTDatValue;

class TDatValue
{
public:
	virtual TDatValue * GetCopy() = 0;
	virtual ~TDatValue() {};
};
