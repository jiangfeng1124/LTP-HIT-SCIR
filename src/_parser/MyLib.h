#ifndef _MYLIB_H_
#define _MYLIB_H_

#include "Node.h"
#include <iostream>
#include <cstring>
#include <vector>
#include "stl.h"
#define STL_USING_ALL
using namespace std;

//以分隔符为分隔把一句话切分到一个vector中
void split(const char separator, const string& str, vector < string > & vec);

//以"/"为分隔符把vector的每一个元素转换成一个pair
void convert_to_pair(vector<string>& vecString, 
					 vector< pair<string, string> >& vecPair);

//以上两个函数的结合
void split_to_pair(string& str, vector< pair<string, string> >& vecPair);

string add(string str, int n);

string itos(int number);

bool IsMarked(DATA* pData); 

#endif

