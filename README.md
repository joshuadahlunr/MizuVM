# Mizu

Mizu is a lightweight easily extensible interpreter loosely modeled off of RISC-V assembly.

Programs are represented as an array of opcodes which are then allowed to manipulate virtual registers and a virtual stack.
The simplest "useful" Mizu program is:

```cpp
#define MIZU_IMPLEMENTATION
#include <mizu/instructions.hpp>

const static opcode program[] = {
    opcode{load_immediate, registers::t(0)}.set_immediate(40),
    opcode{debug_print, 0, registers::t(0)},
    opcode{halt},
};

int main() {
    registers_and_stack environment = {};
    setup_environment(environment);

    MIZU_START_FROM_ENVIRONMENT(program, env);
}
```

Take a read through the [documentorial](https://joshuadahlunr.github.io/MizuVM/) (documentation and tutorial rolled into one) to learn about the details of Mizu programs and our instructions.

## Features

* Small (our test executables are less than 50kb)
* Portable (should run anywhere with a C++ compiler, even microcontrollers and the web)
* Fast (recursively calculates the 40th Fibonacci a full second faster than Lua)
* Header-only[^1]
* Simple and easily extensible instructions
* Integer and float support
* Built in threading instructions (also includes simple go-like channels for inter-thread communication)
* Fallback coroutine "threading" for single core machines
* Built in FFI instructions (Mizu can call external functions in the same way it calls its own, just substitute the jump_to instruction for ffi::call)

[^1] FFI support relies on [libffi](https://github.com/libffi/libffi) which is not header-only!

## Tail Call Warning

Mizu makes heavy use of tail call optimization, if this optimization is not present programs will likely crash.
At the moment only clang has been configured to support tail call operations in debug mode.
**Visual Studio will likely fail!** Testing has shown the Microsoft's Visual Studio compiler doesn't tail call optimize, thus on Windows using Msys or Mingw is necessary!

## How to Integrate

The easiest way to integrate Mizu is to add it as a sub_director using Cmake:

```cmake
add_subdirectory(path/to/mizu)
...
target_link_libraries(your_cmake_target PUBLIC mizu::vm)
```

Then just include `mizu/instructions.hpp` and define `MIZU_IMPLEMENTATION` in one of your source files.
