/**
   ******************************************************************************************************************************************************
   * @file		Data.c
   * @author	Morris
   * @version	V1.0
   * @date		2018年4月20日21:08:19 在VS2017上Debug模式最终运行
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


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include "../inc/Data.h"

/**
 * @brief	用于生成一个随机序列
 * @param	DT_TypeDefPtr dPtr 数据存储结构体指针
 * @retval	无
 */
void DT_randForSequence( DT_TypeDefPtr dPtr )
{
	i32 i;
	i32 seq		= 0;
	i32 count	= 0;
	i32 numS	= dPtr->numOfSample; /* 读取训练样本总数 */

	while( count < numS ){/* 判断产生随机数的个数与样本数是否相同*/
		seq = rand() % numS;	 /*生成一个0~样本总数之间的一个随机数	*/
		
		for( i = 0; i < count; i++ ){																					
			if( dPtr->seqPtr[ i ] == seq ){	/* 判断生成的随机数是否与之前的相同 */
				seq = rand() % numS;	/* 重新生成随机数 */
				i = -1; /* 清零重新遍历随机序列数组 */
			}/* end if */
		}/* end for */

		dPtr->seqPtr[ count  ] = seq;	/* 将生产的随机数存储到数组当中	*/
		count++;
	}/* end while */
}/* end function DT_randForSequence */

/**
 * @brief	设置样本存储结构参数
 * @param DT_TypeDefPtr dPtr 数据存储结构体指针 
 * @retval	无
 */
void DT_SetSampleParameters( DT_TypeDefPtr dPtr )
{
	i32 num1 = 0;

	do{
		printf("\n设置训练样本总数:( 退出 -1 ):");	
		scanf_s("%d", &num1 ); /*输入用于训练的样本总数*/

		if( num1 == -1 ){ /* 判断输入的选择是否是退出 */
			return;	
		}/* end if */

		if( num1 < 0 ){
			printf("\n请输入大于0的数.\n");
		}/* end if */
	}while( num1 < 0 );/* 循环输入直至用户选择退出或输入正确*/
	dPtr->numOfSample = num1;/* 设置训练样本总数 */

	do{
		printf("\n设置测试样本总数:");	
		scanf_s("%d", &num1);/*	输入测试样本总数*/

		if( num1 == -1 ){/*判断输入的选择是否是退出*/
			return;	
		}/* end if */

		if( num1 < 0 ){
			printf("\n请输入大于0的数.\n");
		}/* end if */
	}while( num1 < 0 );/* 循环输入直至用户选择退出或输入正确 */
	dPtr->numOfTSample = num1; /* 设置测试样本总数 */

	do{
		printf("\n设置样本输入维数( 退出 -1 ):");
		scanf_s("%d", &num1);/* 输入输入向量的维数 */

		if( num1 == -1 ){ /*判断输入的选择是否是退出 */
			return;	
		}/* end if */	

		if( num1 < 0 ){
			printf("\n请输入大于0的数.\n");
		}/* end if */
	}while( num1 < 0 );/* 循环输入直至用户选择退出或输入正确 */
	dPtr->numOfInput = num1;/*设置输入向量维数*/

	do{
		printf("\n设置输出向量维数 ( 退出 -1 ):");
		scanf_s("%d", &num1);/*	输入输出向量的维数 */

		if( num1 == -1 ){/* 判断输入的选择是否是退出 */
			return;	
		}/* end if */

		if( num1 < 0 ){
			printf("\n请输入大于0的数.\n");					
		}/* end if */
	}while( num1 < 0 );/* 循环输入直至用户选择退出或输入正确 */
	dPtr->numOfOutput = num1;/* 设置输出向量维数 */

	dPtr->samParmLabel = 1; /* 数据参数设置标志 */
}/* end function DT_SetSampleParameters */

/**
 * @brief	创建数据存储结构
 * @param DT_TypeDefPtr dPtr 数据存储结构体指针 
 * @retval	无*/
