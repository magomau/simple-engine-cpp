# 🎮 Simple Engine C++

Custom game engine built from scratch using **C++**, **SDL3**, and **OpenGL**.
This project focuses on learning low-level graphics programming, engine architecture, and real-time rendering.

---

## 🚀 Features

* 🪟 Window creation using SDL3
* 🎨 OpenGL rendering pipeline
* 🔺 Triangle rendering
* 🔄 Real-time rotation (transformations)
* 🧱 Modular engine structure
* 📝 Basic logging system

---

## 🧠 Architecture

The engine is structured in a modular way to separate responsibilities:

```
src/
├── core/
│   └── Logger
├── engine/
│   ├── Application
│   ├── Engine
│   ├── Window
│   ├── Renderer
│   ├── Shader
│   └── GLFunctions
└── main.cpp
```

### Key Components

* **Application** → Entry point and main loop
* **Engine** → Core engine lifecycle management
* **Window** → SDL3 window handling
* **Renderer** → OpenGL rendering logic
* **Shader** → Shader compilation and management
* **GLFunctions** → OpenGL function loading
* **Logger** → Debug and info output

---

## 🖥️ Technologies Used

* C++17+
* SDL3
* OpenGL
* CMake

---

## ⚙️ Build Instructions

### 📌 Requirements

* CMake (3.20+ recommended)
* C++ compiler (MSVC / GCC / Clang)
* SDL3 installed
* OpenGL support

---

### 🛠️ Build (Windows / Linux)

```bash
git clone https://github.com/magomau/simple-engine-cpp.git
cd simple-engine-cpp

mkdir build
cd build

cmake ..
cmake --build .
```

---

### ▶️ Run

```bash
./SimpleEngine
```

---

## 🎥 Current Output

The engine currently renders a rotating triangle using OpenGL:

* Vertex buffers
* Shader pipeline
* Transformations

---

## 🛣️ Roadmap

Planned features:

* 🎮 Input system (keyboard & mouse)
* 📷 Camera system
* 🧩 Multiple objects rendering
* 🧮 Math library (vectors, matrices)
* 🎨 Texture support
* 💡 Lighting system
* 🧠 ECS (Entity Component System)

---

## 📚 Learning Goals

This project is focused on:

* Understanding how game engines work internally
* Learning OpenGL at a low level
* Practicing clean architecture in C++
* Building a scalable rendering pipeline

---

## 📌 Author

**Mauricio Carpentier**
Software Engineer | Game Dev learner

---

## ⭐ Notes

This is a learning project and will evolve over time.
Contributions, ideas, and feedback are welcome!

