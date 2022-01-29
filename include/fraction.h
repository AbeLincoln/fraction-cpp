#ifndef FRACTION_H_
#define FRACTION_H_

#include <string>

class Fraction {
private:
  int numerator;
  int denominator;
  void init(int, int);
public:
  // Constructors
  Fraction();
  Fraction(const Fraction&);
  Fraction(int);
  Fraction(int, int);
  // TODO Support Fraction(Fraction, Fraction); ?  Is there even a speed-up this would provide?
  ~Fraction() = default;          // default because the class is trivial

  // Accessors
  int getNumerator();
  int getDenominator();

  // Helpers
  bool reduce();
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
  Fraction& operator = (const Fraction&);
  // TODO Implement and extend the other assignment operators, if time allows.

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
  friend std::ostream& operator << (std::ostream&, const Fraction&);
  // TODO Extend 'float()' if time allows
  // TODO Extend 'bool()' at the end, if time allows

};

#endif //FRACTION_H_