void DT_DatasCreat( DT_TypeDefPtr dPtr )
{
	i32 i;
	i32 numS = dPtr->numOfSample; 
	i32 numI = dPtr->numOfInput;
	i32 numO = dPtr->numOfOutput;
	i32 numT = dPtr->numOfTSample;	
																					
	if( dPtr->samParmLabel == 1 ){ /* 判断是否设置了样本参数 */
		dPtr->samPtrs = ( d64 ** )malloc	( sizeof( d64 * ) * ( numI ) ); /* 动态分配存储训练样本数据的指针数组 */

		if( dPtr->samPtrs != NULL ){	/* 判断指针数组内存是否分配成功	 */	
			for( i = 0; i < numI; i++ ){
				dPtr->samPtrs[ i ] = ( d64 * )malloc( sizeof( d64 ) * numS );	/* 指针数组动态分配一维数组，构成二维数组 */

				if( dPtr->samPtrs[ i ] == NULL ){ /* 判断训练样本二维数组动态分配是否为空	*/
					printf("\nDT_DatasCreat()内存不足!\n");
					exit( -1 );/* 结束应用程序 */
				}/* end if */
			}/* end for */
		}/* end if */
		else{
			printf("\nDT_DatasCreat()内存不足!\n");
			exit( -1 );/* 结束应用程序 */
		}/* end else */

		dPtr->seqPtr = ( i32 * )malloc( sizeof( i32 ) * numS ); /* 动态分配用于存储随机序列的一维数组 */

		if( dPtr->seqPtr == NULL ){ /* 判断随机序列动态分配内存是否成功 */
			printf("\nDT_DatasCreat()内存不足!\n");
			exit( -1 );/* 结束应用程序 */
		}/* end if */

		dPtr->aimPtrs = ( d64 ** )malloc( sizeof( d64 * ) * numO );	/* 动态分配存储训练样本目标输出的指针数组*/

		if( dPtr->aimPtrs != NULL ){	/* 判断指针数组内存是否分配成功	*/
			for( i = 0; i < numO; i++ ){
				dPtr->aimPtrs[ i ] = ( d64 * )malloc( sizeof( d64 ) * numS );/* 指针数组动态分配一维数组，构成二维数组*/

				if( dPtr->aimPtrs[ i ] == NULL ){	 /* 判断目标输出二维数组动态分配是否为空	*/
					printf("\nDT_DatasCreat()内存不足!\n");
				}/* end if */
			}/* end for */
		}/* end if */
		else{
			printf("\nDT_DatasCreat()内存不足!\n");
			exit( -1 );/* 结束应用程序 */
		}/* end else */

		dPtr->tSamPtrs = ( d64 ** )malloc( sizeof( d64 * ) * numI );	/* 动态分配存储测试样本数据的指针数组	 */
		if( dPtr->tSamPtrs != NULL ){ /* 判断指针数组内存是否分配成功 */
			for( i = 0; i < numI; i++ ){
				dPtr->tSamPtrs[ i ] = ( d64 * )malloc( sizeof( d64 ) * numT ); /* 指针数组动态分配一维数组，构成二维数组 */

				if( dPtr->tSamPtrs[ i ] == NULL ){ /* 判断测试样本二维数组动态分配是否为空 */
					printf("\nDT_DatasCreat()内存不足!\n");
					exit( -1 );/* 结束应用程序 */
				}/* end if */
			}/* end for */
		}/* end if */
		else{
			printf("\nDT_DatasCreat()内存不足!\n");
			exit( -1 ); /* 结束应用程序 */
		}/* end else */

		dPtr->tAimPtrs = ( d64 ** )malloc( sizeof( d64 * ) * numO ); /* 动态分配一个存储测试样本目标输出的指针数组	 */
		if ( dPtr->tAimPtrs != NULL ){ /* 判断动态分配指针数组是否成功 */
			for ( i = 0; i < numO; i++ ){
				dPtr->tAimPtrs[ i ] = ( d64 * )malloc( sizeof( d64 ) * numT ); /* 指针数组动态分配一维数组，构成二维数组 */

				if ( dPtr->tAimPtrs[ i ] == NULL ){/* 判断测试样本目标输出二维数组动态分配是否为空 */
					printf( "\nDT_DatasCreat()内存不足!\n" );
					exit( -1 );/* 结束应用程序*/
				}/* end if */
			}/* end for */
		}/* end if */
		else{
			printf( "\nDT_DatasCreat()内存不足!\n" );
			exit( -1 );/* 结束应用程序 */
		}/* end else */
	}/* end if */
	else{
		printf( "\nDT_DatasCreat()内存不足!\n" );
		return;
	}/* end else */

	dPtr->creatLabel = 1;	/* 样本存储结构创建标志置1*/
}/* end function  DT_DatasCreat */

