/*******************************************************************
 *                                             Princess v0.0.1
 *                           Created by Ranyodh Mandur - � 2024
 *
 *                         Licensed under the MIT License (MIT).
 *                  For more details, see the LICENSE file or visit:
 *                        https://opensource.org/licenses/MIT
 *
 *                         Princess is an open-source visual code editor
********************************************************************/
#define SDL_MAIN_HANDLED

#define NK_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define VOLK_IMPLEMENTATION
#define MINIAUDIO_IMPLEMENTATION

#include "../include/EditorManager.h"

#include <csignal>

static void 
    SegFaultHandler(int fp_Signal) //primitive segfault handler
{
    Princess::PrintError(format("[!] Crash signal received: {}", fp_Signal));
    // possibly notify watchdog or dump stack trace
    exit(EXIT_FAILURE);
}

//////////////////////////////////////////////
// MAIN FUNCTION BABY
//////////////////////////////////////////////
int 
    main(int fp_ArgCount, const char* fp_ArgVector[])
{

    cout << "Hello World!" << "\n";

    //WARNING: WE ONLY USE THIS FOR DEVELOPMENT, FOR DEPLOYMENT WE NEED THIS DIRECTORY TO BE THE BASE DIR OF THE EXECUTABLE
    // Get the full path of the executable
    filesystem::path mf_ExePath = filesystem::absolute(fp_ArgVector[0]);
    filesystem::path mf_TopLevelDir = mf_ExePath.parent_path();  // Start from the executable directory

    // Traverse upwards until we find the "Peach-E" directory
    while (not mf_TopLevelDir.empty() and mf_TopLevelDir.filename() != "Princess-VS_Tools")
    {
        mf_TopLevelDir = mf_TopLevelDir.parent_path();
    }

    if (mf_TopLevelDir.empty())
    {
        Princess::PrintError("Failed to find the top-level directory 'Peach-E'!", Princess::Colours::Magenta);
        return EXIT_FAILURE;
    }

    string mf_RootProjectPath = mf_TopLevelDir.string();

    signal(SIGSEGV, SegFaultHandler); //XXX: used for trying to close and flush logs on seg fault

    ////////////////////////////////////////////////
    // Setup Environment
    ////////////////////////////////////////////////
    try
    {
        auto editor_manager = &Princess::EditorManager::Princess();

        editor_manager->InitializePrincess
        (
            mf_RootProjectPath
        );

        editor_manager->StartMainEventLoop();
        editor_manager->ShutdownPrincess();

        return EXIT_SUCCESS;
    }
    catch (const std::exception& Exception) ///Try to ensure all destructors are called especially close() on LogManager
    {
        Princess::PrintError(format("Unhandled exception: {}", Exception.what()));

        return EXIT_FAILURE;
    }
}
