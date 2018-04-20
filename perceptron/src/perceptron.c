/**
   ******************************************************************************************************************************************************
   * @file		peceptron.c
   * @author	Morris
   * @version	V1.0
   * @date		2018年4月20日21:08:19 在VS2017上Debug模式最终运行
   * @brief		统计学习、神经网络中的感知机（感知器）
   ******************************************************************************************************************************************************
   * @attention (1)应以-1、+1来给样本类别进行标签
   *                     (2)应将感知机输出维数设置为1，多类别分类在本程序中未实现，只支持2类别
   *                     (3)本程序采用串行更新的方式
   *                     (4)在权值更新方式中可优化为附加动量法
   *                     (5)可参照我的CSDN博客进行阅读，
   *                     地址: https://blog.csdn.net/weixin_41592704/article/details/80024234
   *
   ******************************************************************************************************************************************************
   */

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "../inc/perceptron.h"

/**
 * @brief		判断一个数是否是Inf或者NaN
 * @param		d64 sum 要判断的数
 * @retval		i32 类型数据，1表示正常， 0表示不正常
 */
static i32 PCPT__IsNormal( d64 sum )
{
	if( sum == sum && sum != ( sum + 1.0 ) ){/* 判断一个数是否是正常数字	 */
		return 1; /* 条件成立返回1 */
	}/* end if */
	else{
		return 0; /* 否则返回0 */
	}/* end else */
}/* end function PCPTPCPT__IsNormal */

/**
 * @brief		随机生成-1~+1之间的小数
 * @param		d64 sum 要判断的数
 * @retval		d64类型，生成的随机数
 */
static d64 PCPT_RandOfd64( void )/* 生成随机数函数 */
{
	return ( -1 + rand() % 2 + ( d64 )rand() / RAND_MAX ); /* 随机生成一个-1~1之间的小数 */
}/*end function PCPT_randOfd64 */

/**
 * @brief		符号函数
 * @param		d64 sum 输入
 * @retval		i32类型数据，+1或-1
 */
static i32 PCPT_SignFunction( d64 sum )
{
	if( sum >= 0 ){
		return 1;
	}/* end if */															
	else{																
		return -1;
	}/* end else */
}/*end function PCPT_signFunction */

/**
 * @brief		感知机参数设定函数
 * @param		PCPT_TypeDefPtr pPtr 感知机结构体指针
 * @retval		无
 */
void PCPT_SetPerceptronParam( PCPT_TypeDefPtr pPtr )
{
	i32 num1;	
	d64 lr;

	do{
		printf("\n输入最大训练回合数（退出-1）:\n");
		scanf_s("%d", &num1);	/* 输入训练最大回合数 */
		if( num1 == -1 ){/* 判断是否选择退出感知机参数设定 */
			return;	
		}/* end if */

		if( num1 < 0 ){
			printf("\n请输入大于0的数!\n ");
		}/* end if */
	}while( num1 < 0 ); /* 循环直至输入正确或选择退出 */
	pPtr->epoch = num1;/* 设定最大训练回合数*/

	do{
		printf("\n输入学习率（退出-1）:\n");
		scanf_s("%lf", &lr);/* 输入学习率 */
		if( -0.9999 > lr && lr > -1.0001 ){ /* 判断是否选择退出感知机参数设定 */
			return;	
		}/* end if */

		if( lr < 0 || lr > 1.0 ){ /* 判断学习率输入是否符合 */											
			printf("\n输入学习率大于0且小于1！\n ");
		}/* end if */
	}while( lr < 0 || lr > 1.0 );/* 循环直至输入正确或选择退出 */
	pPtr->learnRate = lr;	/* 设定学习率	 */
	
	pPtr->parameter.numOfInput = pPtr->perceptData.numOfInput;
	pPtr->parameter.numOfOutput = pPtr->perceptData.numOfOutput;

	pPtr->pcptParmLabel = 1; /* 感知机参数设定完成标志置 */
}/*end function PCPT_SetPerceptronParam */

/**
 * @brief		感知机生成函数
 * @param		PCPT_TypeDefPtr pPtr 感知机结构体指针
 * @retval		无
 */
