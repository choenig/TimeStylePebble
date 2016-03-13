#pragma once
#include <pebble.h>

// "public" functions
void Secondsbar_init(Window* window);
void Secondsbar_deinit();
void Secondsbar_redraw();
void Secondsbar_update(int seconds);
