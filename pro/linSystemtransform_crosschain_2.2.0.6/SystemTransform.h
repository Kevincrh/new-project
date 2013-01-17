/** @file    SystemTransform.h
  * @note    HANGZHOU Hikvison Software Co.,Ltd.All Right Reserved.
  * @brief   SystemTransform header file
  * 
  * @author  PlaySDK
  * @date    27/8/2012
  * 
  * @note
  *
  * @warning  Windows 32bit /Linux32 bit version
  */

#ifndef _SYSTEM_TRANSFORM_H_
#define _SYSTEM_TRANSFORM_H_

#ifdef WIN32
	#if defined(_WINDLL)
	    #define SYSTRANS_API  __declspec(dllexport) 
	#else 
	    #define SYSTRANS_API  __declspec(dllimport) 
    #endif
#else
    #ifndef __stdcall
	    #define __stdcall
    #endif

	#ifndef SYSTRANS_API
	    #define  SYSTRANS_API
	#endif
#endif

#define SWITCH_BY_TIME			2

#define SUBNAME_BY_GLOBALTIME	2

/************************************************************************
* ״̬�붨��
************************************************************************/
#define SYSTRANS_OK				0x00000000
#define SYSTRANS_E_HANDLE		0x80000000	//ת���������
#define SYSTRANS_E_SUPPORT		0x80000001	//���Ͳ�֧��
#define SYSTRANS_E_RESOURCE		0x80000002	//��Դ������ͷŴ���
#define SYSTRANS_E_PARA			0x80000003	//��������
#define SYSTRANS_E_PRECONDITION 0x80000004  //ǰ������δ���㣬����˳��
#define SYSTRANS_E_OVERFLOW     0x80000005  //�������
#define SYSTRANS_E_STOP			0x80000006  //ֹͣ״̬
#define SYSTRANS_E_FILE         0x80000007  //�ļ�����

/************************************************************************
* Ŀ���װ��ʽ����
************************************************************************/
typedef enum SYSTEM_TYPE
{
	TRANS_SYSTEM_HIK		= 0x1,	//�����ļ��㣬�����ڴ���ʹ洢
	TRANS_SYSTEM_MPEG2_PS	= 0x2,	//PS�ļ��㣬��Ҫ���ڴ洢��Ҳ�����ڴ���
	TRANS_SYSTEM_MPEG2_TS	= 0x3,	//TS�ļ��㣬��Ҫ���ڴ��䣬Ҳ�����ڴ洢
	TRANS_SYSTEM_RTP		= 0x4,	//RTP�ļ��㣬���ڴ���
	TRANS_SYSTEM_MPEG4		= 0x5,	//MPEG4�ļ��㣬���ڴ洢
};

typedef struct SYS_TRANS_PARA 
{
	unsigned char* pSrcInfo;		//�����豸����ý����Ϣͷ
	unsigned long  dwSrcInfoLen;	//��ǰ�̶�Ϊ40
	SYSTEM_TYPE    enTgtType;
	unsigned long  dwTgtPackSize;	//���Ŀ��ΪRTP��PS/TS�ȷ�װ��ʽʱ���趨ÿ������С������
} SYS_TRANS_PARA;

typedef struct AUTO_SWITCH_PARA
{
	unsigned long dwSwitchFlag;		    //SWITCH_BY_TIME��ͨ��ʱ�����л�
	unsigned long dwSwitchValue;	    //ʱ���Է���Ϊ��λ
	unsigned long dwSubNameFlag;	    //SUBNAME_BY_GLOBALTIME: �ļ�����ȫ��ʱ������
	char          szMajorName[128];     //��szMajorName = c:\test,�л��ļ�������� = c:\test_������ʱ����.mp4
} AUTO_SWITCH_PARA;