void PCPT_PerceptronCreat( PCPT_TypeDefPtr pPtr )
{
	i32 i;
	i32 numI =pPtr->parameter.numOfInput;
	i32 numO =  pPtr->parameter.numOfOutput;

	if( pPtr->pcptParmLabel == 1 ){/* 判断感知机参数是否设定 */
		pPtr->inPtr = ( d64 * )malloc( sizeof( d64 ) * ( numI + 1 ) ); /* 动态一维数组用于存储感知机输入 */

		if( pPtr->inPtr == NULL ){ /* 判断存储输入一维数组内存是否分配 */
			printf( "\n%dPCPT_PerceptronCreat（）内存不足!\n", __LINE__ );
			exit( -1 );
		}/* end if */

		pPtr->ouPtr = ( d64 * )malloc( sizeof( d64 ) * numO );/* 动态一维数组用于存储感知机输出 */
	
		if( pPtr->ouPtr == NULL ){ /* 判断存储输入一维数组内存是否分配 */
			printf( "\n%dPCPT_PerceptronCreat（）内存不足!\n", __LINE__ );
			exit( -1 );
		}/* end if */

		pPtr->wPtrs = ( d64 ** )malloc( sizeof( d64 * ) * ( numI + 1 ) );/* 动态指针数组用于存储权值一维数组*/

		if( pPtr->wPtrs != NULL ){ /* 判断指针数组内存分配是否成功 */
			for( i = 0; i <= numI; i++ ){
				pPtr->wPtrs[ i ] = ( d64 * )malloc( sizeof( d64 ) * numO ); /* 动态一维数组生成权值存储二维数组 */

				if( pPtr->wPtrs[ i ] == NULL ){ /* 判断权值一维数组内存是否分配成功	*/
					printf( "\n%dPCPT_PerceptronCreat（）内存不足!\n", __LINE__ );
					exit( -1 );
				}/* end if */
			}/* end for */
		}/* end if */
		else{																																	
			printf( "\n%dPCPT_PerceptronCreat（）内存不足!\n", __LINE__ );	
			exit( -1 );
		}/* end else */
	}/* end if */
	else{
		printf("\n感知机生成失败，感知机参数未设置！\n");
		return;	
	}/* end else */

	pPtr->pcptCreatLabel = 1; /* 感知机创建标志置 */
}/* end function PCPT_PerceptronCreat */

/**
 * @brief		感知机初始化函数
 * @param		PCPT_TypeDefPtr pPtr 感知机结构体指针
 * @retval		无
 */
void PCPT_PerceptronInit( PCPT_TypeDefPtr pPtr )
{
	i32 i;
	i32 j;
	i32 numI = pPtr->parameter.numOfInput;
	i32 numO = pPtr->parameter.numOfOutput;
	
	if( pPtr->pcptCreatLabel == 1 ){ /* 判断感知机是否创建 */
		for( i = 0; i < ( numI + 1 ); i++ ){
			if( i == 0 ){
				pPtr->inPtr[ i ] = 1.0; /* 输入比设定维数高1维，固定值1 */
			}/* end if */
			else{
				pPtr->inPtr[ i ] = 0.0; /* 感知机输入初始化为0 */
			}/* end else */
		}/* end for */

		for( i = 0; i < numO; i++ ){
			pPtr->ouPtr[ i ] = 0.0;	 /* 感知机输出初始化为0 */
		}/* end for */

		for( i = 0; i < numO; i++ ){
			for( j = 0; j < ( numI + 1 ); j++ ){
				if( j == 0 ){
					pPtr->wPtrs[ j ][ i ] = 1.0;	 /* 感知机权值矩阵，第0行为偏置 */
				}/* end if */
				else{
					pPtr->wPtrs[ j ][ i ] = PCPT_RandOfd64(); /* 感知机权值初始化为-1~+1的数值 */
				}/* end else */
			}/* end for */
		}/* end for */
	}/* end if */
	else{
		printf("\n初始化失败，感知机不存在！\n");
		return;	
	}/* end else */
}/* end function perceptronInit */

/**
 * @brief		感知机训练函数
 * @param		PCPT_TypeDefPtr pPtr 感知机结构体指针
 * @retval		无
 */
