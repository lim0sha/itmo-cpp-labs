#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstring>
#include <string_view>
#include <cctype>

template<class T, class Tcheck>
bool my_all_of(T begin, T end, Tcheck tcheck) {
  for (auto i = begin; i != end; ++i) {
    if (!tcheck(*i))
      return false;
  }
  return true;
}

template<class T, class Tcheck>
bool my_is_sorted(T begin, T end, Tcheck comp) {
  if (begin == end)
    return true;
  T next = begin;
  ++next;

  while (next != end) {
    if (comp(*next, *begin))
      return false;
    ++begin;
    ++next;
  }

  return true;
}

template<class T, class Tcheck>
bool my_is_palindrome(T begin, T end, Tcheck tcheck) {
  while (begin < end) {
    if (!tcheck(*begin, *end))
      return false;
    ++begin;
    --end;
  }

  return true;
}