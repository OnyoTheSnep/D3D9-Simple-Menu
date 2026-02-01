# D3D9 Simple Menu

A lightweight **Direct3D 9** (D3D9) menu / UI overlay written in C++.

This repo is meant as a small, easy-to-read starting point for drawing a simple in-game (or in-app) menu using a D3D9 device.

> **Note**: This project is intended for **legitimate development / debugging / tooling** in applications you own or have permission to modify.

![Basic preview](assets/preview.gif)

---

## Features

- Simple menu framework (tabs / items / values)
- Basic animation helpers (`Animations.*`)
- Font/text rendering helper (`cFont.*`)
- Example usage scaffold (`Example.*`)
- Minimal D3D9 window/device bootstrap (`WinD3D.*`)

---

## Project Layout

- `Menu.h / Menu.cpp` – menu UI + drawing logic
- `Animations.h / Animations.cpp` – small animation utilities
- `cFont.h / cFont.cpp` – font rendering helper
- `WinD3D.h / WinD3D.cpp` – Win32 + D3D9 init (device creation, loop helpers)
- `Example.h / Example.cpp` – example menu content + callbacks
- `main.h / main.cpp` – entry point / wiring

The repository also includes a submodule folder:

- `D3D9-DirectX-SDK/` – DirectX SDK dependency (submodule)

---

## Requirements

- **Windows**
- **Visual Studio** (2019/2022 recommended)
- **DirectX SDK (June 2010)** *or* a compatible setup that provides D3D9 headers/libs.

If you're using the legacy DXSDK, make sure the `DXSDK_DIR` environment variable is set (Visual Studio can also be configured via project include/lib paths).

---

## Clone

This repo uses a submodule, so clone with submodules enabled:

```bash
git clone --recurse-submodules https://github.com/OnyoTheSnep/D3D9-Simple-Menu.git
```

If you already cloned without submodules:

```bash
git submodule update --init --recursive
```

---

## Build (Visual Studio)

1. Open the folder in Visual Studio (**File → Open → Folder…**) **or** create a new VS solution and add the `.cpp/.h` files.
2. Make sure your project targets **x86** or **x64** consistently with your D3D9 libs.
3. Add include paths for D3D9 headers (one of the following):
   - `$(DXSDK_DIR)Include` (legacy SDK), or
   - Windows SDK / custom include path if you provide your own D3D9 headers.
4. Add library paths:
   - `$(DXSDK_DIR)Lib\x86` or `$(DXSDK_DIR)Lib\x64` (legacy SDK)
5. Link against (typical minimum):
   - `d3d9.lib`
   - `d3dx9.lib` *(if used by your code)*
   - `d3dcompiler.lib` *(if used)*
   - `winmm.lib`, `user32.lib`, `gdi32.lib` *(common Win32 deps)*

> Exact linker deps depend on what you enabled in the code. If you get unresolved externals, add the missing `.lib` shown in the linker error.

---

## Run

Build and run from Visual Studio (or run the produced `.exe`).

The entry point is in `main.cpp`. The sample menu content is in `Example.cpp`.

---

## Customization

- Add tabs/items in `Example.cpp`
- Change look & feel in `Menu.cpp` (sizes, spacing, colors, font usage)
- Adjust animation speed/curves in `Animations.cpp`
- Replace font logic inside `cFont.cpp` if you prefer a different text renderer

---

## License

MIT — see [LICENSE](LICENSE).

---

## Credits

Made by **Onyo (Bar)**.
