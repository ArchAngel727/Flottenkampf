#include "../headers/renderer.hpp"
#include <cstring>
#include <iostream>

Renderer::Renderer(int w, int h, int cs)
    : width((w + 1) + w * cs), height((h + 1) + h * cs) {
  this->init_buffer();
}
Renderer::~Renderer() { this->delete_buffer(); }

const char *Renderer::begin() const { return this->buffer; }
const char *Renderer::end() const {
  return this->buffer + this->width * this->height;
}

void Renderer::init_buffer() {
  this->buffer = new char[width * height];
  std::memset(this->buffer, ' ', this->width * this->height);
}
void Renderer::delete_buffer() { delete[] this->buffer; }

void Renderer::render_to_buffer() {
  for (int i = 0; i < this->width; i++) {
    this->buffer[i] = '#';
  }

  for (int i = 0; i < this->width; i++) {
    this->buffer[(this->height - 1) * this->width + i] = '#';
  }

  for (int i = 0; i < this->height; i++) {
    this->buffer[this->width * i] = '#';
  }

  for (int i = 0; i < this->height; i++) {
    this->buffer[this->width * i + (this->width - 1)] = '#';
  }

  for (int i = 0; i < this->width; i++) {
    for (int j = 0; j < this->height; j++) {
      if (i % 3 == 0) {
        this->buffer[this->height * j + this->width + i] = '#';
      }

      if (j % 3 == 0) {
        this->buffer[this->height * j + i] = '#';
      }
    }
  }
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

  std::cout << "W: " << this->width << ' ';
  std::cout << "H: " << this->height << '\n';
}
