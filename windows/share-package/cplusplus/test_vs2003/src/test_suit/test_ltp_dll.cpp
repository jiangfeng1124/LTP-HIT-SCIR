#include "../__ltp_dll/__ltp_dll.h"
#pragma comment(lib, "__ltp_dll.lib")
#include "../__util/MyLib.h"

#pragma warning(disable : 4786)

#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <map>
#include <fstream>
#include <conio.h>
#include <ctime>
using namespace std;

using namespace HIT_IR_LTP;	// Important!

clock_t start_time;
ofstream logfile("test_log.txt");
string strText;

int readText();

int test_main2();

int test_IRLAS_vec();
int test_NER_vec();
int test_WSD_vec();
int test_Parser_vec();

int test_SplitSentence();
int test_IRLAS();
int test_NE();
int test_WSD();
int test_Parser();
int test_SDS();
int test_TextClassify();
int test_SRL();
int test_CR();


int readText()
{
	ifstream infile("test.txt");
	if ( !infile.is_open() )
	{
		cerr << "can not open: text.txt" << endl;
		exit(0);
	}

	string strLine;
	while ( getline(infile, strLine) )
	{
		strText += strLine;
		strText += "\n";
	}

	infile.close();
	return 0;
}

int test_main2()
{
	return main2("test.txt", "test_main2.xml");
}

int test_SplitSentence()
{
	logfile << "\n\n------------"
		<< "\ntest SplitSentence\n";

	// -------------------------
	CreateDOMFromTxt("test.txt");
	
	// Before split sentence, we can get the paragraphs
	logfile << "\n\nbefore split sentence, para info";
	int paraNum = CountParagraphInDocument();
	int i;

	for (i=0; i < paraNum; ++i)
	{
		logfile	<< "\npara " << i << ":";

		const char *para = GetParagraph(i);
		if (para != NULL)
		{
			logfile << "\n" << para;
		}
	}

	SplitSentence();
	SaveDOM("test_splitsentence.xml");

	// -------------------------
	// The xml file has done SplitSentence().
	ClearDOM();		// This is optional, will be done implicitly before CreateDOM.
	CreateDOMFromXml("test_splitsentence.xml");
	
	// Get all sentences in the first way
	logfile << "\n\nsent info, first method";
	int sentNum = CountSentenceInDocument();
	for (i=0; i < sentNum; ++i)
	{
		const char *sent = GetSentence(i);
		if (sent != NULL)
		{
			logfile << "\n" << sent;
		}
	}

	// -------------------------
	CreateDOMFromString(strText.c_str());
	SplitSentence();

	// Get all sentences in the sencond way
	logfile << "\n\nsent info, second method";
	paraNum = CountParagraphInDocument();
	for (i=0; i < paraNum; ++i)
	{
		int sentNum = CountSentenceInParagraph(i);
		for (int j=0; j<sentNum; ++j)
		{
			const char *sent = GetSentence(i, j);
			if (sent != NULL)
			{
				logfile << "\n" << sent;
			}
		}
	}
	SaveDOM("test_splitsentence_string.xml");

	return 0;
}

int test_IRLAS()
{
	logfile << "\n\n------------"
		<< "\ntest IRLAS\n";

	// -------------------------
	CreateDOMFromTxt("test.txt");
	SplitSentence();
	IRLAS();
	SaveDOM("test_irlas.xml");

	// Get all word and POS in the first way
	logfile << "\n\nword and POS info, first method\n";
	int wordNum = CountWordInDocument();
	for (int i=0; i < wordNum; ++i)
	{
		const char *word = GetWord(i);
		const char *pos = GetPOS(i);
		if (word != NULL && pos != NULL)
		{
			logfile << word << "/" << pos << " ";
		}
		if ((i+1) % 15 == 0)
		{
			logfile << endl;;
		}
	}


	// -------------------------
	CreateDOMFromXml("test_irlas.xml");

	// Get all word and POS in the second way
	logfile << "\n\nword and POS info, second method\n";
	int sentNum = CountSentenceInDocument();
	for (int j=0; j < sentNum; ++j)
	{
		int wordNum = CountWordInSentence(j);
		for (int i=0; i < wordNum; ++i)
		{
			const char *word = GetWord(j, i);
			const char *pos = GetPOS(j, i);
			if (word != NULL && pos != NULL)
			{
				logfile << word << "/" << pos << " ";
			}
		}
		logfile << endl;
	}

	// -------------------------
	CreateDOMFromString(strText.c_str());
	SplitSentence();
	IRLAS();

	// Get all word and POS in the third way
	logfile << "\n\nword and POS info, third method\n";
	int paraNum = CountParagraphInDocument();
	for (int k=0; k < paraNum; ++k)
	{
		int sentNum = CountSentenceInParagraph(k);
		for (int j=0; j < sentNum; ++j)
		{
			int wordNum = CountWordInSentence(k, j);
			for (int i=0; i < wordNum; ++i)
			{
				const char *word = GetWord(k, j, i);
				const char *pos = GetPOS(k, j, i);
				if (word != NULL && pos != NULL)
				{
					logfile << word << "/" << pos << " ";
				}
			}
			logfile << endl;
		}

	}

	SaveDOM("test_irlas_string.xml");
	return 0;
}

