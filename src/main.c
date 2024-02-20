#include <pico/stdlib.h>
#include <cofgifs.h>
#include "device.h"
#include "external.h"

struct cgif_render_rgb render_buffer[512];
struct cgif_dict_entry dictionary[CGIF_DICT_COUNT_MAX(32, 16)];

void set_address(uint8_t address)
{
    gpio_put(A, address & 1);
    gpio_put(B, address & 2);
    gpio_put(C, address & 4);
}

void init_io()
{
    // Initialize pins
    gpio_init(R1);
    gpio_init(R2);
    gpio_init(B1);
    gpio_init(B2);
    gpio_init(G1);
    gpio_init(G2);

    gpio_init(A);
    gpio_init(B);
    gpio_init(C);

    gpio_init(CLK);
    gpio_init(OE);
    gpio_init(LAT);

    // Enable output mode
    gpio_set_dir(R1, GPIO_OUT);
    gpio_set_dir(R2, GPIO_OUT);
    gpio_set_dir(B1, GPIO_OUT);
    gpio_set_dir(B2, GPIO_OUT);
    gpio_set_dir(G1, GPIO_OUT);
    gpio_set_dir(G2, GPIO_OUT);

    gpio_set_dir(A, GPIO_OUT);
    gpio_set_dir(B, GPIO_OUT);
    gpio_set_dir(C, GPIO_OUT);

    gpio_set_dir(CLK, GPIO_OUT);
    gpio_set_dir(OE, GPIO_OUT);
    gpio_set_dir(LAT, GPIO_OUT);

    // Initialize colors
    gpio_put(R1, false);
    gpio_put(R2, false);
    gpio_put(G1, false);
    gpio_put(G2, false);
    gpio_put(B1, false);
    gpio_put(B2, false);

    // Initialize output
    gpio_put(CLK, false);
    gpio_put(OE, false);
    gpio_put(LAT, false);
}

int main()
{
    init_io();

    struct cgif gif;
    cgif_error_t err;

    char const *image = display_images;
    err = cgif_init(&gif, image, dictionary, sizeof(dictionary));

    while(true) {
        for(uint8_t i = 0; i < 8; i++) {
            set_address(i);

            gpio_put(OE, true);
            for(int y = 0; y < 32; y++) {
                gpio_put(CLK, false);

                unsigned int top_index = (i * 32) + y;
                unsigned int bottom_index = ((i + 8) * 32) + y;

                /*
                // Set top
                gpio_put(R1, output_buffer[top_index] & RED);
                gpio_put(G1, output_buffer[top_index] & GREEN);
                gpio_put(B1, output_buffer[top_index] & BLUE);

                // Set bottom
                gpio_put(R2, output_buffer[bottom_index] & RED);
                gpio_put(G2, output_buffer[bottom_index] & GREEN);
                gpio_put(B2, output_buffer[bottom_index] & BLUE);
                 */

                gpio_put(CLK, true);
            }
            gpio_put(LAT, false);
            gpio_put(LAT, true);
            gpio_put(OE, false);
            sleep_us(200);
        }
    }
}
