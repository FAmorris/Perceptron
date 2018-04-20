#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "./inc/perceptron.h"
#include "./inc/Data.h"

#define MODE 1

int main( void )
{
	PCPT_TypeDef p;
#if !MODE
	int chose = 0;
	int i;
#endif

	srand( ( unsigned int )time( NULL ) );
#if MODE
	DT_SetSampleParameters( &p.perceptData );
	DT_DatasCreat( &p.perceptData );
	DT_DatasInit( &p.perceptData );
	DT_InputTrainSamples( &p.perceptData ); 
	DT_InputTestSamples( &p.perceptData );

#if 0 /* 可选择是否显示样本 */
	DT_PrintTrainSamples( &p.perceptData );
	DT_InputTestSamples( &p.perceptData );
#endif

	PCPT_SetPerceptronParam( &p );
	PCPT_PerceptronInit( &p );
	PCPT_PerceptronTrain( &p );
	PCPT_PerceptronTest( &p );
	PCPT_UsePerceptron( &p );

#if 0/* 可选择是否显示参数 */
	PCPT_PrintWeights( &p );
	PCPT_PrintBiases( &p );
#endif

#else
	PCPT_PrintInstructions( &chose );
	while( chose ){
		switch( chose ){
			case 1:
				DT_SetSampleParameters( &p.perceptData );
				break;
			case 2:
				DT_PrintDatasParams( &p.perceptData );
				break;
			case 3:
				PCPT_SetPerceptronParam( &p );
				break;
			case 4:
				PCPT_PrintPerceptronParam( &p );
				break;
			case 5:
				DT_DatasCreat( &p.perceptData );
				break;
			case 6:
				PCPT_PerceptronCreat( &p );
				break;
			case 7:
				DT_DatasInit( &p.perceptData );
				break;
			case 8:
				PCPT_PerceptronInit( &p );
				break;
			case 9:
				DT_InputTrainSamples( &p.perceptData ); 
				break;
			case 10:
				DT_InputTestSamples( &p.perceptData );
				break;
			case 11:
				DT_PrintTrainSamples( &p.perceptData );
				break;
			case 12:
				DT_PrintTestSamples( &p.perceptData );
				break;
			case 13:
				PCPT_PrintWeights( &p );
				break;
			case 14:
				PCPT_PrintBiases( &p );
				break;
			case 15:
				PCPT_PerceptronInit( &p );
				PCPT_PerceptronTrain( &p );
				break;
			case 16:
				PCPT_PerceptronTest( &p );
				break;
			case 17:
				PCPT_UsePerceptron( &p );
				break;
		}/* end switch */
		PCPT_PrintInstructions( &chose );
	}/* end while */
#endif
	return 0;
}/* end function main */