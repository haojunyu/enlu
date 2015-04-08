#ifndef __CONSTANTS__
#define __CONSTANTS__
#define BOOL unsigned int


/************** USER DICT LIST **************/
#define UD_APP 0
#define UD_CONTACT 1
#define UD_SONG 2
#define UD_APP_ORIG 3

/************** MUSIC INFO LIST **************/
#define SONG_NM 3
#define ALBUM_NM 4
#define NO_RESULT 5
#define STOCK_NM 6
/************** Path seperator **************/
#ifdef __WIN32
#define SEPA "\\"
#else
#define SEPA "/"
#endif
/************** ERROR CODE LIST **************/
/**************  GENERAL ERROR  **************/
/************** 0x0000 ~ 0x00FF **************/
#define G_FAIL 0x0000
/* general failure, unknow reason */
#define G_SUCCESS 0x0001
/* general success */
#define G_NOT_INIT 0x0002
/* the out put buffer is not long enough to 
 * copy all the output */
#define G_I_SSRF 0x0003
/* init failed in mode 1, 
 * S SUCCESS but R failed */
#define G_I_SUFRF 0x0004
/* init failed in mode 1, 
 * S SUCCESS but R failed, 
 * And S Uninit Failed*/
#define G_I_CUFTF 0x0005
/* init failed in mode 0, 
 * CLS SUCCESS but TAG failed, 
 * And CLS Uninit Failed*/
#define G_U_DSRF 0x0006
/* Uninit failed in mode 1, 
 * D,S,R All Failed*/
#define G_U_DSF 0x0007
/* Uninit failed in mode 1, 
 * D,S Failed*/
#define G_U_DRF 0x0008
/* Uninit failed in mode 1, 
 * D,R Failed*/
#define G_U_SRF 0x0009
/* Uninit failed in mode 1, 
 * S,R Failed*/
#define G_U_DCTF 0x000A
/* Uninit failed in mode 0, 
 * D,C,T All Failed*/
#define G_U_DCF 0x000B
/* Uninit failed in mode 0, 
 * D,C Failed*/
#define G_U_DTF 0x000C
/* Uninit failed in mode 0, 
 * D,T Failed*/
#define G_U_CTF 0x000D
/* Uninit failed in mode 0, 
 * C,T Failed*/
#define G_A_INIT 0x000E
/* Already init*/
#define G_EMPTY_I 0x000F
/*Empty input*/
/**************      M ERROR    **************/
/************** 0x0100 ~ 0x01FF **************/
/**************      R ERROR    **************/
/************** 0x0200 ~ 0x02FF **************/
/**************      S ERROR    **************/
/************** 0x0300 ~ 0x03FF **************/
#define S_MODEL_OPEN_FAILED 0x0301
/*can't open model file*/
#define S_NOT_SUPPORT_ESTI 0x0302
/**************      D ERROR    **************/
/************** 0x0400 ~ 0x04FF **************/
#define D_MODEL_OPEN_FAILED 0x0401
#define D_MALLOC_FAILED 0x0402
#define D_SUCCESS 0x0403
#define D_NO_RESULT 0x0404
#define D_INITIAL_FAILED 0x0405
/*Model does not support probabiliy estimates*/
/**************      U ERROR    **************/
/************** 0x0500 ~ 0x05FF **************/
#define U_NOT_SUPPORT 0x0500
#define U_EMPTY_DICT 0x0501
/**************      DC ERROR    **************/
/************** 0x0600 ~ 0x06FF **************/
#define DC_INIT_FAIL 0x0600
#define DC_WS_FAIL 0x0601
/* The UD type is not in the predefined list */
#endif