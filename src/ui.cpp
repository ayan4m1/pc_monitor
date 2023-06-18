#include <interface.hpp>
// required to implort the icon implementation
// must appear only once in the project
#define DISCONNECTED_ICON_IMPLEMENTATION
#include <disconnected_icon.hpp>
// our font for the UI. 
#define OPENSANS_REGULAR_IMPLEMENTATION
#include <fonts/OpenSans_Regular.hpp>
#include <ui.hpp>
// for easier modification
const gfx::open_font& text_font = OpenSans_Regular;

using namespace uix;
using namespace gfx;

read_status_t current_status;

// used for the draw routines
// the state data for the bars
typedef struct bar_info {
    bool bottom;
} bar_info_t;
// the state data for the graphs
typedef struct graph_info {
    bool bottom;
    //buffer_t* buffers;
} graph_info_t;

static rgba_pixel<32> compute_color(float value, int start_hue,int end_hue,int alpha) {

    const int range = abs(end_hue-start_hue)+1;
    int h = 0;
    if(end_hue>=start_hue) {
        h=(range*value)+start_hue;
    } else {
        h=start_hue-(range*value);
    }
    rgba_pixel<32> result;
    convert(hsv_pixel<24>((uint8_t)h,255,255),&result);
    result.template channel<channel_name::A>((uint8_t)alpha);
    return result;
}
// callback for a canvas control to draw the bars
static void draw_bar(canvas_t::control_surface_type& destination, 
                    const gfx::srect16& clip, 
                    void* state) {
    // reconstitute our state info
    const bar_info_t& inf = *(bar_info_t*)state;
    // get the height of each bar
    int h = destination.dimensions().height / 2;
    int y = 0;
    for (size_t i = 0; i < 2; ++i) {
        float v = NAN;
        int hue_start;
        int hue_end;
        if(!inf.bottom) { // top
            if(i==0) {
                v = current_status.top_value1/(float)current_status.top_value1_max;
                hue_start = current_status.top1_hue1;
                hue_end = current_status.top1_hue2;
            } else {
                v = current_status.top_value2/(float)current_status.top_value2_max;
                hue_start = current_status.top2_hue1;
                hue_end = current_status.top2_hue2;
            }
        } else { // bottom
            if(i==0) {
                v = current_status.bottom_value1/(float)current_status.bottom_value1_max;
                hue_start = current_status.bottom1_hue1;
                hue_end = current_status.bottom1_hue2;
            } else {
                v = current_status.bottom_value2/(float)current_status.bottom_value2_max;
                hue_start = current_status.bottom2_hue1;
                hue_end = current_status.bottom2_hue2;
            }
        }
       
        auto range = abs(hue_end - hue_start) + 1;
        if(range==1) {
            auto col = compute_color(1,hue_start,hue_end,95);
            draw::filled_rectangle(destination, 
                                srect16((destination.dimensions().width * v), 
                                        y, 
                                        destination.dimensions().width - 1, 
                                        y + h), 
                                col, 
                                &clip);
            col = compute_color(1,hue_start,hue_end,255);
            // now the filled part
            draw::filled_rectangle(destination, 
                                srect16(0, 
                                        y, 
                                        (destination.dimensions().width * v) - 1, 
                                        y + h),
                                col, 
                                &clip);
        } else {
            // the width of each gradient segment
            int w = (int)ceilf(destination.dimensions().width / 
                                (float)range) + 1;
            // the step of each segment - default 1
            int s = 1;
            // if the gradient is larger than the control
            if (destination.dimensions().width < range) {
                // change the segment to width 1
                w = 1;
                // and make its step larger
                s = range / (float)destination.dimensions().width;
            }
            int x = 0;
            // c is the current color offset
            // it increases by s (step)
            int c = 0;
            // for each color in the range
            for (auto j = 0; j < range; ++j) {
                int alpha = 255;
                if (x >= (v * destination.dimensions().width)) {
                    alpha=95;
                }
                auto col = compute_color(j/(float)(range-1),hue_start,hue_end,alpha);
                // create the rect for our segment
                rect16 r(x, y, x + w, y + h);
                // if we're drawing the filled part
                // it's fully opaque
                // otherwise it's semi-transparent
                
                // black out the area underneath so alpha blending
                // works correctly
                draw::filled_rectangle(destination, 
                                    r, 
                                    main_screen.background_color(), 
                                    &clip);
                // draw the segment
                draw::filled_rectangle(destination, 
                                    r, 
                                    col, 
                                    &clip);
                // increment
                x += w;
                c += s;
            }
        }
        // increment to the next bar
        y += h;
    }
}
static void draw_graph(canvas_t::control_surface_type& destination, 
                    const gfx::srect16& clip, 
                    void* state) {
    // reconstitute the state
    const graph_info_t& inf = *(graph_info_t*)state;
    buffer_t* buffer = nullptr;
    int hue_start = 0;
    int hue_end = 0;
    // store the dimensions
    const uint16_t width = destination.dimensions().width;
    const uint16_t height = destination.dimensions().height;
    spoint16 pt = spoint16::zero();
    // for each graph
    for (size_t i = 0; i < 2; ++i) {
        if(!inf.bottom) { // top
            if(i==0) {
                buffer = &top_buffers[0];
                hue_start = current_status.top1_hue1;
                hue_end = current_status.top1_hue2;
            } else {
                buffer = &top_buffers[1];
                hue_start = current_status.top2_hue1;
                hue_end = current_status.top2_hue2;
            }
        } else { // bottom
            if(i==0) {
                buffer = &bottom_buffers[0];
                hue_start = current_status.bottom1_hue1;
                hue_end = current_status.bottom1_hue2;
            } else {
                buffer = &bottom_buffers[1];
                hue_start = current_status.bottom2_hue1;
                hue_end = current_status.bottom2_hue2;
            }
        }
        // easy access to the current buffer
        buffer_t& buf = *buffer;
        // the point value
        float v = NAN;
        // if we have data
        if (!buf.empty()) {
            // get and store the first value
            // (translating it to the graph)
            v = *buf.peek(0);
            pt.x = 0;
            pt.y = height - (v * height) - 1;
            if (pt.y < 0) pt.y = 0;
        }
        // for each subsequent value
        for (size_t i = 1; i < buf.size(); ++i) {
            // retrieve the value
            v = *buf.peek(i);
            // get the color based on v 
            auto col=compute_color(v ,hue_start,hue_end,255);
            // compute the current data point
            spoint16 pt2;
            pt2.x = (i / 100.0f) * width;
            pt2.y = height - (v * height) - 1;
            if (pt2.y < 0) pt2.y = 0;
            // draw an anti-aliased line
            // from the old point to the 
            // new point.
            // convert it to rgb to AA properly
            rgb_pixel<24> px;
            convert(col,&px);
            draw::line_aa(destination, 
                            srect16(pt, pt2), 
                            px, 
                            px, 
                            true, 
                            &clip);
            // store the current point as 
            // the next old point
            pt = pt2;
        }
    }
}
// define the declarations from the header

