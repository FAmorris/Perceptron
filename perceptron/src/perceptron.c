/**
   ******************************************************************************************************************************************************
   * @file		peceptron.c
   * @author	Morris
   * @version	V1.0
   * @date		2018年4月17日22:05:52 在VS2017上Debug模式最终运行
   * @brief		统计学习、神经网络中的感知机（感知器）
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
 * @brief		判断一个数是否是Inf或者NaN
 * @param		double sum 要判断的数
 * @retval
 */

static int __isNormal( double sum )
{
	if( sum == sum && sum != ( sum + 1.0 ) ){/* 判断一个数是否是正常数字	 */
		return 1; /* 条件成立返回1 */
	}/* end if */
	else{
		return 0; /* 否则返回0 */
	}/* end else */
}/* end function __isNormal */

double randOfDouble( void )/* 生成随机数函数 */
{
	return ( -1 + rand() % 2 + ( double )rand() / RAND_MAX ); /* 随机生成一个-1~1之间的小数 */
}/*end function randOfDouble */

int signFunction( double sum )																								/* 符号函数													*/
{
	if( sum >= 0 ){																														/* 判断函数输入是否大于或等于0			*/
		return 1;																															/* 判断条件成立返回 +1							*/
	}/* end if */															
	else{																
		return -1;																															/* 否则返回-1												*/
	}/* end else */
}/**************************************************************** end function signFunction *********************************************************************/

void setPerceptronParam( perceptPtr pPtr )																			/* 感知机参数设定函数								*/
{
	int num1;																																/* 临时变量													*/
	double lr;																																/* 学习率临时变量										*/

	do{																																		/* do...while循环体										*/
		printf("\nEnter the max train epochs of perceptron"
					"(Enter -1 to exit): ");																							/* 文本显示信息											*/
		scanf("%d", &num1);																										/* 输入训练最大回合数								*/
		if( num1 == -1 ){																												/* 判断是否选择退出感知机参数设定		*/
			return;																															/* 条件成立则函数返回								*/
		}/* end if */

		if( num1 < 0 ){																													/* 判断最大训练回合数是否小于0			*/
			printf("\nError: Please enter an interger which is"
						" greater than 0.\n ");																						/* 文本显示信息											*/
		}/* end if */
	}while( num1 < 0 );																												/* 循环直至输入正确或选择退出				*/
	pPtr->epoch = num1;																											/* 设定最大训练回合数								*/

	do{																																		/* do...while循环体										*/
		printf("\nEnter the learn rate of perceptron"
					"train(Enter -1 to exit): ");																					/* 文本显示信息											*/	
		scanf("%lf", &lr);																											/* 输入学习率												*/
		if( -0.9999 > lr && lr > -1.0001 ){																					/* 判断是否选择退出感知机参数设定		*/
			return;																															/* 条件成立则函数返回								*/
		}/* end if */

		if( lr < 0 || lr > 1.0 ){																										/* 判断学习率输入是否符合						*/											
			printf("\nError: Please enter an number which is"
						" greater than 0 but lower than 1.\n ");															/* 文本显示信息											*/
		}/* end if */
	}while( lr < 0 || lr > 1.0 );																									/* 循环直至输入正确或选择退出				*/
	pPtr->learnRate = lr;																											/* 设定学习率												*/

	do{																																		/* do...while 循环体									*/
		printf("\nEnter the input dimentions of perceptron,"
			      " which are same to the input dimentions "
				  "of samples!(Enter -1 to exit)");																			/* 文本显示信息											*/
		scanf("%d", &num1);																										/* 输入样本输入向量维数							*/

		if( num1 == -1 ){																												/* 判断是否选择退出感知机参数设定		*/
			return;																															/* 条件成立则函数返回								*/
		}/* end if */

		if( num1 < 0 ){																													/* 判断感知机输入维数是否小于0			*/
			printf("\nError:Please enter an interger which "
					  "is greater than 0.\n");																						/* 文本显示信息											*/
		}/* end if */

		if( pPtr->perceptData.numOfInput != num1 ){																/* 判断感知机设定与数据设定是否相同 */
			printf("\nError: dimentions of input of perceptron"
					  " need same to samples!\n"
					  "The dimentions of samples input are %d.\n", 
					  pPtr->perceptData.numOfInput);																		/* 文本显示信息											*/
		}/* end if */
	}while( num1 < 0 || pPtr->perceptData.numOfInput != num1 );										/* 循环直至感知机输入维数正确或退出	*/
	pPtr->parameter.numOfInput = num1;																				/* 设置样本输入维数									*/

	do{																																		/* do...while 循环体									*/
		printf("\nEnter the output dimentions of perceptron,"
			      " which need same to the output dimentions "
				  "of samples!(Enter -1 to exit)");																			/* 文本显示信息											*/
		scanf("%d", &num1);																										/* 输入感知机输出维数								*/

		if( num1 == -1 ){																												/* 判断是否选择退出感知机参数设定		*/
			return;																															/* 条件成立则函数返回								*/
		}/* end if */

		if( num1 < 0 ){																													/* 判断感知机输出维数是否小于0			*/
			printf("\nError:Please enter an interger which "
					  "is greater than 0.\n");																						/* 文本显示信息											*/
		}/* end if */

		if( pPtr->perceptData.numOfOutput != num1 ){															/* 判断感知机维数与数据设定是否相同	*/
			printf("\nError: dimentions of output of perceptron"
					  " need same to samples!\n"
					  "The dimentions of samples output are %d.\n", 
					  pPtr->perceptData.numOfOutput);																	/* 文本显示信息											*/
		}/* end if */
	}while( num1 < 0 || pPtr->perceptData.numOfOutput != num1 );										/* 循环直至输出维数设定正确或退出		*/
	pPtr->parameter.numOfOutput = num1;																			/* 设定感知机输出维数								*/

	pPtr->perParmLabel = 1;																									/* 感知机参数设定完成标志置1				*/
}/********************************************************************** end function setPer ************************************************************************/

