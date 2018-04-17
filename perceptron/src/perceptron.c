/**
   ******************************************************************************************************************************************************
   * @file		peceptron.c
   * @author	Morris
   * @version	V1.0
   * @date		2018��4��17��22:05:52 ��VS2017��Debugģʽ��������
   * @brief		ͳ��ѧϰ���������еĸ�֪������֪����
   ******************************************************************************************************************************************************
   * @attention
   *
   *
   *
   *
   *
   *
   ******************************************************************************************************************************************************
   */

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "perceptron.h"

/**
 * @brief		�ж�һ�����Ƿ���Inf����NaN
 * @param		double sum Ҫ�жϵ���
 * @retval
 */

static int __isNormal( double sum )
{
	if( sum == sum && sum != ( sum + 1.0 ) ){/* �ж�һ�����Ƿ�����������	 */
		return 1; /* ������������1 */
	}/* end if */
	else{
		return 0; /* ���򷵻�0 */
	}/* end else */
}/* end function __isNormal */

double randOfDouble( void )/* ������������� */
{
	return ( -1 + rand() % 2 + ( double )rand() / RAND_MAX ); /* �������һ��-1~1֮���С�� */
}/*end function randOfDouble */

int signFunction( double sum )																								/* ���ź���													*/
{
	if( sum >= 0 ){																														/* �жϺ��������Ƿ���ڻ����0			*/
		return 1;																															/* �ж������������� +1							*/
	}/* end if */															
	else{																
		return -1;																															/* ���򷵻�-1												*/
	}/* end else */
}/**************************************************************** end function signFunction *********************************************************************/

