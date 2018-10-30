#include "random.h"

#include <time.h>       /* time */
#include <stdlib.h>     /* srand, rand */
#include <ctime>

float makeRandom() {
	/*int a;

	srand(time(NULL));

	a = rand() % 10;
	
	return a;*/
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0) - 1.0;
}