# meg
A hybrid compiler project
## Testing
On Windows:
```powershell
cmake -S . -B build -G "Visual Studio 18 2026" -A x64
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure -V

```
On Linux:
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=gcc
cmake --build build
ctest --test-dir build --output-on-failure -V

```
