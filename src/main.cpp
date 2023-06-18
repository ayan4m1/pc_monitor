#include <Arduino.h>
#ifdef ESP_PLATFORM
// required to import the actual definitions
// for lcd_init.h
#define LCD_IMPLEMENTATION
#include <lcd_init.h>
#endif
#include <uix.hpp>
using namespace gfx;
using namespace uix;
#include <ui.hpp>
#include <interface.hpp>
#ifdef M5STACK_CORE2
#include <m5core2_power.hpp>
#endif
#ifdef WIO_TERMINAL
#include <tft_spi.hpp>
#include <ili9341.hpp>
using namespace arduino;
using bus_t = tft_spi_ex<3,LCD_SS_PIN,SPI_MODE0>;
using lcd_t = ili9341<LCD_DC,LCD_RESET,LCD_BACKLIGHT,bus_t,3,true,400,200>;

lcd_t lcd;
#endif
// label string data
static char top_title_sz[5];
static char top_value1_sz[16];
static char top_value2_sz[16];
static char bottom_title_sz[5];
static char bottom_value1_sz[16];
static char bottom_value2_sz[16];

// signal timer for disconnection detection
static uint32_t timeout_ts = 0;

#ifdef M5STACK_CORE2
m5core2_power power;
#endif

#ifdef ESP_PLATFORM
// only needed if not RGB interface screen
#ifdef LCD_DMA
static bool lcd_flush_ready(esp_lcd_panel_io_handle_t panel_io, 
                            esp_lcd_panel_io_event_data_t* edata, 
                            void* user_ctx) {
    main_screen.set_flush_complete();
    return true;
}
#endif

static void uix_flush(const rect16& bounds, 
                    const void* bmp, 
                    void* state) {
    lcd_panel_draw_bitmap(bounds.x1, 
                        bounds.y1, 
                        bounds.x2, 
                        bounds.y2,
                        (void*) bmp);
    // no DMA, so we are done once the above completes
#ifndef LCD_DMA
    main_screen.set_flush_complete();
#endif
}
#else
static void uix_wait(void* state) {
    draw::wait_all_async(lcd);
}
static void uix_flush(const rect16& bounds, 
                    const void* bmp, 
                    void* state) {
    const_bitmap<screen_t::pixel_type,screen_t::palette_type> cbmp(size16(bounds.width(),bounds.height()),bmp);
    draw::bitmap_async(lcd,bounds,cbmp,cbmp.bounds());
}
#endif
void setup() {
    memset(top_title_sz,0,5);
    memset(top_value1_sz,0,16);
    memset(top_value2_sz,0,16);
    memset(bottom_title_sz,0,5);
    memset(bottom_value1_sz,0,16);
    memset(bottom_value2_sz,0,16);
    Serial.begin(460800);
    // enable the power pins, as necessary
#ifdef T_DISPLAY_S3
    pinMode(15, OUTPUT); 
    digitalWrite(15, HIGH);
#elif defined(S3_T_QT)
    pinMode(4, OUTPUT); 
    digitalWrite(4, HIGH);
#endif
#ifdef M5STACK_CORE2
    power.initialize();
#endif
#ifdef ESP_PLATFORM
    // RGB interface LCD init is slightly different
#ifdef LCD_PIN_NUM_VSYNC
    lcd_panel_init();
#else
    lcd_panel_init(lcd_buffer_size,lcd_flush_ready);
#endif
#else
    lcd.initialize();
    main_screen.wait_flush_callback(uix_wait);
#endif
    // initialize the main screen (ui.cpp)
    main_screen_init(uix_flush);
}

void loop() {
    // timeout for disconnection detection (1 second)
    if(timeout_ts!=0 && millis()>timeout_ts+1000) {
        timeout_ts = 0;
        disconnected_label.visible(true);
        disconnected_svg.visible(true);
    }
    // update the UI
    main_screen.update();

    // listen for incoming serial
    int i = Serial.read();
    float tmp;
    if(i>-1) { // if data received...
         // reset the disconnect timeout
        timeout_ts = millis(); 
        disconnected_label.visible(false);
        disconnected_svg.visible(false);
        switch(i) {
            case read_status_t::command: {
                read_status_t data;
                if(sizeof(data)==Serial.readBytes((char*)&data,sizeof(data))) {
                    if (top_buffers[0].full()) {
                        top_buffers[0].get(&tmp);
                    }
                    top_buffers[0].put(data.top_value1/(float)data.top_value1_max);
                    if (top_buffers[1].full()) {
                        top_buffers[1].get(&tmp);
                    }
                    top_buffers[1].put(data.top_value2/(float)data.top_value2_max);
                    top_graph.invalidate();
                    top_bar.invalidate();
                    if(0!=memcmp(current_status.top_title,data.top_title,sizeof(data.top_title))) {
                        memset(top_title_sz,0,sizeof(top_title_sz));
                        memcpy(top_title_sz,data.top_title,sizeof(data.top_title));
                        top_title_label.text(top_title_sz);
                    }
                    if(current_status.top_value1!=data.top_value1 || current_status.top_unit1!=data.top_unit1) {
                        sprintf(top_value1_sz,"%d%c",data.top_value1,data.top_unit1);
                        top_value1_label.text(top_value1_sz);
                    }
                    if(current_status.top_value2!=data.top_value2 || current_status.top_unit2!=data.top_unit2) {
                        sprintf(top_value2_sz,"%d%c",data.top_value2,data.top_unit2);
                        top_value2_label.text(top_value2_sz);
                    }
                    if (bottom_buffers[0].full()) {
                        bottom_buffers[0].get(&tmp);
                    }
                    bottom_buffers[0].put(data.bottom_value1/(float)data.bottom_value1_max);
                    if (bottom_buffers[1].full()) {
                        bottom_buffers[1].get(&tmp);
                    }
                    bottom_buffers[1].put(data.bottom_value2/(float)data.bottom_value2_max);
                    // force a redraw of the GPU bar and graph
                    bottom_graph.invalidate();
                    bottom_bar.invalidate();
                    if(0!=memcmp(current_status.bottom_title,data.bottom_title,sizeof(data.bottom_title))) {
                        memset(bottom_title_sz,0,sizeof(bottom_title_sz));
                        memcpy(bottom_title_sz,data.bottom_title,sizeof(data.bottom_title));
                        bottom_title_label.text(bottom_title_sz);
                    }
                    // update the bottom labels
                    if(current_status.bottom_value1!=data.bottom_value1 || current_status.bottom_unit1!=data.bottom_unit1) {
                        sprintf(bottom_value1_sz,"%d%c",data.bottom_value1,data.bottom_unit1);
                        bottom_value1_label.text(bottom_value1_sz);
                    }
                    if(data.bottom_value2!=current_status.bottom_value2 || current_status.bottom_unit2!=data.bottom_unit2) {
                        sprintf(bottom_value2_sz,"%d%c",data.bottom_value2,data.bottom_unit2);
                        bottom_value2_label.text(bottom_value2_sz);   
                    }
                    current_status = data;
                } else {
                    // eat bad data
                    while(-1!=Serial.read());
                }
            }
            break;
            default:
                // eat unrecognized data
                while(-1!=Serial.read());
                break;
        };
    }
}