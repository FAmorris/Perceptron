/**
   ******************************************************************************************************************************************************
   * @file		peceptron.c
   * @author	Morris
   * @version	V1.0
   * @date		2018��4��20��21:08:19 ��VS2017��Debugģʽ��������
   * @brief		ͳ��ѧϰ���������еĸ�֪������֪����
   ******************************************************************************************************************************************************
   * @attention (1)Ӧ��-1��+1�������������б�ǩ
   *                     (2)Ӧ����֪�����ά������Ϊ1�����������ڱ�������δʵ�֣�ֻ֧��2���
   *                     (3)��������ô��и��µķ�ʽ
   *                     (4)��Ȩֵ���·�ʽ�п��Ż�Ϊ���Ӷ�����
   *                     (5)�ɲ����ҵ�CSDN���ͽ����Ķ���
   *                     ��ַ: https://blog.csdn.net/weixin_41592704/article/details/80024234
   *
   ******************************************************************************************************************************************************
   */

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "../inc/perceptron.h"

/**
 * @brief		�ж�һ�����Ƿ���Inf����NaN
 * @param		d64 sum Ҫ�жϵ���
 * @retval		i32 �������ݣ�1��ʾ������ 0��ʾ������
 */
static i32 PCPT__IsNormal( d64 sum )
{
	if( sum == sum && sum != ( sum + 1.0 ) ){/* �ж�һ�����Ƿ�����������	 */
		return 1; /* ������������1 */
	}/* end if */
	else{
		return 0; /* ���򷵻�0 */
	}/* end else */
}/* end function PCPTPCPT__IsNormal */

/**
 * @brief		�������-1~+1֮���С��
 * @param		d64 sum Ҫ�жϵ���
 * @retval		d64���ͣ����ɵ������
 */
static d64 PCPT_RandOfd64( void )/* ������������� */
{
	return ( -1 + rand() % 2 + ( d64 )rand() / RAND_MAX ); /* �������һ��-1~1֮���С�� */
}/*end function PCPT_randOfd64 */

/**
 * @brief		���ź���
 * @param		d64 sum ����
 * @retval		i32�������ݣ�+1��-1
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
 * @brief		��֪�������趨����
 * @param		PCPT_TypeDefPtr pPtr ��֪���ṹ��ָ��
 * @retval		��
 */
void PCPT_SetPerceptronParam( PCPT_TypeDefPtr pPtr )
{
	i32 num1;	
	d64 lr;

	do{
		printf("\n�������ѵ���غ������˳�-1��:\n");
		scanf_s("%d", &num1);	/* ����ѵ�����غ��� */
		if( num1 == -1 ){/* �ж��Ƿ�ѡ���˳���֪�������趨 */
			return;	
		}/* end if */

		if( num1 < 0 ){
			printf("\n���������0����!\n ");
		}/* end if */
	}while( num1 < 0 ); /* ѭ��ֱ��������ȷ��ѡ���˳� */
	pPtr->epoch = num1;/* �趨���ѵ���غ���*/

	do{
		printf("\n����ѧϰ�ʣ��˳�-1��:\n");
		scanf_s("%lf", &lr);/* ����ѧϰ�� */
		if( -0.9999 > lr && lr > -1.0001 ){ /* �ж��Ƿ�ѡ���˳���֪�������趨 */
			return;	
		}/* end if */

		if( lr < 0 || lr > 1.0 ){ /* �ж�ѧϰ�������Ƿ���� */											
			printf("\n����ѧϰ�ʴ���0��С��1��\n ");
		}/* end if */
	}while( lr < 0 || lr > 1.0 );/* ѭ��ֱ��������ȷ��ѡ���˳� */
	pPtr->learnRate = lr;	/* �趨ѧϰ��	 */
	
	pPtr->parameter.numOfInput = pPtr->perceptData.numOfInput;
	pPtr->parameter.numOfOutput = pPtr->perceptData.numOfOutput;

	pPtr->pcptParmLabel = 1; /* ��֪�������趨��ɱ�־�� */
}/*end function PCPT_SetPerceptronParam */

/**
 * @brief		��֪�����ɺ���
 * @param		PCPT_TypeDefPtr pPtr ��֪���ṹ��ָ��
 * @retval		��
 */
