#include "fraction.h"
#include <iostream>

/* Assumptions:
 * - We do not have to worry about numbers too large to handle with integers
 * - We do not have to worry about representing complex fractions
 * TODO We could improve arithmetic logic by having intermediate products be handled with "longer" ints 
*/

// Constructors
Fraction::Fraction() {
  init(0, 1);
}

Fraction::Fraction(const Fraction& f) {
  init(f.numerator, f.denominator);
}

Fraction::Fraction(int num) {
  init(num, 1);
}

Fraction::Fraction(int num, int den) {
  init(num, den);
}


// Accessors
int Fraction::getNumerator() {
  return numerator;
}

int Fraction::getDenominator() {
  return denominator;
}


// Helpers
void Fraction::init(int num, int den) {
  if (den == 0)
    throw std::domain_error("Divide by zero error.");
  numerator = num;
  denominator = den;
  reduce();
}

// sets the fraction to a reduced form, with the sign on the numerator.  If it is already reduced, return true
bool Fraction::reduce() {
  int gcd = Fraction::gcd(abs(numerator), abs(denominator));
  if ((gcd == 1) && (denominator >= 0))
    return true;
  // We need to reduce
  int sign = 1;
  if ((numerator < 0) ^ (denominator < 0))
    sign = -1;
  numerator = sign * abs(numerator / gcd);
  denominator = abs(denominator / gcd);
  return false;
}

Fraction Fraction::invert() {
  if (numerator == 0)
    throw std::domain_error("Divide by zero error.");
  init(denominator, numerator);
  return *this;
}

// Euclidean Algorithm
int Fraction::gcd(int x, int y) {
  if (y == 0)
    return x;
  else
    return gcd(y, x % y);
}


// Basic Arithmetic
/* Note for all arithmetic (and paired compound assignment) operators:
 *  - We have to create a copy for the binary arithmetic operator anyway, so we do so in the function header
 *  - We have to define the paired compound assignment operator anyway, so we use it to define the arithmetic operator to save an extra evaluation of the copy
*/
inline Fraction operator + (Fraction leftF, const Fraction& rightF) {
  leftF += rightF;
  return leftF;
}
Fraction& Fraction::operator += (const Fraction& f) {
  int gcd = Fraction::gcd(denominator, f.denominator); // Denominators from fraction objects are always positive
  /* Minimize integer literal maxima by dividing by gcd first.
   * We know it is a divisor of both denominators, so this is a safe order.
   * We assign directly to prevent calling reduce().
   *  - We know the denominators are positive, so the sign will be the result of numerator addition
   *  - We know the fraction is reduced because we divide the denominator product by their greatest common divisor */
  numerator = ((f.denominator / gcd * numerator) + (denominator / gcd * f.numerator));
  denominator = (denominator / gcd) * f.denominator;
  return *this;
}

inline Fraction operator - (Fraction leftF, const Fraction& rightF) {
  leftF -= rightF;
  return leftF;
}
Fraction& Fraction::operator -= (const Fraction& f) {
  int gcd = Fraction::gcd(denominator, f.denominator); // Denominators from fraction objects are always positive
  /* Minimize integer literal maxima by dividing by gcd first.
   * We know it is a divisor of both denominators, so this is a safe order.
   * We assign directly to prevent calling reduce().
   *  - We know the denominators are positive, so the sign will be the result of numerator subtraction
   *  - We know the fraction is reduced because we divide the denominator product by their greatest common divisor */
  numerator = ((f.denominator / gcd * numerator) - (denominator / gcd * f.numerator));
  denominator = (denominator / gcd) * f.denominator;
  return *this;
}

inline Fraction operator * (Fraction leftF, const Fraction& rightF) {
  leftF *= rightF;
  return leftF;
}
Fraction& Fraction::operator *= (const Fraction& f) {
  init(numerator * f.numerator,
       denominator * f.denominator);
  return *this;
}

// TODO Improve logic if appropriate
inline Fraction operator / (Fraction leftF, const Fraction& rightF) {
  leftF /= rightF;
  return leftF;
}
Fraction& Fraction::operator /= (const Fraction& f) {
  if (f.numerator == 0)
    throw std::domain_error("Divide by zero error.");
  init(numerator * f.denominator,
       denominator * f.numerator);
  return *this;
}

// TODO Implement and extend the '%' operator at the end, if time allows?
// TODO Implement and extend the '%=' operator if the '%' operator is implemented.


