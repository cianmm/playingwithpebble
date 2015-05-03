#include <pebble.h>

static Window *window;
static TextLayer *text_layer;

static void select_click_handler (ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Select pressed");
}
static void up_click_handler (ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Up pressed");
}
static void down_click_handler (ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Down pressed");
}
static void select_multi_click_handler (ClickRecognizerRef recognizer, void*context) {
  text_layer_set_text(text_layer, "Multi select");
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);

  window_multi_click_subscribe(BUTTON_ID_SELECT, 2, 10, 0, true, select_multi_click_handler);
}

static void init(void) {

  // Create and display a window
  window = window_create();
  window_stack_push(window, true);
  
  window_set_click_config_provider(window, click_config_provider);
  
  // get window root layer and bounds
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  
  // create a text layer
  text_layer = text_layer_create((GRect) { .origin = {0,45 }, .size = { bounds.size.w, 80 } });
  text_layer_set_text(text_layer, "Press buttons!");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
  
  // add text layer to window root
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