void PCPT_PerceptronCreat( PCPT_TypeDefPtr pPtr )
{
	i32 i;
	i32 numI =pPtr->parameter.numOfInput;
	i32 numO =  pPtr->parameter.numOfOutput;

	if( pPtr->pcptParmLabel == 1 ){/* �жϸ�֪�������Ƿ��趨 */
		pPtr->inPtr = ( d64 * )malloc( sizeof( d64 ) * ( numI + 1 ) ); /* ��̬һά�������ڴ洢��֪������ */

		if( pPtr->inPtr == NULL ){ /* �жϴ洢����һά�����ڴ��Ƿ���� */
			printf( "\n%dPCPT_PerceptronCreat�����ڴ治��!\n", __LINE__ );
			exit( -1 );
		}/* end if */

		pPtr->ouPtr = ( d64 * )malloc( sizeof( d64 ) * numO );/* ��̬һά�������ڴ洢��֪����� */
	
		if( pPtr->ouPtr == NULL ){ /* �жϴ洢����һά�����ڴ��Ƿ���� */
			printf( "\n%dPCPT_PerceptronCreat�����ڴ治��!\n", __LINE__ );
			exit( -1 );
		}/* end if */

		pPtr->wPtrs = ( d64 ** )malloc( sizeof( d64 * ) * ( numI + 1 ) );/* ��ָ̬���������ڴ洢Ȩֵһά����*/

		if( pPtr->wPtrs != NULL ){ /* �ж�ָ�������ڴ�����Ƿ�ɹ� */
			for( i = 0; i <= numI; i++ ){
				pPtr->wPtrs[ i ] = ( d64 * )malloc( sizeof( d64 ) * numO ); /* ��̬һά��������Ȩֵ�洢��ά���� */

				if( pPtr->wPtrs[ i ] == NULL ){ /* �ж�Ȩֵһά�����ڴ��Ƿ����ɹ�	*/
					printf( "\n%dPCPT_PerceptronCreat�����ڴ治��!\n", __LINE__ );
					exit( -1 );
				}/* end if */
			}/* end for */
		}/* end if */
		else{																																	
			printf( "\n%dPCPT_PerceptronCreat�����ڴ治��!\n", __LINE__ );	
			exit( -1 );
		}/* end else */
	}/* end if */
	else{
		printf("\n��֪������ʧ�ܣ���֪������δ���ã�\n");
		return;	
	}/* end else */

	pPtr->pcptCreatLabel = 1; /* ��֪��������־�� */
}/* end function PCPT_PerceptronCreat */

/**
 * @brief		��֪����ʼ������
 * @param		PCPT_TypeDefPtr pPtr ��֪���ṹ��ָ��
 * @retval		��
 */
void PCPT_PerceptronInit( PCPT_TypeDefPtr pPtr )
{
	i32 i;
	i32 j;
	i32 numI = pPtr->parameter.numOfInput;
	i32 numO = pPtr->parameter.numOfOutput;
	
	if( pPtr->pcptCreatLabel == 1 ){ /* �жϸ�֪���Ƿ񴴽� */
		for( i = 0; i < ( numI + 1 ); i++ ){
			if( i == 0 ){
				pPtr->inPtr[ i ] = 1.0; /* ������趨ά����1ά���̶�ֵ1 */
			}/* end if */
			else{
				pPtr->inPtr[ i ] = 0.0; /* ��֪�������ʼ��Ϊ0 */
			}/* end else */
		}/* end for */

		for( i = 0; i < numO; i++ ){
			pPtr->ouPtr[ i ] = 0.0;	 /* ��֪�������ʼ��Ϊ0 */
		}/* end for */

		for( i = 0; i < numO; i++ ){
			for( j = 0; j < ( numI + 1 ); j++ ){
				if( j == 0 ){
					pPtr->wPtrs[ j ][ i ] = 1.0;	 /* ��֪��Ȩֵ���󣬵�0��Ϊƫ�� */
				}/* end if */
				else{
					pPtr->wPtrs[ j ][ i ] = PCPT_RandOfd64(); /* ��֪��Ȩֵ��ʼ��Ϊ-1~+1����ֵ */
				}/* end else */
			}/* end for */
		}/* end for */
	}/* end if */
	else{
		printf("\n��ʼ��ʧ�ܣ���֪�������ڣ�\n");
		return;	
	}/* end else */
}/* end function perceptronInit */

/**
 * @brief		��֪��ѵ������
 * @param		PCPT_TypeDefPtr pPtr ��֪���ṹ��ָ��
 * @retval		��
 */
