#define _CRT_SECURE_NO_WARNINGS

#pragma once
#include "include/TDataCom.h"
#include "include/TTextLink.h"
#include <stack>
#include <cstring>

#define TextOk 0
#define TextNoDown 101
#define TextNoNext 102 // 
#define TextNoPrev 103 // позиция в начале текста
#define TextError -102
#define TextNoMem -101


class TText : public TDataCom {
protected:
	PTTextLink pFirst;                      // указатель корня дерева
	PTTextLink pCurrent;                    // указатель текущей строки
	stack < PTTextLink > Path;              // стек траектории движения по тексту
	stack < PTTextLink > St;                // стек для итератора

	PTTextLink GetFirstAtom(PTTextLink pl); // поиск первого атома
	PTTextLink ReadText(ifstream &TxtFile); // чтение текста из файла
	void       PrintText(PTTextLink ptl);   // печать текста со звена ptl

public:
	TText (PTTextLink pl = nullptr);
	TText(const TText & txt);
	~TText() { pFirst = nullptr; }

	PTText getCopy();
                                            // навигация
	int GoFirstLink(void);                  // переход к первой строке
	int GoDownLink(void);                   // переход к следующей строке по Down
	int GoNextLink(void);                   // переход к следующей строке по Next
	int GoPrevLink(void);                   // переход к предыдущей позиции в тексте
                                            // доступ
	string GetLine(void);                   // чтение текущей строки
	void   SetLine(string s);               // замена текущей строки 
                                            // модификация
	void InsDownLine(string s);             // вставка строки в подуровень
	void InsDownSection(string s);          // вставка раздела в подуровень
	void InsNextLine(string s);             // вставка строки в том же уровне
	void InsNextSection(string s);          // вставка раздела в том же уровне
	void DelDownLine(void);                 // удаление строки в подуровне
	void DelDownSection(void);              // удаление раздела в подуровне
	void DelNextLine(void);                 // удаление строки в том же уровне
	void DelNextSection(void);              // удаление раздела в том же уровне
                                            // итератор
	int Reset(void);                        // установить на первую звапись
											// текст завершен?
	int IsTextEnded(void) const { return !St.size(); } 
	int GoNext(void);                       // переход к следующей записи
                                            //работа с файлами
	void Read(char * pFileName);            // ввод текста из файла
	void Write(char * pFileName);           // вывод текста в файл
                                            //печать
	void Print(void) { PrintText(pFirst); } // печать текста
};