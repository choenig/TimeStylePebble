#include <pebble.h>
#include "settings.h"
#include "batterybar.h"

#define SCREEN_HEIGHT 168

// taken from sidebar.c
#define SIDEBAR_WIDTH 30

Layer* batteryLayer;
static int batteryOffset = 0;

static void updateBatteryLayer(Layer *l, GContext* ctx);

void Batterybar_init(Window* window) {
  const int x = globalSettings.sidebarOnLeft ? SIDEBAR_WIDTH : 0;
  GRect bounds;
  if(globalSettings.batteryBarAtTheTop) {
      bounds = GRect(x, 0, 144-SIDEBAR_WIDTH, 2);
  } else {
      bounds = GRect(x, SCREEN_HEIGHT-2, 144-SIDEBAR_WIDTH, 2);
  }

  batteryLayer = layer_create(bounds);
  layer_add_child(window_get_root_layer(window), batteryLayer);

  layer_set_update_proc(batteryLayer, updateBatteryLayer);
}

void Batterybar_deinit() {
  layer_destroy(batteryLayer);
}

void Batterybar_redraw() {
  if (globalSettings.showBatterybar != !layer_get_hidden(batteryLayer)) {
    layer_set_hidden(batteryLayer, globalSettings.showBatterybar);
    if (!globalSettings.showBatterybar) return;
  }

  // reposition the batterybar if needed
  const int x = globalSettings.sidebarOnLeft ? SIDEBAR_WIDTH : 0;
  if(globalSettings.batteryBarAtTheTop) {
    layer_set_frame(batteryLayer, GRect(x, 0, 144, 2));
  } else {
    layer_set_frame(batteryLayer, GRect(x, SCREEN_HEIGHT-2, 144, 2));
  }

  // redraw the layer
  layer_mark_dirty(batteryLayer);
}

void Batterybar_update(BatteryChargeState charge_state) {
  batteryOffset = (144-SIDEBAR_WIDTH) * charge_state.charge_percent/100;

  // redraw the batterybar in case it changed in any way
  Batterybar_redraw();
}



// "private" functions

static void updateBatteryLayer(Layer *l, GContext* ctx)
{
  graphics_context_set_stroke_color(ctx, globalSettings.timeColor);
  graphics_draw_rect(ctx, GRect(0, 0, batteryOffset, 2));
}