int test_NER()
{
	logfile << "\n\n------------"
		<< "\ntest NER\n";

	// -------------------------
	CreateDOMFromTxt("test.txt");
	SplitSentence();
	NER();
	SaveDOM("test_ner.xml");

	// Get all NE in the first way
	logfile << "\n\nNE info, first method\n";
	int wordNum = CountWordInDocument();
	for (int i=0; i < wordNum; ++i)
	{
		const char *ne = GetNE(i);
		if (ne != NULL)
		{
			logfile << ne << " ";
		}
		if ((i+1) % 15 == 0)
		{
			logfile << endl;
		}
	}


	// -------------------------
	CreateDOMFromXml("test_ner.xml");

	// Get all NE in the second way
	logfile << "\n\nNE info, second method\n";
	int sentNum = CountSentenceInDocument();
	for (int j=0; j < sentNum; ++j)
	{
		int wordNum = CountWordInSentence(j);
		for (int i=0; i < wordNum; ++i)
		{
			const char *ne = GetNE(j, i);
			if (ne != NULL)
			{
				logfile << ne << " ";
			}
		}
		logfile << endl;
	}

	// -------------------------
	CreateDOMFromString(strText.c_str());
	SplitSentence();
	NER();

	// Get all NE in the second way
	logfile << "\n\nNE info, third method\n";
	int paraNum = CountParagraphInDocument();
	for (int k=0; k < paraNum; ++k)
	{
		int sentNum = CountSentenceInParagraph(k);
		for (int j=0; j < sentNum; ++j)
		{
			int wordNum = CountWordInSentence(k, j);
			for (int i=0; i < wordNum; ++i)
			{
				const char *ne = GetNE(k, j, i);
				if (ne != NULL)
				{
					logfile << ne << " ";
				}
			}
			logfile << endl;
		}
	}

	SaveDOM("test_ner_string.xml");
	return 0;
}

int test_WSD()
{
	logfile << "\n\n------------"
		<< "\ntest WSD\n";

	// -------------------------
	CreateDOMFromTxt("test.txt");
	SplitSentence();
	WSD();
	SaveDOM("test_wsd.xml");

	// Get all WSD in the first way
	logfile << "\n\nWSD info, first method\n";
	int wordNum = CountWordInDocument();
	for (int i=0; i < wordNum; ++i)
	{
		pair<const char *, const char *> WSD_explain;
		int ret = GetWSD(WSD_explain, i);
		if (0 == ret && WSD_explain.first != NULL && WSD_explain.second != NULL)
		{
			logfile << "<" << WSD_explain.first << ", " << WSD_explain.second << "> ";
		}
		if ((i+1) % 15 == 0)
		{
			logfile << endl;
		}
	}


	// -------------------------
	CreateDOMFromXml("test_wsd.xml");

	// Get all WSD in the second way
	logfile << "\n\nWSD info, second method\n";
	int sentNum = CountSentenceInDocument();
	for (int j=0; j < sentNum; ++j)
	{
		int wordNum = CountWordInSentence(j);
		for (int i=0; i < wordNum; ++i)
		{
			pair<const char *, const char *> WSD_explain;
			int ret = GetWSD(WSD_explain, j, i);
			if (0 == ret && WSD_explain.first != NULL && WSD_explain.second != NULL)
			{
				logfile << "<" << WSD_explain.first << ", " << WSD_explain.second << "> ";
			}
		}
		logfile << endl;
	}

	// -------------------------
	CreateDOMFromString(strText.c_str());
	SplitSentence();
	WSD();

	// Get all WSD in the third way
	logfile << "\n\nWSD info, third method\n";
	int paraNum = CountParagraphInDocument();
	for (int k=0; k < paraNum; ++k)
	{
		int sentNum = CountSentenceInParagraph(k);
		for (int j=0; j < sentNum; ++j)
		{
			int wordNum = CountWordInSentence(k, j);
			for (int i=0; i < wordNum; ++i)
			{
				pair<const char *, const char *> WSD_explain;
				int ret = GetWSD(WSD_explain, k, j, i);
				if (0 == ret && WSD_explain.first != NULL && WSD_explain.second != NULL)
				{
					logfile << "<" << WSD_explain.first << ", " << WSD_explain.second << "> ";
				}
			}
			logfile << endl;
		}
	}

	SaveDOM("test_wsd_string.xml");
	return 0;
}



