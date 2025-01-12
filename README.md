# TBD

## To build (outside of qt creator).

```sh
# Either at {QT_DIR}/bin/ to your PATH or use the full path.
qt-cmake -S . -B build

CMAKE_BINARY_DIR=build cmake --build build

ln -s build/compile_commands.json compile_commands.json
```

I have literally no idea if this will build outside of mac with the current lists. Try it and let me know if it doesn't
lol.

## Goals

The goal of this is to be my finance tracker for general use. Right now it requires two dependencies (qt and sqlite).
Here is a tentative feature list for the MVP.

- Dual entry accounting.
- Scheduled transactions.
- Future balance report.

There are a lot of features I can think of for after, but I think getting the basics is more important.

## Data

For now, the database will be sqlite. As I work there will be a `current.sql` file to represent the current state of the
tables. You are then free to build your own queries or integrations directly against the database. If you do so, ensure
that only one application is connecting to the database at any one time.

## License

It's GPL. There is no API, so it being GPL shouldn't be an issue for anyone. Qt is LGPL, and sqlite is public domain.
