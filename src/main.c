#include <pebble.h>

static Window *window;
static TextLayer *text_layer;

static void init(void) {

  // create and display a Window
  window = window_create();
  window_stack_push(window, true);
  
  // get window root layer and its bounds
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  
  // create a text layer
  text_layer = text_layer_create((GRect) { .origin = { 0, 72 }, .size = { bounds.size.w, 20}});
  text_layer_set_text(text_layer, "OH HAI DAR");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  
  // Add the layer to the window root layer
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

static void deinit(void) {
  text_layer_destroy(text_layer);
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}