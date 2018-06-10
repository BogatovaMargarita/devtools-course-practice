#include "include/TText.h"
#include <cstring>

TTextMem TTextLink::MemHeader;

TTextLink::TTextLink(string s, PTTextLink pn, PTTextLink pd)
{
	if (s.size() > TEXT_LINE_LENGTH) throw std::out_of_range("String length is too long");
	pNext = pn;
	pDown = pd;
	if (s.size() != 0) strcpy(Str, s.c_str());
	else Str[0] = '\0';
}

void TTextLink::InitMemSystem(int size)
{
	if (size <= 0) std::out_of_range("Size is incorrect!");

	if (MemHeader.pFirst != nullptr){
		std::cout << " Memory has already been allocated! " << std::endl;
		throw std::string("Memory has already been allocated!");
	}
	else {
		MemHeader.pFirst = (PTTextLink) new char[size * sizeof(TTextLink)];
		MemHeader.pLast = MemHeader.pFirst + (size - 1);
		MemHeader.pFree = MemHeader.pFirst;

		PTTextLink tmp = MemHeader.pFirst;
		for (int i = 0; i < size - 1; i++){
			tmp->pNext = tmp + 1;
			tmp = tmp->pNext;
		}
		tmp->pNext = nullptr;
	}
}

void TTextLink::PrintFreeLink(void)
{
	PTTextLink tmp = MemHeader.pFree;
	std::cout << "Free links: " << std::endl;

	for (; tmp->pNext != nullptr; tmp = tmp->pNext)
		std::cout << tmp->Str << std::endl;
}

void TTextLink::MemCleaner(TText txt)
{
	char marker[9] = "&&&";
	std::string tmpStr;

	for (txt.Reset(); txt.IsTextEnded(); txt.GoNext())
		txt.SetLine(marker + txt.GetLine());

	PTTextLink tmp = MemHeader.pFree;
	for (; tmp->pNext != nullptr; tmp = tmp->pNext)
		strcpy(tmp->Str, marker);

	tmp =  MemHeader.pFirst;
	for (; tmp->pNext != nullptr; tmp++, tmpStr=tmp->Str)
		if (tmpStr.find(marker) == 0)
			delete tmp;
}

void TTextLink::DelMemSystem()
{
	if (MemHeader.pFirst != nullptr) {
		delete[](char *)MemHeader.pFirst;
		MemHeader.pFirst = MemHeader.pFree = MemHeader.pLast = nullptr;
	}
}

void * TTextLink::operator new(size_t size)
{
	PTTextLink tmp = MemHeader.pFree;
	if (MemHeader.pFree != nullptr) MemHeader.pFree = MemHeader.pFree->pNext;
	return tmp;
}

void TTextLink::operator delete(void * pM)
{
	PTTextLink tmp = (PTTextLink)pM;
	tmp->pNext = MemHeader.pFree;
	MemHeader.pFree = tmp;
}

void TTextLink::SetStr(std::string str)
{
	strcpy(Str, str.c_str());
	Str[str.length()] = '\0';
}

std::ostream & operator<<(std::ostream & os, TTextLink & t)
{
	os << t.Str << std::endl;
	return os;
}