buffer_t top_buffers[2];
buffer_t bottom_buffers[2];

// define our transfer buffer(s) and initialize
// the main screen with it/them.
// for RGB interface screens we only use one
// because there is no DMA
#ifdef LCD_DMA
static uint8_t lcd_buffer1[lcd_buffer_size];
static uint8_t lcd_buffer2[lcd_buffer_size];
screen_t main_screen(lcd_buffer_size, lcd_buffer1, lcd_buffer2);
#else
static uint8_t lcd_buffer1[lcd_buffer_size];
screen_t main_screen(lcd_buffer_size, lcd_buffer1, nullptr);
#endif
// define our top controls and state
label_t top_title_label(main_screen);
label_t top_value1_label(main_screen);
label_t top_value2_label(main_screen);
canvas_t top_bar(main_screen);
canvas_t top_graph(main_screen);
static bar_info_t top_bar_state;
static graph_info_t top_graph_state;

// define our bottom controls and state
label_t bottom_title_label(main_screen);
canvas_t bottom_bar(main_screen);
label_t bottom_value1_label(main_screen);
label_t bottom_value2_label(main_screen);
canvas_t bottom_graph(main_screen);
static bar_info_t bottom_bar_state;
static graph_info_t bottom_graph_state;

// define our disconnected controls
svg_box_t disconnected_svg(main_screen);
label_t disconnected_label(main_screen);

