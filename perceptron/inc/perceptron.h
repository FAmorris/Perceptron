#ifndef __PERCEPTRON_H
#define __PERCEPTRON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Data.h"
typedef struct {
	i32 numOfInput;/* 感知机输入向量维数 */
	i32 numOfOutput; /* 感知机输出向量维数 */
}PCPT_ParamTypeDef, /* 感知机结构参数结构体 */
*PCPT_ParamTypeDefPtr; /* 感知机结构参数结构体指针 */

typedef struct{
	PCPT_ParamTypeDef parameter; /* 感知机参数结构体变量 */
	DT_TypeDef perceptData; /* 感知机训练、测试数据结构体 */
		
	d64 *inPtr;	 /* 感知机数据输入存储一维数组 */
	d64 **wPtrs; /* 感知机权值存储二维数 */
	d64 *ouPtr; /* 感知机输出存储一维数组 */
	 
	d64 learnRate; /* 感知机训练学习率 */

	i32 epoch; /* 感知机训练最大步数*/
	i32 pcptCreatLabel; /* 感知机内存已分配标志 */
	i32 pcptParmLabel; /* 感知机参数已设置标志 */

}PCPT_TypeDef, /* 感知机参数结构体 */
*PCPT_TypeDefPtr;/* 感知机参数结构体指针 */

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