void perceptronCreat( perceptPtr pPtr )																				/* 创建感知机框架	函数							*/
{
	int i;																																		/* 临时变量													*/
	int numI = 0;																														/* 感知机输入维数临时变量						*/
	int numO = 0;																														/* 感知机	输出维数临时变量					*/

	numI = pPtr->parameter.numOfInput;																				/* 读取感知机输入维数								*/
	numO = pPtr->parameter.numOfOutput;																			/* 读取感知机输出维数								*/
	if( pPtr->perParmLabel == 1 ){																							/* 判断感知机参数是否设定						*/
		pPtr->inPtr = ( double * )malloc( sizeof( double ) * ( numI + 1 ) );								/* 动态一维数组用于存储感知机输入		*/

		if( pPtr->inPtr == NULL ){																								/* 判断存储输入一维数组内存是否分配	*/
			printf("\nMemery for input of perceptron did not enough!\n");								/* 文本显示信息											*/
			exit( -1 );																														/* 退出应用程序											*/
		}/* end if */

		pPtr->ouPtr = ( double * )malloc( sizeof( double ) * numO );										/* 动态一维数组用于存储感知机输出		*/
	
		if( pPtr->ouPtr == NULL ){																							/* 判断存储输入一维数组内存是否分配	*/
			printf( "\nMemery for output of perceptron did not enough!\n ");							/* 文本显示信息											*/
			exit( -1 );																														/* 退出应用程序											*/
		}/* end if */

		pPtr->wPtrs = ( double ** )malloc( sizeof( double * ) * ( numI + 1 ) );							/* 动态指针数组用于存储权值一维数组	*/

		if( pPtr->wPtrs != NULL ){																								/* 判断指针数组内存分配是否成功			*/
			for( i = 0; i <= numI; i++ ){
				pPtr->wPtrs[ i ] = ( double * )malloc( sizeof( double ) * numO );							/* 动态一维数组生成权值存储二维数组	*/

				if( pPtr->wPtrs[ i ] == NULL ){																				/* 判断权值一维数组内存是否分配成功	*/
					printf("\nMemery for weight did not enough!\n");											/* 文本显示信息											*/
					exit( -1 );																												/* 退出应用程序											*/
				}/* end if */
			}/* end for */
		}/* end if */
		else{																																	
			printf("\nMemery for weight did not enough!\n");													/* 文本显示信息											*/
			exit( -1 );																														/*	退出应用程序										*/
		}/* end else */
	}/* end if */
	else{
		printf("\nPerceptron creat fail!\n"
				  "Plese set the parameters of perceptron.\n");														/* 文本显示信息											*/
		return;																																/* 函数返回													*/
	}/* end else */

	pPtr->perCreatLabel = 1;																									/* 感知机创建标志置1								*/
}/****************************************************************** end function perceptronCreat ***************************************************************/

