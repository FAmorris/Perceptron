#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include "../inc/Data.h"

/**
 * @brief	��������һ���������
 * @param	DT_TypeDefPtr dPtr ���ݴ洢�ṹ��ָ��
 * @retval	��
 */
void DT_randForSequence( DT_TypeDefPtr dPtr )
{
	i32 i;
	i32 seq		= 0;
	i32 count	= 0;
	i32 numS	= dPtr->numOfSample; /* ��ȡѵ���������� */

	while( count < numS ){/* �жϲ���������ĸ������������Ƿ���ͬ*/
		seq = rand() % numS;	 /*����һ��0~��������֮���һ�������	*/
		
		for( i = 0; i < count; i++ ){																					
			if( dPtr->seqPtr[ i ] == seq ){	/* �ж����ɵ�������Ƿ���֮ǰ����ͬ */
				seq = rand() % numS;	/* ������������� */
				i = -1; /* �������±�������������� */
			}/* end if */
		}/* end for */

		dPtr->seqPtr[ count  ] = seq;	/* ��������������洢�����鵱��	*/
		count++;
	}/* end while */
}/* end function DT_randForSequence */

/**
 * @brief	���������洢�ṹ����
 * @param DT_TypeDefPtr dPtr ���ݴ洢�ṹ��ָ�� 
 * @retval	��
 */
void DT_SetSampleParameters( DT_TypeDefPtr dPtr )
{
	i32 num1 = 0;

	do{
		printf("\n����ѵ����������:( �˳� -1 ):");	
		scanf_s("%d", &num1 ); /*��������ѵ������������*/

		if( num1 == -1 ){ /* �ж������ѡ���Ƿ����˳� */
			return;	
		}/* end if */

		if( num1 < 0 ){
			printf("\n���������0����.\n");
		}/* end if */
	}while( num1 < 0 );/* ѭ������ֱ���û�ѡ���˳���������ȷ*/
	dPtr->numOfSample = num1;/* ����ѵ���������� */

	do{
		printf("\n���ò�����������:");	
		scanf_s("%d", &num1);/*	���������������*/

		if( num1 == -1 ){/*�ж������ѡ���Ƿ����˳�*/
			return;	
		}/* end if */

		if( num1 < 0 ){
			printf("\n���������0����.\n");
		}/* end if */
	}while( num1 < 0 );/* ѭ������ֱ���û�ѡ���˳���������ȷ */
	dPtr->numOfTSample = num1; /* ���ò����������� */

	do{
		printf("\n������������ά��( �˳� -1 ):");
		scanf_s("%d", &num1);/* ��������������ά�� */

		if( num1 == -1 ){ /*�ж������ѡ���Ƿ����˳� */
			return;	
		}/* end if */	

		if( num1 < 0 ){
			printf("\n���������0����.\n");
		}/* end if */
	}while( num1 < 0 );/* ѭ������ֱ���û�ѡ���˳���������ȷ */
	dPtr->numOfInput = num1;/*������������ά��*/

	do{
		printf("\n�����������ά�� ( �˳� -1 ):");
		scanf_s("%d", &num1);/*	�������������ά�� */

		if( num1 == -1 ){/* �ж������ѡ���Ƿ����˳� */
			return;	
		}/* end if */

		if( num1 < 0 ){
			printf("\n���������0����.\n");					
		}/* end if */
	}while( num1 < 0 );/* ѭ������ֱ���û�ѡ���˳���������ȷ */
	dPtr->numOfOutput = num1;/* �����������ά�� */

	dPtr->samParmLabel = 1; /* ���ݲ������ñ�־ */
}/* end function DT_SetSampleParameters */

/**
 * @brief	�������ݴ洢�ṹ
 * @param DT_TypeDefPtr dPtr ���ݴ洢�ṹ��ָ�� 
 * @retval	��*/
