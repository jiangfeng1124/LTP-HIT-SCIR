 /////////////////////////////////////////////////////////////////////////////////////
// File Name   : NumTime.cpp
// Project Name: IRLAS
// Author      : Huipeng Zhang (zhp@ir.hit.edu.cn)
// Environment : Microsoft Visual C++ 6.0
// Description : the implementation of class NumTime
// Create Time : 2005.5
// History     : 
// CopyRight   : HIT-IRLab (c) 2001-2005, all rights reserved.
/////////////////////////////////////////////////////////////////////////////////////
#include "NumTime.h"

/////////////////////////////////////////////////////////////////////////////////////
/// initialize the data member setNumUnit, setTimeUnit and setSepNumUnit.
/////////////////////////////////////////////////////////////////////////////////////
NumTime::NumTime() //���漸��ʲô��˼��
{
	string numUnit[] =  {"��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", 
		                 "��", "һ", "��", "��", "��", "��", "��", "��", "��", "��", "ʮ", 
					     "��", "ǧ", "��", "��", "��", "��", "��", "��"};

	string timeUnit[] = {"��", "��", "��", "ʱ", "��", "��", "��", "�·�", "����", 
	                     "���", "ʱ��"};

	string sepNumUnit[] = {"��", "��", "��", "��", "��", "��", "��", "��", "��"};
	
	setNumUnit.insert(numUnit, numUnit + sizeof(numUnit) / sizeof(numUnit[0]));
	setTimeUnit.insert(timeUnit, timeUnit + sizeof(timeUnit) / sizeof(timeUnit[0]));
	setSepNumUnit.insert(sepNumUnit, sepNumUnit + sizeof(sepNumUnit) / sizeof(sepNumUnit[0]));
}

