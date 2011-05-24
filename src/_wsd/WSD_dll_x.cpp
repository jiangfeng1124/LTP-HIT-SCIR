#include "WSD_dll.h"

///////////////////////////////////////////////////////////////
//	�� �� �� : WSD
//	�������� : 
//	������� : 
//	��    ע : 
//	��    �� : lemon
//	ʱ    �� : 2006��4��24��
//	�� �� ֵ : bool
//	����˵�� : vector< string >& input ,����Ĵʻ�
//				 vector< string > &output ,�ʻ���������
//				 vector<string> &strexplain,�������Ľ���
//				 vector< vector<string> > & strcode���ʻ�����п��ܵ��������
///////////////////////////////////////////////////////////////
bool WSD(vector< string >& input , vector< string > &output , vector<string> &strexplain, vector< vector<string> > & strcode)
{
   string line;
   int count; //����input�к��ֵĸ�����
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
   int up = (input.size())*6 + count; // ÿ������������ռ�ĸ��ֽڣ��Է���һ����������һЩ
   char* chresult = new char[up+1]; //��̬����ռ�
   
   up = (input.size())*35 ; //��������Ľ�����34
   char *chexplain = new char[up+1];

   up = (input.size())*105; // ����ʻ�����б�����ռ���ֽ����������104
   char *chcode = new char[up+1];

   WSD_GetResults(line,chresult,chexplain,chcode); //�������

   string stresult = chresult;
   int pos = 0;
   int pos1;
   output.clear();
   strexplain.clear();
   strcode.clear();

   //���벿�֣�
   while((pos1 = stresult.find_first_of(' ',pos)) != string::npos)
   {
	   //pos = stresult.find_first_of(' ',pos1);
	   output.push_back(stresult.substr(pos,pos1-pos));
	   pos = pos1+1;

   }
   

   //���Ͳ��֣�
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


   //�ʻ��Ӧ��ȫ�����룻
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