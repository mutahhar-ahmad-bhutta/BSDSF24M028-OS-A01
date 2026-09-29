# OS Programming Assignment 01 - Report

**Name:** Mutahhar Ahmad
**Roll No:** BSDSF24M028

## Feature 2: Multi-file Build

### Q1. Explain the linking rule `$(TARGET): $(OBJECTS)`. How does it differ from a rule that links against a library?

In my Makefile, `$(TARGET)` is the final program (`../bin/client`) and `$(OBJECTS)` is the list of object files (`main.o`, `mystrfunctions.o` and `myfilefunctions.o`). The rule means that the program is built from these object files. Make checks the dates of the files. If any object file is newer than the program, it runs the link command again. Otherwise it skips it, because the program is already up to date.

The command under this rule gives all the object files directly to gcc:

`gcc ../obj/main.o ../obj/mystrfunctions.o ../obj/myfilefunctions.o -o ../bin/client`

The linker then joins them into one executable, so the code from every object file ends up inside the program.

When we link against a library, the rule is different. The program depends on `main.o` and a library file (like `libmyutils.a`) instead of all the separate object files. We also don't list the object files by name. Instead we use two flags: `-L` tells gcc which folder to look in for the library, and `-l` tells it the library's name. For example:

`gcc main.o -L../lib -lmyutils -o client`

So in Feature 2 we link the object files ourselves, one by one. With a library, the functions are already packed together, and the linker takes only what the program needs from it.

### Q2. What is a git tag and why is it useful? What is the difference between a simple and an annotated tag?

A git tag is a name that we attach to one specific commit, usually to mark a version, like `v0.1.1-multifile`. It is useful because a branch keeps moving forward every time we commit, but a tag stays on the same commit forever. So even later, we can always go back and see exactly what the code looked like at that version. GitHub Releases are also created from tags.

A simple (lightweight) tag is just a name pointing to a commit. It is made with `git tag v1.0` and stores nothing else.

An annotated tag stores extra information: the name and email of the person who made it, the date, and a message. It is made with `git tag -a v1.0 -m "message"`. Annotated tags are better for official versions because they record who released the version, when, and why. I used an annotated tag for `v0.1.1-multifile`.

### Q3. What is the purpose of a GitHub Release? What is the significance of attaching binaries?

A GitHub Release is an official version of the project that people can download. It is connected to a tag and has a title and a description that explains what the version does. Instead of downloading whatever code is currently on a branch, users get a stable version that is known to work.

Attaching binaries means uploading the already compiled program (in my case `bin/client`) to the release. This is important because a normal user may not have gcc or make installed, or may not know how to build C code. With the binary attached, they can just download it and run it. The source code is still available for developers, but the binary makes the program easy to use for everyone else.
## Feature 3: Static Library

### Q1. Compare the Makefile from Part 2 and Part 3. What are the key differences in the variables and rules that enable the creation of a static library?

In Part 2, the Makefile had one list of object files (`OBJECTS`) and a single link rule that gave all the object files directly to gcc to make `client`.

In Part 3, I made these changes:

- **New variables:** `AR` (the archiver tool), `ARFLAGS` (options for ar), `LIB_DIR` (folder for libraries), `LIB_NAME` (the name `myutils`) and `STATIC_LIB` (the full path `../lib/libmyutils.a`).
- **Split object lists:** instead of one list, I now have `LIB_OBJS` (the string and file function objects that go into the library) and `MAIN_OBJ` (`main.o`, which uses the library). `main.o` does not go into the library.
- **A new rule to build the library:** `$(STATIC_LIB): $(LIB_OBJS)` runs `ar rc` to pack the object files into `libmyutils.a`, and then `ranlib` to add an index.
- **A changed link rule:** `$(TARGET): $(MAIN_OBJ) $(STATIC_LIB)`. Instead of listing every object file, it links `main.o` with the library using `-L../lib` (where to look) and `-lmyutils` (which library to use).
- **A new program name:** the output is now `client_static`.

Because the program depends on the library, and the library depends on the object files, make builds everything in the right order automatically.

### Q2. What is the purpose of the `ar` command? Why is `ranlib` often used immediately after it?

`ar` (archiver) is used to make a static library. It takes several object files and packs them into one archive file with a `.a` extension, a bit like making a zip file of compiled code. In my project, `ar rc` put `mystrfunctions.o` and `myfilefunctions.o` into `libmyutils.a`. I can list what is inside with `ar -t lib/libmyutils.a`.

`ranlib` adds an index (symbol table) to the archive. This index is a list of which function is inside which object file. When the linker needs a function like `mystrlen`, it can look it up in the index quickly instead of searching through every object file. That is why `ranlib` is run right after `ar`. On modern Linux, using `ar rcs` (with the `s` option) creates the same index, so running `ranlib` separately does the same job as the `s` flag.

### Q3. When you run `nm` on your `client_static` executable, are the symbols for functions like `mystrlen` present? What does this tell you about how static linking works?

Yes. When I ran `nm bin/client_static | grep my`, all my functions (`mystrlen`, `mystrcpy`, `mystrncpy`, `mystrcat`, `wordCount` and `mygrep`) were listed with the letter `T`. `T` means the code of the function is inside the file.

In `main.o`, these same functions were marked `U` (undefined), because `main.c` only calls them and does not contain their code.

This shows that in static linking, the linker copies the actual code of the functions from `libmyutils.a` into the final executable. After linking, the program does not need the library anymore to run. I also checked this with `readelf -d bin/client_static`: the only needed shared library was `libc.so.6`, and `libmyutils` was not listed.

One interesting thing I noticed is that `printf` still showed `U` in `client_static`. This is because only my own library was linked statically. The standard C library (which contains `printf`, `fopen` and `malloc`) is still linked dynamically, and the operating system loads it when the program starts.