void PCPT_PerceptronTrain( PCPT_TypeDefPtr pPtr )
{
	i32 i, j, n, k;
	i32 count = 0;/* 临时变量，计算分类错误样本个数 */	
	d64 sum = 0;/* 临时变量，存储感知机计算值*/
	d64 temp = 0;

	if( pPtr->pcptCreatLabel == 1 && pPtr->perceptData.creatLabel == 1 ){ /* 判断感知机、数据存储框架是否创建 */
		for( n = 0; n < pPtr->epoch; n++ ){ /* 在最大训练回合中训练感知机 */

			DT_randForSequence( &pPtr->perceptData );/* 生成用于训练样本时呈现的随机序列	*/
			
			count = 0; /* 分类错误样本数清零 */
			sum = 0; /* 感知机计算值清零 */	
			for( k = 0; k < pPtr->perceptData.numOfSample; k++ ){
				for( i = 1; i <= pPtr->perceptData.numOfInput; i++ ){
					pPtr->inPtr[ i ] = pPtr->perceptData.samPtrs[ i - 1 ]
						[ pPtr->perceptData.seqPtr[ k ] ]; /* 按生成的随机序列选取训练样本实例 */
				}/* end for */

				for( i = 0; i < pPtr->parameter.numOfOutput; i++ ){
					for( j = 0; j <= pPtr->parameter.numOfInput; j++ ){
						temp = pPtr->inPtr[ j ] * pPtr->wPtrs[ j ][ i ]; /* 输入与权值、偏置运算 */

						if( !PCPT__IsNormal( temp ) ) temp = 0.0;

						sum += temp; /* 计算诱导局部域 */
					}/* end for */

					pPtr->ouPtr[ i ] = PCPT_SignFunction( sum ); /* 计算感知机输出值 */

					sum = 0.0; /* 诱导局部域清零，进行下一个计算 */

					temp = pPtr->ouPtr[ i ] * pPtr->perceptData.aimPtrs[ i ]
						[ pPtr->perceptData.seqPtr[ k ] ]; /* 判断感知机是否将训练样本误分类	 */

					if( !PCPT__IsNormal( temp ) ) temp = 0.0;																												

					if( temp <= 0 ){ /* 若条件成立，则说明感知机误分类 */
						for( j = 0; j <= pPtr->parameter.numOfInput; j++ ){
							temp = pPtr->learnRate * pPtr->perceptData.aimPtrs[ i ]
								[ pPtr->perceptData.seqPtr[ k ] ] * pPtr->inPtr[ j ]; /* 计算自由参数变化量 */

							if( !PCPT__IsNormal( temp ) ) temp = 0.0;

							pPtr->wPtrs[ j ][ i ] += temp;	 /* 更新自由参数 */
						}/* end for */

						count++; /* 统计训练样本中的误分类数 */
					}/* end if */
				}/* end for */
			}/* end for */

			printf("回合: %d\n", n);

			if( count == 0 ){ /* 判断训练样本是否全部分类正确*/
				printf("\n所有训练样本正确分类!\n");
				break; /* 跳出训练回合for循环 */
			}/* end if */
		}/* end for */
	}/* end if */
	else printf("\n不存在数据或感知机未生成!\n");

}/*  end function perceptronTrain */

/**
 * @brief		感知机测试函数
 * @param		PCPT_TypeDefPtr pPtr 感知机结构体指针
 * @retval		无
 */
void PCPT_PerceptronTest( PCPT_TypeDefPtr pPtr )	
{
	i32 i, j, k;
	i32 count = 0;/* 测试样本误分类统计 */
	d64 temp = 0.0;
	d64 sum = 0.0;  /* 感知机诱导局部域 */
	d64 rate = 0.0;	 /* 测试样本分类错误率 */

	if( pPtr->pcptCreatLabel == 1 && pPtr->perceptData.creatLabel == 1 ){/* 判断感知机、数据存储结构是否创建	*/

		for( k = 0; k < pPtr->perceptData.numOfTSample; k++ ){
			for( i = 1; i <= pPtr->parameter.numOfInput; i++ ){
				pPtr->inPtr[ i ] = pPtr->perceptData.tSamPtrs[ i - 1 ][ k ];	/* 读取测试样本某个实例输入 */
			}/* end for */

			for( i = 0; i < pPtr->parameter.numOfOutput; i++ ){
				for( j = 0; j <= pPtr->parameter.numOfInput; j++ ){
					temp = pPtr->wPtrs[ j ][ i ] * pPtr->inPtr[ j ]; /* 输入与权值、偏置运算 */

					if( !PCPT__IsNormal( temp ) ) temp = 0.0;

					sum += temp;	/* 计算诱导局部域 */	
				}/* end for */

				pPtr->ouPtr[ i ] = PCPT_SignFunction( sum );/* 计算感知机输出*/
				sum = 0.0;	/* 诱导局部域清零，进行下一次计算 */

				if( pPtr->ouPtr[ i ] != pPtr->perceptData.tAimPtrs[ i ][ k ] ){ /*判断感知机输出与测试样本目标输出*/
					count++; /*若分类错误则增加错误分类数*/
				}/* end if */
			}/* end for */
		}/* end for */

		rate = ( d64 )count / pPtr->perceptData.numOfTSample * 100.0; /*计算感知机对测试样本的分类错误率*/

		printf("\n测试样本分类错误率: %.3lf%%\n", rate);

		rate = 100.0 - rate;/* 计算分类正确率 */

		printf("\n测试样本分类正确率: %.3lf%%\n", rate);
	}/* end if */
	else printf("\n感知机未生成!\n");

}/* end function PCPT_PerceptronTest */

