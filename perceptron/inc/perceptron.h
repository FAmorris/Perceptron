#ifndef __PERCEPTRON_H
#define __PERCEPTRON_H
#include "Data.h"
typedef struct {
	int numOfInput;																								/* 感知机输入向量维数						*/
	int numOfOutput;																							/* 感知机输出向量维数						*/
}perceptParam;																									/* 感知机结构参数结构体定义			*/

typedef struct{
	perceptParam parameter;																				/* 感知机参数结构体变量					*/
	DT_TypeDef perceptData;																							/* 感知机训练、测试数据结构体		*/
		
	double *inPtr;																									/* 感知机数据输入存储一维数组		*/
	double **wPtrs;																								/* 感知机权值存储二维数组				*/
	double *ouPtr;																									/* 感知机输出存储一维数组				*/
	 
	double learnRate;																							/* 感知机训练学习率							*/

	int epoch;																										/* 感知机训练最大步数						*/
	int perCreatLabel;																							/* 感知机内存已分配标志					*/
	int perParmLabel;																							/* 感知机参数已设置标志					*/

}percetron, *perceptPtr;																						/* 感知机参数结构体定义					*/

double randOfDouble( void );																			/* 随机生产一个-1~+1之间的小数	*/
int signFunction( double sum );																			/* 符号函数											*/
void setPerceptronParam( perceptPtr pPtr );														/* 设置感知机参数函数						*/
void perceptronCreat( perceptPtr pPtr );															/*	感知机分配内存函数					*/
void perceptronInit( perceptPtr pPtr );																/*	感知机初始化函数						*/
void perceptronTrain( perceptPtr pPtr );															/*	感知机训练自由参数函数			*/
void perceptronTest( perceptPtr pPtr );																/*	感知机测试性能函数					*/
void usePerceptron( perceptPtr pPtr );																/*	使用感知机函数							*/
void printWeights( perceptPtr pPtr );																/* 显示感知机权值								*/
void printBiases( perceptPtr pPtr );																	/* 显示感知机偏置								*/
void printPerceptronParam( perceptPtr pPtr );
void printInstructions( int *cho );
#endif  /* __PERCEPTRON_H */

/******************************************************* END OF HEARD FILE *************************************************************/