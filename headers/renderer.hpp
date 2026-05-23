#pragma once

class Renderer {
private:
  int width, height;
  char *buffer;

public:
  Renderer(int, int, int);
  ~Renderer();

  const char *begin() const;
  const char *end() const;

  void init_buffer();
  void delete_buffer();
  void render_to_buffer();
  void print() const;
};