/**
 * @brief	输入训练样本函数
 * @param	DT_TypeDefPtr dPtr 数据存储结构体指针
 * @retval	无
 */
void DT_InputTrainSamples( DT_TypeDefPtr dPtr )
{
	i32 i;
	i32 j;
	i32 numI = dPtr->numOfInput;
	i32 numO = dPtr->numOfOutput;
	i32 numS = dPtr->numOfSample;
	
	if( dPtr->creatLabel == 1 ){/* 判断样本存储结构是否创建	 */
		printf("\n输入训练样本，样本总数：%d，样本输入维数：%d\n", numS, numI);
		for( i = 0; i < numS; i++ ){
			for( j = 0; j < numI; j++ ){
				scanf_s("%lf", &dPtr->samPtrs[ j ][ i ] );	/* 输入训练样本数据输入 */
			}/* end for */
		}/* end for */

		printf("\n输入训练样本目标输出，样本总数：%d，样本输出维数：%d\n", numS, numO);
		for( i = 0; i < numS; i++ ){
			for( j = 0; j < numO; j++ ){
				scanf_s("%lf", &dPtr->aimPtrs[ j ][ i ]);/* 输入训练样本目标输出 */
			}/* end for */
		}/* end for */
		dPtr->trainDataEntered = 1;
	}/* end if */
	else{
		printf( "\n请先创建样本数据存储结构体！\n");
	}/* end else */
}/*end function DT_InputTrainSamples */

/**
 * @brief	输入测试样本函数
 * @param	DT_TypeDefPtr dPtr 数据存储结构体指针
 * @retval	无
 */
void DT_InputTestSamples( DT_TypeDefPtr dPtr )
{
	i32 i;
	i32 j;
	i32 numI = dPtr->numOfInput;
	i32 numO = dPtr->numOfOutput;
	i32 numT = dPtr->numOfTSample;

	if( dPtr->creatLabel == 1 ){ /* 判断样本存储结构是否创建 */
		printf("\n输入测试样本，样本总数：%d，样本输入维数：%d\n", numT, numI);
		for( i = 0; i < numT; i++ ){
			for( j = 0; j < numI; j++ ){
				scanf_s("%lf", &dPtr->tSamPtrs[ j ][ i ]); /* 输入测试样本数据输入 */
			}/* end for */
		}/* end for */

		printf("\n输入测试样本目标输出，样本总数：%d，样本输出维数：%d\n", numT, numO);
		for( i = 0; i < numT; i++ ){
			for( j = 0; j < numO; j++ ){
				scanf_s("%lf", &dPtr->tAimPtrs[ j ][ i ]); /* 输入测试样本目标输出 */
			}/* end for */
		}/* end for */

		dPtr->testDataEntered = 1;
	}/* end if */
	else{
		printf("\n请先创建数据存储结构");	
	}/* end else */
}/* end function DT_InputTestSamples */

/**
 * @brief	初始化数据结构体参数
 * @param	DT_TypeDefPtr dPtr 数据存储结构体指针
 * @retval	无
 */
void DT_DatasInit( DT_TypeDefPtr  dPtr )
{
	i32 i;
	i32 j;
	i32 numI   = dPtr->numOfInput;
	i32 numO = dPtr->numOfOutput;
	i32 numS  = dPtr->numOfSample;
	i32 numT = dPtr->numOfTSample;

	for( i = 0; i < numS; i++ ){
		for(  j = 0; j < numI; j++ ){
			dPtr->samPtrs[ j ][ i ] = 0.0; /* 初始化训练样本存储二维数组 */
		}/* end for */

		for( j = 0; j < numO; j++ ){
			dPtr->aimPtrs[ j ][ i ] = 0.0; /* 初始化训练样本目标输出存储二位数组 */
		}/* end for */

		dPtr->seqPtr[ i ] = 0;/* 初始化随机序列数组 */
	}/* end for */

	for( i = 0; i < numT; i++ ){
		for( j = 0; j < numI; j++ ){
			dPtr->tSamPtrs[ j ][ i ] = 0.0;/* 初始化测试样本目标输出存储二位数组 */
		}/*  end for */

		for( j = 0; j < numO; j++ ){
			dPtr->tAimPtrs[ j ][ i ] = 0.0;/* 初始化测试样本目标输出存储二位数组 */
		}/* end for */
	}/* end for */

	dPtr->testDataEntered = 0;
	dPtr->trainDataEntered = 0;

}/* end function DataInit */

