#ifndef YAOF_MISC_MACROS_HPP
#define YAOF_MISC_MACROS_HPP

#include "Yaof/Core/Application.hpp"
#include "Yaof/Core/FpsLimiter.hpp"
#include "Yaof/Core/ResourceManager.hpp"

#define YAOF_DELETE(x)       delete x; x = nullptr;

#define YAOF_DELETE_ARRAY(x) delete[] x; x = nullptr;

#define YAOF_APPLICATION     yf::Application::getInstance()

#define YAOF_FPSLIMITER      yf::FpsLimiter::getInstance()

#define YAOF_RESOURCEMANAGER yf::ResourceManager::getInstance()

#endif
