#include "Engine.h"

#include <SDL3/SDL.h>

#include "Application.h"
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

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        Logger::error("Failed to initialize SDL.");
        return false;
    }

    m_window = std::make_unique<Window>();
    if (!m_window->create("Simple Engine", 1280, 720)) {
        Logger::error("Failed to create window.");
        shutdown();
        return false;
    }

    m_renderer = std::make_unique<Renderer>();
    if (!m_renderer->init(*m_window)) {
        Logger::error("Failed to initialize renderer.");
        shutdown();
        return false;
    }

    m_application = std::make_unique<Application>();
    m_running = true;

    Logger::info("Engine initialized successfully.");
    return true;
}

void Engine::run() {
    if (!m_running || !m_application || !m_renderer) {
        return;
    }

    const double performanceFrequency = static_cast<double>(SDL_GetPerformanceFrequency());
    Uint64 previousCounter = SDL_GetPerformanceCounter();

    while (m_running) {
        const Uint64 currentCounter = SDL_GetPerformanceCounter();
        const float deltaTime = static_cast<float>((currentCounter - previousCounter) / performanceFrequency);
        previousCounter = currentCounter;

        m_application->processEvents(m_running);
        m_application->getScene().update(deltaTime);
        m_application->getScene().render(*m_renderer, *m_window);
        SDL_Delay(16);
    }
}

void Engine::shutdown() {
    if (!m_window && !m_application && !m_renderer && !SDL_WasInit(0)) {
        return;
    }

    Logger::info("Shutting down engine...");

    m_application.reset();

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
