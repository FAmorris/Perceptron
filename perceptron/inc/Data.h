#ifndef __DATA_H
#define __DATA_H
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
}DT_TypeDef, *DT_TypeDefPtr; /* �������ݴ洢�ṹ������ͽṹ��ָ�� */

void DT_randForSequence( DT_TypeDefPtr dPtr );
void DT_SetSampleParameters( DT_TypeDefPtr dPtr );
void DT_DatasCreat( DT_TypeDefPtr dPtr );
void InputTestSamples( DataPtr dPtr );	
void DatasInit( DataPtr  dPtr ); 
void DatasDeInit( DataPtr dPtr );
void printTrainSamples( DataPtr dPtr );
void printTestSamples( DataPtr dPtr );
void setSampleParameters( DataPtr dPtr );
void printDatasParams( DataPtr dPtr );
#endif /* __DATA_H */

/********************************************************** END OF HEARD FILE ***************************************************************/