#ifndef __NLU_TUBE__
#define __NLU_TUBE__

#include "ENLU_data_struct.h"
using namespace std;

/*******************************************************************************
* NAME :            ENLU_Init
* 
* DESCRIPTION :     Init Model
* 	
* PARAMETERS:
* 	const char* folder 	folder name
*	const int mode		init mode - currently only 1 is valid
* RETURN VALUES:
*   1               successful
*   others          unsuccessful
*
* NOTES :           
*******************************************************************************/
unsigned int ENLU_Init(const char* folder,const int mode);
/*******************************************************************************
* NAME :            ENLU_Extract
* 
* DESCRIPTION :     ENLU Extraction
* 	
* PARAMETERS:
* 	const NLU_Input& 	nlp_data_s		input
*	NLU_Result& 		NLU_Result		output
* RETURN VALUES:
*   1               successful
*   others          unsuccessful
*
* NOTES :
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
unsigned int ENLU_Extract(const NLU_Input& nlp_data_s,NLU_Result& nlu_result);
/*******************************************************************************
* NAME :            ENLU_Uninit
* 
* DESCRIPTION :     Uninit Model
* 	
* PARAMETERS:
*
* RETURN VALUES:
*   1               successful
*   others          unsuccessful
*
* NOTES :           
*******************************************************************************/
unsigned int ENLU_Uninit();
/*******************************************************************************
* NAME :            ENLU_User_dict
* 
* DESCRIPTION :     Upload user dictionary
* 	
* PARAMETERS:
* 	int dict_type						the id of dictionary type
*	const vector<string>& word_list		the input list
*
* RETURN VALUES:
*   1               successful
*   others          unsuccessful
*
* NOTES : 
*
*	**WARNING**: If you want to put any user dict into ENLU,
*				 please run ENLU_User_dict before ENLU_Init
*   
*	available dict id:
*		#define UD_APP 0		//APP list 
*		#define UD_CONTACT 1	//Contact list
*		#define UD_SONG 2       //Song list 	
*******************************************************************************/
unsigned int ENLU_User_dict(int dict_type, const vector<string>& word_list);

#endif