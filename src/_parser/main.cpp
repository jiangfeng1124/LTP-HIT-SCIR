#define PARSER_DLL_API_EXPORT
#include "Parser_dll.h"
#include "Parser.h"
#include "VerbTag.h"
#include "AugPronTag.h"

CParser parser;
CVerbTag verbTag;
AugPronTag APTag;
string g_strDataPath;

void Parser_LoadResource(const char *cszDataPath)
{
	g_strDataPath = cszDataPath;
	parser.Initialize();
	verbTag.Initialize();
	APTag.Initialize();
}

void Parser_ReleaseResource()
{
	parser.Release();
	verbTag.Release();
	APTag.Release();
}


int GetParseResults(vector < string >& vecWord, vector < string >& vecPOS, char * strOutput)
{
	size_t nSize_Word = vecWord.size();
	size_t nSize_POS = vecPOS.size();
	size_t i = 0; 

	if(nSize_Word == 0)	// 句子为空
	{
		strOutput = "";
		return 0;
	}

	// convert input to the form: "可是/c ，/wp 铜锅/n 也/d 有/v 遇/v 着/u 铁刷把/n 的/u 时候/n 。/wp ";
	string strSent = "";
	for(i = 0; i < nSize_Word, i < nSize_POS; i++)
	{
		string word = vecWord[i];
		if(word.find(" ") != -1 || word.find("/") != -1 || word.find("	") != -1)
			word = "xyz";
		//Replace(word, " ", ""); // 删除词中的空格，为了处理LTP中分词之后词中有空格的情况
		//Replace(word, "/", ""); // 删除词中的斜杠，为了处理LTP中分词之后词中有斜杠的情况

		string pos = vecPOS[i];
		if(pos.find(" ") != -1 || pos.find("/") != -1 || pos.find("	") != -1)
			pos = "a";
		//Replace(pos, " ", ""); // 删除词性中的空格，为了处理LTP中分词之后词性中有空格的情况
		//Replace(pos, "/", ""); // 删除词性中的斜杠，为了处理LTP中分词之后词性中有斜杠的情况
		strSent += word + "/" + pos + " ";
	}

	// POS classification
	verbTag.VerbTagging(strSent,strSent);
	APTag.TagAug(strSent);
	APTag.TagPron(strSent);

	vector <string> vecSent;
	size_t pos1 = 0;
	size_t pos3 = strSent.find(' ', pos1);
	size_t pos2 = strSent.rfind('/', pos3);
	for(i = 0; i < nSize_Word && i < nSize_POS; i++)
	{
		if (pos1 == string::npos || pos3 == string::npos || pos2 == string::npos) break;
		string tag = strSent.substr(pos2+1,pos3-pos2-1);

		string word = vecWord[i];
		string ctag = vecPOS[i];
       unsigned int id = i+1;

		string strData = itos(id) + "\t" + word + "\t" + word + "\t" + ctag + "\t" + tag; 
		vecSent.push_back(strData);

		pos1 = pos3 + 1;
		if (pos1 >= strSent.size()) {
			pos3 = string::npos;
		}
		pos3 = strSent.find(' ', pos1);
		if (pos3 != string::npos) {
			pos2 = strSent.rfind('/', pos3);
		}
	}

	string strTmp;
	if (0 != parser.ParseSent(vecSent, strTmp)) return -1;
	strcpy(strOutput, strTmp.c_str());
	return 0;
}

int GetParseResults_with_postag(vector < string >& vecWord, vector<string> &vecCPOS,  vector < string >& vecPOS,char *strOutput)
{
	if (vecWord.size() != vecCPOS.size() || vecWord.size() != vecPOS.size()) {
		cerr << "GetParseResults_with_postag: vecWord, vecCPOS, vecPOS size unequal" << endl;
		strOutput[0] = 0;
		return -1;
	}

	if(vecWord.empty())	// 句子为空
	{
		strOutput[0] = 0;
		return 0;
	}	

	vector <string> vecSent;
	size_t i = 0; 
	for(i = 0; i < vecWord.size(); i++)
	{
		int id = i+1;
		string strData = itos(id) + "\t" + vecWord[i] + "\t" + vecWord[i] + "\t" + vecCPOS[i] + "\t" + vecPOS[i]; 
		vecSent.push_back(strData);
	}

	string strTmp;
	if (0 != parser.ParseSent(vecSent, strTmp)) return -1;
	strcpy(strOutput, strTmp.c_str());
	return 0;
}