int test_Parser()
{
	logfile << "\n\n------------"
		<< "\ntest Parser\n";

	// -------------------------
	CreateDOMFromTxt("test.txt");
	SplitSentence();
	GParser();
	SaveDOM("test_parser.xml");

	// Get all Parser in the first way
	logfile << "\n\nParser info, first method\n";
	int wordNum = CountWordInDocument();
	for (int i=0; i < wordNum; ++i)
	{
		pair<int, const char *> parent_relate;
		int ret = GetParse(parent_relate, i);
		if (0 == ret && parent_relate.second != NULL)
		{
			logfile << "<" << parent_relate.first << ", " << parent_relate.second << "> ";
		}
		if ((i+1) % 15 == 0)
		{
			logfile << endl;
		}
	}


	// -------------------------
	CreateDOMFromXml("test_parser.xml");

	// Get all Parser in the second way
	logfile << "\n\nParser info, second method\n";
	int sentNum = CountSentenceInDocument();
	for (int j=0; j < sentNum; ++j)
	{
		int wordNum = CountWordInSentence(j);
		for (int i=0; i < wordNum; ++i)
		{
			pair<int, const char *> parent_relate;
			int ret = GetParse(parent_relate, j, i);
			if (0 == ret && parent_relate.second != NULL)
			{
				logfile << "<" << parent_relate.first << ", " << parent_relate.second << "> ";
			}
		}
		logfile << endl;
	}

	// -------------------------
	CreateDOMFromString(strText);
	SplitSentence();
	GParser();

	// Get all Parser in the third way
	logfile << "\n\nParser info, third method\n";
	int paraNum = CountParagraphInDocument();
	for (int k=0; k < paraNum; ++k)
	{
		int sentNum = CountSentenceInParagraph(k);
		for (int j=0; j < sentNum; ++j)
		{
			int wordNum = CountWordInSentence(k, j);
			for (int i=0; i < wordNum; ++i)
			{
				pair<int, const char *> parent_relate;
				int ret = GetParse(parent_relate, k, j, i);
				if (0 == ret && parent_relate.second != NULL)
				{
					logfile << "<" << parent_relate.first << ", " << parent_relate.second << "> ";
				}
			}
			logfile << endl;
		}
	}

	SaveDOM("test_parser_string.xml");
	return 0;
}