/**
 * @brief		感知机预测输入函数
 * @param		PCPT_TypeDefPtr pPtr 感知机结构体指针
 * @retval		无
 */
void PCPT_UsePerceptron( PCPT_TypeDefPtr pPtr )
{
	i32 i, j;
	d64 sum = 0.0;	/* 诱导局部域 */
	d64 temp = 0.0;

	if( pPtr->pcptCreatLabel == 1 && pPtr->perceptData.creatLabel == 1 ){	/* 判断感知机、数据存储结构是否创建 */
		printf("\n输入数据:\n");
		for( i = 1; i <= pPtr->parameter.numOfInput; i++ ){
			scanf_s("%lf", &pPtr->inPtr[ i ]); /* 输入样本实例的输入*/
		}/* end for */

		for( i = 0; i < pPtr->parameter.numOfOutput; i++ ){
			for( j = 0; j <= pPtr->parameter.numOfInput; j++ ){
				temp = pPtr->wPtrs[ j ][ i ] * pPtr->inPtr[ j ];/* 输入向量与权值向量、偏置做运算 */

				if( !PCPT__IsNormal( temp ) ) temp = 0.0;																				

				sum += temp; /* 计算诱导局部域 */
			}/* end for */

			pPtr->ouPtr[ i ]  = PCPT_SignFunction( sum );	 /* 计算输出 */
			sum = 0.0;	/* 临时变量清零，用于下次运算 */


		}/* end for */

		printf("\n感知机输出:\n");
		for( i = 0; i < pPtr->parameter.numOfOutput; i++ ){
			printf("%.3lf\n", pPtr->ouPtr[ i ]); 
		}/* end for */
	}/* end if */
	else printf("\n感知机未生成!\n");
}/* end function PCPT_UsePerceptron */

/**
 * @brief		感知机显示权值函数
 * @param		PCPT_TypeDefPtr pPtr 感知机结构体指针
 * @retval		无
 */
void PCPT_PrintWeights( PCPT_TypeDefPtr pPtr )
{
	i32 i, j, n;
	i32 numI = pPtr->parameter.numOfInput;
	i32 numO = pPtr->parameter.numOfOutput;
	i32 temp1 = 0;	/* 需显示的页数 */
	i32 temp2 = 0; /* 不够一页的剩余量 */
	i32 temp3 = 0; /* 开始显示的位置 */
	i32 temp4 = 0;	 /* 终止显示的位置 */

	temp1 = numO / 10; /* 计算每页以10个权值向量需显示几页 */
	temp2 = numO % 10;	 /*剩余多少个权值向量 */

	if( pPtr->pcptCreatLabel == 1 ){ /* 判断感知机是否创建 */
		if( temp1 != 0 ){ /* 判断是否有10为基数的显示页数 */
			for( n = 0; n < temp1; n++ ){
				temp3 = temp4; /* 从上一次结束的位置换页显示 */
				temp4 += 10; /* 计算终止显示的位置 */

				printf("\n权值 %d - %d :\n", temp3 + 1, temp4);

				for( i = 1; i <= numI; i++ ){
					for( j = temp3; j < temp4; j++ ){
						printf("%8.3lf ", pPtr->wPtrs[ i ][ j ]);
					}/* end for */
					printf("\n");
				}/* end for */
			}/* end for */
		}/* end if */

		if( temp2 != 0 ){ /* 判断剩余的个数是否为0 */
			temp3 = temp4; /* 从上次显示的位置换页显示 */
			temp4 += temp2; /* 计算终止显示的位置 */
			
			printf("\n权值 %d - %d :\n", temp3 + 1, temp4);

			for( i = 1; i <= numI; i++ ){
				for( j = temp3; j < temp4; j++ ){
					printf("%8.3lf ", pPtr->wPtrs[ i ][ j ]);
				}/* end for */
				printf("\n");
			}/* end for */
		}/* end if */
	}/* end if */
	else printf("\n感知机未生成!\n");

}/* end function PCPT_PrintWeights */