#define TRANS_SYSHEAD				1	//ϵͳͷ����
#define TRANS_STREAMDATA			2	//��Ƶ�����ݣ�����������������Ƶ�ֿ�����Ƶ�����ݣ�
#define TRANS_AUDIOSTREAMDATA		3	//��Ƶ������
#define TRANS_PRIVTSTREAMDATA       4   //Private stream
#define TRANS_PACKPARAM             5   //Parameter for raw data

typedef struct OUTPUTDATA_INFO 
{
	unsigned char* pData;          //�ص����ݻ��棬��ָ�����������첽�Ĵ���
	unsigned long dwDataLen;       //�ص����ݳ���
	unsigned long dwDataType;      //�������ͣ���TRANS_SYSHEAD,TRANS_STREAMDATA
} OUTPUTDATA_INFO;


typedef enum DATA_TYPE 
{
	MULTI_DATA,
 	VIDEO_DATA,
 	AUDIO_DATA,
 	PRIVATE_DATA,
    VIDEO_PARA,
	AUDIO_PARA,
	PRIVATE_PARA
};

//����Ľṹ����������VIDEO_PARA��������
typedef struct _HK_SYSTEM_TIME_
{
    unsigned int		   dwYear;
    unsigned int           dwMonth;
    unsigned int		   dwDay;
    unsigned int		   dwHour;
    unsigned int		   dwMinute;
    unsigned int		   dwSecond;
    unsigned int           dwMilliSecond;
    unsigned int           dwReserved;
} HK_SYSTEM_TIME;

typedef struct _HK_VIDEO_PACK_PARA_ 
{
    unsigned int   dwFrameNum;
    unsigned int   dwTimeStamp;
    float          fFrameRate;
    unsigned int   dwReserved;
    HK_SYSTEM_TIME stSysTime;
    
} HK_VIDEO_PACK_PARA;

//����Ľṹ����������AUDIO_PARA��������
typedef struct _HK_AUDIO_PACK_PARA_ 
{
    unsigned int          dwChannels;
    unsigned int		  dwBitsPerSample;
    unsigned int          dwSampleRate;
    unsigned int          dwBitRate;
	unsigned int          dwTimeStamp;
	unsigned int          dwReserved[3];
} HK_AUDIO_PACK_PARA;

//����Ľṹ����������PRIVATE_PARA��������
typedef struct _HK_PRIVATE_PACK_PARA_ 
{
    unsigned int          dwPrivateType;
    unsigned int		  dwDataType;
    unsigned int          dwSycVideoFrame;
    unsigned int          dwReserved;
	unsigned int          dwTimeStamp;
    unsigned int          dwReserved1[2];
} HK_PRIVATE_PACK_PARA;

