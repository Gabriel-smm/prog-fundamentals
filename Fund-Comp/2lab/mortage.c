#include <stdio.h>
#include <math.h>


int main (){


	float princ, y_interest, m_pay;// asking the main inputs: the initial amount, the yearly interest rate and the desired monthly payment
	printf("\nWhat is the principal (initial amount) in US$? ");
	scanf("%f", &princ);
	printf("\nWhat is the Yearly Interest rate (in %)? ");
	scanf("%f", &y_interest);
	printf("\nWhat is the desired monthly payment in US$? ");
	scanf("%f", &m_pay);

	int stop = 1; //used to verify if the monthly payment can surpass the monthly interest

	float m_interest = y_interest / 1200; //after search, I dicovered that the nominal monthly rate is given by a simple division in US
	float interest = m_interest * princ; //monthly interest paid
	float interest_t = interest; //variable which will be used to sum all the interest paid
	float princ1 = princ; //variable which will be used to store the principal in the end


       	if (m_pay < interest){ 
        	printf("\nError: The monthly payment is not enough to cover the interest.\n");
		stop = 0;
	}
	
               
	int i = 0;

	while(princ > 0 && stop){
		
		if (i == 0) //it will run just 1 time
			printf("Month     Payment    Interest      Balance\n");
			
		

		i++;
		princ = princ - (m_pay - interest);
		printf("%3d       ",i); // display the month
		printf("$%7.2f    $%5.2f     $%10.2f\n", m_pay, interest, princ); //display all the numbers with their specific format 
		
		interest = m_interest * princ;	
		interest_t = interest_t + interest;

		if ((m_pay + interest) > princ){
			float total_p = princ1 + interest_t;
			m_pay = princ + interest;
			princ = 0;
			i++;
                	printf("%3d       ",i);
                	printf("$%7.2f    $%5.2f     $%10.2f\n", m_pay, interest, princ);
			int total_y = floor(i/12);
			int total_m = i % 12;
			printf("\nYou paid a total of $%.2f over %d years and %d months.\n", total_p, total_y, total_m); 
                        break;}}

	return 0;
}