/**
 * @brief	释放数据存储结构中的内存分配
 * @param DT_TypeDefPtr dPtr 数据存储结构体指针
 * @retval	无
 */
void DT_DatasDeInit( DT_TypeDefPtr dPtr )
{
	i32 i;
	i32 numI = dPtr->numOfInput;
	i32 numO = dPtr->numOfOutput;
	i32 numS = dPtr->numOfSample;
	i32 numT = dPtr->numOfTSample;

	if ( dPtr->creatLabel == 1 ){
		for ( i = 0; i < numI; i++ ){
			free( dPtr->samPtrs[ i ] ); /* 释放存储训练样本数据二维数组内存 */
			free( dPtr->tSamPtrs[ i ] ); /*释放存储测试样本数据二维数组内存 */
		}/* end for */

		free( dPtr->samPtrs );/* 释放训练样本数据的指针数组 */
		free( dPtr->tSamPtrs ); /* 释放测试样本数据的指针数组 */

		for ( i = 0; i < numO; i++ ){
			free( dPtr->aimPtrs[ i ] );	 /* 释放存储训练样本目标输出的二维数组内存 */
			free( dPtr->tAimPtrs[ i ] ); /* 释放存储测试样本目标输出的二维数组内存 */
		}/* end for */

		free( dPtr->aimPtrs );	 /* 释放训练样本目标输出的指针数组 */
		free( dPtr->tAimPtrs );/* 释放测试样本目标输出的指针数组	 */
		free( dPtr->seqPtr ); /* 释放随机序列一维数组内存 */
		dPtr->creatLabel = 0;
	}/* end if */
	else printf( "\n数据结构体不存在！\n" );

	dPtr->creatLabel = 0; /* 初始化创建标志 */
	dPtr->samParmLabel	 = 0; /* 初始化创建标志 */
	dPtr->numOfInput = 0;  /* 初始化输入维数 */
	dPtr->numOfOutput = 0;  /* 初始化输出维数 */
	dPtr->numOfSample	= 0;  /* 初始化训练样本总数 */
	dPtr->numOfTSample= 0;  /* 初始化测试样本总数 */
	dPtr->testDataEntered = 0;
	dPtr->trainDataEntered = 0;
}/*end function DT_DatasDeInit*/

/**
 * @brief	显示训练样本每10个样本换行
 * @param DT_TypeDefPtr dPtr 数据存储结构体指针
 * @retval	无
 */
