
#include "MyLib.h"

void split(const char separator, const string& str, vector < string >& vec)
{
	string::size_type pos1 = 0, pos2 = 0;
	string word;
	vec.clear();
	while((pos2 = str.find_first_of(separator, pos1)) != string::npos)
	{
		word = str.substr(pos1, pos2-pos1);
		pos1 = pos2 + 1;
		if(!word.empty()) 
			vec.push_back(word);
	}
	word = str.substr(pos1);
	if(!word.empty())
		vec.push_back(word);
}

void convert_to_pair(vector<string>& vecString, 
					 vector< pair<string, string> >& vecPair)
{
	vecPair.clear();
	size_t size = vecString.size();
	size_t cur;
	string strWord, strPos;
	for (size_t i = 0; i < size; ++i)
	{
		cur = vecString[i].find('/');
		
		if (cur == string::npos) 
		{
			strWord = vecString[i].substr(0);
			strPos = "";
		}
		else if (cur == vecString[i].size()-1) 
		{
			strWord = vecString[i].substr(0, cur);
			strPos = "";
		}
		else
		{
			strWord = vecString[i].substr(0, cur);
			strPos = vecString[i].substr(cur+1);
		}
		
		vecPair.push_back(pair<string, string>(strWord, strPos));
	}
}

void split_to_pair(string& str, vector< pair<string, string> >& vecPair)
{
	vector<string> vec;
	split(' ', str, vec);
	convert_to_pair(vec, vecPair);
}

string add(string str, int n)
{
	int number = atoi(str.c_str());
	char buffer[4];
	itoa(number+n,buffer,10);
	str = buffer;
	return str;
} 

string itos(int number)
{
	char buf[256];
	itoa(number,buf,10);
	return buf;
}

bool IsMarked(DATA* pData)
{
	if(pData->mark == 1)	// this node has been reduced
	{
		delete pData;		// release memory
		return 1;
	}
	else
		return 0;
}

