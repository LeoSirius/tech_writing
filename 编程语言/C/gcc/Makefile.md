# Makefile

notes from https://makefiletutorial.com/

## Get Started

why do Makefiles exists?

- Makefiles are used to help decide which parts of a large program need to be recompiled. The goal of Makefiles is to compile whatever files need to be compiled, based on what files have changed.

### Running the Examples

First touch a file named `Makefile` with these contents. The second line must start with a tab rather than spaces.

```makefile
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

```makefile
targets: prerequisites (dependencies)
    command
    command
    command
```

- targets: filenames, seperated by spaces
- commands: series of steps typically used to make the target(s)
- prerequisites: filenames, seperated by spaces. These files need to exists before the commands for the target are run.

### Beginner Examples

```makefile
blah: blah.o
    cc blah.o -o blah # Runs third

blah.o: blah.c
    cc -c blah.c -o blah.o # Runs second

blah.c:
    echo "int main() { return 0; }" > blah.c # Runs first
```

We type command `make blah`. To get blah, need blah.o. To get blah.o, need blah.c.

### Variables

Variables must be strings. Both `$()` and `${}` can referece them.

```makefile
files = file1 file2
some_file: $(files)
	echo "Look at this variable: " $(files)
	touch some_file

file1:
	touch file1
file2:
	touch file2

clean:
	rm -f file1 file2 some_file
```

## Targets

### all

```makefile
all: one two three

one:
	touch one
two:
	touch two
three:
	touch three

clean:
	rm -f one two three
```

### multiple targets

Commands will be run for each target

> `$@` is an automatic variable contains the target name

```makefile
all: f1.o f2.o

f1.o f2.o:
	echo $@
# Equivalent to:
# f1.o:
#	echo $@
# fi.o:
#	echo $@
```

## Automatic Variables and Wildcards

### `*` wildcard

`*` is better wrapped in `wildcard` function. The reason will be described below.

```makefile
# Print out file information of every .c file
print: $(wildcard *.c)
	ls -la $?
```

Notice the right and wrong below.


```makefile
thing_wrong := *.o # Don't do this! '*' will not get expanded
thing_right := $(wildcard *.o)

all: one two three four

# Fails, because $(thing_wrong) is the string "*.o"
one: $(thing_wrong)

# Stays as *.o if there are no files that match this pattern :(
two: *.o 

# Works as you would expect! In this case, it does nothing.
three: $(thing_right)

# Same as rule three
four: $(wildcard *.o)
```

### `%` wildcard
