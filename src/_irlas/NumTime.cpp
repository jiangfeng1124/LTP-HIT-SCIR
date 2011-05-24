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
NumTime::NumTime() //后面几句什么意思？
{
	string numUnit[] =  {"０", "１", "２", "３", "４", "５", "６", "７", "８", "９", "零", 
		                 "○", "一", "二", "三", "四", "五", "六", "七", "八", "九", "十", 
					     "百", "千", "万", "亿", "两", "几", "数", "〇"};

	string timeUnit[] = {"年", "月", "日", "时", "点", "分", "秒", "月份", "点钟", 
	                     "点半", "时半"};

	string sepNumUnit[] = {"∶", "．", "／", "·", "‰", "％", "－", "：", "点"};
	
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
	if (IsTimeUnit(vecAtoms[endIndex])) //the end of time is one Chinese character such as "月"
	{
		if ((vecAtoms[endIndex] == "分" || vecAtoms[endIndex] == "秒") 
			&& !IsMinuteSecond(begIndex, endIndex, vecAtoms)) 
		{
			return 0;
		}
		else if (vecAtoms[endIndex] == "点" && !IsHour(begIndex, endIndex, vecAtoms)) 
		{
			return 0;
		}
		else if (vecAtoms[endIndex] == "日") 
		{
			if (endIndex + 1 < (int)vecAtoms.size() && vecAtoms[endIndex+1] == "元") 
				return 0;
			else
				return 1;
		}
		else if (vecAtoms[endIndex] == "年" && !IsYear(begIndex, endIndex, vecAtoms))
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	//the end of time is two Chinese character such as "月份"
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
	if (endIndex+1 < (int)vecAtoms.size() && vecAtoms[endIndex+1] == "钟") 
		return 0; //"10分钟" isn't time
	
	int i;
	for (i = 0; i < endIndex; i++) 
	{
		if (vecAtoms[endIndex] == "分")
		{
			if (vecAtoms[i] == "点" || vecAtoms[i] == "时") 
				break;
		}
		else if (vecAtoms[endIndex] == "秒") 
		{
			if (vecAtoms[i] == "分") 
				break;
		}
	}
	if (i == endIndex) //"分", "秒" must be accompanied with "点", "时" or "分"
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
		if (vecAtoms[begIndex] >= "０" && vecAtoms[begIndex] <= "９") 
			return 0;
		else if (vecAtoms[begIndex] != "二") 
			return 0;
		else if (vecAtoms[begIndex+1] != "十")
			return 0;
		else
			return 1;
	}
	else if (endIndex - begIndex == 2) 
	{
		if (vecAtoms[begIndex] >= "０" && vecAtoms[begIndex] <= "９") 
		{
			if (vecAtoms[begIndex] + vecAtoms[begIndex+1] <= "２４") 
				return 1;
			else 
				return 0;
		}
		else if (vecAtoms[begIndex] != "十") 
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
	else if (vecAtoms[endIndex-1] == "点") 
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
	//--------------------------deal with "公元（前）"--------------------------
	if (begIndex > 1) 
	{
		if (vecAtoms[begIndex-2] == "公" && vecAtoms[begIndex-1] == "元") 
			return 1;
		else if (vecAtoms[begIndex-2] == "元" && vecAtoms[begIndex-1] == "前") 
			return 1;
		else if (vecAtoms[begIndex-2] == "元" && vecAtoms[begIndex-1] == "后") 
			return 1;
	}
	//---------------------deal with English number before "年"-------------------
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
	//------------------------deal with Chinese numbers before "年"---------------------
	else if (begIndex+1 == endIndex || begIndex + 3 == endIndex) 
	{
		return 0;
	}
	else if (begIndex+2 == endIndex || endIndex - begIndex >= 4 ) 
	{
		for (int i = begIndex; i < endIndex; i++) 
		{
			if (vecAtoms[i] == "十" || vecAtoms[i] == "百" || vecAtoms[i] == "千" ||
				vecAtoms[i] == "万" || vecAtoms[i] == "亿") 
			{
				return 0;
			}
		}
		if (begIndex+2 == endIndex) 
		{
			if (vecAtoms[begIndex] <= "９") //"９６年" is time
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
	
	if (vecAtoms[begIndex-1] == "一" && begIndex + 1 < size 
		&& vecAtoms[begIndex] == vecAtoms[begIndex+1]) //overlap word, for example "一排排"
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
			if (vecAtoms[i] != "·" && vecAtoms[i] != "点" && is_chinese_char(vecAtoms[i-1])) 
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
		else if (vecAtoms[i] == "分" && i+1 < size && vecAtoms[i+1] == "之") 
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
		if (vecAtoms[i-1] == "‰" || vecAtoms[i-1] == "％") //‰ and ％ can be the end of number
			return i-1;
		else
			return i-2;
	}
	else if (vecAtoms[i-1] == "千" && i < size && 
		(vecAtoms[i] == "瓦" || vecAtoms[i] == "伏" ||  
		 vecAtoms[i] == "克" || vecAtoms[i] == "米")) 
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
	else if (begIndex+1 < (int)vecAtoms.size() && vecAtoms[begIndex] == "年" 
		&& vecAtoms[begIndex+1] == "代")
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
		else if (flag && (atom[i] == '/' || atom[i] == '.' || atom[i] == ':')) //数字后出现这些标点
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
/// judge if the atom is a prefix of number such as "第".
/////////////////////////////////////////////////////////////////////////////////////
int NumTime::IsNumPrefix(string& atom)
{
	if (atom == "第" || atom == "几" || atom == "数") 
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
/// judge if the str is a number separator such as "％".
/////////////////////////////////////////////////////////////////////////////////////
int NumTime::IsSepNumUnit(string& str)
{
	if (setSepNumUnit.find(str) != setSepNumUnit.end()) 
		return 1;
	else
		return 0;
}