void setPerceptronParam( perceptPtr pPtr )																			/* ��֪�������趨����								*/
{
	int num1;																																/* ��ʱ����													*/
	double lr;																																/* ѧϰ����ʱ����										*/

	do{																																		/* do...whileѭ����										*/
		printf("\nEnter the max train epochs of perceptron"
					"(Enter -1 to exit): ");																							/* �ı���ʾ��Ϣ											*/
		scanf("%d", &num1);																										/* ����ѵ�����غ���								*/
		if( num1 == -1 ){																												/* �ж��Ƿ�ѡ���˳���֪�������趨		*/
			return;																															/* ����������������								*/
		}/* end if */

		if( num1 < 0 ){																													/* �ж����ѵ���غ����Ƿ�С��0			*/
			printf("\nError: Please enter an interger which is"
						" greater than 0.\n ");																						/* �ı���ʾ��Ϣ											*/
		}/* end if */
	}while( num1 < 0 );																												/* ѭ��ֱ��������ȷ��ѡ���˳�				*/
	pPtr->epoch = num1;																											/* �趨���ѵ���غ���								*/

	do{																																		/* do...whileѭ����										*/
		printf("\nEnter the learn rate of perceptron"
					"train(Enter -1 to exit): ");																					/* �ı���ʾ��Ϣ											*/	
		scanf("%lf", &lr);																											/* ����ѧϰ��												*/
		if( -0.9999 > lr && lr > -1.0001 ){																					/* �ж��Ƿ�ѡ���˳���֪�������趨		*/
			return;																															/* ����������������								*/
		}/* end if */

		if( lr < 0 || lr > 1.0 ){																										/* �ж�ѧϰ�������Ƿ����						*/											
			printf("\nError: Please enter an number which is"
						" greater than 0 but lower than 1.\n ");															/* �ı���ʾ��Ϣ											*/
		}/* end if */
	}while( lr < 0 || lr > 1.0 );																									/* ѭ��ֱ��������ȷ��ѡ���˳�				*/
	pPtr->learnRate = lr;																											/* �趨ѧϰ��												*/

	do{																																		/* do...while ѭ����									*/
		printf("\nEnter the input dimentions of perceptron,"
			      " which are same to the input dimentions "
				  "of samples!(Enter -1 to exit)");																			/* �ı���ʾ��Ϣ											*/
		scanf("%d", &num1);																										/* ����������������ά��							*/

		if( num1 == -1 ){																												/* �ж��Ƿ�ѡ���˳���֪�������趨		*/
			return;																															/* ����������������								*/
		}/* end if */

		if( num1 < 0 ){																													/* �жϸ�֪������ά���Ƿ�С��0			*/
			printf("\nError:Please enter an interger which "
					  "is greater than 0.\n");																						/* �ı���ʾ��Ϣ											*/
		}/* end if */

		if( pPtr->perceptData.numOfInput != num1 ){																/* �жϸ�֪���趨�������趨�Ƿ���ͬ */
			printf("\nError: dimentions of input of perceptron"
					  " need same to samples!\n"
					  "The dimentions of samples input are %d.\n", 
					  pPtr->perceptData.numOfInput);																		/* �ı���ʾ��Ϣ											*/
		}/* end if */
	}while( num1 < 0 || pPtr->perceptData.numOfInput != num1 );										/* ѭ��ֱ����֪������ά����ȷ���˳�	*/
	pPtr->parameter.numOfInput = num1;																				/* ������������ά��									*/

	do{																																		/* do...while ѭ����									*/
		printf("\nEnter the output dimentions of perceptron,"
			      " which need same to the output dimentions "
				  "of samples!(Enter -1 to exit)");																			/* �ı���ʾ��Ϣ											*/
		scanf("%d", &num1);																										/* �����֪�����ά��								*/

		if( num1 == -1 ){																												/* �ж��Ƿ�ѡ���˳���֪�������趨		*/
			return;																															/* ����������������								*/
		}/* end if */

		if( num1 < 0 ){																													/* �жϸ�֪�����ά���Ƿ�С��0			*/
			printf("\nError:Please enter an interger which "
					  "is greater than 0.\n");																						/* �ı���ʾ��Ϣ											*/
		}/* end if */

		if( pPtr->perceptData.numOfOutput != num1 ){															/* �жϸ�֪��ά���������趨�Ƿ���ͬ	*/
			printf("\nError: dimentions of output of perceptron"
					  " need same to samples!\n"
					  "The dimentions of samples output are %d.\n", 
					  pPtr->perceptData.numOfOutput);																	/* �ı���ʾ��Ϣ											*/
		}/* end if */
	}while( num1 < 0 || pPtr->perceptData.numOfOutput != num1 );										/* ѭ��ֱ�����ά���趨��ȷ���˳�		*/
	pPtr->parameter.numOfOutput = num1;																			/* �趨��֪�����ά��								*/

	pPtr->perParmLabel = 1;																									/* ��֪�������趨��ɱ�־��1				*/
}/********************************************************************** end function setPer ************************************************************************/

