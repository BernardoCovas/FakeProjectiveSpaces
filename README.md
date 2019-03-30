# Build instuctions
Standard CMake build:

```bash
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_INSTALL_PREFIX=../
$ make -j
$ make install
```

# Usage
This program takes as arguments:
 - Command to run [`generate`, `compile`, `compute`]
 - Args to each command.

An example usage might be:
```bash
$ export COMPILE_COMMAND="gcc %s -O3 -shared -o %s"
$ mkdir ./det/ ./solved/
$ ./bin/fkps_app generate ./det/ ./parsed_C_dim8nfp6dets.txt
$ ./bin/fkps_app compile "${COMPILE_COMMAND}" ./det/*.c
$ ./bin/fkps_app compute ./solved/ ./det/*.so
```

Or a Windows PowerShell equivalent:
```PowerShell
$ $COMPILE_COMMAND="gcc %s -O3 -shared -o %s" # Or whatever command you need to compile a single file.
$ mkdir ./det,./solved
$ .\bin\fkps_app.exe generate .\det\ .\parsed_C_dim8nfp6dets.txt
$ .\bin\fkps_app.exe compile "${COMPILE_COMMAND}" (Get-Item .\det\*.c)
$ .\bin\fkps_app.exe compute .\solved\ (Get-Item .\det\*.so)
```
