# Keyple Plugin Stub C++ Library

## Overview

The **Keyple Plugin Stub C++ Library** is an add-on to allow an application using Keyple to interact with virtual readers and emulated smart cards.

## Documentation & Contribution Guide

The full documentation, including the **user guide**, **download information** and **contribution guide**, is available on the Keyple website [keyple.org](https://keyple.org).

## API documentation

API documentation & class diagram is available online: [docs.keyple.org/keyple-plugin-stub-cpp-lib](https://docs.keyple.org/keyple-plugin-cpp-java-lib)

## Examples

Examples of implementation are available in the following repository: [github.com/eclipse/keyple-cpp-example](https://github.com/eclipse/keyple-cpp-example)

## Building with Conan

This repository is packaged as a [Conan](https://conan.io/) recipe (`conanfile.py`), providing the
`Keyple::Plugin::Stub` CMake target as `keyple-plugin-stub-cpp-lib`. It requires `keyple-common-cpp-api/2.0.2`,
`keyple-plugin-cpp-api/2.3.2` and `keyple-util-cpp-lib/2.4.1` (all declared with `transitive_headers=True`, since
this library's public headers include their headers directly) plus `keypop-reader-cpp-api/2.1.0` (linked by the
CMake target but not currently referenced by any public header), all resolved via Conan instead of `FetchContent`.
Downstream keyple recipes should consume this package the same way, with
`self.requires("keyple-plugin-stub-cpp-lib/2.2.2")`. The `shared` option (default `True`) controls whether a shared
or static library is built, and `fPIC` is available for static, non-Windows builds.

The unit test suite is opt-in via the `with_tests` option (default `False`), so consumers of the package don't pay
for compiling GoogleTest.

### Local development

Use `conan build` to configure/compile in-tree, in a regular `build/` folder you can inspect, rerun and debug
against (and which generates a `CMakeUserPresets.json` for IDE integration). The build type defaults to `Release`;
pass `-s build_type=Debug` for a debug build, which lands in its own `build/Debug` subfolder alongside `build/Release`:

```bash
# Release build, with the unit test suite, under ./build/Release
conan build . -o with_tests=True --build=missing

# Debug build, under ./build/Debug
conan build . -o with_tests=True -s build_type=Debug --build=missing

# Re-run the tests directly afterwards
./build/Release/bin/keyplepluginstubcpplib_ut
./build/Debug/bin/keyplepluginstubcpplib_ut
```

### Packaging to the local cache

Use `conan create` to export the recipe and package to your local Conan cache, for consumption by other
recipes/repos (no remote upload involved):

```bash
# Build and export the package to the local cache
conan create . --build=missing

# Same, but also build and run the unit test suite as part of the recipe build
conan create . -o with_tests=True --build=missing

# Package a static build instead (default is shared)
conan create . -o shared=False --build=missing
```

### Conan profile

Builds use your default Conan profile. If you don't have one yet, create it with:

```bash
conan profile detect
```

## About the source code

The code is built with **CLang / GCC / MSVC** in order to address a wide range of applications.
