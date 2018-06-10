#include "include/TText.h"
#include <fstream>  

PTTextLink TText::GetFirstAtom(PTTextLink pl)
{
	PTTextLink tmp = pl;
	for (; tmp->IsAtom(); St.push(tmp), tmp = tmp->pDown);
	return tmp;
}

PTTextLink TText::ReadText(ifstream & TxtFile)
{
	PTTextLink root = new TTextLink, tmp = root;
	char buf[TEXT_LINE_LENGTH];

	while (!TxtFile.eof())
	{
		TxtFile.getline(buf, TEXT_LINE_LENGTH);
		if (buf[0] == '{')
		{
			tmp->pDown = ReadText(TxtFile);
		}
		else if (buf[0] == '}')
		{
			break;
		}
		else
		{
			tmp->pNext = new TTextLink(buf, nullptr, nullptr);
			tmp = tmp->pNext;
		}
	} 

	tmp = root;
	if (root->pDown == nullptr)
	{
		root = root->pNext;
		delete tmp;
	}
	return root;
}

void TText::PrintText(PTTextLink ptl)
{
	if (ptl != nullptr)
	{
		cout << *ptl;
		PrintText(ptl->pDown);
		PrintText(ptl->pNext);
	}
}

TText::TText(PTTextLink pl)
{
	if (pl == nullptr)
		pFirst =  new TTextLink;
	else pFirst = pl;

	pCurrent = nullptr;
}

TText::TText(const TText & txt)
{
	PTTextLink copyHead = nullptr, currentLink = txt.pFirst, topLink, newLink;

	if (txt.pFirst != nullptr)
	{
		while (!St.empty()) St.pop();
		while (1)
			if (currentLink != nullptr)
			{
				St.push(currentLink);
				currentLink = currentLink->GetDown();
			}
			else if (St.empty()) break;
			else
			{
				topLink = St.top();	St.pop();
				if (strstr(topLink->Str, "Copy") == nullptr)
				{
					newLink = new TTextLink("Copy", topLink, copyHead);
					St.push(newLink);
					currentLink = topLink->pNext;
					copyHead = nullptr;
				}
				else
				{
					topLink->SetStr(topLink->pNext->Str);
					topLink->pNext = copyHead;
					copyHead = topLink;
				}
			}
	}
	pFirst = pCurrent = copyHead;
}

PTText TText::getCopy()
{
	PTTextLink copyHead = nullptr, currentLink = pFirst, topLink, newLink;

	if (pFirst != nullptr)
	{
		while (!St.empty()) St.pop();
		while (1)

			if (currentLink != nullptr)
			{
				// Идем вниз до атомарного звена
				St.push(currentLink);
				currentLink = currentLink->GetDown();
			}
			else if (St.empty()) break;
			else
			{
				topLink = St.top();	St.pop();
				if (strstr(topLink->Str, "Copy") == nullptr)
				{
					newLink = new TTextLink("Copy", topLink, copyHead);
					St.push(newLink);
					currentLink = topLink->pNext;
					copyHead = nullptr;
				}
				else
				{
					topLink->SetStr(topLink->pNext->Str);
					topLink->pNext = copyHead;
					copyHead = topLink;
				}
			}
	}
	return new TText(copyHead);
}


int TText::GoFirstLink(void)
{
	if (pFirst == nullptr) SetRetCode(TextNoMem);
	else
	{
		while (!Path.empty()) Path.pop();
		pCurrent = pFirst;
		SetRetCode(TextOk);
	}
	return RetCode;
}

int TText::GoDownLink(void)
{
	if (pCurrent == nullptr) SetRetCode(TextError);
	else if (pCurrent->pDown == nullptr) SetRetCode(TextNoDown);
	else
	{
		Path.push(pCurrent);
		pCurrent = pCurrent->pDown;
		SetRetCode(TextOk);
	}
	return RetCode;
}

int TText::GoNextLink(void)
{
	if (pCurrent == nullptr) SetRetCode(TextError); // надо бросить исключение
	else if (pCurrent->pNext == nullptr ) SetRetCode(TextNoNext);
	else
	{
		Path.push(pCurrent);
		pCurrent = pCurrent->pNext;
		SetRetCode(TextOk);
	}
	return RetCode;
}

int TText::GoPrevLink(void)
{
	if (pCurrent == nullptr) SetRetCode(TextError);
	else if (Path.empty()) SetRetCode(TextNoPrev);
	else
	{
		pCurrent = Path.top();
		Path.pop();
		SetRetCode(TextOk);
	}
	return RetCode;
}

string TText::GetLine(void)
{
	if (pCurrent == nullptr)
		return string();
	else
		return pCurrent->Str;
}

void TText::SetLine(string s)
{
	if (pCurrent == nullptr)
		return;
	else
		pCurrent->SetStr(s);
}