void PCPT_PerceptronTrain( PCPT_TypeDefPtr pPtr )
{
	i32 i, j, n, k;
	i32 count = 0;/* ��ʱ������������������������ */	
	d64 sum = 0;/* ��ʱ�������洢��֪������ֵ*/
	d64 temp = 0;

	if( pPtr->pcptCreatLabel == 1 && pPtr->perceptData.creatLabel == 1 ){ /* �жϸ�֪�������ݴ洢����Ƿ񴴽� */
		for( n = 0; n < pPtr->epoch; n++ ){ /* �����ѵ���غ���ѵ����֪�� */

			DT_randForSequence( &pPtr->perceptData );/* ��������ѵ������ʱ���ֵ��������	*/
			
			count = 0; /* ����������������� */
			sum = 0; /* ��֪������ֵ���� */	
			for( k = 0; k < pPtr->perceptData.numOfSample; k++ ){
				for( i = 1; i <= pPtr->perceptData.numOfInput; i++ ){
					pPtr->inPtr[ i ] = pPtr->perceptData.samPtrs[ i - 1 ]
						[ pPtr->perceptData.seqPtr[ k ] ]; /* �����ɵ��������ѡȡѵ������ʵ�� */
				}/* end for */

				for( i = 0; i < pPtr->parameter.numOfOutput; i++ ){
					for( j = 0; j <= pPtr->parameter.numOfInput; j++ ){
						temp = pPtr->inPtr[ j ] * pPtr->wPtrs[ j ][ i ]; /* ������Ȩֵ��ƫ������ */

						if( !PCPT__IsNormal( temp ) ) temp = 0.0;

						sum += temp; /* �����յ��ֲ��� */
					}/* end for */

					pPtr->ouPtr[ i ] = PCPT_SignFunction( sum ); /* �����֪�����ֵ */

					sum = 0.0; /* �յ��ֲ������㣬������һ������ */

					temp = pPtr->ouPtr[ i ] * pPtr->perceptData.aimPtrs[ i ]
						[ pPtr->perceptData.seqPtr[ k ] ]; /* �жϸ�֪���Ƿ�ѵ�����������	 */

					if( !PCPT__IsNormal( temp ) ) temp = 0.0;																												

					if( temp <= 0 ){ /* ��������������˵����֪������� */
						for( j = 0; j <= pPtr->parameter.numOfInput; j++ ){
							temp = pPtr->learnRate * pPtr->perceptData.aimPtrs[ i ]
								[ pPtr->perceptData.seqPtr[ k ] ] * pPtr->inPtr[ j ]; /* �������ɲ����仯�� */

							if( !PCPT__IsNormal( temp ) ) temp = 0.0;

							pPtr->wPtrs[ j ][ i ] += temp;	 /* �������ɲ��� */
						}/* end for */

						count++; /* ͳ��ѵ�������е�������� */
					}/* end if */
				}/* end for */
			}/* end for */

			printf("�غ�: %d\n", n);

			if( count == 0 ){ /* �ж�ѵ�������Ƿ�ȫ��������ȷ*/
				printf("\n����ѵ��������ȷ����!\n");
				break; /* ����ѵ���غ�forѭ�� */
			}/* end if */
		}/* end for */
	}/* end if */
	else printf("\n���������ݻ��֪��δ����!\n");

}/*  end function perceptronTrain */

/**
 * @brief		��֪�����Ժ���
 * @param		PCPT_TypeDefPtr pPtr ��֪���ṹ��ָ��
 * @retval		��
 */
void PCPT_PerceptronTest( PCPT_TypeDefPtr pPtr )	
{
	i32 i, j, k;
	i32 count = 0;/* �������������ͳ�� */
	d64 temp = 0.0;
	d64 sum = 0.0;  /* ��֪���յ��ֲ��� */
	d64 rate = 0.0;	 /* ����������������� */

	if( pPtr->pcptCreatLabel == 1 && pPtr->perceptData.creatLabel == 1 ){/* �жϸ�֪�������ݴ洢�ṹ�Ƿ񴴽�	*/

		for( k = 0; k < pPtr->perceptData.numOfTSample; k++ ){
			for( i = 1; i <= pPtr->parameter.numOfInput; i++ ){
				pPtr->inPtr[ i ] = pPtr->perceptData.tSamPtrs[ i - 1 ][ k ];	/* ��ȡ��������ĳ��ʵ������ */
			}/* end for */

			for( i = 0; i < pPtr->parameter.numOfOutput; i++ ){
				for( j = 0; j <= pPtr->parameter.numOfInput; j++ ){
					temp = pPtr->wPtrs[ j ][ i ] * pPtr->inPtr[ j ]; /* ������Ȩֵ��ƫ������ */

					if( !PCPT__IsNormal( temp ) ) temp = 0.0;

					sum += temp;	/* �����յ��ֲ��� */	
				}/* end for */

				pPtr->ouPtr[ i ] = PCPT_SignFunction( sum );/* �����֪�����*/
				sum = 0.0;	/* �յ��ֲ������㣬������һ�μ��� */

				if( pPtr->ouPtr[ i ] != pPtr->perceptData.tAimPtrs[ i ][ k ] ){ /*�жϸ�֪��������������Ŀ�����*/
					count++; /*��������������Ӵ��������*/
				}/* end if */
			}/* end for */
		}/* end for */

		rate = ( d64 )count / pPtr->perceptData.numOfTSample * 100.0; /*�����֪���Բ��������ķ��������*/

		printf("\n�����������������: %.3lf%%\n", rate);

		rate = 100.0 - rate;/* ���������ȷ�� */

		printf("\n��������������ȷ��: %.3lf%%\n", rate);
	}/* end if */
	else printf("\n��֪��δ����!\n");

}/* end function PCPT_PerceptronTest */

