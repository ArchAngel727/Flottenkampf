#include "../headers/renderer.hpp"
#include <array>
#include <cstring>
#include <iostream>
#include <vector>

Renderer::Renderer(int w, int h, int cs)
    : width((w + 1) + w * cs), height((h + 1) + h * cs), cell_size(cs) {
  this->buffer = new char[this->width * this->height];
  std::memset(this->buffer, ' ', this->width * this->height);
}

Renderer::~Renderer() { delete[] this->buffer; }

const char *Renderer::begin() const { return this->buffer; }
const char *Renderer::end() const {
  return this->buffer + this->width * this->height;
}

void Renderer::render_to_buffer(
    std::array<const std::vector<Ship *> *, 2> ships) {
  for (int i = 0; i < this->width; i++) {
    for (int j = 0; j < this->height; j++) {
      if (i % (this->cell_size + 1) == 0) {
        this->buffer[j * this->width + i] = '#';
      }

      if (j % (this->cell_size + 1) == 0) {
        this->buffer[j * this->height + i] = '#';
      }
    }
  }

  for (auto vec : ships) {
    for (auto ship : *vec) {
      this->draw_ship(ship->get_position());
    }
  }
}

void Renderer::draw_ship(int x, int y) {
  char *ptr = this->get_cell_at(x, y);
  *ptr = 'S';

  if (!(this->cell_size > 1)) {
    return;
  }

  ptr += 1;
  *ptr = 'H';
  ptr += this->width - 1;
  *ptr = 'I';
  ptr += 1;
  *ptr = 'P';
}

void Renderer::draw_ship(const Vector2 &vec) {
  this->draw_ship(vec.get_x(), vec.get_y());
}

char *Renderer::get_cell_at(int x, int y) {
  int row = ((this->cell_size + 1) * y + 1);
  int column = ((this->cell_size + 1) * x + 1);
  int idx = row * this->width + column;

  if (idx < this->width * this->height) {
    return &this->buffer[idx];
  } else {
    std::cerr << "OOB: cell(" << x << "," << y << ") -> offset " << idx
              << " >= buffer " << this->width * this->height
              << " (cell_size=" << cell_size << ")\n";
    std::abort();
  }
}

void Renderer::clear_buffer() {
  std::memset(this->buffer, ' ', this->width * this->height);
}

void Renderer::print() const {
  const char *ptr = this->begin();

  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {
      std::cout << *ptr;
      ptr += 1;
    }

    std::cout << '\n';
  }
}
