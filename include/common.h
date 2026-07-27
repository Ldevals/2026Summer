#ifndef COMMON__H
#define COMMON__H

#include <iostream>
#include <time.h>
#include <random>
#include <sstream>
#include <functional>
#include <vector>
#include <cstdlib>
#include <format>
#include <unordered_map>


#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/OpenGL.hpp"
//voir plus tard si utile
#define SINGLETON_PUBLIC_DECLARATION( _class )	static void s_create() { if (!s_instance) s_instance = new _class(); }					\
												static void s_destroy() { if (s_instance) delete s_instance; s_instance = nullptr; }	\
												static _class* get() { return s_instance; }
#define SINGLETON_PRIVATE_DECLARATION( _class ) static _class* s_instance;

#define SINGLETON_DEFINITION( _class )			_class* _class::s_instance = nullptr;

constexpr const float PI = 3.14159f;

#endif