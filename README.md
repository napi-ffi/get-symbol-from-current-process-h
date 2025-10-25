# @napi-ffi/get-symbol-from-current-process-h

[![CI](https://github.com/napi-ffi/get-symbol-from-current-process-h/actions/workflows/ci.yml/badge.svg?branch=main)](https://github.com/napi-ffi/get-symbol-from-current-process-h/actions/workflows/ci.yml)
[![npm version](https://img.shields.io/npm/v/@napi-ffi/get-symbol-from-current-process-h.svg)](https://www.npmjs.com/package/@napi-ffi/get-symbol-from-current-process-h)
[![npm downloads](https://img.shields.io/npm/dm/@napi-ffi/get-symbol-from-current-process-h.svg)](https://www.npmjs.com/package/@napi-ffi/get-symbol-from-current-process-h)
[![License: ISC](https://img.shields.io/badge/License-ISC-blue.svg)](./LICENSE)

> Cross-platform C function to get a symbol from the current process

This package provides a header-only C library for retrieving symbols from the current process in a cross-platform manner. It works on Unix-like systems (using `dlsym`) and Windows (using `GetProcAddress`).

Originally authored by [Anna Henningsen](https://github.com/addaleax) as part of the [node-ffi-napi](https://github.com/node-ffi-napi) project. This is a maintained fork under the [@napi-ffi](https://github.com/napi-ffi) organization.

## Installation

Install with npm:

```bash
npm install @napi-ffi/get-symbol-from-current-process-h
```

## Usage

### In your `binding.gyp`:

```python
'include_dirs': [
  "<!@(node -p \"require('@napi-ffi/get-symbol-from-current-process-h').include\")"
]
```

### In your C/C++ code:

```c
#include <get-symbol-from-current-process.h>

void* sym = get_symbol_from_current_process("my_function");
if (sym != NULL) {
  // Use the symbol
}
```

## API

### `void* get_symbol_from_current_process(const char* name)`

Retrieves a symbol from the current process by name.

**Parameters:**
- `name`: The name of the symbol to retrieve (must not be NULL)

**Returns:**
- Pointer to the symbol if found
- `NULL` if the symbol is not found or an error occurs



This package requires Node.js >= 20.0.0

## License

ISC License - See [LICENSE](LICENSE) file for details