int test_SRL()
{
	logfile << "\n\n------------"
		<< "\ntest SRL\n";

	CreateDOMFromTxt( "test.txt" );
	SplitSentence();
	SRL();
	SaveDOM("test_srl.xml");

	// Get all SRL in the first way
	logfile << "\n\nSRL info, first method\n";
	int wordNum = CountWordInDocument();
	for (int i=0; i < wordNum; ++i)
	{
		vector<const char *> vecType;
		vector< pair<int, int> > vecBegEnd;
		
		GetPredArgToWord(vecType, vecBegEnd, i);
		if ( !vecType.empty() )
		{
			logfile << endl;
			for (int m=0; m < vecType.size(); ++m)
			{
				logfile << vecType[m] << " "
					<< vecBegEnd[m].first << " "
					<< vecBegEnd[m].second << " ^ ";
			}
		}
	}


	// -------------------------
	CreateDOMFromXml("test_srl.xml");

	// Get all SRL in the second way
	logfile << "\n\nSRL info, second method\n";
	int sentNum = CountSentenceInDocument();
	for (int j=0; j < sentNum; ++j)
	{
		int wordNum = CountWordInSentence(j);
		for (int i=0; i < wordNum; ++i)
		{
			vector<const char *> vecType;
			vector< pair<int, int> > vecBegEnd;

			GetPredArgToWord(vecType, vecBegEnd, j, i);
			if ( !vecType.empty() )
			{
				logfile << endl;
				for (int m=0; m < vecType.size(); ++m)
				{
					logfile << vecType[m] << " "
						<< vecBegEnd[m].first << " "
						<< vecBegEnd[m].second << " ^ ";
				}
			}
		}
	}

	// -------------------------
	CreateDOMFromString( strText.c_str() ); // [const char *] as parameter, not string, OK
	SplitSentence();
	SRL();

	logfile << "\n\nSRL info, third method\n";
	int paraNum = CountParagraphInDocument();
	for (int k=0; k < paraNum; ++k)
	{
		int sentNum = CountSentenceInParagraph(k);
		for (int j=0; j < sentNum; ++j)
		{
			int wordNum = CountWordInSentence(k, j);
			for (int i=0; i < wordNum; ++i)
			{
				vector<const char *> vecType;
				vector< pair<int, int> > vecBegEnd;

				GetPredArgToWord(vecType, vecBegEnd, k, j, i);
				if ( !vecType.empty() )
				{
					logfile << endl;
					for (int m=0; m < vecType.size(); ++m)
					{
						logfile << vecType[m] << " "
							<< vecBegEnd[m].first << " "
							<< vecBegEnd[m].second << " ^ ";
					}
				}
			}
		}
	}

	SaveDOM("test_srl_string.xml");

	return 0;
}

int test_IRLAS_vec()
{
	logfile << "\n\n------------"
		<< "\ntest IRLAS vec\n";

	if (0 != CreateDOMFromXml("test_irlas.xml")) return -1;

	logfile << "\nfirst method\n";
	int sentNum = CountSentenceInDocument();
	for (int i=0; i < sentNum; ++i)
	{
		vector<const char *> vecWord;
		vector<const char *> vecPOS;
		GetWordsFromSentence(vecWord, i);
		GetPOSsFromSentence(vecPOS, i);
		
		copy(vecWord.begin(), vecWord.end(), ostream_iterator<const char *>(logfile, " "));
		logfile << endl;
		copy(vecPOS.begin(), vecPOS.end(), ostream_iterator<const char *>(logfile, " "));
		logfile << endl;	
	}

	logfile << "\nsecond method\n";
	int paraNum = CountParagraphInDocument();
	for (int j=0; j < paraNum; ++j)
	{
		int sentNum = CountSentenceInParagraph(j);
		for (int i=0; i<sentNum; ++i)
		{
			vector<const char *> vecWord;
			vector<const char *> vecPOS;
			GetWordsFromSentence(vecWord, j, i);
			GetPOSsFromSentence(vecPOS, j, i);
			
			copy(vecWord.begin(), vecWord.end(), ostream_iterator<const char *>(logfile, " "));
			logfile << endl;
			copy(vecPOS.begin(), vecPOS.end(), ostream_iterator<const char *>(logfile, " "));
			logfile << endl;	
		}
	}	
	return 0;
}

int test_NER_vec()
{
	logfile << "\n\n------------"
		<< "\ntest NER vec\n";

	if (0 != CreateDOMFromXml("test_ner.xml")) return -1;

	logfile << "\nfirst method\n";
	int sentNum = CountSentenceInDocument();
	for (int i=0; i<sentNum; ++i)
	{
		vector<const char *> vecNE;
		GetNEsFromSentence(vecNE, i);
		
		copy(vecNE.begin(), vecNE.end(), ostream_iterator<const char *>(logfile, " "));
		logfile << endl;
	}

	logfile << "\nsecond method\n";
	int paraNum = CountParagraphInDocument();
	for (int j=0; j < paraNum; ++j)
	{
		int sentNum = CountSentenceInParagraph(j);
		for (int i=0; i<sentNum; ++i)
		{
			vector<const char *> vecNE;
			GetNEsFromSentence(vecNE, j, i);
			
			copy(vecNE.begin(), vecNE.end(), ostream_iterator<const char *>(logfile, " "));
			logfile << endl;
		}
	}
	return 0;
}