void DT_DatasCreat( DT_TypeDefPtr dPtr )
{
	i32 i;
	i32 numS = dPtr->numOfSample; 
	i32 numI = dPtr->numOfInput;
	i32 numO = dPtr->numOfOutput;
	i32 numT = dPtr->numOfTSample;	
																					
	if( dPtr->samParmLabel == 1 ){ /* �ж��Ƿ��������������� */
		dPtr->samPtrs = ( d64 ** )malloc	( sizeof( d64 * ) * ( numI ) ); /* ��̬����洢ѵ���������ݵ�ָ������ */

		if( dPtr->samPtrs != NULL ){	/* �ж�ָ�������ڴ��Ƿ����ɹ�	 */	
			for( i = 0; i < numI; i++ ){
				dPtr->samPtrs[ i ] = ( d64 * )malloc( sizeof( d64 ) * numS );	/* ָ�����鶯̬����һά���飬���ɶ�ά���� */

				if( dPtr->samPtrs[ i ] == NULL ){ /* �ж�ѵ��������ά���鶯̬�����Ƿ�Ϊ��	*/
					printf("\nDT_DatasCreat()�ڴ治��!\n");
					exit( -1 );/* ����Ӧ�ó��� */
				}/* end if */
			}/* end for */
		}/* end if */
		else{
			printf("\nDT_DatasCreat()�ڴ治��!\n");
			exit( -1 );/* ����Ӧ�ó��� */
		}/* end else */

		dPtr->seqPtr = ( i32 * )malloc( sizeof( i32 ) * numS ); /* ��̬�������ڴ洢������е�һά���� */

		if( dPtr->seqPtr == NULL ){ /* �ж�������ж�̬�����ڴ��Ƿ�ɹ� */
			printf("\nDT_DatasCreat()�ڴ治��!\n");
			exit( -1 );/* ����Ӧ�ó��� */
		}/* end if */

		dPtr->aimPtrs = ( d64 ** )malloc( sizeof( d64 * ) * numO );	/* ��̬����洢ѵ������Ŀ�������ָ������*/

		if( dPtr->aimPtrs != NULL ){	/* �ж�ָ�������ڴ��Ƿ����ɹ�	*/
			for( i = 0; i < numO; i++ ){
				dPtr->aimPtrs[ i ] = ( d64 * )malloc( sizeof( d64 ) * numS );/* ָ�����鶯̬����һά���飬���ɶ�ά����*/

				if( dPtr->aimPtrs[ i ] == NULL ){	 /* �ж�Ŀ�������ά���鶯̬�����Ƿ�Ϊ��	*/
					printf("\nDT_DatasCreat()�ڴ治��!\n");
				}/* end if */
			}/* end for */
		}/* end if */
		else{
			printf("\nDT_DatasCreat()�ڴ治��!\n");
			exit( -1 );/* ����Ӧ�ó��� */
		}/* end else */

		dPtr->tSamPtrs = ( d64 ** )malloc( sizeof( d64 * ) * numI );	/* ��̬����洢�����������ݵ�ָ������	 */
		if( dPtr->tSamPtrs != NULL ){ /* �ж�ָ�������ڴ��Ƿ����ɹ� */
			for( i = 0; i < numI; i++ ){
				dPtr->tSamPtrs[ i ] = ( d64 * )malloc( sizeof( d64 ) * numT ); /* ָ�����鶯̬����һά���飬���ɶ�ά���� */

				if( dPtr->tSamPtrs[ i ] == NULL ){ /* �жϲ���������ά���鶯̬�����Ƿ�Ϊ�� */
					printf("\nDT_DatasCreat()�ڴ治��!\n");
					exit( -1 );/* ����Ӧ�ó��� */
				}/* end if */
			}/* end for */
		}/* end if */
		else{
			printf("\nDT_DatasCreat()�ڴ治��!\n");
			exit( -1 ); /* ����Ӧ�ó��� */
		}/* end else */

		dPtr->tAimPtrs = ( d64 ** )malloc( sizeof( d64 * ) * numO ); /* ��̬����һ���洢��������Ŀ�������ָ������	 */
		if ( dPtr->tAimPtrs != NULL ){ /* �ж϶�̬����ָ�������Ƿ�ɹ� */
			for ( i = 0; i < numO; i++ ){
				dPtr->tAimPtrs[ i ] = ( d64 * )malloc( sizeof( d64 ) * numT ); /* ָ�����鶯̬����һά���飬���ɶ�ά���� */

				if ( dPtr->tAimPtrs[ i ] == NULL ){/* �жϲ�������Ŀ�������ά���鶯̬�����Ƿ�Ϊ�� */
					printf( "\nDT_DatasCreat()�ڴ治��!\n" );
					exit( -1 );/* ����Ӧ�ó���*/
				}/* end if */
			}/* end for */
		}/* end if */
		else{
			printf( "\nDT_DatasCreat()�ڴ治��!\n" );
			exit( -1 );/* ����Ӧ�ó��� */
		}/* end else */
	}/* end if */
	else{
		printf( "\nDT_DatasCreat()�ڴ治��!\n" );
		return;
	}/* end else */

	dPtr->creatLabel = 1;	/* �����洢�ṹ������־��1*/
}/* end function  DT_DatasCreat */

