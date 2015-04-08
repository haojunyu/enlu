#pragma once
#include <string>
#include <vector>

using namespace std;
/*******************************************************************************
*	How to fill in nlp_data_s:
*		This is the struct of NLU_Input:
*		struct NLU_Input
*		{
*			string ctx_tag;
*			vector<string> tokens;
*			string topic_note;
*		};
*		If this input is from NCS:
*			set	ctx_tag = "res_type_NCS"
*			set tokens as a one-element vector and fill the NCS sentence into it
*			set topic_note = " "	<-**WARNING** To prevent runtime error,
*									 topic_note must be set as a non-empty string
*		else:
*			set	ctx_tag = res_type_FST or res_type_FM
*			fill every segment of FM/FST input into tokens
*			set topic_not = " " <- non-empty again!
*******************************************************************************/

struct NLU_Input
{
    string ctx_tag;
    vector<string> tokens;
    string topic_note;
};

/*******************************************************************************
*	How to use NLU_Result:
*		This is the struct of NLU_Result:
*			struct NLU_Result
*			{
*				string domain_text; 	//the name of the domain
*				double domain_score;	//the confidence score of domain[0,1]
*				vector<string> slot_values;	//the arrays of slots, 
*										//every slot value will look like <POI_NM>=XXX
*										//you'll need to split them according 
*										//to your demand
*				double slot_score;		//the confidence score of slot extraction
*				string utterance;		//the input string without space
*			};
*		
*******************************************************************************/

struct NLU_Result
{
    string domain_text;
    double domain_score;
    vector<string> slot_values;
    double slot_score;
    string utterance;
};
