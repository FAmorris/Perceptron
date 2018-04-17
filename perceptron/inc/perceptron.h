#ifndef __PERCEPTRON_H
#define __PERCEPTRON_H
#include "Data.h"
typedef struct {
	int numOfInput;																								/* ��֪����������ά��						*/
	int numOfOutput;																							/* ��֪���������ά��						*/
}perceptParam;																									/* ��֪���ṹ�����ṹ�嶨��			*/

typedef struct{
	perceptParam parameter;																				/* ��֪�������ṹ�����					*/
	DT_TypeDef perceptData;																							/* ��֪��ѵ�����������ݽṹ��		*/
		
	double *inPtr;																									/* ��֪����������洢һά����		*/
	double **wPtrs;																								/* ��֪��Ȩֵ�洢��ά����				*/
	double *ouPtr;																									/* ��֪������洢һά����				*/
	 
	double learnRate;																							/* ��֪��ѵ��ѧϰ��							*/

	int epoch;																										/* ��֪��ѵ�������						*/
	int perCreatLabel;																							/* ��֪���ڴ��ѷ����־					*/
	int perParmLabel;																							/* ��֪�����������ñ�־					*/

}percetron, *perceptPtr;																						/* ��֪�������ṹ�嶨��					*/

double randOfDouble( void );																			/* �������һ��-1~+1֮���С��	*/
int signFunction( double sum );																			/* ���ź���											*/
void setPerceptronParam( perceptPtr pPtr );														/* ���ø�֪����������						*/
void perceptronCreat( perceptPtr pPtr );															/*	��֪�������ڴ溯��					*/
void perceptronInit( perceptPtr pPtr );																/*	��֪����ʼ������						*/
void perceptronTrain( perceptPtr pPtr );															/*	��֪��ѵ�����ɲ�������			*/
void perceptronTest( perceptPtr pPtr );																/*	��֪���������ܺ���					*/
void usePerceptron( perceptPtr pPtr );																/*	ʹ�ø�֪������							*/
void printWeights( perceptPtr pPtr );																/* ��ʾ��֪��Ȩֵ								*/
void printBiases( perceptPtr pPtr );																	/* ��ʾ��֪��ƫ��								*/
void printPerceptronParam( perceptPtr pPtr );
void printInstructions( int *cho );
#endif  /* __PERCEPTRON_H */

/******************************************************* END OF HEARD FILE *************************************************************/