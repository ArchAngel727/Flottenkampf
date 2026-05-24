#pragma once

#include "ship.hpp"
#include "vector_2.hpp"
#include <vector>
class Renderer {
private:
  int width, height, cell_size;
  char *buffer;

public:
  Renderer(int, int, int);
  ~Renderer();

  const char *begin() const;
  const char *end() const;

  void render_to_buffer(std::array<const std::vector<Ship *> *, 2>);
  char *get_cell_at(int, int);
  void draw_ship(int, int);
  void draw_ship(const Vector2 &);
  void clear_buffer();
  void print() const;
};