void perceptronInit( perceptPtr pPtr )																					/* 感知机参数初始化函数							*/
{
	int i;																																		/* 临时变量													*/
	int j;																																		/* 临时变量													*/
	int numI = pPtr->parameter.numOfInput;																			/* 读取感知机输入维数								*/
	int numO = pPtr->parameter.numOfOutput;																		/* 读取感知机输出维数								*/
	
	if( pPtr->perCreatLabel == 1 ){																							/* 判断感知机是否创建								*/
		for( i = 0; i < ( numI + 1 ); i++ ){
			if( i == 0 ){
				pPtr->inPtr[ i ] = 1.0;																								/* 输入比设定维数高1维，固定值1			*/
			}/* end if */
			else{
				pPtr->inPtr[ i ] = 0.0;																								/* 感知机输入初始化为0							*/
			}/* end else */
		}/* end for */

		for( i = 0; i < numO; i++ ){
			pPtr->ouPtr[ i ] = 0.0;																									/* 感知机输出初始化为0							*/
		}/* end for */

		for( i = 0; i < numO; i++ ){
			for( j = 0; j < ( numI + 1 ); j++ ){
				if( j == 0 ){
					pPtr->wPtrs[ j ][ i ] = 1.0;																					/* 感知机权值矩阵，第0行为偏置			*/
				}/* end if */
				else{
					pPtr->wPtrs[ j ][ i ] = randOfDouble();																/* 感知机权值初始化为-1~+1的数值		*/
				}/* end else */
			}/* end for */
		}/* end for */
	}/* end if */
	else{
		printf("\nPerceptron init fail!\n"
				   "Please creat the perceptron\n");																			/* 文本显示信息											*/
		return;																																/* 若感知机未建立，跳出函数					*/
	}/* end else */
}/****************************************************************** end function perceptronInit *****************************************************************/

