#include <stdio.h>


int main(){

	int touchdowns, extras, fg, safe;


	//touchdowns, extra points, field goals and safeties
	printf("\nHow many touchdowns? ");
	scanf("%d", &touchdowns);

	printf("\nHow many extra points? ");
	scanf("%d", &extras);

	printf("\nHow many field goals? ");
	scanf("%d", &fg);

	printf("\nHow many safeties? ");
	scanf("%d",  &safe);
	

	int tdPoints = touchdowns * 6;
	int fgPoints = fg * 3;
	int safePoints = safe * 2;
	int total = tdPoints + fgPoints + safePoints + extras;

	printf("The total of points the Irish scored was: %d\n\n", total);

	

	return 0;


}
