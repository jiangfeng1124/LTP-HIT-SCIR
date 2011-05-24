#ifndef _MYLIB_H_
#define _MYLIB_H_

#include "Node.h"
#include <iostream>
#include <cstring>
#include <vector>
#include "stl.h"
#define STL_USING_ALL
using namespace std;

//�Էָ���Ϊ�ָ���һ�仰�зֵ�һ��vector��
void split(const char separator, const string& str, vector < string > & vec);

//��"/"Ϊ�ָ�����vector��ÿһ��Ԫ��ת����һ��pair
void convert_to_pair(vector<string>& vecString, 
					 vector< pair<string, string> >& vecPair);

//�������������Ľ��
void split_to_pair(string& str, vector< pair<string, string> >& vecPair);

string add(string str, int n);

string itos(int number);

bool IsMarked(DATA* pData); 

#endif

