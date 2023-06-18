#pragma once
#include <interface.hpp>
#include <lcd_config.h>
#include <gfx.hpp>
#include <uix.hpp>
#include <circular_buffer.hpp>
// declare the types for our controls and other things
using screen_t = uix::screen_ex<LCD_WIDTH,LCD_HEIGHT,
                            LCD_FRAME_ADAPTER,LCD_X_ALIGN,LCD_Y_ALIGN>;


using label_t = uix::label<typename screen_t::control_surface_type>;
using svg_box_t = uix::svg_box<typename screen_t::control_surface_type>;
using canvas_t = uix::canvas<typename screen_t::control_surface_type>;
// X11 colors (used for screen)
using color_t = gfx::color<typename screen_t::pixel_type>;
// RGBA8888 X11 colors (used for controls)
using color32_t = gfx::color<gfx::rgba_pixel<32>>;
// circular buffer for graphs
using buffer_t = circular_buffer<float,100>;

// holds the current status off the serial line
extern read_status_t current_status;

// the buffers hold the graph data for the CPU
extern buffer_t top_buffers[];
// the buffers hold the graph data for the GPU
extern buffer_t bottom_buffers[];

// for most screens, we declare two 32kB buffers which
// we swap out for DMA. For RGB screens, DMA is not
// used so we put 64kB in one buffer
#ifdef LCD_DMA
constexpr static const int lcd_buffer_size = 32 * 1024;
#else
constexpr static const int lcd_buffer_size = 64 * 1024;
#endif


// the screen that holds the controls
extern screen_t main_screen;

// the controls for the top region
extern label_t top_title_label;
extern label_t top_value1_label;
extern label_t top_value2_label;
extern canvas_t top_bar;
extern canvas_t top_graph;

// the controls for the bottom region
extern label_t bottom_title_label;
extern label_t bottom_value1_label;
extern label_t bottom_value2_label;
extern canvas_t bottom_bar;
extern canvas_t bottom_graph;

// the controls for the disconnected "screen"
extern label_t disconnected_label;
extern svg_box_t disconnected_svg;

extern void main_screen_init(screen_t::on_flush_callback_type flush_callback, 
                            void* flush_callback_state = nullptr);