void perceptronTrain( perceptPtr pPtr )																				/* 感知机自由参数训练函数						*/
{
	int i;																																		/* 临时变量													*/
	int j;																																		/* 临时变量													*/
	int n;																																	/* 临时变量													*/
	int k;																																	/* 临时变量													*/
	int count = 0;																														/* 临时变量，计算分类错误样本个数		*/	
	double sum = 0;																													/* 临时变量，存储感知机计算值				*/
	double temp = 0;

	if( pPtr->perCreatLabel == 1 && pPtr->perceptData.creatLabel == 1 ){							/* 判断感知机、数据存储框架是否创建	*/
		for( n = 0; n < pPtr->epoch; n++ ){																					/* 在最大训练回合中训练感知机				*/

			randForSequence( &pPtr->perceptData );																	/* 生成用于训练样本时呈现的随机序列	*/
			
			count = 0;																													/* 分类错误样本数清零								*/
			sum = 0;																														/* 感知机计算值清零									*/
#if 0																																			/* 条件编译，调试使用信息						*/
			printf("\nThe sequence of trainning sapamples:\n");

			for( i = 0; i < pPtr->perceptData.numOfSample; i++ ){
				printf("%d ", pPtr->perceptData.seqPtr[ i ]);
			}/* end for */

			printf("\n");
#endif																																		/* 条件编译													*/
			for( k = 0; k < pPtr->perceptData.numOfSample; k++ ){
				for( i = 1; i <= pPtr->perceptData.numOfInput; i++ ){
					pPtr->inPtr[ i ] = pPtr->perceptData.samPtrs[ i - 1 ]
													[ pPtr->perceptData.seqPtr[ k ] ];										/* 按生成的随机序列选取训练样本实例	*/
				}/* end for */

#if 0																																			/* 条件编译，调试显示信息						*/
				printf("\nThe input:\n");

				for( i = 0; i <= pPtr->parameter.numOfInput; i++ ){
					printf("%10.3lf\n", pPtr->inPtr[ i ]);
				}/* end for */
#endif																																		/* 条件编译													*/
				for( i = 0; i < pPtr->parameter.numOfOutput; i++ ){
					for( j = 0; j <= pPtr->parameter.numOfInput; j++ ){
						temp = pPtr->inPtr[ j ] * pPtr->wPtrs[ j ][ i ];												/* 输入与权值、偏置运算							*/

						if( !__isNormal( temp ) ){																				/* 判断运算结果是否为一个正常数			*/
							temp = 0.0;
						}/* end if */

						sum += temp;																									/* 计算诱导局部域										*/
					}/* end for */

					pPtr->ouPtr[ i ] = signFunction( sum );																/* 计算感知机输出值									*/

					sum = 0.0;																											/* 诱导局部域清零，进行下一个计算		*/

					temp = pPtr->ouPtr[ i ] * pPtr->perceptData.aimPtrs[ i ]
															[ pPtr->perceptData.seqPtr[ k ] ];								/* 判断感知机是否将训练样本误分类		*/

					if( !__isNormal( temp ) ){																					/* 判断计算结果是否是一个正常数			*/
						temp = 0.0;
					}/* end if */																													

					if( temp <= 0 ){																									/* 若条件成立，则说明感知机误分类		*/
						for( j = 0; j <= pPtr->parameter.numOfInput; j++ ){
							temp = pPtr->learnRate * pPtr->perceptData.aimPtrs[ i ]
											[ pPtr->perceptData.seqPtr[ k ] ] * pPtr->inPtr[ j ];					/* 计算自由参数变化量								*/

							if( !__isNormal( temp )){																			/* 判断计算结果是否为一个常数				*/
								temp = 0.0;						
							}/* end if */

							pPtr->wPtrs[ j ][ i ] += temp;																		/* 更新自由参数											*/
						}/* end for */

						count++;																											/* 统计训练样本中的误分类数					*/
					}/* end if */
				}/* end for */
			}/* end for */

			printf("epoch: %d\n", n);																								/* 文本显示信息											*/

			if( count == 0 ){																											/* 判断训练样本是否全部分类正确			*/
				printf("\nAll trainning samples has been classified correct!\n");							/* 文本显示信息											*/
				break;																														/* 跳出训练回合for循环							*/
			}/* end if */
		}/* end for */
	}/* end if */
	else{
		printf("\nNo perceptron or samples!\n");																		/* 文本显示信息											*/
		return;																																/* 函数返回													*/
	}/* end else */
}/***************************************************************  end function perceptronTrain *****************************************************************/

