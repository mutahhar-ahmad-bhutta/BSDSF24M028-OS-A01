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
