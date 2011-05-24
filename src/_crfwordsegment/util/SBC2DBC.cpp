#include "SBC2DBC.h"
#include <iostream>
#include <fstream>

using namespace std;

SBC2DBC::SBC2DBC(void)
{
	Initialize();
}

SBC2DBC::~SBC2DBC(void)
{
}

void SBC2DBC::Initialize()
{
	const char *szSBCTable[SBC_TABLE_SIZE] =		//ȫ���ַ����ݱ���λ����
	{
		"��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
		"��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
		"��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
		"��", "��", "��", "��", "��", "��",
		"��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
		"��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
		"��", "��", "��", "��", "��", "��", "��","��","��","��","��","��","��"
	};

	const char szDBCTable[SBC_TABLE_SIZE] =			//����ַ����ݱ���ȫ���ַ����ݱ�һһ��Ӧ
	{
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
		'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
		'U', 'V', 'W', 'X', 'Y', 'Z',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
		'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
		'u', 'v', 'w', 'x', 'y', 'z', ' ','\'','"',',','.','!','?'
	};

	int i = 0;
	for (; i < SBC_TABLE_SIZE; ++i)
	{
		m_mapSBC2DBC.insert( make_pair(std::string(szSBCTable[i]), szDBCTable[i]) );
	}
}

void SBC2DBC::DoSBC2DBC(const std::string &str, std::string &strResult)
{
	strResult.clear();
	std::string::size_type pos = 0;
	while(pos < str.size()) {
		if ((str[pos] & 0x80) == 0) // English character
		{
			strResult.append(1, str[pos]);
			++pos;
			continue;
		}
		std::string strGBWord = str.substr(pos, 2);
		pos += 2;
		std::map<std::string, char>::const_iterator it = m_mapSBC2DBC.find(strGBWord);
		if (it == m_mapSBC2DBC.end()) {
			strResult.append(strGBWord);
		} else {
			strResult.append(1, it->second);
		}
	}
}

void SBC2DBC::DoSBC2DBC_if_begin_with_SBC(const std::string &str, std::string &strResult)
{
	bool isBeginWithSBC = true;
	if (str.size() < 2 || (str[0] & 0x80) == 0) {
		isBeginWithSBC = false;
	}

	std::string strFirstGB = str.substr(0, 2);
	if (m_mapSBC2DBC.find(strFirstGB) == m_mapSBC2DBC.end()) {
		isBeginWithSBC = false;
	}
	if (!isBeginWithSBC) {
		strResult = str;
		return;
	}

	DoSBC2DBC(str, strResult);
}

int main()
{
	SBC2DBC sb;
	string line;
	while (getline(cin,line))
	{
		string resultLine;
		sb.DoSBC2DBC(line,resultLine);
		cout << resultLine <<endl;
	}

}