/**
 * @brief		感知机显示偏置函数
 * @param		PCPT_TypeDefPtr pPtr 感知机结构体指针
 * @retval		无
 */
void PCPT_PrintBiases( PCPT_TypeDefPtr pPtr )
{
	i32 i, n;
	i32 temp1 = pPtr->parameter.numOfOutput / 10; /* 计算显示页数 */
	i32 temp2 = pPtr->parameter.numOfOutput % 10;	 /* 计算剩余量 */
	i32 temp3 = 0;	 /* 开始显示的位置 */
	i32 temp4 = 0;	/* 终止显示的位置 */

	if( pPtr->pcptCreatLabel == 1){/* 判断感知机是否生成 */
		if( temp1 != 0 ){/* 判断需显示的页数是否为0 */
			for( n = 0; n < temp1; n++ ){
				temp3  = temp4;/* 开始显示的位置 */
				temp4 += 10; /* 终止显示的位置 */

				printf("\n偏置 %d - %d :\n", temp3 + 1, temp4);

				for( i = temp3; i < temp4; i++ ){
					printf("%.3lf\n", pPtr->wPtrs[ 0 ][ i ]);
				}/* end for */
			}/* end for */
		}/* end if */

		if( temp2 != 0 ){ /* 判断剩余量是否为0 */

			temp3 = temp4;/* 开始显示的位置 */
			temp4 += temp2;/* 终止显示的位置	*/

			printf("\n偏置 %d - %d :\n", temp3 + 1, temp4);

			for( i = temp3; i < temp4; i++ ){
				printf("%.3lf\n", pPtr->wPtrs[ 0 ][ i ]);
			}/* end for */
		}/* end if */
	}/* end if */
	else{
		printf("\n感知机未生成！\n");
	}/* end else */
}/* end function PCPT_PrintBiases */

void PCPT_PrintPerceptronParam( PCPT_TypeDefPtr pPtr )
{
	printf("\n感知机输入维数: %d\n"
			  "\n感知机输出维数: %d\n"
			  "\n感知机学习率: %.3lf\n"
			  "\n感知机最大训练回合数: %d\n", 
			  pPtr->parameter.numOfInput, 
			  pPtr->parameter.numOfOutput,
			  pPtr->learnRate, pPtr->epoch);
}/* end function PCPT_PrintPerceptronParam */

void PCPT_PrintInstructions( i32 *cho )
{
	printf("\n你想干什么?\n");

	printf("================================\n"
			  "* 1.  设置样本数据存储结构参数.\n"
			  "* 2.  显示样本存储结构参数.\n"
			  "* 3.  设置感知机参数.\n"
			  "* 4.  显示感知机参数.\n"
			  "* 5.  生成样本数据存储结构.\n"
			  "* 6.  生成感知机.\n"
			  "* 7.  初始化数据结构.\n"
			  "* 8.  初始化感知机.\n"
			  "* 9.  输入训练样本.\n"
			  "* 10. 输入测试样本\n"
			  "* 11. 显示训练样本.\n"
			  "* 12. 显示测试样本.\n"
			  "* 13. 显示感知机权值.\n"
			  "* 14. 显示感知机偏置.\n"
			  "* 15. 训练感知机.\n"
			  "* 16. 测试感知机.\n"
			  "* 17. 使用感知机进行预测.\n"
			  "* 0.  退出.\n"
			  "================================\n"
			  "输入你的选择:");
	scanf_s("%d", cho );
}/* end function printInstruction */