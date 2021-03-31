# Makefile

notes from https://makefiletutorial.com/

## Get Started

why do Makefiles exists?

- Makefiles are used to help decide which parts of a large program need to be recompiled. The goal of Makefiles is to compile whatever files need to be compiled, based on what files have changed.

### Running the Examples

First touch a file named `Makefile` with these contents. The second line must start with a tab rather than spaces.

```
hello:
    echo "hello world"
```

And run it!

```
$ make
echo "hello world"
hello world
```

### Makefile Syntax

```
targets: prerequisites
    command
    command
    command
```

- targets: filenames, seperated by spaces
- commands: 


