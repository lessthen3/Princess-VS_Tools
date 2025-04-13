#pragma once

#include "Logger.h"
#include "ResourceLoader.h"

#include <SDL3/SDL.h>

namespace Princess{

    class RenderingManager
    {
    //////////////////////////////////////////////
    // Private Destructor
    //////////////////////////////////////////////
    private:
        ~RenderingManager() = default;

    //////////////////////////////////////////////
    // Singleton Instance
    //////////////////////////////////////////////
    public:
        static RenderingManager& Renderer()
        {
            static RenderingManager princess_renderer;
            return princess_renderer;
        }

    //////////////////////////////////////////////
    // Private Constructor
    //////////////////////////////////////////////
    private:
        RenderingManager() = default;

        RenderingManager(const RenderingManager&) = delete;
        RenderingManager& operator=(const RenderingManager&) = delete;

    //////////////////////////////////////////////
    // Private Members
    //////////////////////////////////////////////
    private:
        unique_ptr<Logger> rendering_logger = nullptr;
        bool pm_IsInitialized = false;

        SDL_Window* pm_MainWindow = nullptr;

    //////////////////////////////////////////////
    // Public Members
    //////////////////////////////////////////////
    public:
        bool 
            Initialize
            (
                const string& fp_LogOutputDirectory
            )   
        {
            if(pm_IsInitialized) ///just in case i do something incredibly stupid, which is definitely not out of the question UwU
            {
                rendering_logger->LogAndPrint("Tried to initialize RenderingManager again! be careful brutha", "RenderingManager", Logger::LogLevel::Warning);
                return false;
            }

            rendering_logger = make_unique<Logger>();

            if (not rendering_logger->Initialize("render_thread", fp_LogOutputDirectory, "RenderingManager"))
            {
                PrintError("Unable to initialize Rendering Logger, exiting execution immediately");
                return false;
            }

            rendering_logger->LogAndPrint("RenderingLogger successfully initialized", "RenderingManager", Logger::LogLevel::Debug);

            if (not CreateSDLWindow(&pm_MainWindow, "Princess", 800, 600))
            {
                rendering_logger->LogAndPrint("Initialization failed: RenderingManager was not able to create main window, exiting execution immediately", "RenderingManager", Logger::LogLevel::Fatal);
                return false;
            }

            if (not InitializeVulkan())
            {
                rendering_logger->LogAndPrint("Initialization failed: RenderingManager was not able to initialize Vulkan, exiting execution immediately", "RenderingManager", Logger::LogLevel::Fatal);
                return false;
            }

            pm_IsInitialized = true;
            return true;
        }

        bool
            CreateSDLWindow
            (
                SDL_Window** fp_SDLWindow,
                const string& fp_WindowTitle,
                const uint32_t fp_WindowWidth,
                const uint32_t fp_WindowHeight
            )
            const
        {
            if (*fp_SDLWindow)
            {
                rendering_logger->LogAndPrint("Tried passing a valid SDL_Window* handle for window creation, please cleanup original SDL window or dereference pointer before attempting to create a new SDL window", "RenderingManager", Logger::LogLevel::Error);
                return false;
            }

            *fp_SDLWindow = SDL_CreateWindow
            (
                fp_WindowTitle.c_str(),
                fp_WindowWidth,
                fp_WindowHeight,
                SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE
            );

            if (not *fp_SDLWindow)
            {
                rendering_logger->LogAndPrint("Window could not be created! SDL_Error: " + string(SDL_GetError()), "RenderingManager", Logger::LogLevel::Fatal);
                return false;
            }

            return true;
        }
    //////////////////////////////////////////////
    // Private Methods
    //////////////////////////////////////////////
    private:
    //////////////////////////////////////////////
    // Initialization Methods
    //////////////////////////////////////////////
        bool
            InitializeVulkan()
        {
            return true; // >w<
        }
    };

}