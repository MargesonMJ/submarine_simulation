# Submarine Simulation

A 3D submarine simulation written in C using OpenGL and FreeGLUT.

This project features a visually interactive environment where a submarine navigates through an ocean scene, complete with ocean waves, fog, 3D models, and flocking fish. The simulation showcases environmental effects and modular programming design, demonstrating advanced OpenGL capabilities.

---

## Author

**Matthew Margeson**  
Email: margesonmj@dal.ca  
GitHub: [margesonmj](https://github.com/margesonmj)

---

## Features

- **3D Submarine Control**: Navigate a 3D submarine through an underwater environment using keyboard controls.
- **OBJ Model Integration**: Submarine rendered from a loaded `.obj` model file (replaced by `.txt`).
- **Ocean Wave Simulation**: Dynamic vertical wave motion applied to the water grid.
- **Environmental Effects**:
  - Blue ocean tint fog rendering for underwater appearance.
  - Sunlight-inspired lighting.
- **Boid-Based Fish Flocking**:
  - 3D boids simulating fish behavior
  - Flock movement with basic cohesion, alignment, and separation
- **Modular Code Design**: Clear separation of logic for input, physics, rendering, and simulation components.

---

## Controls

| Key             | Action                          |
|-----------------|---------------------------------|
| `w`, `s`        | Move submarine forward/backward |
| `a`, `d`        | Move submarine left/right       |
| `Arrow Up/Down` | Move submarine up/down          |
| `u`             | Toggle wire frame mode          |
| `b`             | Toggle fog                      |
| `f`             | Toggle full screen window       |
| `q`             | Quit the simulation             |

---

## Build & Run

### Requirements

- A C compiler (e.g., `gcc`, `clang`)
- Make (optional, for simplified builds)

> All necessary `.h`, `.lib`, and `.dll` files for OpenGL and FreeGLUT are included in the project directory—no additional installation required.

### Build (example using `gcc`)

```bash

gcc -o submarine_simulation source/*.c -Iinclude -Ilibraries/include -Llibraries/lib -lfreeglut -lopengl32 -lm

```

### Run

```bash

submarine_simulation.exe

```

---

## License

This project is licensed under the [MIT License](LICENSE).
