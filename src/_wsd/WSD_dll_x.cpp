#include "WSD_dll.h"

///////////////////////////////////////////////////////////////
//	函 数 名 : WSD
//	函数功能 : 
//	处理过程 : 
//	备    注 : 
//	作    者 : lemon
//	时    间 : 2006年4月24日
//	返 回 值 : bool
//	参数说明 : vector< string >& input ,输入的词汇
//				 vector< string > &output ,词汇的语义代码
//				 vector<string> &strexplain,语义代码的解释
//				 vector< vector<string> > & strcode，词汇的所有可能的语义编码
///////////////////////////////////////////////////////////////
bool WSD(vector< string >& input , vector< string > &output , vector<string> &strexplain, vector< vector<string> > & strcode)
{
   string line;
   int count; //计算input中汉字的个数；
   if(input.size() <= 0)
   {
	   return false;
   }
   else
   {
      line = "";
	  count = 0;
	  vector< string >::iterator iter = input.begin(), iter_end = input.end();
	  while(iter!=iter_end)
	  {
		  line = line + (*iter) + "/-1 ";
          count = count + (*iter).size();
		  iter++;
	  }
   }
   int up = (input.size())*6 + count; // 每个词义编码最多占四个字节，以防万一，多申请了一些
   char* chresult = new char[up+1]; //动态申请空间
   
   up = (input.size())*35 ; //最多字数的解释是34
   char *chexplain = new char[up+1];

   up = (input.size())*105; // 计算词汇的所有编码所占的字节数，最多是104
   char *chcode = new char[up+1];

   WSD_GetResults(line,chresult,chexplain,chcode); //消歧过程

   string stresult = chresult;
   int pos = 0;
   int pos1;
   output.clear();
   strexplain.clear();
   strcode.clear();

   //编码部分；
   while((pos1 = stresult.find_first_of(' ',pos)) != string::npos)
   {
	   //pos = stresult.find_first_of(' ',pos1);
	   output.push_back(stresult.substr(pos,pos1-pos));
	   pos = pos1+1;

   }
   

   //解释部分；
   pos = 0;
   string explain = chexplain;
   while((pos1 = explain.find_first_of(' ',pos)) != string::npos)
   {
	   string temp = explain.substr(pos,pos1-pos);
	   if(temp == "-1")
	   {
		   string emptystring = "";
		   strexplain.push_back(emptystring);
	   }
	   else
	   {
		   strexplain.push_back(temp);
	   }
       pos = pos1+1;

   }


   //词汇对应的全部编码；
   pos = 0;
   string code = chcode;
   while((pos1 = code.find_first_of('#',pos)) != string::npos)
   {
	   string temp = code.substr(pos,pos1-pos);
	   vector<string> incode;
	   incode.clear();

	   if(temp == "-1")
	   {
		   string emptystring = "";
		   incode.push_back(emptystring);
	   }
	   else
	   {
		   int pos2 = 0;
		   int pos3;
		   while((pos3 = temp.find_first_of(' ',pos2)) != string::npos)
		   {
			   incode.push_back(temp.substr(pos2,pos3-pos2));
			   pos2 = pos3 +1;
		   }
		   incode.push_back(temp.substr(pos2));
	   }
	   strcode.push_back(incode);
	   pos = pos1+1;
   }
   
   delete[] chresult; 
   delete[] chexplain;
   delete[] chcode;

   if((output.size() != input.size()) || (output.size() != strexplain.size()) || (output.size() != strcode.size()))
   {
	   return false;
   }

   return true;
}