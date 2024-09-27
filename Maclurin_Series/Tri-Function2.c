#include <stdio.h>
#include <stdlib.h>

typedef struct { // above/below
	long long above;
	long long below;
} Fraction;

// declaration
long long FindGCD(long long, long long); 
long long Factorial(long long);
void cancellate(Fraction *);
Fraction addition(Fraction, Fraction);
Fraction multiple(Fraction, Fraction);
Fraction divide(Fraction, Fraction);

long double exponential(long double, int);
// declaration

// main
int main() {
	
	// declare variables
	const long double pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975665933446128475648233786783165271201909145648566923460348610454326648213393607260249141273724587; // to use Characteristic of Periodic Function : sin x - pi*2 = sin x, and why are these digits so many is to get maximum accuracy.

	Fraction * COEFs_of_SIN;
	Fraction * COEFs_of_COS;
	Fraction * COEFs_of_TAN;

	long long const n = 7;
	long long i, j;
	long double q;
	long long g;

	long double input;
	long double x;
	long double sin, cos, tan;

	// declare variables
	// printf("How many General terms of Taylor's Series of Tangent which will be calculated? : ");
	// scanf("%lld", &n);

	COEFs_of_SIN = (Fraction *) malloc(sizeof(Fraction)*n);
	COEFs_of_COS = (Fraction *) malloc(sizeof(Fraction)*n);
	COEFs_of_TAN = (Fraction *) malloc(sizeof(Fraction)*n);


	for ( i = 0; i < n; i++ ) {
		if ( i % 2 ) // i is odd
			(*(COEFs_of_SIN + i)).above = -1;
		else
			(*(COEFs_of_SIN + i)).above = 1;
		(*(COEFs_of_SIN + i )).below = Factorial(2*i + 1);
	}

	// Calculated Sin

	for ( i = 0; i < n; i++ ) {
		if ( i % 2 ) // i is odd
			(*(COEFs_of_COS + i)).above = -1;
		else
			(*(COEFs_of_COS + i)).above = 1;
		(*(COEFs_of_COS + i)).below = Factorial(2*i);
	}
	// printf("Sinx = \n");

	// Calculated Cos

	// for ( i = 0; i < n-1; i++ )
	// 	printf("(%lld / %lld)x^%lld\n+", (*(COEFs_of_SIN + i)).above, (*(COEFs_of_SIN + i)).below, 2*i + 1);
	// printf("(%lld / %lld)x^%lld\n", (*(COEFs_of_SIN + i)).above, (*(COEFs_of_SIN + i)).below, 2*i + 1);

	// printf("Cosx = \n");
	// for ( i = 0; i < n-1; i++ )
	// 	printf("(%lld / %lld)x^%lld\n+", (*(COEFs_of_COS + i)).above, (*(COEFs_of_COS + i)).below, 2*i + 1);
	// printf("(%lld / %lld)x^%lld\n", (*(COEFs_of_COS + i)).above, (*(COEFs_of_COS + i)).below, 2*i + 1);

	// print sin and cos

	for ( i = 0; i < n; i++ ) {
		(*(COEFs_of_COS + i)).above *= -1;
	}

	// for subtract

	for ( i = 0; i < n; i++ ) {
		*(COEFs_of_TAN + i) = *(COEFs_of_SIN + i);
		for ( j = i; j < n; j++ ) {
			*(COEFs_of_SIN + j) = addition(*(COEFs_of_SIN + j), multiple(*(COEFs_of_TAN + i), *(COEFs_of_COS + j - i)));
			// subtract
		}
	}

	for ( i = 0; i < n; i++ ) {
		if ( i % 2 ) // i is odd
			(*(COEFs_of_SIN + i)).above = -1;
		else
			(*(COEFs_of_SIN + i)).above = 1;
		(*(COEFs_of_SIN + i )).below = Factorial(2*i + 1);
	}

	// Re Calculated Sin

	for ( i = 0; i < n; i++ ) {
		if ( i % 2 ) // i is odd
			(*(COEFs_of_COS + i)).above = -1;
		else
			(*(COEFs_of_COS + i)).above = 1;
		(*(COEFs_of_COS + i)).below = Factorial(2*i);
	}

	// Re Calculated Cos

	
	// printf("Tanx = \n");
	// for ( i = 0; i < n-1; i++ )
	// 	printf("(%lld / %lld)x^%lld\n+", (*(COEFs_of_TAN + i)).above, (*(COEFs_of_TAN + i)).below, 2*i + 1);
	// printf("(%lld / %lld)x^%lld\n", (*(COEFs_of_TAN + i)).above, (*(COEFs_of_TAN + i)).below, 2*i + 1);

	printf("Input x to substitute into sin, cos, tan : ");
	scanf("%Lf", &input);

	// Subtract 2*pi*n from x to maximize the effect which is highly accurate within the restricted area-(0,2pi)

	q = input / ( 2 * pi );
	for ( g = 0; q > 0.0l; g++, q -= 1.0l )
		;
	g--;

	x = input - g * ( 2 * pi); // now x is in (0,2pi) I guess.

	sin = 0.0l;
	for ( i = 0; i < n; i++ )
		sin += exponential(x,2*i + 1) * (*(COEFs_of_SIN + i)).above / (*(COEFs_of_SIN + i)).below;
	
	cos = 0.0l;
	for ( i = 0; i < n; i++ )
		cos += exponential(x,2*i) * (*(COEFs_of_COS + i)).above / (*(COEFs_of_COS + i)).below;

	printf("sin(%Lf) = sin(%Lf) = %.8Lf\n", input, x, sin);
	printf("cos(%Lf) = cos(%Lf) = %.8Lf\n", input, x, cos);

	q = input / pi;

	for ( g = 0; q > 0.0l; g++, q -= 1.0l )
		;
	g--;

	x = input - g * pi;
	x -= ( x >= pi/2 ) ? pi : 0.0l; // especially into (-pi/2,pi/2)


	tan = 0.0l;
	for ( i = 0; i < n; i++ )
		tan += exponential(x,2*i + 1) * (*(COEFs_of_TAN + i)).above / (*(COEFs_of_TAN + i)).below;
	
	printf("tan(%Lf) = tan(%Lf) = %.8Lf\n", input, x, tan);

	return 0;
}
// main