// Assignment
Fraction& Fraction::operator = (const Fraction& copy) {
  init(copy.numerator, copy.denominator);
  return *this;
}


// Comparators
bool Fraction::operator == (Fraction f) {
  // Forcing all Fractions to be reduced means we can just compare raw
  return ((f.numerator == numerator) && (f.denominator == denominator));
}

bool Fraction::operator != (Fraction f) {
  // Forcing all Fractions to be reduced means we can just compare raw
  return ((f.numerator != numerator) || (f.denominator != denominator));
}

// TODO Consider if a manual algorithm is faster than casting
bool Fraction::operator > (Fraction f) {
  return (float)*this > (float)f;
}

// TODO Consider if a manual algorithm is faster than casting
bool Fraction::operator < (Fraction f) {
  return (float)*this < (float)f; 
}

bool Fraction::operator >= (const Fraction f) {
  // equality is a pair of integer checks, so more precise than a float comparison
  if (*this == f)
    return true;
  return *this > f;
}

bool Fraction::operator <= (const Fraction f) {
  // equality is a pair of integer checks, so more precise than a float comparison
  if (*this == f)
    return true;
  return *this < f;
}

// Casting
// TODO: Implement some way to define the format to display at the end, if time allows
// Stream operator as a convenient way to display the fraction.
std::ostream& operator << (std::ostream& outputStream, const Fraction& f) {
  outputStream << f.numerator;
  if (f.denominator != 1)
    outputStream << "/" << f.denominator;
  return outputStream;
}

Fraction::operator float() {
  return (float)numerator / (float)denominator;
}

Fraction::operator bool() {
  //Non-zero should return true, by C spec.
  return (bool)numerator;
}

/*************************
 * TESTS                 *
 *************************/

void testConstructors() {
  std::cout << std::endl << "Testing Fraction constructors!" << std::endl;
  Fraction defaultFraction = Fraction();
  std::cout << "Fraction() = " << defaultFraction << std::endl;
  Fraction integerFraction = Fraction(2);
  std::cout << "Fraction(2) = " << integerFraction << std::endl;
  Fraction baseFraction = Fraction(1, 2);
  std::cout << "Fraction(1,2) = " << baseFraction << std::endl;
  Fraction assignFraction = Fraction(baseFraction);
  std::cout << "assignFraction = " << assignFraction << std::endl;
  Fraction copyFraction = baseFraction;
  std::cout << "copyFraction = " << copyFraction << std::endl;
}

void testErrors() {
  std::cout << std::endl << "Testing Fraction errors!" << std::endl;
  Fraction zeroFraction = Fraction(0);
  try {
    std::cout << "Fraction() = " << zeroFraction.invert() << std::endl;
  } catch (std::domain_error) {
    std::cout << "We caught a divide by zero error while inverting 0" << std::endl;
  }
  try {
    std::cout << "Fraction(1,0) = " << Fraction(1,0) << std::endl;
  } catch (std::domain_error) {
    std::cout << "We caught a divide by zero error while initializing an empty denominator" << std::endl;
  }

}

void testReduction() {
  std::cout << std::endl << "Testing Fraction reduction!" << std::endl;
  Fraction basicFraction = Fraction(1,4);
  std::cout << "Fraction(1,4) = " << basicFraction << std::endl;
  Fraction reducableFraction = Fraction(2,4);
  std::cout << "Fraction(2,4) = " << reducableFraction << std::endl;
  Fraction improperFraction = Fraction(4,2);
  std::cout << "Fraction(4,2) = " << improperFraction << std::endl;
  Fraction negativeFraction = Fraction(-2,4);
  std::cout << "Fraction(-2,4) = " << negativeFraction << std::endl;
  Fraction negativeSwappedFraction = Fraction(2,-4);
  std::cout << "Fraction(2,-4) = " << negativeSwappedFraction << std::endl;
}

