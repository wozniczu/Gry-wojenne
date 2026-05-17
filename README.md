# Gry wojenne

C++17, SFML 3, CMake 3.22+. Wskaż katalog SDK SFML (`include`, `lib`, `bin`), np. `-DCMAKE_PREFIX_PATH=...` albo rozpakuj do `third_party/SFML-3.0.0-msvc-x64` / `...-x86` (jak w `CMakeLists.txt`).

```text
cmake -S . -B build
cmake --build build
```

Uruchom `projekt.exe` z **katalogu głównego** repozytorium (obok folderów `fonts/` i `textures/`).
