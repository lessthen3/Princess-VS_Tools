#pragma once

#include "RenderingManager.h"
#include <atomic>


namespace Princess{

    class EditorManager
    {
    //////////////////////////////////////////////
    // Private Destructor
    //////////////////////////////////////////////
    private:
        ~EditorManager() = default;

    //////////////////////////////////////////////
    // Singleton Instance
    //////////////////////////////////////////////
    public:
        static EditorManager& Princess()
        {
            static EditorManager pwincess_uwu;
            return pwincess_uwu;
        }

    //////////////////////////////////////////////
    // Private Constructor
    //////////////////////////////////////////////
    private:
        EditorManager() = default;

        EditorManager(const EditorManager&) = delete;
        EditorManager& operator=(const EditorManager&) = delete;

    //////////////////////////////////////////////
    // Private Members
    //////////////////////////////////////////////
    private:
        unique_ptr<Logger> editor_logger = nullptr;

    //////////////////////////////////////////////
    // Public Members
    //////////////////////////////////////////////
    public:
        atomic<bool> m_Running = true;

        const uint32_t USER_DEFINED_UPDATE_FPS = 60;
        uint32_t          USER_DEFINED_RENDER_FPS = 120; //Needs to be adjustable in-game so no const >w<

    //////////////////////////////////////////////
    // Public Methods
    //////////////////////////////////////////////
    public:

        bool
            InitializePrincess(const string& fp_RootPath)
        {
            //Enable ANSI colour codes for windows console grumble grumble
            #if defined(_WIN32) || defined(_WIN64)
                EnableColors();
            #endif

            editor_logger = make_unique<Logger>();

            if(not editor_logger->Initialize("main_thread", fp_RootPath + "/logs", "EditorManager"))
            {
                PrintError("Unable to initialize internal editor logger, exiting program execution immediately");
                return false;
            }

            if (not InitalizeManagers(fp_RootPath))
            {
                editor_logger->LogAndPrint("Failed to initialize Peach Engine managers, ending engine program execution immediately", "EditorManager", Logger::LogLevel::Fatal);
                return false;
            }

            if (not InitializePhysFS(fp_RootPath.c_str()))
            {
                editor_logger->LogAndPrint("Failed to initialize Peach Engine virtual file system, ending engine program execution immediately", "EditorManager", Logger::LogLevel::Fatal);
                return false;
            }
            
            if (not SDL_Init(SDL_INIT_VIDEO))
            {
                editor_logger->LogAndPrint(format("SDL could not initialize! ending engine program execution immediately, SDL_Error: {}", string(SDL_GetError())), "EditorManager", Logger::LogLevel::Fatal);
                return false;
            }

            return true;
        }

        void
            StartMainEventLoop()
        {
            const float f_UserDefinedDeltaTime = 1.0f / USER_DEFINED_UPDATE_FPS;  // User-defined Update() rate
            float f_RenderDeltaTime = 1.0f / USER_DEFINED_RENDER_FPS;  // Should be variable to allow dynamic adjustment in-game

            float f_GeneralUpdateAccumulator = 0.0f;
            float f_RenderAccumulator = 0.0f;

            auto f_CurrentTime = chrono::high_resolution_clock::now();

            while (m_Running)
            {
                auto f_NewTime = chrono::high_resolution_clock::now();
                float f_FrameTime = chrono::duration<float>(f_NewTime - f_CurrentTime).count();
                f_CurrentTime = f_NewTime;

                // Prevent spiral of death by clamping frame time, frames will be skipped, but if you're already this behind then thats the least of your problems lmao
                if (f_FrameTime > 0.25)
                {
                    f_FrameTime = 0.25;
                }

                f_GeneralUpdateAccumulator += f_FrameTime;
                f_RenderAccumulator += f_FrameTime;

                PollUserInputEvents();  // Handle user input

                // User-defined game logic updates
                while (f_GeneralUpdateAccumulator >= f_UserDefinedDeltaTime)
                {
                    // PeachCore::PluginManager::ManagePlugins().UpdatePlugins(f_UserDefinedDeltaTime); //run loaded plugins alongside player scripts uwu
                    UpdateEditorState();
                    f_GeneralUpdateAccumulator -= f_UserDefinedDeltaTime;
                }

                if (f_RenderAccumulator >= f_RenderDeltaTime)
                {
                    RenderFrame();
                    f_RenderAccumulator -= f_RenderDeltaTime;
                }
            }
        }

