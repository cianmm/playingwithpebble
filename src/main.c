#include <pebble.h>

static Window *windowOne;
static Window *windowTwo;
static TextLayer *text_layer;

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (window_stack_get_top_window() != windowOne) {
    window_stack_push(windowOne, true);
  }
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (window_stack_get_top_window() != windowTwo) {
    window_stack_push(windowTwo, true);
  }
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  window_stack_pop(true);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void AddTextToWindow(Window *toWindow, char *text) {
  // get window root layer and its bounds
  Layer *window_layer = window_get_root_layer(toWindow);
  GRect bounds = layer_get_bounds(window_layer);
  
  // create a text layer
  text_layer = text_layer_create((GRect) { .origin = { 0, 45 }, .size = { bounds.size.w, 80 } });
  text_layer_set_text(text_layer, text);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
  
  // Add to window root
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

static void init(void) {
  // Create window 1
  windowOne = window_create();
  window_stack_push(windowOne, true);
  
  // Create window 2
  windowTwo = window_create();
  window_stack_push(windowTwo, true);
  
  // Config buttons on each window
  window_set_click_config_provider(windowOne, click_config_provider);
  window_set_click_config_provider(windowTwo, click_config_provider);
  
  // Add text to each window
  AddTextToWindow(windowOne, "Window One");
  AddTextToWindow(windowTwo, "Window Two");
}

static void deinit(void) {
  window_destroy(windowOne);
  window_destroy(windowTwo);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}