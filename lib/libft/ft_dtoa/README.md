# Dragon4 implementation of dtoa

This libdtoa contains a modified version of [Ryan Juckett's Dragon4](http://www.ryanjuckett.com/programming/printing-floating-point-numbers/)
implementation, which has been ported from C++ to C and has modifications
specific to my needs of ft_printf. These modifications include:

- No inline declarations of variables, they must always be pre-declared
- No functions longer than 25 lines
- No more than 5 functions per file
- Only functions allowed that are implemented by myself (apart from `write`, `malloc`, `exit`, `free`). E.g `ft_memmove` in `../libft`.
- Formatting changes based on whether flags # or g are used on ft_printf side
- Usage of plain `stdint.h` types (don't see why those should be redefined)
- Only snake case instead of camel case.

Code follows School 42 norms.

# Simple tests

While implementing the algorithm, a super simple test framework was used.
(My own modification of [mu_test.h](http://www.jera.com/techinfo/jtns/jtn002.html) using a TestState struct to better output results and not stop at failures).

The dragon4 implementation permission note:

```
/*
 * Copyright (c) 2014 Ryan Juckett
 * http://www.ryanjuckett.com/
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 *    distribution.
 */
```
