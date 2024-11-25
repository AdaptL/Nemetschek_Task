#include <iostream>
#include <cstdlib>
#include "Application.h"

Application* InitializeApplication();

void DeleteApplication(Application* app);

int main()
{
    Application* app = InitializeApplication();

    if (!app)
        return EXIT_FAILURE;

    try
    {
        app->Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
        DeleteApplication(app);
        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::cerr << "Failed to run application!" << std::endl;
        DeleteApplication(app);
        return EXIT_FAILURE;
    }

    DeleteApplication(app);

    return EXIT_SUCCESS;
}

Application* InitializeApplication()
{
    return new Application();
}

void DeleteApplication(Application* app)
{
    if (app != nullptr)
        delete app;

    app = nullptr;
}