        //////////////////////////////////////////////
        // Shutdown and Cleanup OwO
        //////////////////////////////////////////////
        bool
            ShutdownPrincess()
        {
            //CLEAN-UP AND ANY CLOSING THINGS THAT SHOULD BE LOGGED TO CHECK THE STATE OF THE ENGINE AS IT EXITS
            // PeachCore::PluginManager::ManagePlugins().ShutdownPlugins();
            SDL_Quit(); //just makes more sense to have the ShutdownPeachEngine method to do this

            return true;
        }
    
    //////////////////////////////////////////////
    // Private Methods
    //////////////////////////////////////////////
    private:
        //////////////////////////////////////////////
        // Engine Initialization Methods
        //////////////////////////////////////////////
        bool
            InitalizeManagers(const string& fp_RootPath)
        {
            const string f_LogDir = fp_RootPath + "/logs";

            // PeachCore::PluginManager::ManagePlugins().Initialize(f_LogDir, peach_engine_console.GetConsoleLogger());
            // PeachCore::AudioManager::AudioPlayer().Initialize(f_LogDir, peach_engine_console.GetConsoleLogger());
            Princess::RenderingManager::Renderer().Initialize(f_LogDir);

            //PeachCore::Logger::NetworkLogger().Initialize(f_LogDir, "NetworkLogger");

            //PeachCore::Logger::NetworkLogger().LogAndPrint("NetworkLogger successfully initialized", "Peach-E", "debug");

            editor_logger->LogAndPrint("NEW EDITOR ON THE BLOCK MY SLIME", "EditorManager", Logger::LogLevel::Warning);

            return true;
        }
        /// Setting Up and Setting Output Directory
        bool
            InitializePhysFS(const char* fp_RootPath)
        {
            if (not PHYSFS_init(fp_RootPath))
            {
                editor_logger->LogAndPrint("Failed to initialize PhysFS: " + static_cast<string>(PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode())), "EditorManager", Logger::LogLevel::Fatal);
                return false;
            }

            // Set the writable directory to the repo root
            if (not PHYSFS_setWriteDir(fp_RootPath))
            {
                editor_logger->LogAndPrint("Failed to set write directory: " + static_cast<string>(PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode())), "EditorManager", Logger::LogLevel::Fatal);
                return false;
            }

            // Mount the root directory for asset loading
            if (not PHYSFS_mount(fp_RootPath, nullptr, 1))
            {
                editor_logger->LogAndPrint("Failed to set search path: " + static_cast<string>(PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode())), "EditorManager", Logger::LogLevel::Fatal);
                return false;
            }

            editor_logger->LogAndPrint("PhysFS initialized at root: " + static_cast<string>(fp_RootPath), "EditorManager", Logger::LogLevel::Debug);
            return true;
        }

        void
            RenderFrame()
        {
            
        }

        void
            PollUserInputEvents()
        {
            ////////////////////////////////////////////////
            // Input Handling
            ////////////////////////////////////////////////
            SDL_Event f_Event;
            //nk_input_begin(pm_NuklearCtx);
            while (SDL_PollEvent(&f_Event))
            {
                if (f_Event.window.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
                {
                    m_Running = false;
                }
                //nk_sdl_handle_event(&f_Event);
            }
            //nk_sdl_handle_grab();
            //nk_input_end(pm_NuklearCtx);
        }

        void
            UpdateEditorState()
        {
            
        }

        //////////////////////////////////////////////
        // Thread Methods
        //////////////////////////////////////////////
        void 
            RenderThread()
        {
            while (true)
            {
                // Play audio
                cout << "Playing ur mom LOL...\n";
                this_thread::sleep_for(chrono::milliseconds(16)); // Simulate work
            }
        }

        void 
            AudioThread()
        {
            while (true)
            {
                // Play audio
                cout << "Playing audio...\n";
                this_thread::sleep_for(chrono::milliseconds(16)); // Simulate work
            }
        }

        void 
            ResourceLoadingThread()
        {
            while (true)
            {
                // Load resources
                cout << "Loading resources...\n";
                this_thread::sleep_for(chrono::milliseconds(100)); // Simulate work
            }
        }
    };
}