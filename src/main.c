#include <pebble.h>

static Window *window;
static Layer *myLayer;

static void my_layer_draw(Layer *layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(layer);
  
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, bounds, 0, GCornerNone);
  
  graphics_context_set_fill_color(ctx, GColorWhite);
  const int16_t half_h = bounds.size.h / 2;
  graphics_fill_circle(ctx, GPoint(half_h, half_h), half_h);
  
  graphics_context_set_fill_color(ctx, GColorBlack);
  const int16_t half_h2 = bounds.size.h / 3;
  graphics_fill_circle(ctx, GPoint(half_h, half_h), half_h2);
}
  
static void window_load(Window *window) {
  // get window root layer and bounds
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // create a layer
  myLayer = layer_create((GRect) { . origin = {0,72}, .size = { bounds.size.w, 50 }});
  layer_set_update_proc(myLayer, my_layer_draw);
  
  // Add layer to window root layer
  layer_add_child(window_layer, myLayer);
}

static void window_unload(Window *window) {
  layer_destroy(myLayer);
}

static void init(void) {

  // Create and display a window
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload
  });
  window_stack_push(window, true);
  
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}