void DT_InputTrainSamples( DT_TypeDefPtr dPtr )
{
	i32 i;																															/* ��ʱ����																			*/
	i32 j;																															/* ��ʱ����																			*/
	i32 numI = dPtr->numOfInput;																				/* ��ȡ��������ά��															*/
	i32 numO = dPtr->numOfOutput;																			/* ��ȡ�������ά��															*/
	i32 numS = dPtr->numOfSample;																			/* ��ȡѵ����������															*/
	
	if( dPtr->creatLabel == 1 ){																						/* �ж������洢�ṹ�Ƿ񴴽�											*/
		printf("Enter the input of trainnning samples,"
				  "total of trainning samples of you setted were %d, "
				  "dimentions were %d\n", numS, numI);													/* �ı���ʾ��Ϣ																	*/
		for( i = 0; i < numS; i++ ){
			for( j = 0; j < numI; j++ ){
				scanf_s("%lf", &dPtr->samPtrs[ j ][ i ] );														/* ����ѵ��������������													*/
			}/* end for */
		}/* end for */

		printf("Enter the aim output of trainning samples, "
				  "total of trainning samples of you setted were %d, "
				  "dimention of output were %d:\n", numS, numO);									/* �ı���ʾ��Ϣ																	*/
		for( i = 0; i < numS; i++ ){
			for( j = 0; j < numO; j++ ){
				scanf_s("%lf", &dPtr->aimPtrs[ j ][ i ]);														/* ����ѵ������Ŀ�����													*/
			}/* end for */
		}/* end for */
	}/* end if */
	else{
		printf( "Could not enter the samples! "
				   "Memery for sample did not allocate!\n");												/*	�ı���ʾ��Ϣ																*/
	}/* end else */
}/****************************************************************** end function InputTrainSamples *********************************************************************/

void DT_InputTestSamples( DT_TypeDefPtr dPtr )
{
	i32 i;																															/* ��ʱ����																			*/
	i32 j;																															/* ��ʱ����																			*/
	i32 numI = dPtr->numOfInput;																				/* ��ȡ��������ά��															*/
	i32 numO = dPtr->numOfOutput;																			/* ��ȡ�������ά��															*/
	i32 numT = dPtr->numOfTSample;																		/* ��ȡ������������															*/

	if( dPtr->creatLabel == 1 ){																						/* �ж������洢�ṹ�Ƿ񴴽�											*/
		printf("Enter the input of test samples,"
				  " total of test samples of you setted were %d, "
				  " dimentions were %d\n", numT, numI);													/* �ı���ʾ��Ϣ																	*/
		for( i = 0; i < numT; i++ ){
			for( j = 0; j < numI; j++ ){
				scanf_s("%lf", &dPtr->tSamPtrs[ j ][ i ]);														/* �������������������													*/
			}/* end for */
		}/* end for */

		printf("Enter the aim output of test samples, "
				  "total of test samples of you setted were %d, "
				  "dimention of output were %d:\n", numT, numO);									/* �ı���ʾ��Ϣ																	*/
		for( i = 0; i < numT; i++ ){
			for( j = 0; j < numO; j++ ){
				scanf_s("%lf", &dPtr->tAimPtrs[ j ][ i ]);														/* �����������Ŀ�����													*/
			}/* end for */
		}/* end for */
	}/* end if */
	else{
		printf("Please allocate memery for samples!\n");											   /* �ı���ʾ��Ϣ																	*/
	}/* end else */
}/******************************************************************* end function InputTestSamples *********************************************************************/

