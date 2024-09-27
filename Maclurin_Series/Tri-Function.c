#include <stdio.h>
#include <stdlib.h>

typedef struct { // above/below
	long long above;
	long long below;
} Fraction;

// declaration
long long FindGCD(long long a, long long b); 
long long Factorial(long long a);
void cancellate(Fraction * a);
Fraction addition(Fraction a, Fraction b);
Fraction multiple(Fraction a, Fraction b);
Fraction divise(Fraction a, Fraction b);
// declaration

// main
int main() {
	
	// declare variables
	Fraction * COEFs_of_SIN;
	Fraction * COEFs_of_COS;
	Fraction * COEFs_of_TAN;

	long long n;
	long long i, j;

	// declare variables
	printf("How many General terms of Taylor's Series of Tangent which will be calculated? : ");
	scanf("%lld", &n);

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
	printf("Sinx = \n");

	// Calculated Cos

	for ( i = 0; i < n-1; i++ )
		printf("(%lld / %lld)x^%lld\n+", (*(COEFs_of_SIN + i)).above, (*(COEFs_of_SIN + i)).below, 2*i + 1);
	printf("(%lld / %lld)x^%lld\n", (*(COEFs_of_SIN + i)).above, (*(COEFs_of_SIN + i)).below, 2*i + 1);

	printf("Cosx = \n");
	for ( i = 0; i < n-1; i++ )
		printf("(%lld / %lld)x^%lld\n", (*(COEFs_of_COS + i)).above, (*(COEFs_of_COS + i)).below, 2*i + 1);
	printf("(%lld / %lld)x^%lld\n", (*(COEFs_of_COS + i)).above, (*(COEFs_of_COS + i)).below, 2*i + 1);

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
	
	printf("Tanx = \n");
	for ( i = 0; i < n-1; i++ )
		printf("(%lld / %lld)x^%lld\n", (*(COEFs_of_TAN + i)).above, (*(COEFs_of_TAN + i)).below, 2*i + 1);
	printf("(%lld / %lld)x^%lld\n", (*(COEFs_of_TAN + i)).above, (*(COEFs_of_TAN + i)).below, 2*i + 1);

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
Fraction divise(Fraction a, Fraction b) {
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