void perceptronCreat( perceptPtr pPtr )																				/* ������֪�����	����							*/
{
	int i;																																		/* ��ʱ����													*/
	int numI = 0;																														/* ��֪������ά����ʱ����						*/
	int numO = 0;																														/* ��֪��	���ά����ʱ����					*/

	numI = pPtr->parameter.numOfInput;																				/* ��ȡ��֪������ά��								*/
	numO = pPtr->parameter.numOfOutput;																			/* ��ȡ��֪�����ά��								*/
	if( pPtr->perParmLabel == 1 ){																							/* �жϸ�֪�������Ƿ��趨						*/
		pPtr->inPtr = ( double * )malloc( sizeof( double ) * ( numI + 1 ) );								/* ��̬һά�������ڴ洢��֪������		*/

		if( pPtr->inPtr == NULL ){																								/* �жϴ洢����һά�����ڴ��Ƿ����	*/
			printf("\nMemery for input of perceptron did not enough!\n");								/* �ı���ʾ��Ϣ											*/
			exit( -1 );																														/* �˳�Ӧ�ó���											*/
		}/* end if */

		pPtr->ouPtr = ( double * )malloc( sizeof( double ) * numO );										/* ��̬һά�������ڴ洢��֪�����		*/
	
		if( pPtr->ouPtr == NULL ){																							/* �жϴ洢����һά�����ڴ��Ƿ����	*/
			printf( "\nMemery for output of perceptron did not enough!\n ");							/* �ı���ʾ��Ϣ											*/
			exit( -1 );																														/* �˳�Ӧ�ó���											*/
		}/* end if */

		pPtr->wPtrs = ( double ** )malloc( sizeof( double * ) * ( numI + 1 ) );							/* ��ָ̬���������ڴ洢Ȩֵһά����	*/

		if( pPtr->wPtrs != NULL ){																								/* �ж�ָ�������ڴ�����Ƿ�ɹ�			*/
			for( i = 0; i <= numI; i++ ){
				pPtr->wPtrs[ i ] = ( double * )malloc( sizeof( double ) * numO );							/* ��̬һά��������Ȩֵ�洢��ά����	*/

				if( pPtr->wPtrs[ i ] == NULL ){																				/* �ж�Ȩֵһά�����ڴ��Ƿ����ɹ�	*/
					printf("\nMemery for weight did not enough!\n");											/* �ı���ʾ��Ϣ											*/
					exit( -1 );																												/* �˳�Ӧ�ó���											*/
				}/* end if */
			}/* end for */
		}/* end if */
		else{																																	
			printf("\nMemery for weight did not enough!\n");													/* �ı���ʾ��Ϣ											*/
			exit( -1 );																														/*	�˳�Ӧ�ó���										*/
		}/* end else */
	}/* end if */
	else{
		printf("\nPerceptron creat fail!\n"
				  "Plese set the parameters of perceptron.\n");														/* �ı���ʾ��Ϣ											*/
		return;																																/* ��������													*/
	}/* end else */

	pPtr->perCreatLabel = 1;																									/* ��֪��������־��1								*/
}/****************************************************************** end function perceptronCreat ***************************************************************/

void perceptronInit( perceptPtr pPtr )																					/* ��֪��������ʼ������							*/
{
	int i;																																		/* ��ʱ����													*/
	int j;																																		/* ��ʱ����													*/
	int numI = pPtr->parameter.numOfInput;																			/* ��ȡ��֪������ά��								*/
	int numO = pPtr->parameter.numOfOutput;																		/* ��ȡ��֪�����ά��								*/
	
	if( pPtr->perCreatLabel == 1 ){																							/* �жϸ�֪���Ƿ񴴽�								*/
		for( i = 0; i < ( numI + 1 ); i++ ){
			if( i == 0 ){
				pPtr->inPtr[ i ] = 1.0;																								/* ������趨ά����1ά���̶�ֵ1			*/
			}/* end if */
			else{
				pPtr->inPtr[ i ] = 0.0;																								/* ��֪�������ʼ��Ϊ0							*/
			}/* end else */
		}/* end for */

		for( i = 0; i < numO; i++ ){
			pPtr->ouPtr[ i ] = 0.0;																									/* ��֪�������ʼ��Ϊ0							*/
		}/* end for */

		for( i = 0; i < numO; i++ ){
			for( j = 0; j < ( numI + 1 ); j++ ){
				if( j == 0 ){
					pPtr->wPtrs[ j ][ i ] = 1.0;																					/* ��֪��Ȩֵ���󣬵�0��Ϊƫ��			*/
				}/* end if */
				else{
					pPtr->wPtrs[ j ][ i ] = randOfDouble();																/* ��֪��Ȩֵ��ʼ��Ϊ-1~+1����ֵ		*/
				}/* end else */
			}/* end for */
		}/* end for */
	}/* end if */
	else{
		printf("\nPerceptron init fail!\n"
				   "Please creat the perceptron\n");																			/* �ı���ʾ��Ϣ											*/
		return;																																/* ����֪��δ��������������					*/
	}/* end else */
}/****************************************************************** end function perceptronInit *****************************************************************/

