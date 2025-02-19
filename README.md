# CC

## Philosophies

### Memory Management

This project will use ZII (zero is initialization). The idea is if you are going to
create or use a struct, begin with a zero-ed version of that, and then modify in
place rather than return a value.

Example:

Prefer

```{c}
arena_t arena = {};
InitArena(&arena, 1024);
```
Over

```{c}
arena_t arena = InitArena(1024);
```

This is a good practice for managing data. It makes your life easier when debugging.

### ECS

This is something I want to learn more about. We will be using a very simple ecs system.
You can think about ecs like a local database, and an entity has an index for
entries for each type that we need.

IE

---------------------------
|Health | Position | Stats|
|                         |
|                         |
---------------------------

Each entity has an id that lets us know which data is its in the table.
This is a concept of DOD (Data oriented design), it greatly helps with
cache locality, or in other words, it means the CPU is only loading the data
it is operating on at that time. Example we update all positions at the same time
for all entities.

- Amazing talk that explains a bit of it.

https://www.youtube.com/watch?v=rX0ItVEVjHc&t=2543s

### Resources

clang on windows

https://stackoverflow.com/questions/63914108/using-clang-in-windows-10-for-c-c

https://git-scm.com/book/en/v2/Getting-Started-About-Version-Control

https://www.raylib.com/cheatsheet/cheatsheet.html

https://www.raylib.com/index.html

https://learnopengl.com/Introduction
