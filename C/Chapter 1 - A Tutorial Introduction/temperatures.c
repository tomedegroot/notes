#include <stdio.h>

/* print Fahrenheit-Celsius table for fahr = 0, 20 ..., 300 */

/* Formula for conversion: C = (5/9) * (F-32) */

int main()
{
	float fahr, celsius;
	int lower, upper, step;
	
	lower = 0;	/* lower limit of temperature table */
	upper = 300;	/* upper limit */
	step = 20;	/* step size */

	fahr = lower;
	
	while(fahr <= upper) {
		//celsius = 5  * (fahr-32) / 9;
		celsius = (5.0/9.0)  * (fahr-32.0);
		//printf("%f\t%f\n", fahr, celsius);
		printf("%3.0f\t%6.1f\n", fahr, celsius);
		fahr = fahr + step;
	}

	return 0;

}
