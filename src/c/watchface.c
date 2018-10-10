#include <pebble.h>


Window *window;
TextLayer *textHours;
TextLayer *textMinutes;
BitmapLayer *Image;
GBitmap *Rock;



static void timeLoop(struct tm* tick_time, TimeUnits units_changed )
{
    static char timeH[] = "00";
    static char timeM[] = "00";
    strftime(timeH, sizeof(timeH), "%H", tick_time);
    strftime(timeM, sizeof(timeM), "%M", tick_time);
    text_layer_set_text(textHours, timeH);
    text_layer_set_text(textMinutes, timeM);
}

void graph(void)
{
    Image = bitmap_layer_create(GRect(0, 0, 144, 168));
    Rock = gbitmap_create_with_resource(RESOURCE_ID_RockIm);
    bitmap_layer_set_bitmap(Image, Rock);
    layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(Image));
    GFont custom_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DooM_26));
    textHours = text_layer_create(GRect(13, 126, 30, 30));
    textMinutes = text_layer_create(GRect(107, 126, 30, 30));
    text_layer_set_text_color(textHours, GColorRed);
    text_layer_set_background_color(textHours, GColorClear);
    text_layer_set_font(textHours, custom_font);
    text_layer_set_text_alignment(textHours, GTextAlignmentCenter);
    text_layer_set_text_color(textMinutes, GColorRed);
    text_layer_set_background_color(textMinutes, GColorClear);
    text_layer_set_font(textMinutes, custom_font);
    text_layer_set_text_alignment(textMinutes, GTextAlignmentCenter);
     layer_add_child(window_get_root_layer(window), text_layer_get_layer(textHours));
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(textMinutes));
   
 }

void handle_init(void)
{
   window = window_create();
    graph();
    time_t now = time(NULL);
    struct tm *current_time = localtime(&now);
    tick_timer_service_subscribe(MINUTE_UNIT, &timeLoop);
    timeLoop(current_time, MINUTE_UNIT);
    window_stack_push(window,true);
    
}

void handle_deinit(void)
{
    text_layer_destroy(textHours);
    text_layer_destroy(textMinutes);
    gbitmap_destroy(Rock);
    bitmap_layer_destroy(Image);
    window_destroy(window);
    tick_timer_service_unsubscribe();
    
}

int main()
{
    handle_init();
    app_event_loop();
    handle_deinit();
    return 0;
    
}
