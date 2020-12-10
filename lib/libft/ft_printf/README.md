# Printf

Printf from scratch with pure c.

Only following library functions allowed, the rest is from scratch.

- `malloc`
- `free`
- `exit`
- The functions of man 3 `stdarg`

## Usage

See e.g: [printf reference](http://www.cplusplus.com/reference/cstdio/printf/)

```
ft_printf("%[flags][width][.precision][length]specifier");
```

## Handles

### Variable specs:

```
ndDiuUoOxX
fFeEgG
csp%
b for binary where first bit = sign
```

### Formatter specs (sub specs):

```
-+ #0
hhhllljztL
*0-9+.*0-9+
```

Does not handle following specs / flags:

```
$: not regonized as flag, ignores whole format and spec if $ is used
aA: not regonized as spec
C(widechar): not regonized as spec
ls(widestring): l is ignored
```

### Floats

Float handling follows dragon4 algorithm implemented with guide by [ryanjuckett](http://www.ryanjuckett.com/programming/printing-floating-point-numbers).

- Also assumes little-endian system due to the way I dissect floats, see `libft.h`

This library includes:

- `ft_printf`
- `ft_sprintf`
- `ft_dprintf`

Since others have written such extensive tests, I've just ensured this passes all
[42FileChecker](https://github.com/jgigault/42FileChecker) and [PFT](https://github.com/gavinfielder/pft) checks (except unhandled flags, (see above)), and then some.