// definition of functions
long long FindGCD(long long a, long long b) {
	
	// declaring variable
	long long q, r; // from Division Algorithm
	long long temp;
	// declaring variable

	// GCD(a,b) == GCD(|a|,|b|), easier to find q;
	if ( a < 0 ) {
		a = -a;
	}
	if ( b < 0 ) {
		b = -b;
	}
	// GCD(a,b) == GCD(|a|,|b|);
	
	// particular cases
	if ( a == 0 ) {
		if ( b == 0 )
			return -1; // error
		else
			return b;
	} else if ( b == 0 )
		return a;
	// particular cases

	// GCD(a,b) == GCD(b,a), WITHOUT LOSS OF GENERALLITY, but none of this declared : if a < b then a = bq + r for some q and r in Z st. q >= 0 is contradiction.
	if ( a < b ) {
		temp = a;
		a = b;
		b = temp;
		// swap
	}
	// GCD(a,b) == GCD(b,a)

	// Start to find
	do {
		q = a/b;
		r = a - q*b;

		a = b;
		b = r;
	} while ( r != 0 );

	return a;
	// END
}
long long Factorial(long long a) {
	long long f;
	long long i;

	if ( ! a || a == 1 )
		return 1;

	f = 1;
	for ( i = 2; i < a; i++ ) {
		f *= i;
	}

	return f*i;
}
void cancellate(Fraction * a) {
	long long GCD = FindGCD(a -> above, a -> below);
	a -> above = a -> above / GCD;
	a -> below = a -> below / GCD;
	// p/d / q/d is relatively prime.
}
Fraction addition(Fraction a, Fraction b) {

	// declaring variables
	long long GCD, LCM; // of belows
	long long q_a, q_b; // LCM = (a.below)*q_a, same as b
	Fraction Sum; // will be returned.
	// declaring variables

	// Start
	GCD = FindGCD(a.below, b.below);
	if ( (a.below)*(b.below) > 0 ) // below cannot be 0.
		LCM = (a.below)*(b.below)/GCD;
	else
		LCM = -(a.below)*(b.below)/GCD;
	// LCM was founded.

	q_a = LCM/(a.below);
	q_b = LCM/(b.below);

	// q series was founded.

	Sum.above = (a.above)*q_a + (b.above)*q_b;
	Sum.below = LCM;

	cancellate(&Sum);

	// calculate Sum

	return Sum;
	
	// END

}
Fraction multiple(Fraction a, Fraction b) {
	Fraction multiplier;
	
	multiplier.above = (a.above) * (b.above);
	multiplier.below = (a.below) * (b.below);
	cancellate(&multiplier);

	return multiplier;
}
Fraction divide(Fraction a, Fraction b) {
	Fraction multiplier;
	
	multiplier.above = (a.above) * (b.below);
	multiplier.below = (a.below) * (b.above);

	if ( multiplier.below < 0 ) {
		multiplier.below *= -1;
		multiplier.above *= -1;
	}
	cancellate(&multiplier);

	return multiplier;
}
long double exponential(long double a, int n) {
	int i;
	long double c;

	c = 1.0l;
	for ( i = 0; i < n; i++ )
		c *= a;
	return c;
}
