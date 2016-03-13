#include <pebble.h>
#include "settings.h"
#include "secondsbar.h"

// taken from sidebar.c
#define SIDEBAR_WIDTH 30

Layer* secondsbarLayer;
static int secondsOffset = -1;

static void updateSecondsbarLayer(Layer *l, GContext* ctx);

void Secondsbar_init(Window* window) {
  const int x = globalSettings.sidebarOnLeft ? SIDEBAR_WIDTH : 0;
  secondsbarLayer = layer_create(GRect(x, 83, 144-SIDEBAR_WIDTH, 2));
  layer_add_child(window_get_root_layer(window), secondsbarLayer);

  layer_set_update_proc(secondsbarLayer, updateSecondsbarLayer);
}

void Secondsbar_deinit() {
  layer_destroy(secondsbarLayer);
}

void Secondsbar_redraw() {
  if (globalSettings.showSecondsbar != !layer_get_hidden(secondsbarLayer)) {
    layer_set_hidden(secondsbarLayer, globalSettings.showSecondsbar);
    if (!globalSettings.showSecondsbar) return;
  }

  // reposition the seconds if needed
  const int x = globalSettings.sidebarOnLeft ? SIDEBAR_WIDTH : 0;
  layer_set_frame(secondsbarLayer, GRect(x, 83, 144-SIDEBAR_WIDTH, 2));

  // redraw the layer
  layer_mark_dirty(secondsbarLayer);
}

void Secondsbar_update(int seconds) {

  if (secondsOffset == -1) {
      seconds = seconds - (seconds % globalSettings.secondsbarResolution);
  }

  if (seconds % globalSettings.secondsbarResolution == 0) {
    secondsOffset = (144-SIDEBAR_WIDTH) * seconds/60;

    // redraw the sidebar in case it changed in any way
    Secondsbar_redraw();
  }
}



// "private" functions

static void updateSecondsbarLayer(Layer *l, GContext* ctx)
{
  graphics_context_set_stroke_color(ctx, globalSettings.timeColor);
  graphics_draw_rect(ctx, GRect(0, 0, secondsOffset, 2));
}
