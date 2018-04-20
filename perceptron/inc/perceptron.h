#ifndef __PERCEPTRON_H
#define __PERCEPTRON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Data.h"
typedef struct {
	i32 numOfInput;/* ��֪����������ά�� */
	i32 numOfOutput; /* ��֪���������ά�� */
}PCPT_ParamTypeDef, /* ��֪���ṹ�����ṹ�� */
*PCPT_ParamTypeDefPtr; /* ��֪���ṹ�����ṹ��ָ�� */

typedef struct{
	PCPT_ParamTypeDef parameter; /* ��֪�������ṹ����� */
	DT_TypeDef perceptData; /* ��֪��ѵ�����������ݽṹ�� */
		
	d64 *inPtr;	 /* ��֪����������洢һά���� */
	d64 **wPtrs; /* ��֪��Ȩֵ�洢��ά�� */
	d64 *ouPtr; /* ��֪������洢һά���� */
	 
	d64 learnRate; /* ��֪��ѵ��ѧϰ�� */

	i32 epoch; /* ��֪��ѵ�������*/
	i32 pcptCreatLabel; /* ��֪���ڴ��ѷ����־ */
	i32 pcptParmLabel; /* ��֪�����������ñ�־ */

}PCPT_TypeDef, /* ��֪�������ṹ�� */
*PCPT_TypeDefPtr;/* ��֪�������ṹ��ָ�� */

void PCPT_SetPerceptronParam( PCPT_TypeDefPtr pPtr );
void PCPT_PerceptronCreat( PCPT_TypeDefPtr pPtr );
void PCPT_PerceptronInit( PCPT_TypeDefPtr pPtr );
void PCPT_PerceptronTrain( PCPT_TypeDefPtr pPtr );
void PCPT_PerceptronTest( PCPT_TypeDefPtr pPtr )	;
void PCPT_UsePerceptron( PCPT_TypeDefPtr pPtr );
void PCPT_PrintWeights( PCPT_TypeDefPtr pPtr );
void PCPT_PrintBiases( PCPT_TypeDefPtr pPtr );
void PCPT_PrintPerceptronParam( PCPT_TypeDefPtr pPtr );
void PCPT_PrintInstructions( i32 *cho );

#ifdef _cplusplus
}
#endif

#endif  /* __PERCEPTRON_H */

/******************************************************* END OF HEARD FILE *************************************************************/