void perceptronTrain( perceptPtr pPtr )																				/* ��֪�����ɲ���ѵ������						*/
{
	int i;																																		/* ��ʱ����													*/
	int j;																																		/* ��ʱ����													*/
	int n;																																	/* ��ʱ����													*/
	int k;																																	/* ��ʱ����													*/
	int count = 0;																														/* ��ʱ������������������������		*/	
	double sum = 0;																													/* ��ʱ�������洢��֪������ֵ				*/
	double temp = 0;

	if( pPtr->perCreatLabel == 1 && pPtr->perceptData.creatLabel == 1 ){							/* �жϸ�֪�������ݴ洢����Ƿ񴴽�	*/
		for( n = 0; n < pPtr->epoch; n++ ){																					/* �����ѵ���غ���ѵ����֪��				*/

			randForSequence( &pPtr->perceptData );																	/* ��������ѵ������ʱ���ֵ��������	*/
			
			count = 0;																													/* �����������������								*/
			sum = 0;																														/* ��֪������ֵ����									*/
#if 0																																			/* �������룬����ʹ����Ϣ						*/
			printf("\nThe sequence of trainning sapamples:\n");

			for( i = 0; i < pPtr->perceptData.numOfSample; i++ ){
				printf("%d ", pPtr->perceptData.seqPtr[ i ]);
			}/* end for */

			printf("\n");
#endif																																		/* ��������													*/
			for( k = 0; k < pPtr->perceptData.numOfSample; k++ ){
				for( i = 1; i <= pPtr->perceptData.numOfInput; i++ ){
					pPtr->inPtr[ i ] = pPtr->perceptData.samPtrs[ i - 1 ]
													[ pPtr->perceptData.seqPtr[ k ] ];										/* �����ɵ��������ѡȡѵ������ʵ��	*/
				}/* end for */

#if 0																																			/* �������룬������ʾ��Ϣ						*/
				printf("\nThe input:\n");

				for( i = 0; i <= pPtr->parameter.numOfInput; i++ ){
					printf("%10.3lf\n", pPtr->inPtr[ i ]);
				}/* end for */
#endif																																		/* ��������													*/
				for( i = 0; i < pPtr->parameter.numOfOutput; i++ ){
					for( j = 0; j <= pPtr->parameter.numOfInput; j++ ){
						temp = pPtr->inPtr[ j ] * pPtr->wPtrs[ j ][ i ];												/* ������Ȩֵ��ƫ������							*/

						if( !__isNormal( temp ) ){																				/* �ж��������Ƿ�Ϊһ��������			*/
							temp = 0.0;
						}/* end if */

						sum += temp;																									/* �����յ��ֲ���										*/
					}/* end for */

					pPtr->ouPtr[ i ] = signFunction( sum );																/* �����֪�����ֵ									*/

					sum = 0.0;																											/* �յ��ֲ������㣬������һ������		*/

					temp = pPtr->ouPtr[ i ] * pPtr->perceptData.aimPtrs[ i ]
															[ pPtr->perceptData.seqPtr[ k ] ];								/* �жϸ�֪���Ƿ�ѵ�����������		*/

					if( !__isNormal( temp ) ){																					/* �жϼ������Ƿ���һ��������			*/
						temp = 0.0;
					}/* end if */																													

					if( temp <= 0 ){																									/* ��������������˵����֪�������		*/
						for( j = 0; j <= pPtr->parameter.numOfInput; j++ ){
							temp = pPtr->learnRate * pPtr->perceptData.aimPtrs[ i ]
											[ pPtr->perceptData.seqPtr[ k ] ] * pPtr->inPtr[ j ];					/* �������ɲ����仯��								*/

							if( !__isNormal( temp )){																			/* �жϼ������Ƿ�Ϊһ������				*/
								temp = 0.0;						
							}/* end if */

							pPtr->wPtrs[ j ][ i ] += temp;																		/* �������ɲ���											*/
						}/* end for */

						count++;																											/* ͳ��ѵ�������е��������					*/
					}/* end if */
				}/* end for */
			}/* end for */

			printf("epoch: %d\n", n);																								/* �ı���ʾ��Ϣ											*/

			if( count == 0 ){																											/* �ж�ѵ�������Ƿ�ȫ��������ȷ			*/
				printf("\nAll trainning samples has been classified correct!\n");							/* �ı���ʾ��Ϣ											*/
				break;																														/* ����ѵ���غ�forѭ��							*/
			}/* end if */
		}/* end for */
	}/* end if */
	else{
		printf("\nNo perceptron or samples!\n");																		/* �ı���ʾ��Ϣ											*/
		return;																																/* ��������													*/
	}/* end else */
}/***************************************************************  end function perceptronTrain *****************************************************************/

