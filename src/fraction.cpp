#include "fraction.h"

// Constructors
Fraction::Fraction() {

}

Fraction::Fraction(Fraction& f) {
  
}

Fraction::Fraction(int num, int den) {
  
}

Fraction::Fraction(int num) {
  
}

// TODO Support Fraction(Fraction, Fraction);


// Accessors
int Fraction::getNumerator() {
  return numerator;
}

int Fraction::getDenominator() {
  return denominator;
}

// Helpers
Fraction Fraction::reduce() {

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
// TODO Implement and extend the assignment operators, if time allows.


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
// TODO Extend '<<' operator if time allows
std::string Fraction::to_string() {
  
}

// TODO Extend 'float()' if time allows

// TODO Extend 'bool()' at the end, if time allows

// TODO Extend '<<' operator if time allows


int main(int argc, char *argv[]) {
  printf("Basic C++ class for implementing fractions\n");
}