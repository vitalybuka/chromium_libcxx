//===----------------------------------------------------------------------===//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03, c++11, c++14, c++17
// UNSUPPORTED: libcpp-no-concepts
// UNSUPPORTED: no-exceptions

// This test requires the dylib support introduced in D92214.
// XFAIL: use_system_cxx_lib && x86_64-apple-macosx10.15
// XFAIL: use_system_cxx_lib && x86_64-apple-macosx10.14
// XFAIL: use_system_cxx_lib && x86_64-apple-macosx10.13
// XFAIL: use_system_cxx_lib && x86_64-apple-macosx10.12
// XFAIL: use_system_cxx_lib && x86_64-apple-macosx10.11
// XFAIL: use_system_cxx_lib && x86_64-apple-macosx10.10
// XFAIL: use_system_cxx_lib && x86_64-apple-macosx10.9

// <format>

// constexpr size_t next_arg_id();

#include <format>
#include <cassert>

#include "test_macros.h"

constexpr bool test() {
  std::format_parse_context context("");
  for (size_t i = 0; i < 10; ++i)
    assert(i == context.next_arg_id());

  return true;
}

void test_exception() {
  std::format_parse_context context("", 1);
  context.check_arg_id(0);

  try {
    context.next_arg_id();
    assert(false);
  } catch (const std::format_error& e) {
    assert(strcmp(e.what(), "Using automatic argument numbering in manual "
                            "argument numbering mode") == 0);
    return;
  }
  assert(false);
}

int main(int, char**) {
  test();
  test_exception();
  static_assert(test());

  return 0;
}
