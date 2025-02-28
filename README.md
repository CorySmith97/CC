# CC

## Philosophies

### Memory Management

This project will use ZII (zero is initialization). The idea is if you are going to
create or use a struct, begin with a zero-ed version of that, and then modify in
place rather than return a value.

Example:

Prefer

```{c}
    allocator_t a;
    arena_allocator_init(&a, 1024);
```



- Amazing talk that explains a bit of it.

https://www.youtube.com/watch?v=rX0ItVEVjHc&t=2543s

### Resources

clang on windows

https://stackoverflow.com/questions/63914108/using-clang-in-windows-10-for-c-c

https://git-scm.com/book/en/v2/Getting-Started-About-Version-Control

https://www.raylib.com/cheatsheet/cheatsheet.html

https://www.raylib.com/index.html

https://learnopengl.com/Introduction
