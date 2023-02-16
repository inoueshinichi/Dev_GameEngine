/**
 * @file main_app.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <pch.hpp>
#include <application.hpp>

int main(int argc, char** argv)
{
    IS_DEFINE_SHIFTJIS_TO_UTF8

    // MainThreadでXamlホストを展開
    init_apartment(apartment_type::single_threaded);
    WindowsXamlManager winXamlManager = WindowsXamlManager::InitializeForCurrentThread();

    is::Application app(argc, argv);

    return app.Exe();
}

