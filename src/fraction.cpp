#include "fraction.h"
#include <iostream>

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

// TODO: If converting Fraction to const, get rid of setters
void Fraction::init(int num, int den) {
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
bool Fraction::reduce() {

}

Fraction Fraction::invert() {
  
}


// Basic Arithmetic
// TODO Extend '+' operator if time allows
Fraction Fraction::plus(Fraction f) {
  
}

// TODO Extend '-' operator if time allows
Fraction Fraction::minus(Fraction f) {
  
}

// TODO Extend '*' operator if time allows
Fraction Fraction::multiply(Fraction f) {
  
}

// TODO Extend '/' operator if time allows
Fraction Fraction::divide(Fraction f) {
  
}

// TODO Implement and extend the '%' operator at the end, if time allows.


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
  outputStream << f.numerator << "/" << f.denominator;
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


int main(int argc, char *argv[]) {
  std::cout << "Basic C++ class for implementing fractions" << std::endl;
  testConstructors();
}