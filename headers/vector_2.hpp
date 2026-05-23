#pragma once

#include <iostream>
#include <string>
class Vector2 {
private:
  int x, y;

public:
  Vector2();
  Vector2(int x, int y);

  const int &get_x() const;
  const int &get_y() const;

  void set_x(int);
  void set_y(int);

  Vector2 &operator+=(const Vector2 &);
  Vector2 &operator-=(const Vector2 &);
  Vector2 operator+(const Vector2 &);
  Vector2 operator-(const Vector2 &);
  bool operator==(const Vector2 &) const;

  Vector2 reverse();
  void normalise();
  std::string to_string() const;

  friend std::ostream &operator<<(std::ostream &, const Vector2 &);
};
