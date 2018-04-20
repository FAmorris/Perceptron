#ifndef __DATA_H
#define __DATA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "UserType.h"

typedef struct{
	d64 **samPtrs;	/* ѵ�������洢��ά����ָ�� */
	d64 **tSamPtrs; /* ���������洢��ά����ָ�� */
	d64 **aimPtrs;	/* ѵ������Ŀ������洢��ά����ָ�� */
	d64 **tAimPtrs; /* ��������Ŀ������洢��ά����ָ�� */
	i32 *seqPtr; /* �洢ѵ��ʱ�����˳��һά����ָ��*/

	i32 numOfSample; /* ѵ����������	 */
	i32 numOfTSample; /* ������������ */
	i32 numOfInput;  /* ��������ά�� */
	i32 numOfOutput; /* �������ά�� */
	i32 samParmLabel; /* ���������ñ�־ */
	i32 creatLabel;
	i32 trainDataEntered;
	i32 testDataEntered;
}DT_TypeDef, *DT_TypeDefPtr; /* �������ݴ洢�ṹ������ͽṹ��ָ�� */

void DT_randForSequence( DT_TypeDefPtr dPtr );
void DT_SetSampleParameters( DT_TypeDefPtr dPtr );
void DT_DatasCreat( DT_TypeDefPtr dPtr );
void DT_InputTrainSamples( DT_TypeDefPtr dPtr );
void DT_InputTestSamples( DT_TypeDefPtr dPtr );
void DT_DatasInit( DT_TypeDefPtr  dPtr );
void DT_DatasDeInit( DT_TypeDefPtr dPtr );
void DT_PrintTrainSamples( DT_TypeDefPtr dPtr );
void DT_PrintTestSamples( DT_TypeDefPtr dPtr );
void DT_PrintDatasParams( DT_TypeDefPtr dPtr );
#endif /* __DATA_H */

#ifdef __cplusplus
}
#endif

/********************************************************** END OF HEARD FILE ***************************************************************/