void perceptronTest( perceptPtr pPtr )																					/* ��֪�����ܲ��Ժ���								*/
{
	int i;																																		/* ��ʱ����													*/
	int j;																																		/* ��ʱ����													*/
	int k;																																	/* ��ʱ����													*/
	int count = 0;																														/* �������������ͳ��								*/
	double temp = 0.0;																												/* ��ʱ����													*/
	double sum = 0.0;																												/* ��֪���յ��ֲ���									*/
	double rate = 0.0;																												/* �����������������								*/

	if( pPtr->perCreatLabel == 1 && pPtr->perceptData.creatLabel == 1 ){							/* �жϸ�֪�������ݴ洢�ṹ�Ƿ񴴽�	*/

		for( k = 0; k < pPtr->perceptData.numOfTSample; k++ ){
			for( i = 1; i <= pPtr->parameter.numOfInput; i++ ){
				pPtr->inPtr[ i ] = pPtr->perceptData.tSamPtrs[ i - 1 ][ k ];									/* ��ȡ��������ĳ��ʵ������					*/
			}/* end for */

			for( i = 0; i < pPtr->parameter.numOfOutput; i++ ){
				for( j = 0; j <= pPtr->parameter.numOfInput; j++ ){
					temp = pPtr->wPtrs[ j ][ i ] * pPtr->inPtr[ j ];													/* ���������ɲ�������								*/

					if( !__isNormal( temp ) ){																					/* �ж��������Ƿ�Ϊһ��������			*/
						temp = 0.0;
					}/* end if */

					sum += temp;																										/* �����յ��ֲ���										*/	
				}/* end for */

				pPtr->ouPtr[ i ] = signFunction( sum );																	/* �����֪�����										*/

				sum = 0.0;																												/* �յ��ֲ������㣬������һ�μ���		*/

				if( pPtr->ouPtr[ i ] != pPtr->perceptData.tAimPtrs[ i ][ k ] ){								/* �жϸ�֪��������������Ŀ�����	*/
					count++;																												/* ��������������Ӵ��������				*/
				}/* end if */
			}/* end for */
		}/* end for */

		rate = ( double )count / pPtr->perceptData.numOfTSample * 100.0;							/* �����֪���Բ��������ķ��������	*/

		printf("\nThe error rate of test samples is: %.3lf%%\n", rate);										/* �ı���ʾ��Ϣ											*/

		rate = 100.0 - rate;																											/* ���������ȷ��										*/

		printf("\nThe correct rate of test samples is: %.3lf%%\n", rate);										/* �ı���ʾ��Ϣ											*/
	}/* end if */
	else{
		printf("\nNo perceptron exist!\n");																					/* �ı���ʾ��Ϣ											*/
		return;																																/* ��������													*/
	}/* end else */
}/*************************************************************** end function perceptronTest *******************************************************************/