int test_WSD_vec()
{
	logfile << "\n\n------------"
		<< "\ntest WSD vec\n";

	if (0 != CreateDOMFromXml("test_wsd.xml")) return -1;

	logfile << "\nfirst method\n";
	int sentNum = CountSentenceInDocument();
	for (int i=0; i<sentNum; ++i)
	{
		vector<const char *> vecWSD;
		vector<const char *> vecWSDExplain;
		GetWSDsFromSentence(vecWSD, i);
		GetWSDExplainsFromSentence(vecWSDExplain, i);
		
		copy(vecWSD.begin(), vecWSD.end(), ostream_iterator<const char *>(logfile, " "));
		logfile << endl;
		copy(vecWSDExplain.begin(), vecWSDExplain.end(), ostream_iterator<const char *>(logfile, " "));
		logfile << endl;
	}

	logfile << "\nsecond method\n";
	int paraNum = CountParagraphInDocument();
	for (int j=0; j < paraNum; ++j)
	{
		int sentNum = CountSentenceInParagraph(j);
		for (int i=0; i<sentNum; ++i)
		{
			vector<const char *> vecWSD;
			vector<const char *> vecWSDExplain;
			GetWSDsFromSentence(vecWSD, j, i);
			GetWSDExplainsFromSentence(vecWSDExplain, j, i);

			copy(vecWSD.begin(), vecWSD.end(), ostream_iterator<const char *>(logfile, " "));
			logfile << endl;
			copy(vecWSDExplain.begin(), vecWSDExplain.end(), ostream_iterator<const char *>(logfile, " "));
			logfile << endl;
		}

	}

	return 0;
}

class print_parse
{
public:
	void operator()(const pair<int, const char *> &val) const
	{
		logfile << val.first << "," << val.second << " | ";
	}
};

int test_Parser_vec()
{
	logfile << "\n\n------------"
		<< "\ntest Parser vec\n";

	if (0 != CreateDOMFromXml("test_parser.xml")) return -1;

	logfile << "\nfirst method\n";
	int sentNum = CountSentenceInDocument();
	for (int i=0; i<sentNum; ++i)
	{
		vector< pair<int, const char *> > vecParse;
		GetParsesFromSentence(vecParse, i);
		
		for_each(vecParse.begin(), vecParse.end(), print_parse());
		logfile << endl;
	}

	logfile << "\nsecond method\n";
	int paraNum = CountParagraphInDocument();
	for (int j=0; j < paraNum; ++j)
	{
		int sentNum = CountSentenceInParagraph(j);
		for (int i=0; i<sentNum; ++i)
		{
			vector< pair<int, const char *> > vecParse;
			GetParsesFromSentence(vecParse, j, i);
			
			for_each(vecParse.begin(), vecParse.end(), print_parse());
			logfile << endl;
		}
	}

	return 0;
}

int main(int argc, char *argv[])
{	
	//cout << "test.txt" << endl;
	//cout << CreateDOMFromTxt("test.txt") << endl;
	//cout << SplitSentence() << endl;
	//cout << IRLAS() << endl;
	//cout << CRFWordSeg(); // Test the CRF based Word Segmentation
	//cout << SegmentWord();
	//cout << PosTag() << endl;
	//cout << NER() << endl;
	//cout << GParser() << endl;
	//cout << Parser() << endl;
	//cout << WSD() << endl;
	//cout << SRL() << endl;
	//cout << SaveDOM("test.xml") << endl;
	//return 0;

	//cout << "test0.txt" << endl;
	//cout << main2("test0.txt", "test0.xml") << endl;

	//test_main2();

	if (!logfile)
	{
		cerr << "can not open test_log.txt" << endl;
		exit(0);
	}
	readText();
	test_IRLAS();
	test_IRLAS_vec();
	return 0;

	test_SplitSentence();
	test_IRLAS();
	test_NER();

	test_WSD();
	test_Parser();

	test_SRL();

	test_IRLAS_vec();
	test_NER_vec();
	test_WSD_vec();
	test_Parser_vec();

	logfile.close();
	return 0;
}