void perceptronTest( perceptPtr pPtr )																					/* 感知机性能测试函数								*/
{
	int i;																																		/* 临时变量													*/
	int j;																																		/* 临时变量													*/
	int k;																																	/* 临时变量													*/
	int count = 0;																														/* 测试样本误分类统计								*/
	double temp = 0.0;																												/* 临时变量													*/
	double sum = 0.0;																												/* 感知机诱导局部域									*/
	double rate = 0.0;																												/* 测试样本分类错误率								*/

	if( pPtr->perCreatLabel == 1 && pPtr->perceptData.creatLabel == 1 ){							/* 判断感知机、数据存储结构是否创建	*/

		for( k = 0; k < pPtr->perceptData.numOfTSample; k++ ){
			for( i = 1; i <= pPtr->parameter.numOfInput; i++ ){
				pPtr->inPtr[ i ] = pPtr->perceptData.tSamPtrs[ i - 1 ][ k ];									/* 读取测试样本某个实例输入					*/
			}/* end for */

			for( i = 0; i < pPtr->parameter.numOfOutput; i++ ){
				for( j = 0; j <= pPtr->parameter.numOfInput; j++ ){
					temp = pPtr->wPtrs[ j ][ i ] * pPtr->inPtr[ j ];													/* 输入与自由参数运算								*/

					if( !__isNormal( temp ) ){																					/* 判断运算结果是否为一个正常数			*/
						temp = 0.0;
					}/* end if */

					sum += temp;																										/* 计算诱导局部域										*/	
				}/* end for */

				pPtr->ouPtr[ i ] = signFunction( sum );																	/* 计算感知机输出										*/

				sum = 0.0;																												/* 诱导局部域清零，进行下一次计算		*/

				if( pPtr->ouPtr[ i ] != pPtr->perceptData.tAimPtrs[ i ][ k ] ){								/* 判断感知机输出与测试样本目标输出	*/
					count++;																												/* 若分类错误则增加错误分类数				*/
				}/* end if */
			}/* end for */
		}/* end for */

		rate = ( double )count / pPtr->perceptData.numOfTSample * 100.0;							/* 计算感知机对测试样本的分类错误率	*/

		printf("\nThe error rate of test samples is: %.3lf%%\n", rate);										/* 文本显示信息											*/

		rate = 100.0 - rate;																											/* 计算分类正确率										*/

		printf("\nThe correct rate of test samples is: %.3lf%%\n", rate);										/* 文本显示信息											*/
	}/* end if */
	else{
		printf("\nNo perceptron exist!\n");																					/* 文本显示信息											*/
		return;																																/* 函数返回													*/
	}/* end else */
}/*************************************************************** end function perceptronTest *******************************************************************/

void usePerceptron( perceptPtr pPtr )																					/* 使用训练好的感知机对输入进行分类	*/
{
	int i;																																		/* 临时变量													*/
	int j;																																		/* 临时变量													*/
	double sum = 0.0;																												/* 计算诱导局部域										*/
	double temp = 0.0;																												/* 临时变量													*/

	if( pPtr->perCreatLabel == 1 && pPtr->perceptData.creatLabel == 1 ){							/* 判断感知机、数据存储结构是否创建	*/
		printf("\nEnter a data:\n");																								/* 文本显示信息											*/
		for( i = 1; i <= pPtr->parameter.numOfInput; i++ ){
			scanf("%lf", &pPtr->inPtr[ i ]);																					/* 输入样本实力的输入								*/
		}/* end for */
	
		printf("\nOutput of perceptron:\n");																				/* 文本显示信息											*/

		for( i = 0; i < pPtr->parameter.numOfOutput; i++ ){
			for( j = 0; j <= pPtr->parameter.numOfInput; j++ ){
				temp = pPtr->wPtrs[ j ][ i ] * pPtr->inPtr[ j ];														/* 输入向量与权值向量、偏置做运算		*/

				if( !__isNormal( temp ) ){																						/* 判断运算结果是否是一个正常数字		*/
					temp = 0.0;
				}/* end if */																					

				sum += temp;																											/* 计算诱导局部域										*/
			}/* end for */

			pPtr->ouPtr[ i ]  = signFunction( sum );																		/* 计算输出													*/

			sum = 0.0;																													/* 临时变量清零，用于下次运算				*/

			printf("%.3lf\n", pPtr->ouPtr[ i ]);																				/* 显示输出													*/
		}/* end for */
	}/* end if */
	else{
		printf("\nNo perceptron exist!\n");																					/* 文本显示信息											*/
		return;																																/* 函数返回													*/
	}/* end else */
}/****************************************************************** end function usePerceptron ******************************************************************/