/**
 * @brief		��֪��Ԥ�����뺯��
 * @param		PCPT_TypeDefPtr pPtr ��֪���ṹ��ָ��
 * @retval		��
 */
void PCPT_UsePerceptron( PCPT_TypeDefPtr pPtr )
{
	i32 i, j;
	d64 sum = 0.0;	/* �յ��ֲ��� */
	d64 temp = 0.0;

	if( pPtr->pcptCreatLabel == 1 && pPtr->perceptData.creatLabel == 1 ){	/* �жϸ�֪�������ݴ洢�ṹ�Ƿ񴴽� */
		printf("\n��������:\n");
		for( i = 1; i <= pPtr->parameter.numOfInput; i++ ){
			scanf_s("%lf", &pPtr->inPtr[ i ]); /* ��������ʵ��������*/
		}/* end for */

		for( i = 0; i < pPtr->parameter.numOfOutput; i++ ){
			for( j = 0; j <= pPtr->parameter.numOfInput; j++ ){
				temp = pPtr->wPtrs[ j ][ i ] * pPtr->inPtr[ j ];/* ����������Ȩֵ������ƫ�������� */

				if( !PCPT__IsNormal( temp ) ) temp = 0.0;																				

				sum += temp; /* �����յ��ֲ��� */
			}/* end for */

			pPtr->ouPtr[ i ]  = PCPT_SignFunction( sum );	 /* ������� */
			sum = 0.0;	/* ��ʱ�������㣬�����´����� */


		}/* end for */

		printf("\n��֪�����:\n");
		for( i = 0; i < pPtr->parameter.numOfOutput; i++ ){
			printf("%.3lf\n", pPtr->ouPtr[ i ]); 
		}/* end for */
	}/* end if */
	else printf("\n��֪��δ����!\n");
}/* end function PCPT_UsePerceptron */

/**
 * @brief		��֪����ʾȨֵ����
 * @param		PCPT_TypeDefPtr pPtr ��֪���ṹ��ָ��
 * @retval		��
 */
void PCPT_PrintWeights( PCPT_TypeDefPtr pPtr )
{
	i32 i, j, n;
	i32 numI = pPtr->parameter.numOfInput;
	i32 numO = pPtr->parameter.numOfOutput;
	i32 temp1 = 0;	/* ����ʾ��ҳ�� */
	i32 temp2 = 0; /* ����һҳ��ʣ���� */
	i32 temp3 = 0; /* ��ʼ��ʾ��λ�� */
	i32 temp4 = 0;	 /* ��ֹ��ʾ��λ�� */

	temp1 = numO / 10; /* ����ÿҳ��10��Ȩֵ��������ʾ��ҳ */
	temp2 = numO % 10;	 /*ʣ����ٸ�Ȩֵ���� */

	if( pPtr->pcptCreatLabel == 1 ){ /* �жϸ�֪���Ƿ񴴽� */
		if( temp1 != 0 ){ /* �ж��Ƿ���10Ϊ��������ʾҳ�� */
			for( n = 0; n < temp1; n++ ){
				temp3 = temp4; /* ����һ�ν�����λ�û�ҳ��ʾ */
				temp4 += 10; /* ������ֹ��ʾ��λ�� */

				printf("\nȨֵ %d - %d :\n", temp3 + 1, temp4);

				for( i = 1; i <= numI; i++ ){
					for( j = temp3; j < temp4; j++ ){
						printf("%8.3lf ", pPtr->wPtrs[ i ][ j ]);
					}/* end for */
					printf("\n");
				}/* end for */
			}/* end for */
		}/* end if */

		if( temp2 != 0 ){ /* �ж�ʣ��ĸ����Ƿ�Ϊ0 */
			temp3 = temp4; /* ���ϴ���ʾ��λ�û�ҳ��ʾ */
			temp4 += temp2; /* ������ֹ��ʾ��λ�� */
			
			printf("\nȨֵ %d - %d :\n", temp3 + 1, temp4);

			for( i = 1; i <= numI; i++ ){
				for( j = temp3; j < temp4; j++ ){
					printf("%8.3lf ", pPtr->wPtrs[ i ][ j ]);
				}/* end for */
				printf("\n");
			}/* end for */
		}/* end if */
	}/* end if */
	else printf("\n��֪��δ����!\n");

}/* end function PCPT_PrintWeights */