void TText::InsDownLine(string s)
{
	if (pCurrent != nullptr)
	{
		PTTextLink tmpDown = pCurrent->pDown;
		PTTextLink newLink = new TTextLink(const_cast<char *>(s.c_str()), tmpDown);
		pCurrent->pDown = newLink;
	}
	else SetRetCode(TextError);
}

void TText::InsDownSection(string s)
{
	if (pCurrent != nullptr)
	{
		PTTextLink tmpDown = pCurrent->pDown;
		PTTextLink newLink = new TTextLink(const_cast<char *>(s.c_str()), nullptr, tmpDown);
		pCurrent->pDown = newLink;
	}
	else SetRetCode(TextError);
}

void TText::InsNextLine(string s)
{
	if (pCurrent != nullptr)
	{
		PTTextLink tmpNext = pCurrent->pNext;
		PTTextLink newLink = new TTextLink(const_cast<char *>(s.c_str()), tmpNext);
		pCurrent->pNext = newLink;
	}
	else SetRetCode(TextError);
}

void TText::InsNextSection(string s)
{
	if (pCurrent != nullptr)
	{
		PTTextLink tmpNext = pCurrent->pNext;
		PTTextLink newLink = new TTextLink(const_cast<char *>(s.c_str()), nullptr,  tmpNext);
		pCurrent->pNext = newLink;
	}
	else SetRetCode(TextError);
}

void TText::DelDownLine(void)
{
	if (pCurrent != nullptr )
	{
		if (pCurrent->pDown != nullptr)
		{
			PTTextLink tmpDown = pCurrent->pDown;
			if (pCurrent->pDown->pDown == nullptr)
			{
				pCurrent->pDown = pCurrent->pDown->pNext;
				delete tmpDown;
			}
		}
		else SetRetCode(TextNoDown);
	}
	else SetRetCode(TextError);
}

void TText::DelDownSection(void)
{
	if (pCurrent != nullptr)
	{
		if (pCurrent->pDown != nullptr)
			pCurrent->pDown = pCurrent->pDown->pNext;
		else SetRetCode(TextNoDown);
	}
	else SetRetCode(TextError);
}

void TText::DelNextLine(void)
{
	if (pCurrent != nullptr)
	{
		if (pCurrent->pNext != nullptr)
		{
			PTTextLink tmpNext = pCurrent->pNext;
			if (pCurrent->pNext->pDown == nullptr)
			{
				pCurrent->pNext = pCurrent->pNext->pNext;
				delete tmpNext;
			}
		}
		else SetRetCode(TextNoNext);
	}
	else SetRetCode(TextError);
}

void TText::DelNextSection(void)
{
	if (pCurrent != nullptr)
	{
		if (pCurrent->pNext != nullptr)
			pCurrent->pNext = pCurrent->pNext->pNext;
		else SetRetCode(TextNoNext);
	}
	else SetRetCode(TextError);
}

int TText::Reset(void)
{
	while (!St.empty())	St.pop();
	while (!Path.empty()) Path.pop();
	pCurrent = pFirst;
	 
	if (pCurrent != nullptr)
	{
		St.push(pFirst);
		if (pCurrent->pNext != nullptr)
			St.push(pCurrent->pNext);
		if (pCurrent->pDown != nullptr)
			St.push(pCurrent->pDown);
	}
	return IsTextEnded();
}

int TText::GoNext(void)
{
	if (!IsTextEnded())
	{
		pCurrent = St.top(); St.pop();
		if (pCurrent != pFirst)
		{
			if (pCurrent->pNext != nullptr)
				St.push(pCurrent->pNext);
			if (pCurrent->pDown != nullptr)
				St.push(pCurrent->pDown);
		}
	}
	return IsTextEnded();
}

void TText::Read(char * pFileName)
{
	ifstream TxtFile(pFileName);
	if (TxtFile.is_open())
		pFirst = pCurrent =  ReadText(TxtFile);
	else 
		throw std::string("Can't open file!");
}

void TText::Write(char * pFileName)
{
	ofstream TxtFile(pFileName);
	if (!TxtFile.is_open())
		cout << "Can't open file! " << endl;
	PTTextLink tmp = pFirst;

	if (tmp != nullptr)
	{
		TxtFile << "{" << endl;
		while (!St.empty())
			St.pop();
		while (1)
		{
			if (tmp != nullptr)
			{
				TxtFile << *tmp;
				St.push(tmp);
				tmp = tmp->pDown;
				if (tmp != nullptr)
					TxtFile << "{" << endl;
			}
			else if (St.empty())
				break;
			else
			{
				tmp = St.top();
				St.pop();
				tmp = tmp->pNext;
				if (tmp == nullptr)
					TxtFile << "}" << endl;
			}
		}
	}
}