void testAddition() {
  std::cout << "+ :" << std::endl;
  Fraction seventh = Fraction(1,7);
  Fraction half = Fraction(1,2);
  Fraction quarter = Fraction(1,4);
  Fraction nquarter = Fraction(1,-4);
  Fraction nhalf = Fraction(-1,2);
  Fraction improper = Fraction(3,2);
  std::cout << "1/7 + 1/7 = " << (seventh + seventh) << std::endl;
  std::cout << "1/2 + 1/4 = " << (half + quarter) << std::endl;
  std::cout << "1/2 + (-1/4) = " << (half + nquarter) << std::endl;
  std::cout << "(-1/2) + (-1/4) = " << (nhalf + nquarter) << std::endl;
  std::cout << "3/2 + 1/2 = " << (improper + half) << std::endl;
  std::cout << "1/2 + 1 = " << (half + 1) << std::endl;
}
void testSubtraction() {
  std::cout << "- :" << std::endl;
  Fraction seventh = Fraction(1,7);
  Fraction half = Fraction(1,2);
  Fraction quarter = Fraction(1,4);
  Fraction nquarter = Fraction(1,-4);
  Fraction nhalf = Fraction(-1,2);
  Fraction improper = Fraction(3,2);
  std::cout << "1/7 - 1/7 = " << (seventh - seventh) << std::endl;
  std::cout << "1/2 - 1/4 = " << (half - quarter) << std::endl;
  std::cout << "1/2 - (-1/4) = " << (half - nquarter) << std::endl;
  std::cout << "(-1/2) - (-1/4) = " << (nhalf - nquarter) << std::endl;
  std::cout << "3/2 - 1/2 = " << (improper - half) << std::endl;
  std::cout << "1/2 - 1 = " << (half - 1) << std::endl;
}
void testMultiplication() {
  std::cout << "* :" << std::endl;
  Fraction seventh = Fraction(1,7);
  Fraction half = Fraction(1,2);
  Fraction twofifths = Fraction(2,5);
  Fraction nquarter = Fraction(1,-4);
  Fraction nhalf = Fraction(-1,2);
  Fraction improper = Fraction(3,2);
  std::cout << "1/7 * 1/7 = " << (seventh * seventh) << std::endl;
  std::cout << "1/2 * 2/5 = " << (half * twofifths) << std::endl;
  std::cout << "1/2 * (-1/4) = " << (half * nquarter) << std::endl;
  std::cout << "(-1/2) * (-1/4) = " << (nhalf * nquarter) << std::endl;
  std::cout << "3/2 * 1/2 = " << (improper * half) << std::endl;
  std::cout << "1/2 * 2 = " << (half * 2) << std::endl;
  std::cout << "1/2 * 0 = " << (half * 0) << std::endl;

}
void testDivision() {
  std::cout << "/ :" << std::endl;
  Fraction seventh = Fraction(1,7);
  Fraction half = Fraction(1,2);
  Fraction quarter = Fraction(1,4);
  Fraction nquarter = Fraction(1,-4);
  Fraction nhalf = Fraction(-1,2);
  Fraction improper = Fraction(3,2);
  std::cout << "1/7 / 1/7 = " << (seventh / seventh) << std::endl;
  std::cout << "1/2 / 1/4 = " << (half / quarter) << std::endl;
  std::cout << "1/2 / (-1/4) = " << (half / nquarter) << std::endl;
  std::cout << "(-1/2) / (-1/4) = " << (nhalf / nquarter) << std::endl;
  std::cout << "3/2 / 1/2 = " << (improper / half) << std::endl;
  std::cout << "1/2 / 2 = " << (half / 2) << std::endl;
  try {
    std::cout << "1/2 / 0 = " << (half / 0) << std::endl;
  } catch (std::domain_error) {
    std::cout << "We caught a divide by zero error while dividing by zero" << std::endl;
  }

}

void testArithmetic() {
  std::cout << std::endl << "Testing Fraction arithmetic!" << std::endl;
  testAddition();
  testSubtraction();
  testMultiplication();
  testDivision();
  // Inversion
  Fraction seventh = Fraction(1,7);
  std::cout << "1/x :" << std::endl;
  Fraction half = Fraction(1,2);
  Fraction nquarter = Fraction(1,-4);
  Fraction improper = Fraction(3,2);
  Fraction one = Fraction(1);
  Fraction zero = Fraction(0);
  std::cout << "1 / (1/7) = " << seventh.invert() << std::endl;
  std::cout << "1 / (1/2) = " << half.invert() << std::endl;
  std::cout << "1 / (-1/4) = " << nquarter.invert() << std::endl;
  std::cout << "1 / (3/2) = " << improper.invert() << std::endl;
  std::cout << "1 / (1/1) = " << one.invert() << std::endl;
  try {
    std::cout << "Fraction() = " << zero.invert() << std::endl;
  } catch (std::domain_error) {
    std::cout << "We caught a divide by zero error while inverting 0" << std::endl;
  }
}

