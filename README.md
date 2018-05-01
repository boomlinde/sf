sf
==

"ShaderForth", closely following the implementation of [Forth Haiku
Salon], implemented in C. A Forth-like language is executed once for
each pixel in an output image. The image is output on the standard
output in plain PPM format.

Features
--------

-   Simple Forth-like compiler based on the Forth Haiku Salon language
-   Plain PPM output
-   Script to generate animated GIF pictures (multicore!): `sfgif`
-   All non-primitive words are inlined

Requirements
------------

-   C compiler (I've used GCC but any C99 compiler should work
-   bash, xargs, ImageMagick (`convert`)

Missing features, compared to Forth Haiku Salon
-----------------------------------------------

-   `dt`: this implementation has no concept of time, though `dt` can be
    implemented as part of `sfgif`
-   `mx`, `my`, `button`, `buttons`: this implementation has no input
    handling
-   `audio`: this implementation has no audio output
-   `sample`, `bwsample`: this implementation has no image sampling
-   `\`: this implementation has no line comments (yet)
-   `@`, `!`: this implementation provides no memory access (yet)
-   `if`, `else`, `then`: this implementation is (for now) completely
    branchless

Additional features
-------------------

-   `width`, `height`: Set the output image height/width. The program is
    executed once with its other output discarded just to retreive these
    values if set. If they are not set, the default of 256x256 is used.

Development
-----------

A brief description of the modules:

-   codebuf: A growable buffer that holds instructions
-   compiler: Sets up a tokenizer and handles the tokens one by one,
    compiling them to the virtual machine
-   instruction: The instruction type and the code that runs when it is
    executed
-   machine: contains two codebufs, two stacks and a small scratch
    memory. One data stack and one "return stack" (which isn't actually
    a return stack in FOrth Haiku Salon and can be used across word
    boundaries); one main codebuf and one macro codebuf that holds
    compiled words
-   readfile: function to read a file by filename, allocating space for
    it and returning the data, leaving it for the caller to free
-   stack: Simple fixed size stack which can be used for push/pop
    operations
-   std: Standard library of primitive words
-   tokenizer: Simple tokenizer, the only real concern is to output
    words separated by whitespace one by one
-   types: Some of the types are interdependent, so most types relating
    to the virtual machine are stored here
-   wordlink: a simple linked list dictionary. This is used by the
    compiler to look up word names
-   sf: Main program, sets up the virtual machine, handles arguments
    etc.

TODO
----

-   Fix potential buffer overflows (token buffer, wordlink name)
-   Stack over/underflow should be a runtime error
-   Compilation, runtime error output with line numbers
-   Implement `\` line comments
-   Implement `@` and `!` as in ForthSalon (did not exist last time I
    used it)
-   (Maybe) implement `IF ... ELSE ... THEN`, though I like keeping it
    branchless
-   (Maybe) implement `random`, though I like that programs are now pure
    functions
-   (Maybe) C89 compliance (I want to build this in Turbo C eventually)

  [Forth Haiku Salon]: https://forthsalon.appspot.com/