void DT_DatasInit( DT_TypeDefPtr  dPtr )
{
	i32 i;																														 /* ��ʱ����																			*/
	i32 j;																														 /* ��ʱ����																			*/
	i32 numI   = dPtr->numOfInput;																			 /* ��ȡ��������ά��															*/
	i32 numO = dPtr->numOfOutput;																		 /* ��ȡ�������ά��															*/
	i32 numS  = dPtr->numOfSample;																		 /* ��ȡѵ����������															*/
	i32 numT = dPtr->numOfTSample;																	 /* ��ȡ������������															*/

	for( i = 0; i < numS; i++ ){
		for(  j = 0; j < numI; j++ ){
			dPtr->samPtrs[ j ][ i ] = 0.0;																		 /*	��ʼ��ѵ�������洢��ά����										*/
		}/* end for */

		for( j = 0; j < numO; j++ ){
			dPtr->aimPtrs[ j ][ i ] = 0.0;																		 /* ��ʼ��ѵ������Ŀ������洢��λ����						*/
		}/* end for */

		dPtr->seqPtr[ i ] = 0;																						/* ��ʼ�������������															*/
	}/* end for */

	for( i = 0; i < numT; i++ ){
		for( j = 0; j < numI; j++ ){
			dPtr->tSamPtrs[ j ][ i ] = 0.0;																	   /* ��ʼ����������Ŀ������洢��λ����							*/
		}/*  end for */

		for( j = 0; j < numO; j++ ){
			dPtr->tAimPtrs[ j ][ i ] = 0.0;																	   /* ��ʼ����������Ŀ������洢��λ����						   */
		}/* end for */
	}/* end for */
}/******************************************************************* end function DataInit *********************************************************************************/

void DT_DatasDeInit( DT_TypeDefPtr dPtr )
{
	i32 i;																													 /* ��ʱ����																				*/
	i32 numI		= dPtr->numOfInput;																	 /* ��ȡ��������ά��																*/
	i32 numO		= dPtr->numOfOutput;																 /* ��ȡ�������ά��																*/
	i32 numS		= dPtr->numOfSample;																 /* ��ȡѵ����������																*/
	i32 numT		= dPtr->numOfTSample;														     /* ��ȡ������������																*/

	for( i = 0; i < numI; i++ ){
		free( dPtr->samPtrs[ i ]);																			/* �ͷŴ洢ѵ���������ݶ�ά����	�ڴ�								*/
		free( dPtr->tSamPtrs[ i ]);																			/* �ͷŴ洢�����������ݶ�ά�����ڴ�									*/
	}/* end for */

	free( dPtr->samPtrs);																						/*	�ͷ�ѵ���������ݵ�ָ������											*/
	free( dPtr->tSamPtrs);																					/*	�ͷŲ����������ݵ�ָ������											*/

	for( i = 0; i < numO; i++ ){
		free( dPtr->aimPtrs[ i ] );																			/* �ͷŴ洢ѵ������Ŀ������Ķ�ά�����ڴ�						*/
		free( dPtr->tAimPtrs[ i ] );																			/* �ͷŴ洢��������Ŀ������Ķ�ά�����ڴ�						*/
	}/* end for */

	free( dPtr->aimPtrs );																						/*	�ͷ�ѵ������Ŀ�������ָ������									*/
	free( dPtr->tAimPtrs );																					/*	�ͷŲ�������Ŀ�������ָ������									*/
	free( dPtr->seqPtr );																						/* �ͷ��������һά�����ڴ�													*/

	dPtr->creatLabel				= 0;																			/* ��ʼ��������־																		*/
	dPtr->samParmLabel		= 0;																			/* ��ʼ��������־																		*/
	dPtr->numOfInput			= 0;																			/* ��ʼ������ά��																		*/
	dPtr->numOfOutput		= 0;																			/* ��ʼ�����ά��																		*/
	dPtr->numOfSample		= 0;																			/* ��ʼ��ѵ����������																*/
	dPtr->numOfTSample	= 0;																			/* ��ʼ��������������																*/
}/******************************************************************* end function DatasDeInit *****************************************************************************/