/////////////////////////////////////////////////////////////////////////////////////
/// number and time words recognition.
/////////////////////////////////////////////////////////////////////////////////////
void NumTime::NumTimeRecg(vector<string>& vecAtoms, Graph& graph)
{
	int endNumIdx;
	int endTimeIdx;
	int size = vecAtoms.size();
	int flag = 0;
	for (int i = 0; i < size; i++) 
	{
		if (IsNumPrefix(vecAtoms[i]) && i < size-1) //this atom is number prefix and
		{                                           //it isn't the end of sentence
			endNumIdx = FindNumEndIndex(i+1, flag, vecAtoms);
			//there are number sequence after number prefix
			if (endNumIdx > i) 
			{
				graph.AddWord(i, endNumIdx, NumberIndex, 0);
				flag = 0;
			}
			i = endNumIdx;
		}
		else if (IsCnNumUnit(vecAtoms[i]) || IsEnNumUnit(vecAtoms[i], flag)) 
		{
			endNumIdx = (i+1 < size) ? FindNumEndIndex(i+1, flag, vecAtoms) : i;			
			endTimeIdx = (endNumIdx+1<size) ? FindTimeEndIndex(endNumIdx+1,vecAtoms) : endNumIdx;
			
			if (IsTime(i, endTimeIdx, vecAtoms)) 
				graph.AddWord(i, endTimeIdx, TimeIndex, 0);
			else 
				graph.AddWord(i, endNumIdx, NumberIndex, 0);
		// 	flag = 0;
			i = endTimeIdx;
		}
		else
		{
			flag = 0;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/// judge if the atom interval between begIndex and endIndex conforms to time format.
/////////////////////////////////////////////////////////////////////////////////////
int NumTime::IsTime(int begIndex, int endIndex, vector<string>& vecAtoms)
{
	if (IsTimeUnit(vecAtoms[endIndex])) //the end of time is one Chinese character such as "��"
	{
		if ((vecAtoms[endIndex] == "��" || vecAtoms[endIndex] == "��") 
			&& !IsMinuteSecond(begIndex, endIndex, vecAtoms)) 
		{
			return 0;
		}
		else if (vecAtoms[endIndex] == "��" && !IsHour(begIndex, endIndex, vecAtoms)) 
		{
			return 0;
		}
		else if (vecAtoms[endIndex] == "��") 
		{
			if (endIndex + 1 < (int)vecAtoms.size() && vecAtoms[endIndex+1] == "Ԫ") 
				return 0;
			else
				return 1;
		}
		else if (vecAtoms[endIndex] == "��" && !IsYear(begIndex, endIndex, vecAtoms))
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	//the end of time is two Chinese character such as "�·�"
	else if (begIndex < endIndex) 
	{
		string str = vecAtoms[endIndex-1]+vecAtoms[endIndex];
		if (IsTimeUnit(str)) 
			return 1;
		else
			return 0;
	}
	else
	{
		return 0;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/// judge if the atom interval between begIndex and endIndex conforms to minute or
/// second format.
/////////////////////////////////////////////////////////////////////////////////////
int NumTime::IsMinuteSecond(int begIndex, int endIndex, vector<string>& vecAtoms)
{
	if (endIndex+1 < (int)vecAtoms.size() && vecAtoms[endIndex+1] == "��") 
		return 0; //"10����" isn't time
	
	int i;
	for (i = 0; i < endIndex; i++) 
	{
		if (vecAtoms[endIndex] == "��")
		{
			if (vecAtoms[i] == "��" || vecAtoms[i] == "ʱ") 
				break;
		}
		else if (vecAtoms[endIndex] == "��") 
		{
			if (vecAtoms[i] == "��") 
				break;
		}
	}
	if (i == endIndex) //"��", "��" must be accompanied with "��", "ʱ" or "��"
		return 0;
	else 
		return 1;
}

/////////////////////////////////////////////////////////////////////////////////////
/// judge if the atom interval between begIndex and endIndex conforms to hour format.
/////////////////////////////////////////////////////////////////////////////////////
int NumTime::IsHour(int begIndex, int endIndex, vector<string>& vecAtoms)
{
	int flag = 0;
	if (endIndex - begIndex > 3) 
	{
		return 0;
	}	
	else if (endIndex - begIndex == 3) 
	{
		if (vecAtoms[begIndex] >= "��" && vecAtoms[begIndex] <= "��") 
			return 0;
		else if (vecAtoms[begIndex] != "��") 
			return 0;
		else if (vecAtoms[begIndex+1] != "ʮ")
			return 0;
		else
			return 1;
	}
	else if (endIndex - begIndex == 2) 
	{
		if (vecAtoms[begIndex] >= "��" && vecAtoms[begIndex] <= "��") 
		{
			if (vecAtoms[begIndex] + vecAtoms[begIndex+1] <= "����") 
				return 1;
			else 
				return 0;
		}
		else if (vecAtoms[begIndex] != "ʮ") 
		{
			return 0;
		}
		else 
		{
			return 1;
		}
	}
	else if (endIndex - begIndex == 1) 
	{
		if (IsEnNumUnit(vecAtoms[begIndex], flag) && vecAtoms[begIndex].size() <= 2
			&& vecAtoms[begIndex] >= "0" && vecAtoms[begIndex] <= "24") 
			return 1;
		else 
			return 0;
	}
	else if (vecAtoms[endIndex-1] == "��") 
	{
		return 0;
	}	
	else 
	{
		return 1;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/// judge if the atom interval between begIndex and endIndex conforms to year format.
/////////////////////////////////////////////////////////////////////////////////////
int NumTime::IsYear(int begIndex, int endIndex, vector<string>& vecAtoms)
{
	int flag = 0;
	//--------------------------deal with "��Ԫ��ǰ��"--------------------------
	if (begIndex > 1) 
	{
		if (vecAtoms[begIndex-2] == "��" && vecAtoms[begIndex-1] == "Ԫ") 
			return 1;
		else if (vecAtoms[begIndex-2] == "Ԫ" && vecAtoms[begIndex-1] == "ǰ") 
			return 1;
		else if (vecAtoms[begIndex-2] == "Ԫ" && vecAtoms[begIndex-1] == "��") 
			return 1;
	}
	//---------------------deal with English number before "��"-------------------
	if (begIndex+1 == endIndex && IsEnNumUnit(vecAtoms[begIndex], flag)) 
	{
		string strNum = vecAtoms[begIndex];
		int len = strNum.size();

		for (int i = 0; i < len; i++) //judge if the atom consists of only numbers
		{
			if (strNum[i] < '0' || strNum[i] > '9') 
				return 0;
		}

		int number = atoi(strNum.c_str()); 

		if (len == 4) 
		{
			if (number >= 3000 || number <= 1000) 
				return 0;
			else 
				return 1;
		}
		else if (len == 2) 
		{
			if (number < 50) 
				return 0;
			else
				return 1;
		}
		else
		{
			return 0;
		}
	}
	//------------------------deal with Chinese numbers before "��"---------------------
	else if (begIndex+1 == endIndex || begIndex + 3 == endIndex) 
	{
		return 0;
	}
	else if (begIndex+2 == endIndex || endIndex - begIndex >= 4 ) 
	{
		for (int i = begIndex; i < endIndex; i++) 
		{
			if (vecAtoms[i] == "ʮ" || vecAtoms[i] == "��" || vecAtoms[i] == "ǧ" ||
				vecAtoms[i] == "��" || vecAtoms[i] == "��") 
			{
				return 0;
			}
		}
		if (begIndex+2 == endIndex) 
		{
			if (vecAtoms[begIndex] <= "��") //"������" is time
				return 0;
			else
				return 1;
		}
		else 
		{
			return 1;
		}
	}
	else 
	{
		return 0;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/// find the end index of number provided the begin index of number.
/////////////////////////////////////////////////////////////////////////////////////
int NumTime::FindNumEndIndex(int begIndex, int& flag, vector<string>& vecAtoms)
{
	int size = vecAtoms.size();
	
	if (vecAtoms[begIndex-1] == "һ" && begIndex + 1 < size 
		&& vecAtoms[begIndex] == vecAtoms[begIndex+1]) //overlap word, for example "һ����"
	{
		if (begIndex+2 < size && !IsCnNumUnit(vecAtoms[begIndex+2])) 
			return begIndex+1;
	}
	int isSepEnd = 0;
	int i;
	for (i = begIndex; i < size; i++) 
	{
		if (IsSepNumUnit(vecAtoms[i]))
		{
			if (vecAtoms[i] != "��" && vecAtoms[i] != "��" && is_chinese_char(vecAtoms[i-1])) 
			{
				break;
			}
			else
			{
				isSepEnd = 1;
				if (i > 0 && IsSepNumUnit(vecAtoms[i-1])) 
					break;
			}
		}
		else if (vecAtoms[i] == "��" && i+1 < size && vecAtoms[i+1] == "֮") 
		{
			isSepEnd = 1;
			i++;
		}
		else if (IsEnNumUnit(vecAtoms[i], flag) || IsCnNumUnit(vecAtoms[i]))
		{
			isSepEnd = 0;
		}
		else
		{
			break;
		}
	}

	if (isSepEnd) 
	{
		if (vecAtoms[i-1] == "��" || vecAtoms[i-1] == "��") //�� and �� can be the end of number
			return i-1;
		else
			return i-2;
	}
	else if (vecAtoms[i-1] == "ǧ" && i < size && 
		(vecAtoms[i] == "��" || vecAtoms[i] == "��" ||  
		 vecAtoms[i] == "��" || vecAtoms[i] == "��")) 
	{
		if (i > begIndex) 
			return i-2;
		else 
			return i-1;
	}
	else
	{
		return i-1;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/// find the end index of time provided the begin index of time.
/////////////////////////////////////////////////////////////////////////////////////
int NumTime::FindTimeEndIndex(int begIndex, vector<string>& vecAtoms)
{
	if (begIndex+1 < (int)vecAtoms.size() && 
		IsTimeUnit(vecAtoms[begIndex]+vecAtoms[begIndex+1]))
		return begIndex+1;
	else if (begIndex+1 < (int)vecAtoms.size() && vecAtoms[begIndex] == "��" 
		&& vecAtoms[begIndex+1] == "��")
		return begIndex-1;
	else if (IsTimeUnit(vecAtoms[begIndex])) 
		return begIndex;
	else
		return begIndex-1;
}

/////////////////////////////////////////////////////////////////////////////////////
/// judge if an atom is a Chinese number unit.
/////////////////////////////////////////////////////////////////////////////////////
int NumTime::IsCnNumUnit(string& atom)
{
	if (setNumUnit.find(atom) != setNumUnit.end()) 
		return 1;
	else
		return 0;
}

/////////////////////////////////////////////////////////////////////////////////////
/// judge if an atom is only made up of English numbers.
/////////////////////////////////////////////////////////////////////////////////////
int NumTime::IsEnNumUnit(string& atom, int& flag)
{
	int atomSize = atom.size();

	int i;
	for (i = 0; i < atomSize; i++) 
	{
	/*
		    	if (atom[i] >= '0' && atom[i] <= '9' || atom[i] == '/' || atom[i] == '-'
		    		    || atom[i] == '.' || atom[i] == '%' || atom[i] == ':') */
		if (atom[i] >= '0' && atom[i] <= '9' || atom[i] == '%')		    
		{
			flag = 1;
			continue;
		}
		else if (flag && (atom[i] == '/' || atom[i] == '.' || atom[i] == ':')) //���ֺ������Щ���
	        continue;
		else if (!flag && atom[i] == '-')
			continue;
		else
			break;
	}
	if (i == atomSize) //the atom is only made up of English numbers
		return 1;
	else
		return 0;
}

/////////////////////////////////////////////////////////////////////////////////////
/// judge if the atom is a prefix of number such as "��".
/////////////////////////////////////////////////////////////////////////////////////
int NumTime::IsNumPrefix(string& atom)
{
	if (atom == "��" || atom == "��" || atom == "��") 
		return 1;
	else
		return 0;
}

/////////////////////////////////////////////////////////////////////////////////////
/// judge if an atom is a time unit.
/////////////////////////////////////////////////////////////////////////////////////
int NumTime::IsTimeUnit(string str)
{
	if (setTimeUnit.find(str) != setTimeUnit.end()) 
		return 1;
	else
		return 0;
}

/////////////////////////////////////////////////////////////////////////////////////
/// judge if the str is a number separator such as "��".
/////////////////////////////////////////////////////////////////////////////////////
int NumTime::IsSepNumUnit(string& str)
{
	if (setSepNumUnit.find(str) != setSepNumUnit.end()) 
		return 1;
	else
		return 0;
}

