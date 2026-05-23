#pragma once

#include <format>
#include <iostream>

namespace crazylogger {

constexpr bool kDebug =
#ifdef DEBUG
    true;
#else
    false;
#endif

template <typename... Args>
void log(std::format_string<Args...> fmt, Args &&...args) {
  if constexpr (kDebug) {
    std::cerr << '\n'
              << "[DEBUG] " << std::format(fmt, std::forward<Args>(args)...)
              << '\n';
  }
}

} // namespace crazylogger