void testCasting() {
  std::cout << std::endl << "Testing Fraction casts!" << std::endl;
  Fraction basicFraction = Fraction(1,4);
  std::cout << "Fraction(1,4) = " << basicFraction << std::endl;
  std::cout << "  float(1,4) = " << (float)basicFraction << std::endl;
  Fraction negativeFraction = Fraction(-2,4);
  std::cout << "Fraction(-2,4) = " << negativeFraction << std::endl;
  std::cout << "  float(-2,4) = " << (float)negativeFraction << std::endl;
  Fraction giantFraction = Fraction(123456789,234567891);
  std::cout << "Fraction(123456789,234567891) = " << giantFraction << std::endl;
  std::cout << "  float(123456789,234567891) = " << (float)giantFraction << std::endl;
  std::cout << "chaining (float)Fraction(4,7) = " << (float)Fraction(4,7) << std::endl;
  std::cout << "chaining (bool)Fraction(0,7) = " << (bool)Fraction(0,7) << std::endl;
  std::cout << "chaining (bool)Fraction(-4,117) = " << (bool)Fraction(-4,117) << std::endl;
}

void testComparison() {
  std::cout << std::endl << "Testing Fraction comparison!" << std::endl;
  std::cout << "(-1/4) >  (1/-4) ? " << (Fraction(-1,4) > Fraction(1,-4)) << std::endl;
  std::cout << "(-1/4) >= (1/-4) ? " << (Fraction(-1,4) >= Fraction(1,-4)) << std::endl;
  std::cout << "(-1/4) <  (1/-4) ? " << (Fraction(-1,4) < Fraction(1,-4)) << std::endl;
  std::cout << "(-1/4) <= (1/-4) ? " << (Fraction(-1,4) <= Fraction(1,-4)) << std::endl;
  std::cout << "(-1/4) == (1/-4) ? " << (Fraction(-1,4) == Fraction(1,-4)) << std::endl;
  std::cout << "(-1/4) != (1/-4) ? " << (Fraction(-1,4) != Fraction(1,-4)) << std::endl;
  std::cout << "(-3/4) >  (1/4)  ? " << (Fraction(-3,4) > Fraction(1,4)) << std::endl;
  std::cout << "(-3/4) >= (1/4)  ? " << (Fraction(-3,4) >= Fraction(1,4)) << std::endl;
  std::cout << "(-3/4) <  (1/4)  ? " << (Fraction(-3,4) < Fraction(1,4)) << std::endl;
  std::cout << "(-3/4) <= (1/4)  ? " << (Fraction(-3,4) <= Fraction(1,4)) << std::endl;
  std::cout << "(-3/4) == (1/4)  ? " << (Fraction(-3,4) == Fraction(1,4)) << std::endl;
  std::cout << "(-3/4) != (1/4)  ? " << (Fraction(-3,4) != Fraction(1,4)) << std::endl;
  std::cout << "(1/4)  >  (-3/4) ? " << (Fraction(1,4) > Fraction(-3,4)) << std::endl;
  std::cout << "(1/4)  >= (-3/4) ? " << (Fraction(1,4) >= Fraction(-3,4)) << std::endl;
  std::cout << "(1/4)  <  (-3/4) ? " << (Fraction(1,4) < Fraction(-3,4)) << std::endl;
  std::cout << "(1/4)  <= (-3/4) ? " << (Fraction(1,4) <= Fraction(-3,4)) << std::endl;
  std::cout << "(1/4)  == (-3/4) ? " << (Fraction(1,4) == Fraction(-3,4)) << std::endl;
  std::cout << "(1/4)  != (-3/4) ? " << (Fraction(1,4) != Fraction(-3,4)) << std::endl;
  std::cout << "(-1/4) <  (0)    ? " << (Fraction(-1,4) < Fraction(0)) << std::endl;
  std::cout << "(-5/4) <  (1)    ? " << (Fraction(-5,4) < Fraction(1)) << std::endl;
}

int main(int argc, char *argv[]) {
  std::cout << "Basic C++ class for implementing fractions" << std::endl;
  testConstructors();
  testErrors();
  testReduction();
  testArithmetic();
  testCasting();
  testComparison();

}