/**
 * @brief		��֪����ʾƫ�ú���
 * @param		PCPT_TypeDefPtr pPtr ��֪���ṹ��ָ��
 * @retval		��
 */
void PCPT_PrintBiases( PCPT_TypeDefPtr pPtr )
{
	i32 i, n;
	i32 temp1 = pPtr->parameter.numOfOutput / 10; /* ������ʾҳ�� */
	i32 temp2 = pPtr->parameter.numOfOutput % 10;	 /* ����ʣ���� */
	i32 temp3 = 0;	 /* ��ʼ��ʾ��λ�� */
	i32 temp4 = 0;	/* ��ֹ��ʾ��λ�� */

	if( pPtr->pcptCreatLabel == 1){/* �жϸ�֪���Ƿ����� */
		if( temp1 != 0 ){/* �ж�����ʾ��ҳ���Ƿ�Ϊ0 */
			for( n = 0; n < temp1; n++ ){
				temp3  = temp4;/* ��ʼ��ʾ��λ�� */
				temp4 += 10; /* ��ֹ��ʾ��λ�� */

				printf("\nƫ�� %d - %d :\n", temp3 + 1, temp4);

				for( i = temp3; i < temp4; i++ ){
					printf("%.3lf\n", pPtr->wPtrs[ 0 ][ i ]);
				}/* end for */
			}/* end for */
		}/* end if */

		if( temp2 != 0 ){ /* �ж�ʣ�����Ƿ�Ϊ0 */

			temp3 = temp4;/* ��ʼ��ʾ��λ�� */
			temp4 += temp2;/* ��ֹ��ʾ��λ��	*/

			printf("\nƫ�� %d - %d :\n", temp3 + 1, temp4);

			for( i = temp3; i < temp4; i++ ){
				printf("%.3lf\n", pPtr->wPtrs[ 0 ][ i ]);
			}/* end for */
		}/* end if */
	}/* end if */
	else{
		printf("\n��֪��δ���ɣ�\n");
	}/* end else */
}/* end function PCPT_PrintBiases */

void PCPT_PrintPerceptronParam( PCPT_TypeDefPtr pPtr )
{
	printf("\n��֪������ά��: %d\n"
			  "\n��֪�����ά��: %d\n"
			  "\n��֪��ѧϰ��: %.3lf\n"
			  "\n��֪�����ѵ���غ���: %d\n", 
			  pPtr->parameter.numOfInput, 
			  pPtr->parameter.numOfOutput,
			  pPtr->learnRate, pPtr->epoch);
}/* end function PCPT_PrintPerceptronParam */

void PCPT_PrintInstructions( i32 *cho )
{
	printf("\n�����ʲô?\n");

	printf("================================\n"
			  "* 1.  �����������ݴ洢�ṹ����.\n"
			  "* 2.  ��ʾ�����洢�ṹ����.\n"
			  "* 3.  ���ø�֪������.\n"
			  "* 4.  ��ʾ��֪������.\n"
			  "* 5.  �����������ݴ洢�ṹ.\n"
			  "* 6.  ���ɸ�֪��.\n"
			  "* 7.  ��ʼ�����ݽṹ.\n"
			  "* 8.  ��ʼ����֪��.\n"
			  "* 9.  ����ѵ������.\n"
			  "* 10. �����������\n"
			  "* 11. ��ʾѵ������.\n"
			  "* 12. ��ʾ��������.\n"
			  "* 13. ��ʾ��֪��Ȩֵ.\n"
			  "* 14. ��ʾ��֪��ƫ��.\n"
			  "* 15. ѵ����֪��.\n"
			  "* 16. ���Ը�֪��.\n"
			  "* 17. ʹ�ø�֪������Ԥ��.\n"
			  "* 0.  �˳�.\n"
			  "================================\n"
			  "�������ѡ��:");
	scanf_s("%d", cho );
}/* end function printInstruction */