void printWeights( perceptPtr pPtr )																						/* 显示感知机所有权值								*/
{
	int i;																																		/* 临时变量													*/
	int j;																																		/* 临时变量													*/
	int n;																																	/* 临时变量													*/
	int numI = pPtr->parameter.numOfInput;																			/* 读取感知机输入维数								*/
	int numO = pPtr->parameter.numOfOutput;																		/* 读取感知机输出维数								*/
	int temp1 = 0;																														/* 需显示的页数											*/
	int temp2 = 0;																														/* 不够一页的剩余量									*/
	int temp3 = 0;																														/* 开始显示的位置										*/
	int temp4 = 0;																														/* 终止显示的位置										*/

	temp1 = numO / 10;																											/* 计算每页以10个权值向量需显示几页	*/
	temp2 = numO % 10;																											/* 剩余多少个权值向量								*/

	if( pPtr->perCreatLabel == 1 ){																							/* 判断感知机是否创建								*/
		if( temp1 != 0 ){																												/* 判断是否有10为基数的显示页数			*/
			for( n = 0; n < temp1; n++ ){
				temp3 = temp4;																										/* 从上一次结束的位置换页显示				*/
				temp4 += 10;																											/* 计算终止显示的位置								*/

				printf("\nThe weights of perceptron between"
						  " %d and %d are:\n", temp3 + 1, temp4);														/* 文本显示信息											*/

				for( i = 1; i <= numI; i++ ){
					for( j = temp3; j < temp4; j++ ){
						printf("%8.3lf ", pPtr->wPtrs[ i ][ j ]);															/* 显示权值													*/
					}/* end for */
					printf("\n");																											/* 换行															*/
				}/* end for */
			}/* end for */
		}/* end if */

		if( temp2 != 0 ){																												/* 判断剩余的个数是否为0						*/
			temp3 = temp4;																											/* 从上次显示的位置换页显示					*/
			temp4 += temp2;																											/* 计算终止显示的位置								*/
			
			printf("\nThe weights of perceptron between"
						  " %d and %d are:\n", temp3 + 1, temp4);														/* 文本显示信息											*/

			for( i = 1; i <= numI; i++ ){
				for( j = temp3; j < temp4; j++ ){
					printf("%8.3lf ", pPtr->wPtrs[ i ][ j ]);																/* 显示权值向量											*/
				}/* end for */
				printf("\n");																												/* 换行显示													*/
			}/* end for */
		}/* end if */
	}/* end if */
	else{
		printf("\nNo perceptron exist!\n");																					/* 文本显示信息											*/
	}/* end else */
}/****************************************************************** end function printWeight ********************************************************************/

void printBiases( perceptPtr pPtr )																						/* 显示感知机偏置函数								*/
{
	int i;																																		/* 临时变量													*/
	int n;																																	/* 临时变量													*/
	int temp1 = 0;																														/* 需显示的页数											*/
	int temp2 = 0;																														/* 不够一页的剩余量									*/
	int temp3 = 0;																														/* 开始显示的位置										*/
	int temp4 = 0;																														/* 终止显示的位置										*/

	temp1 = pPtr->parameter.numOfOutput / 10;																	/* 计算显示页数											*/
	temp2 = pPtr->parameter.numOfOutput % 10;																	/* 计算剩余量												*/

	if( pPtr->perCreatLabel == 1){																							/* 判断感知机是否创建								*/
		if( temp1 != 0 ){																												/* 判断需显示的页数是否为0					*/
			for( n = 0; n < temp1; n++ ){
				temp3  = temp4;																										/* 开始显示的位置										*/
				temp4 += 10;																											/* 终止显示的位置										*/

				printf("\nThe biases of perceptron between"
					   " %d and %d are:\n", temp3 + 1, temp4);														/* 文本显示信息											*/

				for( i = temp3; i < temp4; i++ ){
					printf("%.3lf\n", pPtr->wPtrs[ 0 ][ i ]);																/* 显示偏置													*/
				}/* end for */
			}/* end for */
		}/* end if */

		if( temp2 != 0 ){																												/* 判断剩余量是否为0								*/

			temp3 = temp4;																											/* 开始显示的位置										*/
			temp4 += temp2;																											/* 终止显示的位置										*/

			printf("\nThe biases of perceptron between"
					   " %d and %d are:\n", temp3 + 1, temp4);														/* 文本显示信息											*/

			for( i = temp3; i < temp4; i++ ){
				printf("%.3lf\n", pPtr->wPtrs[ 0 ][ i ]);																	/* 显示偏置													*/
			}/* end for */
		}/* end if */
	}/* end if */
	else{
		printf("\nNo perceptron exist!\n");																					/* 文本显示信息											*/
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