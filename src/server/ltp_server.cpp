// Defines the entry point for the Web Service application.
//

#include <sys/wait.h>
#include <unistd.h>             /* For pause() */
#include <stdlib.h>
#include <signal.h>

#include <iostream>

#include "mongoose.h"

#include "../__xml4nlp/XML4NLP.H"
#include "../__ltp_dll/LTP.h"
#include "../__util/encode.hpp"

#if !defined(LISTENING_PORT)
#define LISTENING_PORT	"12345"
#endif /* !LISTENING_PORT */

using namespace std;

static int exit_flag;                   /* Program termination flag     */
static struct mg_context *ctx;

static XML4NLP xml4nlp;
static LTP ltp(xml4nlp);


static void Service(struct mg_connection *conn, const struct mg_request_info *ri, void *user_data);


static void
signal_handler(int sig_num)
{
        if (sig_num == SIGCHLD) {
                do {
                } while (waitpid(-1, &sig_num, WNOHANG) > 0);
        } else
        {
                exit_flag = sig_num;
        }
}

int main(int argc, char *argv[])
{
        (void) signal(SIGCHLD, signal_handler);
        (void) signal(SIGPIPE, SIG_IGN);

        (void) signal(SIGTERM, signal_handler);
        (void) signal(SIGINT, signal_handler);

        if ((ctx = mg_start()) == NULL) {
                (void) printf("%s\n", "Cannot initialize Mongoose context");
                exit(EXIT_FAILURE);
        }

	if (mg_get_option(ctx, "ports") == NULL &&
	    mg_set_option(ctx, "ports", LISTENING_PORT) != 1)
		exit(EXIT_FAILURE);
	
	if(mg_set_option(ctx, "max_threads", "1")){
		cout << "Set Threads successfully!" << endl;
	}

	// initialize the encoding library 
	enc::init();

	cout << "Begin ..." << endl;

	// mg_bind_to_uri(ctx, "/ltp", &Service, NULL);
	mg_set_uri_callback(ctx, "/ltp", &Service, NULL);

        while (exit_flag == 0)
                pause();

	mg_stop(ctx);

	return 0;
}

static string& utf8_gbk(const string& utf8, string &gbk)
{
	wstring tmp;
	enc::decode_utf8(utf8, tmp);
	enc::encode_gbk(tmp, gbk);
}

static string& gbk_utf8(const string& gbk, string &utf8)
{
	wstring tmp;
	enc::decode_gbk(gbk, tmp);
	enc::encode_utf8(tmp, utf8);
}

static void Service(struct mg_connection *conn, const struct mg_request_info *ri, void *user_data)
{
	char *sentence;
	char *type;
	char *encode;
	char *xml;
	string str_type;
	string str_encode;
	string str_xml;

	sentence = mg_get_var(conn, "s");
	
	if((type = mg_get_var(conn, "t")) == NULL){
		str_type = "";
	}else{
		str_type = type;
	}

	if((encode = mg_get_var(conn, "c")) == NULL){
		str_encode = "gbk";
	}else{
		str_encode = encode;
	}

	if((xml = mg_get_var(conn, "x")) == NULL){
		str_xml = "";
	} else {
		str_xml = xml;
	}
	
	if (sentence == NULL)
		return;
		
	string strSentence = sentence;

	// convert UTF-8 string to GBK
	if(str_encode == "utf8"){
        	utf8_gbk(strSentence, strSentence); 
	}

	cout << "Input sentence is: " << strSentence << endl;
	
	if(str_xml == "y"){
		xml4nlp.LoadXMLFromString(strSentence);
	} else {
		xml4nlp.CreateDOMFromString(strSentence);
	}

	if(str_type == "ws"){
		ltp.crfWordSeg();
	} else if(str_type == "pos"){
		ltp.postag();
	} else if(str_type == "wsd"){
		ltp.wsd();
	} else if(str_type == "ner"){
		ltp.ner();
	} else if(str_type == "dp"){
		ltp.gparser();
	} else if(str_type == "srl"){
		ltp.srl();
	} else {
		ltp.wsd();
		ltp.srl();
	}

	string strResult;
	xml4nlp.SaveDOM(strResult);
	
	strResult = "HTTP/1.1 200 OK\r\n\r\n" + strResult;
	if(str_encode == "utf8"){
        gbk_utf8(strResult, strResult); 
	}
	
	// cout << "Result is: " << strResult << endl;
	int max_len = MAX_REQUEST_SIZE - 1;
	int split_num = strResult.size() / max_len + 1;
	for(int i = 0; i < split_num; i++){
		mg_printf(conn, "%s", strResult.substr(i * max_len, max_len).c_str());
	}

	// mg_printf(conn, "%s", strResult.c_str());

	xml4nlp.ClearDOM();
	free(sentence);
	free(type);
	free(encode);
}

