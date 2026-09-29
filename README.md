<div align="center">

# One Library, Two Ways to Link

**A C utility library built as both a static and a shared library,<br>to see what the operating system does differently at run time.**

[Releases](https://github.com/mutahhar-ahmad-bhutta/BSDSF24M028-OS-A01/releases) ·
[Report](REPORT.md) ·
[Man pages](man/man3)

*Operating Systems · Programming Assignment 01 · PUCIT*

</div>

---

## Try it

```bash
git clone https://github.com/mutahhar-ahmad-bhutta/BSDSF24M028-OS-A01.git
cd BSDSF24M028-OS-A01
make
./bin/client_static
```

Requires Linux with `gcc` and `make`. Built and tested on Kali Linux (VirtualBox).

## How the code becomes a program

```
 mystrfunctions.c ─┐                  ┌──► libmyutils.a ──► client_static
                   ├─► gcc -fPIC -c ──┤      (ar, ranlib)    code copied in
 myfilefunctions.c ┘                  │
                                      └──► libmyutils.so ──► client_dynamic
 main.c ──► main.o ─────────────────────── (gcc -shared)     code loaded at run time
```

A top-level `Makefile` passes the work to `src/Makefile` (recursive make), which compiles, archives and links everything in order.

## What I found

**Program size**, measured with `ls -l bin/`:

```
client_dynamic     ▌  16,448 bytes   library loaded at run time
client_static      ▌  16,840 bytes   library copied in
client_fullstatic  ████████████████████████████████████████  778,368 bytes   C library copied in too
```

1. **Static linking copies code; it doesn't change it.** `client` (linked from plain `.o` files) and `client_static` (linked from `libmyutils.a`) have the same SHA-256 hash, so they are byte-for-byte identical.

2. **Dynamic linking leaves the code out.** `nm` shows `T mystrlen` in `client_static` (the code is inside) and `U mystrlen` in `client_dynamic` (it must be found at run time). That is where the 392-byte difference comes from.

3. **Bigger libraries mean a bigger gap.** Copying the whole C library in with `gcc -static` made the program about 46 times larger.

4. **The loader has its own rules.** `client_dynamic` first failed with *"cannot open shared object file"*, because `-L` only helps at build time. After `export LD_LIBRARY_PATH=$PWD/lib`, `ldd` showed the loader finding `libmyutils.so` in my `lib/` folder.

<details>
<summary><b>What's in the library</b></summary>

```c
int mystrlen(const char* s);                        // length of s
int mystrcpy(char* dest, const char* src);          // copy, returns chars copied
int mystrncpy(char* dest, const char* src, int n);  // copy max n, always adds '\0'
int mystrcat(char* dest, const char* src);          // append, returns new length

int wordCount(FILE* file, int* lines, int* words, int* chars);  // like wc
int mygrep(FILE* fp, const char* search_str, char*** matches);  // like grep
```

`src/main.c` tests every function on `test.txt`. The results match the real `wc` and `grep` commands.

</details>

<details>
<summary><b>Install system-wide</b></summary>

```bash
make                  # build as a normal user first
sudo make install     # client → /usr/local/bin, man pages → /usr/local/share/man/man3
client                # run from any folder
man mygrep            # read the docs
sudo make uninstall   # remove everything
```

</details>

<details>
<summary><b>How this repo grew</b></summary>

Each stage was built on its own branch, merged into `main`, tagged and released.

- `v0.1.1-multifile`: modules and recursive Makefiles
- `v0.2.1-static`: static library `libmyutils.a`
- `v0.3.1-dynamic`: shared library `libmyutils.so` with position-independent code
- `v0.4.1-final`: man pages and install target

</details>

---

<div align="center">

**Mutahhar Ahmad** · BSDSF24M028<br>
[GitHub](https://github.com/mutahhar-ahmad-bhutta) · [Portfolio](https://mutahhar.vercel.app)

<sub>Instructor: Dr. Muhammad Arif Butt<br>
Teaching Assistants: Khadija Shahzad · Rida Batool · Areeba Noor</sub>

</div>
