#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Data.h"
#include "perceptron.h"

int main( void )
{
	percetron p;
	int chose = 0;
	int i;

	srand( ( unsigned int )time( NULL ) );

	printInstructions( &chose );

	while( chose ){
		switch( chose ){
			case 1:
				setSampleParameters( &p.perceptData );
				break;
			case 2:
				printDatasParams( &p.perceptData );
				break;
			case 3:
				setPerceptronParam( &p );
				break;
			case 4:
				printPerceptronParam( &p );
				break;
			case 5:
				DatasCreat( &p.perceptData );
				break;
			case 6:
				perceptronCreat( &p );
				break;
			case 7:
				DatasInit( &p.perceptData );
				break;
			case 8:
				perceptronInit( &p );
				break;
			case 9:
				InputTrainSamples( &p.perceptData ); 
				break;
			case 10:
				InputTestSamples( &p.perceptData );
				break;
			case 11:
				printTrainSamples( &p.perceptData );
				break;
			case 12:
				printTestSamples( &p.perceptData );
				break;
			case 13:
				printWeights( &p );
				break;
			case 14:
				printBiases( &p );
				break;
			case 15:
				perceptronInit( &p );
				perceptronTrain( &p );
				break;
			case 16:
				perceptronTest( &p );
				break;
			case 17:
				usePerceptron( &p );
				break;
		}/* end switch */
		printInstructions( &chose );
	}/* end while */
	return 0;
}/* end function main */