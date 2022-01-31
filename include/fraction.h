#ifndef FRACTION_H_
#define FRACTION_H_

#include <string>

class Fraction {
private:
  int numerator;
  int denominator;  // TODO: At the end, eliminate assignment in init() and have reduce() return the resultant variables instead.  Then denominator can never be negative.
  void init(int, int);
  int lcm(int, int);
  int gcd(int, int);
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
  Fraction plus(int);
  // TODO Extend '-' operator if time allows
  Fraction minus(Fraction);
  Fraction minus(int);
  // TODO Extend '*' operator if time allows
  Fraction multiply(Fraction);
  Fraction multiply(int);
  // TODO Extend '/' operator if time allows
  Fraction divide(Fraction);
  Fraction divide(int);
  // TODO Implement and extend the '%' operator at the end, if time allows.

  // Assignment
  Fraction& operator = (const Fraction&);
  // TODO Implement and extend the other assignment operators, if time allows.

  // Comparators
  bool operator == (const Fraction);
  bool operator != (const Fraction);
  bool operator > (const Fraction);
  bool operator < (const Fraction);
  bool operator <= (const Fraction);
  bool operator >= (const Fraction);

  // Casting
  friend std::ostream& operator << (std::ostream&, const Fraction&);
  operator float();
  operator bool();

};

#endif //FRACTION_H_