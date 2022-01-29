#ifndef FRACTION_H_
#define FRACTION_H_

#include <string>

class Fraction {
private:
  int numerator;
  int denominator;
public:
  // Constructors
  Fraction();                     // 0 / 1
  Fraction(Fraction&);
  Fraction(int, int);             // x / y
  Fraction(int);                  // x / 1
  // TODO Support Fraction(Fraction, Fraction);

  // Accessors
  int getNumerator();
  int getDenominator();

  // Helpers
  Fraction reduce();
  Fraction invert();

  // Basic Arithmetic
  // TODO Extend '+' operator if time allows
  Fraction plus(Fraction);
  // TODO Extend '-' operator if time allows
  Fraction minus(Fraction);
  // TODO Extend '*' operator if time allows
  Fraction multiply(Fraction);
  // TODO Extend '/' operator if time allows
  Fraction divide(Fraction);
  // TODO Implement and extend the '%' operator at the end, if time allows.

  // Assignment
  // TODO Implement and extend the assignment operators, if time allows.

  // Comparators
  // TODO Extend '==' operator if time allows
  bool equals(Fraction);
  // TODO Extend '!=' operator if time allows
  bool notEquals(Fraction);
  // TODO Extend '>' operator if time allows
  bool isGreatThan(Fraction);
  // TODO Extend '<' operator if time allows
  bool isLessThan(Fraction);
  // TODO Should implement and extend '<=' operator if other comparators are extended because a user would expect it
  // TODO Should implement and extend '>=' operator if other comparators are extended because a user would expect it

  // Casting
  std::string to_string(); 
  // TODO Extend 'float()' if time allows
  // TODO Extend 'bool()' at the end, if time allows
  // TODO Extend '<<' operator if time allows

};

#endif //FRACTION_H_