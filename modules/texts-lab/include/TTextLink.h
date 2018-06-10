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
	PTTextLink pFirst;                              // указатель на первое звено
	PTTextLink pLast;                               // указатель на последнее звено
	PTTextLink pFree;                               // указатель на первое свободное звено
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
	TStr Str;                                       // поле для хранения строки текста
	PTTextLink pNext, pDown;                        // указатели по тек. уровень и на подуровень
	static TTextMem MemHeader;                      // система управления памятью

	void SetStr(std::string str);
public:
	TTextLink(string s = "", PTTextLink pn = nullptr, PTTextLink pd = nullptr); 
	
	static void InitMemSystem(int size = MEM_SIZE);  // инициализация памяти
	static void PrintFreeLink(void);                 // печать свободных звеньев
	static void MemCleaner(TText txt);               // сборка мусора
	static void DelMemSystem();
	void * operator new (size_t size);               // выделение звена
	void operator delete (void *pM);                 // освобождение звена
	
	int IsAtom()		 { return pDown == nullptr; }// проверка атомарности звена
	PTTextLink GetNext() { return pNext; }
	PTTextLink GetDown() { return pDown; }
	PTDatValue GetCopy() { return new TTextLink(Str, pNext, pDown); }

	~TTextLink() {}

	friend class TText;
	friend std::ostream& operator<<(std::ostream& os, TTextLink &t);
};