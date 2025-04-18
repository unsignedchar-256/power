# `powermgr`
The shittiest way ever exist to shut down your Linux machine with ncurses.

# ⚠️ Warning
`root` permission is required. Please log in to `root` user or use `sudo` instead.

## HW/SW Requirements
1. Any Linux distribution
2. Screen with resolution at least 640x400 (80x25 characters) with support at least 16 colors

> as long your Linux can boot lmao 💀🙏🏻

## Building
### Prerequisite
- GNU Compiler Collection (GCC) or any compilers (requires modification of `build.sh`)

### Dependencies
- `libstdc++`
- `libncurses-dev` or `ncurses-devel`
- `libtinfo`

### Compiling
Modify the `build.sh` file first with your own configuration then run
```
bash build.sh
```
or
```
chmod "uga+x" "build.sh"
./build.sh
```

## License
Please refer to the `LICENSE` file.<br><br>


---
> the dev ~~can't write~~ is too lazy to write a Makefile<br>icl ts pmo sm 💔