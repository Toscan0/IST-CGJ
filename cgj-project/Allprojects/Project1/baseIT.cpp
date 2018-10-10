#include "baseIT.h"

#include <time.h>       /* time */
#include <stdlib.h>     /* srand, rand */


int makeRandom() {
	int a;

	srand(time(NULL));

	a = rand() % 10;
	
	return a;
}