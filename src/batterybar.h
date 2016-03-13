#pragma once
#include <pebble.h>

// "public" functions
void Batterybar_init(Window* window);
void Batterybar_deinit();
void Batterybar_redraw();
void Batterybar_update(BatteryChargeState charge_state);