void usePerceptron( perceptPtr pPtr )																					/* ʹ��ѵ���õĸ�֪����������з���	*/
{
	int i;																																		/* ��ʱ����													*/
	int j;																																		/* ��ʱ����													*/
	double sum = 0.0;																												/* �����յ��ֲ���										*/
	double temp = 0.0;																												/* ��ʱ����													*/

	if( pPtr->perCreatLabel == 1 && pPtr->perceptData.creatLabel == 1 ){							/* �жϸ�֪�������ݴ洢�ṹ�Ƿ񴴽�	*/
		printf("\nEnter a data:\n");																								/* �ı���ʾ��Ϣ											*/
		for( i = 1; i <= pPtr->parameter.numOfInput; i++ ){
			scanf("%lf", &pPtr->inPtr[ i ]);																					/* ��������ʵ��������								*/
		}/* end for */
	
		printf("\nOutput of perceptron:\n");																				/* �ı���ʾ��Ϣ											*/

		for( i = 0; i < pPtr->parameter.numOfOutput; i++ ){
			for( j = 0; j <= pPtr->parameter.numOfInput; j++ ){
				temp = pPtr->wPtrs[ j ][ i ] * pPtr->inPtr[ j ];														/* ����������Ȩֵ������ƫ��������		*/

				if( !__isNormal( temp ) ){																						/* �ж��������Ƿ���һ����������		*/
					temp = 0.0;
				}/* end if */																					

				sum += temp;																											/* �����յ��ֲ���										*/
			}/* end for */

			pPtr->ouPtr[ i ]  = signFunction( sum );																		/* �������													*/

			sum = 0.0;																													/* ��ʱ�������㣬�����´�����				*/

			printf("%.3lf\n", pPtr->ouPtr[ i ]);																				/* ��ʾ���													*/
		}/* end for */
	}/* end if */
	else{
		printf("\nNo perceptron exist!\n");																					/* �ı���ʾ��Ϣ											*/
		return;																																/* ��������													*/
	}/* end else */
}/****************************************************************** end function usePerceptron ******************************************************************/

void printWeights( perceptPtr pPtr )																						/* ��ʾ��֪������Ȩֵ								*/
{
	int i;																																		/* ��ʱ����													*/
	int j;																																		/* ��ʱ����													*/
	int n;																																	/* ��ʱ����													*/
	int numI = pPtr->parameter.numOfInput;																			/* ��ȡ��֪������ά��								*/
	int numO = pPtr->parameter.numOfOutput;																		/* ��ȡ��֪�����ά��								*/
	int temp1 = 0;																														/* ����ʾ��ҳ��											*/
	int temp2 = 0;																														/* ����һҳ��ʣ����									*/
	int temp3 = 0;																														/* ��ʼ��ʾ��λ��										*/
	int temp4 = 0;																														/* ��ֹ��ʾ��λ��										*/

	temp1 = numO / 10;																											/* ����ÿҳ��10��Ȩֵ��������ʾ��ҳ	*/
	temp2 = numO % 10;																											/* ʣ����ٸ�Ȩֵ����								*/

	if( pPtr->perCreatLabel == 1 ){																							/* �жϸ�֪���Ƿ񴴽�								*/
		if( temp1 != 0 ){																												/* �ж��Ƿ���10Ϊ��������ʾҳ��			*/
			for( n = 0; n < temp1; n++ ){
				temp3 = temp4;																										/* ����һ�ν�����λ�û�ҳ��ʾ				*/
				temp4 += 10;																											/* ������ֹ��ʾ��λ��								*/

				printf("\nThe weights of perceptron between"
						  " %d and %d are:\n", temp3 + 1, temp4);														/* �ı���ʾ��Ϣ											*/

				for( i = 1; i <= numI; i++ ){
					for( j = temp3; j < temp4; j++ ){
						printf("%8.3lf ", pPtr->wPtrs[ i ][ j ]);															/* ��ʾȨֵ													*/
					}/* end for */
					printf("\n");																											/* ����															*/
				}/* end for */
			}/* end for */
		}/* end if */

		if( temp2 != 0 ){																												/* �ж�ʣ��ĸ����Ƿ�Ϊ0						*/
			temp3 = temp4;																											/* ���ϴ���ʾ��λ�û�ҳ��ʾ					*/
			temp4 += temp2;																											/* ������ֹ��ʾ��λ��								*/
			
			printf("\nThe weights of perceptron between"
						  " %d and %d are:\n", temp3 + 1, temp4);														/* �ı���ʾ��Ϣ											*/

			for( i = 1; i <= numI; i++ ){
				for( j = temp3; j < temp4; j++ ){
					printf("%8.3lf ", pPtr->wPtrs[ i ][ j ]);																/* ��ʾȨֵ����											*/
				}/* end for */
				printf("\n");																												/* ������ʾ													*/
			}/* end for */
		}/* end if */
	}/* end if */
	else{
		printf("\nNo perceptron exist!\n");																					/* �ı���ʾ��Ϣ											*/
	}/* end else */
}/****************************************************************** end function printWeight ********************************************************************/

