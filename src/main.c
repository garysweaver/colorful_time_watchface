#include <pebble.h>

// Colorful Time
//
// (c) 2015 Gary Weaver
  
static Window *window;
static TextLayer *text_layer;

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  text_layer = text_layer_create((GRect) { .origin = { 0, 65 }, .size = { bounds.size.w, 38 } });
  text_layer_set_text(text_layer, "");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  text_layer_set_background_color(text_layer, GColorClear);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}

static void handle_second_tick(struct tm *tick_time, TimeUnits units_changed) {
  static char s_time_buffer[16];
  clock_copy_time_string(s_time_buffer, sizeof(s_time_buffer));
  text_layer_set_text(text_layer, s_time_buffer);
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
  text_layer_set_text_color(text_layer, (GColor8) {
    .a = rand() % 4,
    .r = rand() % 4,
    .g = rand() % 4,
    .b = rand() % 4
  });
  window_set_background_color(window, (GColor8) {
    .a = rand() % 4,
    .r = rand() % 4,
    .g = rand() % 4,
    .b = rand() % 4
  });
}

static void init(void) {
  window = window_create();
  window_set_background_color(window, (GColor8) {
    .a = rand() % 4,
    .r = rand() % 4,
    .g = rand() % 4,
    .b = rand() % 4
  });
  window_set_window_handlers(window, (WindowHandlers) {
	  .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);
  tick_timer_service_subscribe(SECOND_UNIT, handle_second_tick);
}

static void deinit(void) {
  window_destroy(window);
  tick_timer_service_unsubscribe();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}