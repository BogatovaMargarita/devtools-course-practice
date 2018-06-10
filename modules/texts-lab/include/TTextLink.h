#pragma once
#include "include/TDatValue.h"
#include <stdexcept>
#include <iostream>

#define TEXT_LINE_LENGTH 50
#define MEM_SIZE 1000

class TTextLink;
typedef TTextLink* PTTextLink;

class TText;
typedef TText * PTText;

typedef char TStr[TEXT_LINE_LENGTH];

class TTextMem {
	PTTextLink pFirst;                              // ��������� �� ������ �����
	PTTextLink pLast;                               // ��������� �� ��������� �����
	PTTextLink pFree;                               // ��������� �� ������ ��������� �����
	//
	//TTextMem(PTTextLink pF = nullptr, PTTextLink pL = nullptr, PTTextLink pFr = nullptr)
	//{
	//	pFirst = pF;
	//	pLast = pL;
	//	pFree = pFr;
	//}
	friend class TTextLink;
};
typedef TTextMem * PTTextMem;

class TTextLink : public TDatValue {
protected:
	TStr Str;                                       // ���� ��� �������� ������ ������
	PTTextLink pNext, pDown;                        // ��������� �� ���. ������� � �� ����������
	static TTextMem MemHeader;                      // ������� ���������� �������

	void SetStr(std::string str);
public:
	TTextLink(string s = "", PTTextLink pn = nullptr, PTTextLink pd = nullptr); 
	
	static void InitMemSystem(int size = MEM_SIZE);  // ������������� ������
	static void PrintFreeLink(void);                 // ������ ��������� �������
	static void MemCleaner(TText txt);               // ������ ������
	static void DelMemSystem();
	void * operator new (size_t size);               // ��������� �����
	void operator delete (void *pM);                 // ������������ �����
	
	int IsAtom()		 { return pDown == nullptr; }// �������� ����������� �����
	PTTextLink GetNext() { return pNext; }
	PTTextLink GetDown() { return pDown; }
	PTDatValue GetCopy() { return new TTextLink(Str, pNext, pDown); }

	~TTextLink() {}

	friend class TText;
	friend std::ostream& operator<<(std::ostream& os, TTextLink &t);
};