void printBiases( perceptPtr pPtr )																						/* ��ʾ��֪��ƫ�ú���								*/
{
	int i;																																		/* ��ʱ����													*/
	int n;																																	/* ��ʱ����													*/
	int temp1 = 0;																														/* ����ʾ��ҳ��											*/
	int temp2 = 0;																														/* ����һҳ��ʣ����									*/
	int temp3 = 0;																														/* ��ʼ��ʾ��λ��										*/
	int temp4 = 0;																														/* ��ֹ��ʾ��λ��										*/

	temp1 = pPtr->parameter.numOfOutput / 10;																	/* ������ʾҳ��											*/
	temp2 = pPtr->parameter.numOfOutput % 10;																	/* ����ʣ����												*/

	if( pPtr->perCreatLabel == 1){																							/* �жϸ�֪���Ƿ񴴽�								*/
		if( temp1 != 0 ){																												/* �ж�����ʾ��ҳ���Ƿ�Ϊ0					*/
			for( n = 0; n < temp1; n++ ){
				temp3  = temp4;																										/* ��ʼ��ʾ��λ��										*/
				temp4 += 10;																											/* ��ֹ��ʾ��λ��										*/

				printf("\nThe biases of perceptron between"
					   " %d and %d are:\n", temp3 + 1, temp4);														/* �ı���ʾ��Ϣ											*/

				for( i = temp3; i < temp4; i++ ){
					printf("%.3lf\n", pPtr->wPtrs[ 0 ][ i ]);																/* ��ʾƫ��													*/
				}/* end for */
			}/* end for */
		}/* end if */

		if( temp2 != 0 ){																												/* �ж�ʣ�����Ƿ�Ϊ0								*/

			temp3 = temp4;																											/* ��ʼ��ʾ��λ��										*/
			temp4 += temp2;																											/* ��ֹ��ʾ��λ��										*/

			printf("\nThe biases of perceptron between"
					   " %d and %d are:\n", temp3 + 1, temp4);														/* �ı���ʾ��Ϣ											*/

			for( i = temp3; i < temp4; i++ ){
				printf("%.3lf\n", pPtr->wPtrs[ 0 ][ i ]);																	/* ��ʾƫ��													*/
			}/* end for */
		}/* end if */
	}/* end if */
	else{
		printf("\nNo perceptron exist!\n");																					/* �ı���ʾ��Ϣ											*/
	}/* end else */
}/* end function printBiases */

void printPerceptronParam( perceptPtr pPtr )
{
	printf("\nInput dimentions of perceptron: %d\n"
			  "\nOutput dimentions of perceptron: %d\n"
			  "\nLearn rate of perceptron: %.3lf\n"
			  "\nMax train epochs of perceptron: %d\n", 
			  pPtr->parameter.numOfInput, 
			  pPtr->parameter.numOfOutput,
			  pPtr->learnRate, pPtr->epoch);
}/* end function printPerceptronParam */

void printInstructions( int *cho )
{
	printf("\nWhat you want to do?\n");

	printf("================================\n"
			  "* 1.  Set parameters of samples.\n"
			  "* 2.  Print parameters of samples.\n"
			  "* 3.  Set parameters of perceptron.\n"
			  "* 4.  Print parameters of perceptron.\n"
			  "* 5.  Creat samples.\n"
			  "* 6.  Creat perceptron.\n"
			  "* 7.  Init datas.\n"
			  "* 8.  Init perceptron.\n"
			  "* 9.  Enter trainning samples.\n"
			  "* 10. Enter test samples.\n"
			  "* 11. Print trainning samples.\n"
			  "* 12. Print test samples.\n"
			  "* 13. Print weights of  perceptron.\n"
			  "* 14. Print biases of perceptron.\n"
			  "* 15. Train perceptron.\n"
			  "* 16. Test perceptron.\n"
			  "* 17. Use perceptron.\n"
			  "* 0.  Exit.\n"
			  "================================\n"
			  "Enter your chosen:");
	scanf("%d", cho );
}/* end function printInstruction */