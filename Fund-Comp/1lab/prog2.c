#include <stdio.h>
#include <math.h>

int main(){


	// Formula for the difference of energy between two atomic levels
	

	/*
	* This formula is used to understand the movements of an electron 
        * attached to an atom, which can absorb light and change to upper
	* atomic layers or emit light and change to lower layers
	*/


	int Ni, Nf; //initial and final atomic level
	float Rh = -2.18;
	int pwRh = -18; //this constant has too many decimal digits for a double, so I will compute the scientific notation separately (-2.18 * 10 ^ (-18))       	


	printf("\nwhat is the electron's initial level? ");
	scanf("%d", &Ni);
	printf("\nwhat is the electron's final level? ");
	scanf("%d", &Nf);



	float frac = (1 / pow(Nf, 2)) - (1 / pow(Ni, 2));//where we compute the "fractional" part of the equation, that would be too complex to calculate in a single line

	float E = Rh * frac; //calculating the numerical part of scientific notation
	
	while (fabs(E) < 1) {
	
		E = E * 10;
		pwRh = pwRh + 1; //fixing the exponential part of scientific notation, which requires the numerical part to be between 1 and 10.
		

	}

	printf("\nEnergy = %f * 10 ^ %d Joules\n\n", E, pwRh);


	return 0;


}