// initialize the main screen
void main_screen_init(screen_t::on_flush_callback_type flush_callback, 
                    void* flush_callback_state) {
    memset(&current_status,0,sizeof(current_status));
    // declare a transparent pixel/color
    rgba_pixel<32> transparent(0, 0, 0, 0);
    // screen is black
    main_screen.background_color(color_t::black);
    // set the flush callback
    main_screen.on_flush_callback(flush_callback, flush_callback_state);

    // declare the first label. Everything else is based on this.
    // to do so we measure the size of the text (@ 1/7th of 
    // height of the screen) and bound the label based on that
    top_title_label.text("????");
    top_title_label.text_line_height(main_screen.dimensions().height / 7);
    top_title_label.bounds(text_font.measure_text(ssize16::max(), 
                                spoint16::zero(), 
                                "MMMM", 
                                text_font.scale(top_title_label.text_line_height()))
                                    .bounds().offset(5, 5).inflate(8, 4));
    // set the design properties
    top_title_label.text_color(color32_t::white);
    top_title_label.background_color(transparent);
    top_title_label.border_color(transparent);
    top_title_label.text_justify(uix_justify::bottom_right);
    top_title_label.text_open_font(&text_font);
    // register the control with the screen
    main_screen.register_control(top_title_label);

    // the next label is right below the first label
    top_value1_label.bounds(top_title_label.bounds()
                            .offset(0, top_title_label.text_line_height() + 1));
    top_value1_label.text_color(color32_t::white);
    top_value1_label.background_color(transparent);
    top_value1_label.border_color(transparent);
    top_value1_label.text("");
    top_value1_label.text_justify(uix_justify::bottom_right);
    top_value1_label.text_open_font(&text_font);
    top_value1_label.text_line_height(top_title_label.text_line_height());
    main_screen.register_control(top_value1_label);

    // the next label right below that
    top_value2_label.bounds(top_value1_label.bounds()
                            .offset(0, top_title_label.text_line_height() + 1));
    top_value2_label.text_color(color32_t::white);
    top_value2_label.background_color(transparent);
    top_value2_label.border_color(transparent);
    top_value2_label.text("");
    top_value2_label.text_justify(uix_justify::bottom_right);
    top_value2_label.text_open_font(&text_font);
    top_value2_label.text_line_height(top_title_label.text_line_height());
    main_screen.register_control(top_value2_label);

    // the bars are to the right of the label
    top_bar.bounds({int16_t(top_title_label.bounds().x2 + 5), 
                    top_title_label.bounds().y1, 
                    int16_t(main_screen.dimensions().width - 5), 
                    top_title_label.bounds().y2});
    top_bar_state.bottom = false;
    top_bar.on_paint(draw_bar, &top_bar_state);
    main_screen.register_control(top_bar);

    // the graph is below the above items.
    top_graph.bounds({top_bar.bounds().x1, 
                        int16_t(top_title_label.bounds().y2 + 5), 
                        top_bar.bounds().x2, 
                        int16_t(main_screen.dimensions().height / 
                                    2 - 5)});
    top_graph_state.bottom=false;
    top_graph.on_paint(draw_graph, &top_graph_state);
    main_screen.register_control(top_graph);

    // the GPU label is offset from the CPU
    // label by half the height of the screen
    bottom_title_label.bounds(top_title_label.bounds().offset(0, main_screen.dimensions().height / 2));
    bottom_title_label.text_color(color32_t::white);
    bottom_title_label.border_color(transparent);
    bottom_title_label.background_color(transparent);
    bottom_title_label.text("????");
    bottom_title_label.text_justify(uix_justify::bottom_right);
    bottom_title_label.text_open_font(&text_font);
    bottom_title_label.text_line_height(top_title_label.text_line_height());
    main_screen.register_control(bottom_title_label);

    // lay out the rest of the controls the 
    // same as was done with the top
    bottom_value1_label.bounds(bottom_title_label.bounds().offset(0, bottom_title_label.text_line_height() + 1));
    bottom_value1_label.text_color(color32_t::white);
    bottom_value1_label.background_color(transparent);
    bottom_value1_label.border_color(transparent);
    bottom_value1_label.text("");
    bottom_value1_label.text_justify(uix_justify::bottom_right);
    bottom_value1_label.text_open_font(&text_font);
    bottom_value1_label.text_line_height(top_title_label.text_line_height());
    main_screen.register_control(bottom_value1_label);

    // the next label right below the value1
    bottom_value2_label.bounds(bottom_value1_label.bounds()
                            .offset(0, bottom_title_label.text_line_height() + 1));
    bottom_value2_label.text_color(color32_t::white);
    bottom_value2_label.background_color(transparent);
    bottom_value2_label.border_color(transparent);
    bottom_value2_label.text("");
    bottom_value2_label.text_justify(uix_justify::bottom_right);
    bottom_value2_label.text_open_font(&text_font);
    bottom_value2_label.text_line_height(bottom_title_label.text_line_height());
    main_screen.register_control(bottom_value2_label);


    bottom_bar.bounds({int16_t(bottom_title_label.bounds().x2 + 5), 
                    bottom_title_label.bounds().y1, 
                    int16_t(main_screen.dimensions().width - 5), 
                    bottom_title_label.bounds().y2});
    bottom_bar_state.bottom = true;
    bottom_bar.on_paint(draw_bar, &bottom_bar_state);
    main_screen.register_control(bottom_bar);

    bottom_graph.bounds(top_graph.bounds()
                        .offset(0, main_screen.dimensions().height / 2));
    bottom_graph_state.bottom = true;
    bottom_graph.on_paint(draw_graph, &bottom_graph_state);
    main_screen.register_control(bottom_graph);

    disconnected_label.bounds(main_screen.bounds());
    disconnected_label.background_color(color32_t::white);
    disconnected_label.border_color(color32_t::white);
    main_screen.register_control(disconnected_label);
    // here we center and scale the SVG control based on
    // the size of the screen, clamped to a max of 128x128
    float sscale;
    if(main_screen.dimensions().width<128 || main_screen.dimensions().height<128) {
        sscale = disconnected_icon.scale(main_screen.dimensions());
    } else {
        sscale = disconnected_icon.scale(size16(128,128));
    }
    disconnected_svg.bounds(srect16(0,
                                    0,
                                    disconnected_icon.dimensions().width*sscale-1,
                                    disconnected_icon.dimensions().height*sscale-1)
                                        .center(main_screen.bounds()));
    disconnected_svg.doc(&disconnected_icon);
    main_screen.register_control(disconnected_svg);
}