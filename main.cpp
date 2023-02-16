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

    is::Application app(argc, argv);

    return app.Exe();
}

