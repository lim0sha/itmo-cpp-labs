#pragma once

class CPoint {
 public:
  CPoint(int x, int y) : m_x(x), m_y(y) {}
  [[nodiscard]] int getX() const { return m_x; }
  [[nodiscard]] int getY() const { return m_y; }
 private:
  int m_x;
  int m_y;
};

class CRational {
 public:
  CRational(int numerator, int denominator) : m_numerator(numerator), m_denominator(denominator) {}
  [[nodiscard]] int getNumerator() const { return m_numerator; }
  [[nodiscard]] int getDenominator() const { return m_denominator; }
 private:
  int m_numerator;
  int m_denominator;
};