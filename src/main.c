#include <pebble.h>

static Window *window;
static TextLayer *text_layer;

static void init(void) {

  // Create and display a window
  window = window_create();
  window_stack_push(window, true);
    
  // get window root layer and bounds
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  
  Layer *another_layer = layer_create(bounds);
  
  // create a text layer
  text_layer = text_layer_create((GRect) { .origin = {0,45 }, .size = { bounds.size.w, 80 } });
  text_layer_set_text(text_layer, "This is another layer!");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  
  layer_add_child(another_layer, text_layer_get_layer(text_layer));
  
  // add text layer to window root
  layer_add_child(window_layer, another_layer);

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