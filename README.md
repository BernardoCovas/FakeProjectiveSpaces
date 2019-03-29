# Build instuctions
Standard CMake build:

```
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_INSTALL_PREFIX=../
$ make -j
$ make install
```

# Usage
This program takes as arguments:
 - Directory to save the solution files.
 - Compiled determinantQ function to use.

 An example usage might be:
 ```
$ find ./determinants/*.c -exec gcc {} -O2 -shared -o {}.so \;
$ find ./determinants/*.so | xargs ./bin/fkps_app ./folder/
 ```

The above command first compiles all the determinantQ functions  
in a folder with 2 levels of optimization (To make it as efficienas possible) and then starts  
the program with all of the compiled files as arguments.  
Each compiled file argument generates a thread.  
As results are obtained, they will be flushed to ./folder/.  
./folder/ must exist.