Gecode Tuple Question
=====================

This project contains a minimal example that occompanies a question
about [Gecode][gecode].

=======
Compiling
---------

In order to compile the example execute

```sh
g++ -I/usr/local/include/ -c tuple.cpp
```

You can link it with

```sh
g++ -o tuple -L/usr/local/lib/  tuple.o -lgecodekernel -lgecodesearch -lgecodeint
```
[gecode]: http://www.gecode.org/
