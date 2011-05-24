#include "__ltp_dll.h"
#pragma comment(lib, "__ltp_dll.lib")

namespace HIT_IR_LTP {
	// Get words
	LTP_DLL_API int _GetWordsFromSentence(vector<const char *> &vecWord, int paragraphIdx, int sentenceIdx);
	LTP_DLL_API int _GetWordsFromSentence(vector<const char *> &vecWord, int globalSentIdx);

	// Get POSs
	LTP_DLL_API int _GetPOSsFromSentence(vector<const char *> &vecPOS, int paragraphIdx, int sentenceIdx);
	LTP_DLL_API int _GetPOSsFromSentence(vector<const char *> &vecPOS, int globalSentIdx);

	// Get NEs
	LTP_DLL_API int _GetNEsFromSentence(vector<const char *> &vecNE, int paragraphIdx, int sentenceIdx);
	LTP_DLL_API int _GetNEsFromSentence(vector<const char *> &vecNE, int globalSentIdx);

	// Get WSDs
	LTP_DLL_API int _GetWSDsFromSentence(vector<const char *> &vecWSD, int paragraphIdx, int sentenceIdx);
	LTP_DLL_API int _GetWSDsFromSentence(vector<const char *> &vecWSD, int globalSentIdx);

	LTP_DLL_API int _GetWSDExplainsFromSentence(vector<const char *> &vecWSDExplain, int paragraphIdx, int sentenceIdx);
	LTP_DLL_API int _GetWSDExplainsFromSentence(vector<const char *> &vecWSDExplain, int globalSentIdx);

	// Get Parses
	LTP_DLL_API int _GetParsesFromSentence(vector< pair<int, const char *> > &vecParse, int paragraphIdx, int sentenceIdx);
	LTP_DLL_API int _GetParsesFromSentence(vector< pair<int, const char *> > &vecParse, int globalSentIdx);

	// Get SRL
	LTP_DLL_API int _GetPredArgToWord(	vector<const char *> &vecType, vector< pair<int, int> > &vecBegEnd,
										int paragraphIdx, int sentenceIdx, int wordIdx);
	LTP_DLL_API int _GetPredArgToWord(	vector<const char *> &vecType, vector< pair<int, int> > &vecBegEnd,
										int globalSentIdx, int wordIdx);
	LTP_DLL_API int _GetPredArgToWord(	vector<const char *> &vecType, vector< pair<int, int> > &vecBegEnd,
										int globalWordIdx);
}

namespace HIT_IR_LTP {
	// Get words
	int GetWordsFromSentence(vector<const char *> &vecWord, int paragraphIdx, int sentenceIdx)
	{
		vecWord.clear();

		int wordNum = CountWordInSentence(paragraphIdx, sentenceIdx);
		if (wordNum > 0)
		{
			vecWord.resize(wordNum);
			_GetWordsFromSentence(vecWord, paragraphIdx, sentenceIdx);
		}

		return 0;
	}

	int GetWordsFromSentence(vector<const char *> &vecWord, int globalSentIdx)
	{
		vecWord.clear();

		int wordNum = CountWordInSentence(globalSentIdx);
		if (wordNum > 0)
		{
			vecWord.resize(wordNum);
			_GetWordsFromSentence(vecWord, globalSentIdx);
		}

		return 0;
	}

	// Get POSs
	int GetPOSsFromSentence(vector<const char *> &vecPOS, int paragraphIdx, int sentenceIdx)
	{
		vecPOS.clear();
		int wordNum = CountWordInSentence(paragraphIdx, sentenceIdx);
		if (wordNum > 0)
		{
			vecPOS.resize(wordNum);
			_GetPOSsFromSentence(vecPOS, paragraphIdx, sentenceIdx);
		}

		return 0;
	}

	int GetPOSsFromSentence(vector<const char *> &vecPOS, int globalSentIdx)
	{
		vecPOS.clear();
		int wordNum = CountWordInSentence(globalSentIdx);
		if (wordNum > 0)
		{
			vecPOS.resize(wordNum);
			_GetPOSsFromSentence(vecPOS, globalSentIdx);
		}

		return 0;
	}

	// Get NEs
	int GetNEsFromSentence(vector<const char *> &vecNE, int paragraphIdx, int sentenceIdx)
	{
		vecNE.clear();
		int wordNum = CountWordInSentence(paragraphIdx, sentenceIdx);
		if (wordNum > 0)
		{
			vecNE.resize(wordNum);
			_GetNEsFromSentence(vecNE, paragraphIdx, sentenceIdx);
		}

		return 0;
	}

