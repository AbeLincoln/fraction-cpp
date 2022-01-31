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
  Fraction(int);  // NOTE: Intentionally left implicit to allow integers to become Fraction objects when using arithmetic
  Fraction(int, int);
  ~Fraction() = default;          // default because the class members are all trivial

  // Accessors
  int getNumerator();
  int getDenominator();

  // Helpers
  bool reduce();
  Fraction invert();

  // Basic Arithmetic defined in `fraction.cpp` file as inline

  // Assignment
  Fraction& operator = (const Fraction&);
  Fraction& operator += (const Fraction&);
  Fraction& operator -= (const Fraction&);
  Fraction& operator *= (const Fraction&);
  Fraction& operator /= (const Fraction&);
  // TODO Implement and extend the '%=' operator if the '%' operator is implemented.

  // Comparators
  bool operator == (const Fraction);
  bool operator != (const Fraction);
  bool operator > (const Fraction);
  bool operator < (const Fraction);
  bool operator <= (const Fraction);
  bool operator >= (const Fraction);

  // Displaying
  friend std::ostream& operator << (std::ostream&, const Fraction&);

  // Casting
  // NOTE: All cast overloads are explicit to prevent our implicit int constructor from looping
  explicit operator float();
  explicit operator bool();  // more for fun than function, but can still allow clever C syntax tricks for savvy users

};

#endif //FRACTION_H_