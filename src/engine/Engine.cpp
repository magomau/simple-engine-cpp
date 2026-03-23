#include "Engine.h"

#include <SDL3/SDL.h>

#include "IGame.h"
#include "Input.h"
#include "Renderer.h"
#include "Window.h"
#include "core/Logger.h"

namespace simple_engine {

Engine::Engine()
    : m_running(false) {
}

Engine::~Engine() {
    shutdown();
}

bool Engine::init() {
    Logger::info("Initializing engine...");

    Logger::info("Step 1: Initializing SDL video and events.");
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        Logger::error("Failed to initialize SDL.");
        return false;
    }

    Logger::info("Step 2-3: Creating SDL window, OpenGL context, and making it current.");
    m_window = std::make_unique<Window>();
    if (!m_window->create("Simple Engine", 1280, 720)) {
        Logger::error("Failed to create window.");
        shutdown();
        return false;
    }

    Logger::info("Step 4: Creating renderer and loading OpenGL function pointers.");
    m_renderer = std::make_unique<Renderer>();
    if (!m_renderer->init(*m_window)) {
        Logger::error("Failed to initialize renderer.");
        shutdown();
        return false;
    }

    m_input = std::make_unique<Input>();
    m_running = true;

    Logger::info("Engine initialized successfully. Game objects can now create shaders and GPU resources.");
    return true;
}

void Engine::run(IGame& game) {
    if (!m_running || !m_input || !m_renderer || !m_window) {
        return;
    }

    Logger::info("Step 5: Initializing game layer after OpenGL is ready.");
    if (!game.init()) {
        Logger::error("Game initialization failed.");
        m_running = false;
        return;
    }

    const double performanceFrequency = static_cast<double>(SDL_GetPerformanceFrequency());
    Uint64 previousCounter = SDL_GetPerformanceCounter();

    while (m_running) {
        const Uint64 currentCounter = SDL_GetPerformanceCounter();
        const float deltaTime = static_cast<float>((currentCounter - previousCounter) / performanceFrequency);
        previousCounter = currentCounter;

        m_input->beginFrame();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                m_running = false;
            }

            m_input->processEvent(event);
            game.handleEvent(event);
        }

        game.update(*m_input, deltaTime);
        game.render(*m_renderer, *m_window);
        SDL_Delay(16);
    }

    game.shutdown();
}

void Engine::shutdown() {
    if (!m_window && !m_input && !m_renderer && !SDL_WasInit(0)) {
        return;
    }

    Logger::info("Shutting down engine...");

    m_input.reset();

    if (m_renderer) {
        m_renderer->shutdown();
        m_renderer.reset();
    }

    if (m_window) {
        m_window->destroy();
        m_window.reset();
    }

    if (SDL_WasInit(0)) {
        SDL_Quit();
    }

    m_running = false;
}

} // namespace simple_engine