#ifdef __cplusplus
	extern "C" {
#endif
/************************************************************************
* ��������SYSTRANS_Create                                                  
* ���ܣ�  ͨ��Դ��Ŀ��ķ�װ������������װ��ʽת�����
* ������  phTrans	   - ���صľ��
*		  pstTransInfo - ת����Ϣ����ָ��
* ����ֵ��״̬��
************************************************************************/
SYSTRANS_API long __stdcall SYSTRANS_Create(void** phTrans, SYS_TRANS_PARA* pstTransInfo);

/************************************************************************
* ��������SYSTRANS_Start                                                 
* ���ܣ�  ��ʼ��װ��ʽת��
* ������  hTrans	- ת�����
*		  szSrcPath - Դ�ļ�·���������NULL������Ϊ��
*		  szTgtPath - Ŀ���ļ�·���������NULL������Ϊ��
* ����ֵ��״̬��
************************************************************************/
SYSTRANS_API long __stdcall SYSTRANS_Start(void* hTrans, const char* szSrcPath, const char* szTgtPath);

/************************************************************************
* ��������SYSTRANS_AutoSwitch                                                 
* ���ܣ�  Ŀ��Ϊ�ļ�ʱ���Զ��л��洢�ļ�
* ������  hTrans	- ת�����
*		  pstPara   - �Զ��л��ļ��Ĳ����ṹָ��
* ����ֵ��״̬�� 
************************************************************************/
SYSTRANS_API long __stdcall SYSTRANS_AutoSwitch(void* hTrans, AUTO_SWITCH_PARA* pstPara);

/************************************************************************
* ��������SYSTRANS_ManualSwitch                                                 
* ���ܣ�  Ŀ��Ϊ�ļ�ʱ���ֶ��л��洢�ļ�
* ������  hTrans	- ת�����
*		  szTgtPath - ��һ�洢�ļ���·��
* ����ֵ��״̬�� 
************************************************************************/
SYSTRANS_API long __stdcall SYSTRANS_ManualSwitch(void* hTrans, const char* szTgtPath);

/************************************************************************
* ��������SYSTRANS_InputData                                                 
* ���ܣ�  ԴΪ��ģʽ����������
* ������  hTrans	- ת�����
*		  pData		- Դ��������ָ��
*		  dwDataLen - �����ݴ�С
*		  enType	- �������ͣ���δʹ�ã�ͳһ��MULTI_DATA
* ����ֵ��״̬��
************************************************************************/
SYSTRANS_API long __stdcall SYSTRANS_InputData(void* hTrans, DATA_TYPE enType, unsigned char* pData, unsigned long dwDataLen);

/************************************************************************
* ��������SYSTRANS_GetTransPercent                                                 
* ���ܣ�  ת�ļ�ģʽʱ�����ת���ٷֱȣ���ʱֻ֧��Դ��HIK��PS��MPEG4
* ������  hTrans	 - ת�����
*		  pdwPercent - ת���ٷֱ�
* ����ֵ��״̬��
************************************************************************/

SYSTRANS_API long __stdcall SYSTRANS_GetTransPercent(void* hTrans,unsigned int* pdwPercent);

/************************************************************************
* ��������SYSTRANS_RegisterOutputDataCallBack                                                 
* ���ܣ�  Ŀ��Ϊ��ģʽ��ע��ת�������ݻص�
* ������  hTrans				- ת�����
*		  OutputDataCallBack	- ����ָ��
*		  dwUser				- �û�����
* ����ֵ��״̬��
* ˵����  3GPP��֧�ֻص�
************************************************************************/
SYSTRANS_API long __stdcall SYSTRANS_RegisterOutputDataCallBack(void* hTrans, void (__stdcall * OutputDataCallBack)(OUTPUTDATA_INFO* pDataInfo, unsigned long dwUser), unsigned long dwUser);


/************************************************************************
* ��������SYSTRANS_RegisterOutputDataCallBackEx                                                 
* ���ܣ�  Ŀ��Ϊ��ģʽ��ע��ת�������ݻص�
* ������  hTrans				- ת�����
*		  OutputDataCallBack	- ����ָ��
*		  dwUser				- �û�����
* ����ֵ��״̬��
* ˵����  3GPP��֧�ֻص�
************************************************************************/
SYSTRANS_API long __stdcall SYSTRANS_RegisterOutputDataCallBackEx(void* hTrans, void (__stdcall * OutputDataCallBack)(OUTPUTDATA_INFO* pDataInfo, void* pUser), void* pUser);

/************************************************************************
* ��������SYSTRANS_Stop                                                 
* ���ܣ�  ֹͣת��
* ������  hTrans	 - ת�����
* ����ֵ��״̬��
************************************************************************/
SYSTRANS_API long __stdcall SYSTRANS_Stop(void* hTrans);

/************************************************************************
* ��������SYSTRANS_Release                                                 
* ���ܣ�  �ͷ�ת�����
* ������  hTrans	 - ת�����
* ����ֵ��״̬��
************************************************************************/
SYSTRANS_API long __stdcall SYSTRANS_Release(void* hTrans);


#ifdef __cplusplus
	}
#endif

#endif //_SYSTEM_TRANSFORM_H_