void DT_PrintTrainSamples( DT_TypeDefPtr dPtr )
{
	i32 i;																													/* ��ʱ����																					*/
	i32 j;																													/* ��ʱ����																					*/
	i32 k;																												/* ��ʱ����																					*/
	i32 temp1 = 0;																									/* ��ʱ����																					*/
	i32 temp2 = 0;																									/* ��ʱ����																					*/
	i32 temp3 = 0;																									/* ��ʱ����																					*/
	i32 temp4 = 0;																									/* ��ʱ����																					*/
	i32 numI		= dPtr->numOfInput;
	i32 numO		= dPtr->numOfOutput;
	i32 numS		= dPtr->numOfSample;

	temp1 = numS / 10;
	temp2 = numS % 10;

	if( temp1 != 0 ){
		temp4 = 10;
		for( k = 0; k < temp1; k++ ){
			printf( "\nInput of trainning samples between"
					   " %d and %d are :\n", temp3 + 1, temp4 );

			for( i = 0; i < numI; i++ ){
				for( j = temp3; j < temp4; j++ ){
					printf("%-5.3lf ", dPtr->samPtrs[ i ][ j ]);
				}/* end for */
				printf("\n");
			}/* end for */

			printf( "\nAim output of trainning samples between"
					   " %d and %d are :\n", temp3 + 1, temp4 );

			for( i = 0; i < numO; i++ ){
				for( j = temp3; j < temp4; j++ ){
					printf("%-5.3lf ", dPtr->aimPtrs[ i ][ j ]);
				}/* end for */
				printf("\n");
			}/* end for */

			temp3 = temp4;
			temp4 += 10;
		}/* end for */
	}/* end if */

	if( temp2 != 0 ){
			temp3 = temp4;
			temp4 += temp2;

			printf( "\nInput of trainning samples between "
				       "%d and %d are :\n", temp3 + 1, temp4 );

			for( i = 0; i < numI; i++ ){
				for( j = temp3; j < temp4; j++ ){
					printf("%-5.3lf ", dPtr->samPtrs[ i ][ j ]);
				}/* end for */
				printf("\n");
			}/* end for */

			printf( "\nAim output of trainning samples between "
					   "%d and %d are :\n", temp3 + 1, temp4 );

			for( i = 0; i < numO; i++ ){
				for( j = temp3; j < temp4; j++ ){
					printf("%-5.3lf ", dPtr->aimPtrs[ i ][ j ]);
				}/* end for */
				printf("\n");
			}/* end for */
		}/* end if */

	if( temp1 == 0 && temp2 == 0 ){
		printf( "No trainning samples exist!\n" );
	}/* end if */
}/* end function printSamples */

void DT_PrintTestSamples( DT_TypeDefPtr dPtr )
{
	i32 i;
	i32 j;
	i32 k;
	i32 temp1 = 0;
	i32 temp2 = 0;
	i32 temp3 = 0;
	i32 temp4 = 0;
	i32 numI		= dPtr->numOfInput;
	i32 numO		= dPtr->numOfOutput;
	i32 numT		= dPtr->numOfTSample;

	temp1 = numT / 10;
	temp2 = numT % 10;

	if( temp1 != 0 ){
		temp4 = 10;

		for( k = 0; k < temp1; k++ ){
			printf( "\nInput of test samples between "
					   "%d and %d are :\n", temp3 + 1, temp4 );

			for( i = 0; i < numI; i++ ){
				for( j = temp3; j < temp4; j++ ){
					printf("%-5.3lf ", dPtr->tSamPtrs[ i ][ j ]);
				}/* end for */
				printf("\n");
			}/* end for */

			printf( "\nAim output of test samples between "
				       "%d and %d are :\n", temp3 + 1, temp4 );

			for( i = 0; i < numO; i++ ){
				for( j = temp3; j < temp4; j++ ){
					printf("%-5.3lf ", dPtr->tAimPtrs[ i ][ j ]);
				}/* end for */
				printf("\n");
			}/* end for */

			temp3 = temp4;
			temp4 += 10;
		}/* end for */
	}/* end if */

	if( temp2 != 0 ){
			temp3 = temp4;
			temp4 += temp2;

			printf( "\nInput of test samples between "
					   "%d and %d are :\n", temp3 + 1, temp4 );

			for( i = 0; i < numI; i++ ){
				for( j = temp3; j < temp4; j++ ){
					printf("%-5.3lf ", dPtr->tSamPtrs[ i ][ j ]);
				}/* end for */
				printf("\n");
			}/* end for */

			printf( "\nAim output of test samples between "
					   "%d and %d are :\n", temp3 + 1, temp4 );

			for( i = 0; i < numO; i++ ){
				for( j = temp3; j < temp4; j++ ){
					printf("%-5.3lf ", dPtr->tAimPtrs[ i ][ j ]);
				}/* end for */
				printf("\n");
			}/* end for */
		}/* end if */

	if( temp1 == 0 && temp2 == 0 ){
		printf( "No test samples exist!\n" );
	}/* end if */
}/* end function printTestSamples */

void DT_PrintDatasParams( DT_TypeDefPtr dPtr )
{
	printf("\nInput dimentions of samples: %d\n"
			  "\nOutput dimentions of samples: %d\n"
			  "\nTotal of trainning samples: %d\n"
			  "\nTotal of test samples: %d\n", 
			  dPtr->numOfInput, dPtr->numOfOutput, 
			  dPtr->numOfSample, dPtr->numOfTSample);
}/* end function printDatasParams */