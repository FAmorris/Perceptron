#ifndef __DATA_H
#define __DATA_H
#include "UserType.h"

typedef struct{
	d64 **samPtrs;	/* 训练样本存储二维数组指针 */
	d64 **tSamPtrs; /* 测试样本存储二维数组指针 */
	d64 **aimPtrs;	/* 训练样本目标输出存储二维数组指针 */
	d64 **tAimPtrs; /* 测试样本目标输出存储二维数组指针 */
	i32 *seqPtr; /* 存储训练时的随机顺序一维数组指针*/

	i32 numOfSample; /* 训练样本总数	 */
	i32 numOfTSample; /* 测试样本总数 */
	i32 numOfInput;  /* 输入向量维数 */
	i32 numOfOutput; /* 输出向量维数 */
	i32 samParmLabel; /* 参数已设置标志 */
	i32 creatLabel;
}DT_TypeDef, *DT_TypeDefPtr; /* 样本数据存储结构体变量和结构体指针 */

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