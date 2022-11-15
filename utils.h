//
// Created by Dyatkovskiy Stepan on 11/13/22.
//

#pragma once

#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <string>
#include <sstream>
#include <type_traits>

using namespace std;

template<typename T>
string get_type_name() {
  return "unknown type";
}

template<>
string get_type_name<int>() {
  return "integer";
}

template<>
string get_type_name<float>() {
  return "floating point number";
}

template<typename T>
pair<T, bool> validate(const string &s) {
  T v;
  istringstream istrm(s);
  istrm >> v;
  if (!istrm.eof() || istrm.fail()) return {0, false};

  return {v, true};
}

template<typename T>
T input(const string &prompt) {
  string vs;
  auto tname = get_type_name<T>();
  do {
    cout << prompt << " (" << tname << "): ";
    cin >> vs;
    auto [v, valid] = validate<T>(vs);
    if (valid) {
      T v;
      istringstream istrm(vs);
      istrm >> v;
      return v;
    }
    cout << "    Unable to parse " << tname
         << ", please try again.\n";
  } while (1);
}

template<typename T>
constexpr bool is_arg_supported() {
  return disjunction < is_same < T, int >, is_same < T, float >> ::value;
}
