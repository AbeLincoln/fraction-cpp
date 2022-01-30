#include "fraction.h"
#include <iostream>

/* Assumptions:
 * - We do not have to worry about numbers too large to handle with integers
 * - We do not have to worry about representing complex fractions
 * TODO: We could improve arithmetic logic by having intermediate products be handled with longer ints 
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

// TODO Support Fraction(Fraction, Fraction) {} ?  Is there even a speed-up this would provide?

void Fraction::init(int num, int den) {
  if (den == 0)
    throw std::domain_error("Divide by zero error.");
  numerator = num;
  denominator = den;
  reduce();
}

// Accessors
int Fraction::getNumerator() {
  return numerator;
}

int Fraction::getDenominator() {
  return denominator;
}


// Helpers
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
// TODO: confirm we even need this - is reduction faster than LCM saves?  We need to reduce signs anyway
int Fraction::lcm(int x, int y) {
  // Minimize integer literal maxima by dividing by gcd first. We know it divides x, so this is safe.
  return x / gcd(x, y) * y;
}
// Euclidean Algorithm
int Fraction::gcd(int x, int y) {
  if (y == 0)
    return x;
  else
    return gcd(y, x % y);
}


// Basic Arithmetic
// TODO Extend '+' operator if time allows
Fraction Fraction::plus(Fraction f) {
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
Fraction Fraction::plus(int add) {
  init(numerator + (add * denominator),
       denominator);
  return *this;
}

// TODO Extend '-' operator if time allows
Fraction Fraction::minus(Fraction f) {
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
Fraction Fraction::minus(int sub) {
  init(numerator - (sub * denominator),
       denominator);
  return *this;
}

// TODO Extend '*' operator if time allows
Fraction Fraction::multiply(Fraction f) {
  init(numerator * f.numerator,
       denominator * f.denominator);
  return *this;
}
Fraction Fraction::multiply(int mul) {
  init(numerator * mul,
       denominator);
  return *this;
}

// TODO Extend '/' operator if time allows
// TODO: Improve logic if appropriate
Fraction Fraction::divide(Fraction f) {
  if (f.numerator == 0)
    throw std::domain_error("Divide by zero error.");
  init(numerator * f.denominator,
       denominator * f.numerator);
  return *this;
}
Fraction Fraction::divide(int div) {
  if (div == 0)
    throw std::domain_error("Divide by zero error.");
  init(numerator,
       denominator * div);
  return *this;
}

// TODO Implement and extend the '%' operator at the end, if time allows?


// Assignment
Fraction& Fraction::operator = (const Fraction& copy) {
  init(copy.numerator, copy.denominator);
  return *this;
}
// TODO Implement and extend the other assignment operators, if time allows.


// Comparators
// TODO Extend '==' operator if time allows
bool Fraction::equals(Fraction f) {
  
}

// TODO Extend '!=' operator if time allows
bool Fraction::notEquals(Fraction f) {
  
}

// TODO Extend '>' operator if time allows
bool Fraction::isGreatThan(Fraction f) {
  
}

// TODO Extend '<' operator if time allows
bool Fraction::isLessThan(Fraction f) {
  
}

// TODO Should implement and extend '<=' operator if other comparators are extended because a user would expect it

// TODO Should implement and extend '>=' operator if other comparators are extended because a user would expect it


// Casting
// Stream operator as a convenient way to display the fraction.  TODO: Implement some way to define the format to display at the end, if time allows
std::ostream& operator << (std::ostream& outputStream, const Fraction& f) {
  outputStream << f.numerator;
  if (f.denominator != 1)
    outputStream << "/" << f.denominator;
  return outputStream;
}

// TODO Extend 'float()' if time allows

// TODO Extend 'bool()' at the very end for fun, if time allows


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

// TODO: Clean up, if time allows
void testArithmetic() {
  // Addition
  std::cout << std::endl << "Testing Fraction arithmetic!" << std::endl;
  std::cout << "+" << std::endl;
  Fraction seventh = Fraction(1,7);
  std::cout << "1/7 + 1/7 = " << seventh.plus(seventh) << std::endl;
  Fraction half = Fraction(1,2);
  Fraction quarter = Fraction(1,4);
  std::cout << "1/2 + 1/4 = " << half.plus(quarter) << std::endl;
  half = Fraction(1,2);
  Fraction nquarter = Fraction(1,-4);
  std::cout << "1/2 + (-1/4) = " << half.plus(nquarter) << std::endl;
  half = Fraction(1,2);
  Fraction nhalf = Fraction(-1,2);
  std::cout << "(-1/2) + (-1/4) = " << nhalf.plus(nquarter) << std::endl;
  Fraction improper = Fraction(3,2);
  std::cout << "3/2 + 1/2 = " << improper.plus(half) << std::endl;
  std::cout << "1/2 + 1 = " << half.plus(1) << std::endl;
  // Subtraction
  std::cout << "-" << std::endl;
  seventh = Fraction(1,7);
  std::cout << "1/7 - 1/7 = " << seventh.minus(seventh) << std::endl;
  half = Fraction(1,2);
  quarter = Fraction(1,4);
  std::cout << "1/2 - 1/4 = " << half.minus(quarter) << std::endl;
  half = Fraction(1,2);
  nquarter = Fraction(1,-4);
  std::cout << "1/2 - (-1/4) = " << half.minus(nquarter) << std::endl;
  nhalf = Fraction(-1,2);
  nquarter = Fraction(1,-4);
  std::cout << "(-1/2) - (-1/4) = " << nhalf.minus(nquarter) << std::endl;
  improper = Fraction(3,2);
  half = Fraction(1,2);
  std::cout << "3/2 - 1/2 = " << improper.minus(half) << std::endl;
  half = Fraction(1,2);
  std::cout << "1/2 - 1 = " << half.minus(1) << std::endl;
  // Multiplication
  std::cout << "*" << std::endl;
  seventh = Fraction(1,7);
  std::cout << "1/7 * 1/7 = " << seventh.multiply(seventh) << std::endl;
  half = Fraction(1,2);
  Fraction twofifths = Fraction(2,5);
  std::cout << "1/2 * 2/5 = " << half.multiply(twofifths) << std::endl;
  half = Fraction(1,2);
  nquarter = Fraction(1,-4);
  std::cout << "1/2 * (-1/4) = " << half.multiply(nquarter) << std::endl;
  nhalf = Fraction(-1,2);
  nquarter = Fraction(1,-4);
  std::cout << "(-1/2) * (-1/4) = " << nhalf.multiply(nquarter) << std::endl;
  improper = Fraction(3,2);
  half = Fraction(1,2);
  std::cout << "3/2 * 1/2 = " << improper.multiply(half) << std::endl;
  half = Fraction(1,2);
  std::cout << "1/2 * 2 = " << half.multiply(2) << std::endl;
  half = Fraction(1,2);
  std::cout << "1/2 * 0 = " << half.multiply(0) << std::endl;
  // Division
  std::cout << "/" << std::endl;
  seventh = Fraction(1,7);
  std::cout << "1/7 / 1/7 = " << seventh.divide(seventh) << std::endl;
  half = Fraction(1,2);
  quarter = Fraction(1,4);
  std::cout << "1/2 / 1/4 = " << half.divide(quarter) << std::endl;
  half = Fraction(1,2);
  nquarter = Fraction(1,-4);
  std::cout << "1/2 / (-1/4) = " << half.divide(nquarter) << std::endl;
  nhalf = Fraction(-1,2);
  nquarter = Fraction(1,-4);
  std::cout << "(-1/2) / (-1/4) = " << nhalf.divide(nquarter) << std::endl;
  improper = Fraction(3,2);
  half = Fraction(1,2);
  std::cout << "3/2 / 1/2 = " << improper.divide(half) << std::endl;
  half = Fraction(1,2);
  std::cout << "1/2 / 2 = " << half.divide(2) << std::endl;
  half = Fraction(1,2);
  try {
    std::cout << "1/2 / 0 = " << half.divide(0) << std::endl;
  } catch (std::domain_error) {
    std::cout << "We caught a divide by zero error while dividing by zero" << std::endl;
  }
  // Inversion
  std::cout << "1/x" << std::endl;
  seventh = Fraction(1,7);
  std::cout << "1 / (1/7) = " << seventh.invert() << std::endl;
  half = Fraction(1,2);
  std::cout << "1 / (1/2) = " << half.invert() << std::endl;
  nquarter = Fraction(1,-4);
  std::cout << "1 / (-1/4) = " << nquarter.invert() << std::endl;
  improper = Fraction(3,2);
  std::cout << "1 / (3/2) = " << improper.invert() << std::endl;
  Fraction one = Fraction(1);
  std::cout << "1 / (1/1) = " << one.invert() << std::endl;
  Fraction zero = Fraction(0);
  try {
    std::cout << "Fraction() = " << zero.invert() << std::endl;
  } catch (std::domain_error) {
    std::cout << "We caught a divide by zero error while inverting 0" << std::endl;
  }
}

int main(int argc, char *argv[]) {
  std::cout << "Basic C++ class for implementing fractions" << std::endl;
  testConstructors();
  testErrors();
  testReduction();
  testArithmetic();

}