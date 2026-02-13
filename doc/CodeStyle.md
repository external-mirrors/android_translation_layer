#### clang-format rules
We use two custom clang-format rules (TODO: attempt to upstream). You can get a static binary
of clang-format with our patches here: https://gitlab.com/android_translation_layer/clang-format/-/artifacts.

#### clang-format caveats
- clang-format is set to respect existing line wrapping decisions, but you must e.g wrap before
  binary operators (not after) in order for it to not reformat stuff into a single line
- use `clang-format off/on` comments for stuff that clang-format doesn't understand, like arranging
  single dimensional arrays into a 2D grid
- when commenting out code, don't put the start of the comment at the start of the line, otherwise
  clang-format will indent it and there will be double indents

#### manual formatting rules
- aim for ~100 columns
- only add blocks for `case` if you need to create a scope
- omit blocks for if/for etc IF AND ONLY IF every single branch contains a single statement;
  nested if/for etc DO NOT count as single statements

example:

```C
if (i <= 0)
	i++;
else
	i--;

if (i <= 0) {
	i++;
} else {
	while(i > 0)
		i--;
}
```
