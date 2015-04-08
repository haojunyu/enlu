#include <ctype.h>
#include <stddef.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <unistd.h>
#include <ENLU_Constants.h>
#include <ENLU_data_struct.h>
#include <ENLU_API.h>

using namespace std;

void SplitLine(vector<string>& word_vec,string line,char separator)
{
	string last = line;
	std::size_t separator_founded = last.find_first_of(separator);
	while (separator_founded != string::npos)
	{
		string word = last.substr(0,separator_founded);
		if (!word.empty())
		{
			word_vec.push_back(word);
		}
		last = last.substr(separator_founded+1);
		separator_founded = last.find_first_of(separator);
	}
	if (!last.empty())
	{
		word_vec.push_back(last);
	}
}
void TransferLine_2_ASRInput(string test_sentence,NLU_Input& asr_input)
{
	vector<string> splited_sentence;
	SplitLine(splited_sentence,test_sentence,' ');
	for (vector<string>::const_iterator it = splited_sentence.begin();it != splited_sentence.end();it++)
	{
		string temp_str("");
		vector<string> splited_word;
		SplitLine(splited_word,*it,'|');
		for(vector<string>::iterator jt = splited_word.begin();jt != splited_word.end();jt++)
		{
			if (jt == splited_word.end()-1)
			{
				temp_str += *jt;
			}
			else
			{
				temp_str += *jt + " ";
			}			
		}
		asr_input.tokens.push_back(temp_str);
	}
    asr_input.topic_note=" ";
}
vector<string> get_user_dict(const char* filename)
{
	vector<string> dict;
	ifstream ifs(filename);
	if(!ifs.is_open())
		return dict;
	string line;
	while(getline(ifs,line))
	{
		string::size_type   pos(0);   
        if((pos=line.find("\r"))!=string::npos)   
            line.replace(pos,1,"");
		if((pos=line.find("\n"))!=string::npos)   
			line.replace(pos,1,"");		
		if(line.empty())
			continue;
		dict.push_back(line);
	}
	return dict;
}
int init_ud(const char* folder)
{
    char* udFiles[]={(char*)"app",(char*)"contact",(char*)"song"};
    for(size_t i=0;i<3;i++)
    {
        string filename=string()+folder+SEPA+udFiles[i]+".txt";
        printf("try to load %s\n",filename.c_str());
        if( G_SUCCESS == ENLU_User_dict(i, get_user_dict(filename.c_str())))
			printf("Initialized.\n");
		else
			printf("Initialization failed.\n");
    }
    return 0;
}
int main(int argc,char** argv)
{
	#ifndef NDEBUG
	printf("this is DEBUG mode.\n");
	#endif
	for(int j=0;j<1;j++){
	if (argc < 2 )
	{
        printf("./ENLU_Test (-c mode) (-m model_folder) (-r result_file) (-u user_dict_folder) test_file\n");
		return 0;
	}
	int mode =1;
    char* model_folder=(char*)"../model/";
    char* result_file =(char*)"result.txt";
    char* user_dict_folder=NULL;
    const char *optstr = ":c:m:r:u:";
    int opt=0;
    while((opt=getopt(argc,argv,optstr)) != -1) 
    {
        switch(opt)
        {
            case 'c':
            {
                mode = atoi(optarg);
                break;
            }
            case 'm':
            {
                model_folder = optarg;
                break;
            }
            case 'r':
            {
                result_file = optarg;
                break;
            }
            case 'u':
            {
                user_dict_folder = optarg;
                break;
            }
            case '?':
                printf("unknow option：%c/n",optopt); 
        }
    }
    if(user_dict_folder)
    {
        init_ud(user_dict_folder);
    }
	if( ENLU_Init(model_folder,mode) != G_SUCCESS )
    {
        printf("Init Failed\n");
        return 0;
    }
	printf("Init Succeeded\n");
	ifstream ifile(argv[optind]);
	ofstream ofile(result_file);
	
	string line("");
	if (!ifile.is_open() || !ofile.is_open())
	{
		cout<<"open test file fail."<<endl;
	}
	ofile<<"#head;Pateo_result;1.0;utf-8"<<endl;
	ofile<<"#text#true_topic#true_slots%%predicted_topic#predicted_slots_and_score"<<endl;
	ofile<<"head#"<<endl;
	while(getline(ifile,line))
	{
	    if (line.size() < 1)
		{
			ofile<<endl;
		}
	    else
		{
			vector<string> line_vec;
			SplitLine(line_vec,line,'#');
			NLU_Input test_asr_input;
			string test_sentence =line_vec[0];
			TransferLine_2_ASRInput(test_sentence,test_asr_input);
			test_asr_input.ctx_tag=line_vec[1];
	        NLU_Result NLU_Result;
			NLU_Result.utterance=" ";
			NLU_Result.domain_text=" ";
			BOOL rtnCode = ENLU_Extract(test_asr_input,NLU_Result);
			if(rtnCode != G_SUCCESS)
			{
				printf("Errror Occurred. Errorno:0x%04x.\n",rtnCode);
				continue;
			}
			char dscore[50];
			memset(dscore,0,50);
			sprintf(dscore,"%f",NLU_Result.domain_score);
			string out_line = NLU_Result.domain_text + ";cls_score=" + dscore + "#";
			string result("");
			if(NLU_Result.slot_values.size()>0 )
			{
				char score[50];
				memset(score,0,50);
				sprintf(score,"%f",NLU_Result.slot_score);
				for(size_t i = 0;i < NLU_Result.slot_values.size();i++)
				{
					result += NLU_Result.slot_values[i] + ';';
				}
				out_line += result + "slot_score="+score+";";
			}
			if (test_asr_input.ctx_tag == "res_type_NCS"){
				line_vec[0]=NLU_Result.utterance;
				for(size_t i=0;i<line_vec.size();i++){
					if (i==0)
						line=line_vec[i];
					else
						line=line+"#"+line_vec[i];
				}
			}
			ofile<<line<<"%%"<<out_line<<endl;
		}
	}
	#ifndef NDEBUG
	char strBuf[512]={'\0'};
	char cmdBuf[256]={'\0'};
	sprintf(cmdBuf,"ps -eo size,cmd|grep '%s'|awk '{print $1}'",argv[0]);
	FILE *fp=popen(cmdBuf,"r");
	fscanf(fp,"%s",strBuf);
	printf("memory consumed:%.2f MB\n",atof(strBuf)/1024);
	fclose(fp);
	ofile<<"#memory#"<<setiosflags(ios::fixed)<<setprecision(2)<<atof(strBuf)/1024<<"MB"<<endl;
	#endif
	if(!ENLU_Uninit())
	{
		printf("Unable to uninitial\n");
	}
	#ifndef NDEBUG
	sprintf(cmdBuf,"tail -n 1 timeLog.txt");
	fp=popen(cmdBuf,"r");
	fgets(strBuf,512,fp);
	printf("%s",strBuf);
	ofile<<"#time#"<<strBuf<<endl;
	fclose(fp);
	#endif
	ifile.close();
	ofile.close();
	}
	return 0;
}
