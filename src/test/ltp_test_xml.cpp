// Defines the entry point for the console application.
//

#include <stdlib.h>
#include <iostream>

#include "../__xml4nlp/XML4NLP.H"
#include "../__ltp_dll/LTP.h"

using namespace std;

static XML4NLP xml4nlp;
static LTP ltp(xml4nlp);

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		cerr << "Usage: ./ltp_test <type> <test_xml_file> <result_file>" << endl;
		exit(1);
	}

	string type(argv[1]);

	xml4nlp.LoadXMLFromFile(argv[2]);
	if(type == "ws"){
		ltp.crfWordSeg();
	} else if(type == "pos"){
		ltp.postag();
	} else if(type == "wsd"){
		ltp.wsd();
	} else if(type == "ner"){
		ltp.ner();
	} else if(type == "dp"){
		ltp.gparser();
	} else if(type == "srl"){
		ltp.srl();
	} else {
		ltp.wsd();
		ltp.srl();
	}

	xml4nlp.SaveDOM(argv[3]);

	xml4nlp.ClearDOM();

	return 0;
}