	int GetNEsFromSentence(vector<const char *> &vecNE, int globalSentIdx)
	{
		vecNE.clear();
		int wordNum = CountWordInSentence(globalSentIdx);
		if (wordNum > 0)
		{
			vecNE.resize(wordNum);
			_GetNEsFromSentence(vecNE, globalSentIdx);
		}

		return 0;
	}

	// Get WSDs
	int GetWSDsFromSentence(vector<const char *> &vecWSD, int paragraphIdx, int sentenceIdx)
	{
		vecWSD.clear();
		int wordNum = CountWordInSentence(paragraphIdx, sentenceIdx);
		if (wordNum > 0)
		{
			vecWSD.resize(wordNum);
			_GetWSDsFromSentence(vecWSD, paragraphIdx, sentenceIdx);
		}

		return 0;
	}

	int GetWSDsFromSentence(vector<const char *> &vecWSD, int globalSentIdx)
	{
		vecWSD.clear();
		int wordNum = CountWordInSentence(globalSentIdx);
		if (wordNum > 0)
		{
			vecWSD.resize(wordNum);
			_GetWSDsFromSentence(vecWSD, globalSentIdx);
		}

		return 0;
	}

	int GetWSDExplainsFromSentence(vector<const char *> &vecWSDExplain, int paragraphIdx, int sentenceIdx)
	{
		vecWSDExplain.clear();
		int wordNum = CountWordInSentence(paragraphIdx, sentenceIdx);
		if (wordNum > 0)
		{
			vecWSDExplain.resize(wordNum);
			_GetWSDExplainsFromSentence(vecWSDExplain, paragraphIdx, sentenceIdx);
		}

		return 0;
	}

	int GetWSDExplainsFromSentence(vector<const char *> &vecWSDExplain, int globalSentIdx)
	{
		vecWSDExplain.clear();
		int wordNum = CountWordInSentence(globalSentIdx);
		if (wordNum > 0)
		{
			vecWSDExplain.resize(wordNum);
			_GetWSDExplainsFromSentence(vecWSDExplain, globalSentIdx);
		}
		return 0;
	}

	// Get Parses
	int GetParsesFromSentence(vector< pair<int, const char *> > &vecParse, int paragraphIdx, int sentenceIdx)
	{
		vecParse.clear();
		int wordNum = CountWordInSentence(paragraphIdx, sentenceIdx);
		if (wordNum > 0)
		{
			vecParse.resize(wordNum);
			_GetParsesFromSentence(vecParse, paragraphIdx, sentenceIdx);
		}
		return 0;
	}

	int GetParsesFromSentence(vector< pair<int, const char *> > &vecParse, int globalSentIdx)
	{
		vecParse.clear();
		int wordNum = CountWordInSentence(globalSentIdx);
		if (wordNum > 0)
		{
			vecParse.resize(wordNum);
			_GetParsesFromSentence(vecParse, globalSentIdx);
		}
		return 0;
	}

	// Get SRL
	int GetPredArgToWord(	vector<const char *> &vecType, vector< pair<int, int> > &vecBegEnd, 
							int paragraphIdx, int sentenceIdx, int wordIdx)
	{
		vecType.clear();
		vecBegEnd.clear();
		int argNum = CountPredArgToWord(paragraphIdx, sentenceIdx, wordIdx);
		if (argNum > 0)
		{
			vecType.resize(argNum);
			vecBegEnd.resize(argNum);
			_GetPredArgToWord(vecType, vecBegEnd, paragraphIdx, sentenceIdx, wordIdx);
		}
		return 0;
	}

	int GetPredArgToWord(	vector<const char *> &vecType, vector< pair<int, int> > &vecBegEnd,
							int globalSentIdx, int wordIdx)
	{
		vecType.clear();
		vecBegEnd.clear();
		int argNum = CountPredArgToWord(globalSentIdx, wordIdx);
		if (argNum > 0)
		{
			vecType.resize(argNum);
			vecBegEnd.resize(argNum);
			_GetPredArgToWord(vecType, vecBegEnd, globalSentIdx, wordIdx);
		}
		return 0;
	}

	int GetPredArgToWord(	vector<const char *> &vecType, vector< pair<int, int> > &vecBegEnd,
							int globalWordIdx)
	{
		vecType.clear();
		vecBegEnd.clear();
		int argNum = CountPredArgToWord(globalWordIdx);
		if (argNum > 0)
		{
			vecType.resize(argNum);
			vecBegEnd.resize(argNum);
			_GetPredArgToWord(vecType, vecBegEnd, globalWordIdx);
		}
		return 0;
	}

}

