#include "../headers/vector_2.hpp"

Vector2::Vector2() {
  this->x = 0;
  this->y = 0;
}

Vector2::Vector2(int x, int y) {
  this->x = x;
  this->y = y;
}

Vector2::Vector2(const Vector2 &vec) {
  this->x = vec.get_x();
  this->y = vec.get_y();
}

const int &Vector2::get_x() const { return this->x; }
const int &Vector2::get_y() const { return this->y; }

void Vector2::set_x(int x) { this->x = x; }
void Vector2::set_y(int y) { this->y = y; }

Vector2 &Vector2::operator+=(const Vector2 &vec) {
  this->x += vec.get_x();
  this->y += vec.get_y();

  return *this;
}

Vector2 &Vector2::operator-=(const Vector2 &vec) {
  this->x -= vec.get_x();
  this->y -= vec.get_y();

  return *this;
}

Vector2 Vector2::operator+(const Vector2 &vec) {
  this->x += vec.get_x();
  this->y += vec.get_y();

  return *this;
}

Vector2 Vector2::operator-(const Vector2 &vec) {
  this->x -= vec.get_x();
  this->y -= vec.get_y();

  return *this;
}

bool Vector2::operator==(const Vector2 &vec) const {
  return (this->x == vec.get_x() && this->y == vec.get_y());
}

Vector2 Vector2::reverse() { return Vector2(this->get_y(), this->get_x()); }

void Vector2::normalise() {
  this->x = (this->x > 0) ? 1 : -1;
  this->y = (this->y > 0) ? 1 : -1;
}

std::ostream &operator<<(std::ostream &stream, const Vector2 &vec) {
  // stream << "x: " << vec.get_x() << " y: " << vec.get_y() << std::endl;
  stream << "<" << vec.get_x() << "," << vec.get_y() << ">";

  return stream;
};