void DT_PrintTrainSamples( DT_TypeDefPtr dPtr )
{
	i32 i, j, k;
	i32 temp1 = 0, temp2 = 0, temp3 = 0, temp4 = 0;
	i32 numI = dPtr->numOfInput;
	i32 numO = dPtr->numOfOutput;
	i32 numS = dPtr->numOfSample;

	temp1 = numS / 10;
	temp2 = numS % 10;
	if ( dPtr->trainDataEntered == 1 ){
		if ( temp1 != 0 ){
			for ( k = 0; k < temp1; k++ ){
				printf( "\n训练样本输入 %d - %d:\n", temp3 + 1, temp4 + 10 );

				for ( i = 0; i < numI; i++ ){
					for ( j = temp3; j < temp4 + 10; j++ ){
						printf( "%-10.3lf ", dPtr->samPtrs[ i ][ j ] );
					}/* end for */
					printf( "\n" );
				}/* end for */

				printf( "\n目标输出：\n" );

				for ( i = 0; i < numO; i++ ){
					for ( j = temp3; j < temp4 + 10; j++ ){
						printf( "%-5.3lf ", dPtr->aimPtrs[ i ][ j ] );
					}/* end for */
					printf( "\n" );
				}/* end for */

				temp3 = temp4 + 10;
				temp4 += 10;
			}/* end for */
		}/* end if */

		if ( temp2 != 0 ){
			temp3 = temp4;
			temp4 += temp2;

			printf( "\n训练样本输入 %d - %d:\n", temp3 + 1, temp4 );

			for ( i = 0; i < numI; i++ ){
				for ( j = temp3; j < temp4; j++ ){
					printf( "%-5.3lf ", dPtr->samPtrs[ i ][ j ] );
				}/* end for */
				printf( "\n" );
			}/* end for */

			printf( "\n目标输出：\n" );

			for ( i = 0; i < numO; i++ ){
				for ( j = temp3; j < temp4; j++ ){
					printf( "%-5.3lf ", dPtr->aimPtrs[ i ][ j ] );
				}/* end for */
				printf( "\n" );
			}/* end for */
		}/* end if */
	}
	else printf( "\n无训练数据.\n" );
}/* end function DT_PrintTrainSamples */

/**
 * @brief	显示测试样本每10个样本换行
 * @param DT_TypeDefPtr dPtr 数据存储结构体指针
 * @retval	无
 */
void DT_PrintTestSamples( DT_TypeDefPtr dPtr )
{
	i32 i, j, k;
	i32 temp1 = 0, temp2 = 0, temp3 = 0, temp4 = 0;
	i32 numI = dPtr->numOfInput;
	i32 numO = dPtr->numOfOutput;
	i32 numT = dPtr->numOfTSample;

	temp1 = numT / 10;
	temp2 = numT % 10;
	if ( dPtr->testDataEntered == 1 ){
		if ( temp1 != 0 ){
			for ( k = 0; k < temp1; k++ ){
				printf( "\n测试样本输入 %d - %d:\n", temp3 + 1, temp4 + 10 );

				for ( i = 0; i < numI; i++ ){
					for ( j = temp3; j < temp4 + 10; j++ ){
						printf( "%-5.3lf ", dPtr->tSamPtrs[ i ][ j ] );
					}/* end for */
					printf( "\n" );
				}/* end for */

				printf( "\n目标输出：\n" );

				for ( i = 0; i < numO; i++ ){
					for ( j = temp3; j < temp4; j++ ){
						printf( "%-5.3lf ", dPtr->tAimPtrs[ i ][ j ] );
					}/* end for */
					printf( "\n" );
				}/* end for */

				temp3 = temp4 + 10;
				temp4 += 10;
			}/* end for */
		}/* end if */

		if ( temp2 != 0 ){
			temp3 = temp4;
			temp4 += temp2;

			printf( "\n测试样本输入 %d - %d:\n", temp3 + 1, temp4 );

			for ( i = 0; i < numI; i++ ){
				for ( j = temp3; j < temp4; j++ ){
					printf( "%-5.3lf ", dPtr->tSamPtrs[ i ][ j ] );
				}/* end for */
				printf( "\n" );
			}/* end for */

			printf( "\n目标输出：\n" );

			for ( i = 0; i < numO; i++ ){
				for ( j = temp3; j < temp4; j++ ){
					printf( "%-5.3lf ", dPtr->tAimPtrs[ i ][ j ] );
				}/* end for */
				printf( "\n" );
			}/* end for */
		}/* end if */
	}/* end if */
	else printf( "\n无测试数据。\n" );
}/* end function DT_PrintTestSamples */

/**
 * @brief	显示数据存储结构体参数
 * @param DT_TypeDefPtr dPtr 数据存储结构体指针
 * @retval	无
 */
void DT_PrintDatasParams( DT_TypeDefPtr dPtr )
{
	printf("\n样本输入维数: %d\n"
			  "\n样本输出维数: %d\n"
			  "\n训练样本总数: %d\n"
			  "\n测试样本总数: %d\n", 
			  dPtr->numOfInput, dPtr->numOfOutput, 
			  dPtr->numOfSample, dPtr->numOfTSample);
}/* end function printDatasParams */