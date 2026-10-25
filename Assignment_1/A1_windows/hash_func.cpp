
#include "puzzle.h"
#include <cmath>
#include <assert.h>
#include <string>
#include <queue>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define T_S 1000000000

int main() {
	double frac, c = (sqrt(1.161803))/2;
	int k = 123456780;
	int x = 123456780*c;

	int y=floor(2 * x);

	// int x1 =  k % 1000;
	// int x2 = (k % 1000000)/1000;
	// int x3 = (k % 1000000000)/1000000;
	// int hash = 1000000 *modf(((x1+x2+x3)*1.61803398), &frac);

		//  cout << c << endl << x << endl << y << endl;
		//  cout << x1 << endl << x2 << endl << x3 << endl ;
        //  cout << "hash: " <<  hash << endl;
		 
	// for(int k = 123456780; k <876543210; k++) {
	// 	int x1 =  k % 1000;
	// 	int x2 = (k % 1000000)/1000;
	// 	int x3 = (k % 1000000000)/1000000;
    //     int hash = floor(1000000 *modf(((x1+x2+x3)*1.61803398), &frac));
	// 	cout << " hash value of: " << k << " = " << hash << endl;
	// }

    cout << 123456780 % 1000000000;
		 
}