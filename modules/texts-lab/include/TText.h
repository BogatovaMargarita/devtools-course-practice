#define _CRT_SECURE_NO_WARNINGS

#pragma once
#include "include/TDataCom.h"
#include "include/TTextLink.h"
#include <stack>
#include <cstring>

#define TextOk 0
#define TextNoDown 101
#define TextNoNext 102 // 
#define TextNoPrev 103 // ������� � ������ ������
#define TextError -102
#define TextNoMem -101


class TText : public TDataCom {
protected:
	PTTextLink pFirst;                      // ��������� ����� ������
	PTTextLink pCurrent;                    // ��������� ������� ������
	stack < PTTextLink > Path;              // ���� ���������� �������� �� ������
	stack < PTTextLink > St;                // ���� ��� ���������

	PTTextLink GetFirstAtom(PTTextLink pl); // ����� ������� �����
	PTTextLink ReadText(ifstream &TxtFile); // ������ ������ �� �����
	void       PrintText(PTTextLink ptl);   // ������ ������ �� ����� ptl

public:
	TText (PTTextLink pl = nullptr);
	TText(const TText & txt);
	~TText() { pFirst = nullptr; }

	PTText getCopy();
                                            // ���������
	int GoFirstLink(void);                  // ������� � ������ ������
	int GoDownLink(void);                   // ������� � ��������� ������ �� Down
	int GoNextLink(void);                   // ������� � ��������� ������ �� Next
	int GoPrevLink(void);                   // ������� � ���������� ������� � ������
                                            // ������
	string GetLine(void);                   // ������ ������� ������
	void   SetLine(string s);               // ������ ������� ������ 
                                            // �����������
	void InsDownLine(string s);             // ������� ������ � ����������
	void InsDownSection(string s);          // ������� ������� � ����������
	void InsNextLine(string s);             // ������� ������ � ��� �� ������
	void InsNextSection(string s);          // ������� ������� � ��� �� ������
	void DelDownLine(void);                 // �������� ������ � ���������
	void DelDownSection(void);              // �������� ������� � ���������
	void DelNextLine(void);                 // �������� ������ � ��� �� ������
	void DelNextSection(void);              // �������� ������� � ��� �� ������
                                            // ��������
	int Reset(void);                        // ���������� �� ������ �������
											// ����� ��������?
	int IsTextEnded(void) const { return !St.size(); } 
	int GoNext(void);                       // ������� � ��������� ������
                                            //������ � �������
	void Read(char * pFileName);            // ���� ������ �� �����
	void Write(char * pFileName);           // ����� ������ � ����
                                            //������
	void Print(void) { PrintText(pFirst); } // ������ ������
};