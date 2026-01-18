#!/usr/bin/env python3
"""
Generate a simple test image in LVGL format (RGB565)
Creates a 240x240 gradient image
"""

import struct

IMAGE_WIDTH = 240
IMAGE_HEIGHT = 240
BYTES_PER_PIXEL = 2
IMAGE_SIZE = IMAGE_WIDTH * IMAGE_HEIGHT * BYTES_PER_PIXEL

# Generate gradient pattern
data = bytearray()
for y in range(IMAGE_HEIGHT):
    for x in range(IMAGE_WIDTH):
        # Create gradient: red increases horizontally, green vertically
        r = (x * 31) // IMAGE_WIDTH  # 5 bits for red
        g = (y * 63) // IMAGE_HEIGHT  # 6 bits for green
        b = 16  # Fixed blue
        
        # Pack into RGB565: RRRRR GGGGGG BBBBB
        rgb565 = (r << 11) | (g << 5) | b
        data.extend(struct.pack('<H', rgb565))

# Generate C file
c_content = f'''#include "lvgl.h"

// Simple test image: {IMAGE_WIDTH}x{IMAGE_HEIGHT} RGB565
// Gradient pattern: red increases horizontally, green vertically
// Size: {IMAGE_SIZE} bytes (~{IMAGE_SIZE // 1024} KB)

#define IMAGE_WIDTH {IMAGE_WIDTH}
#define IMAGE_HEIGHT {IMAGE_HEIGHT}
#define IMAGE_SIZE {IMAGE_SIZE}

static const uint8_t test_image_data[IMAGE_SIZE] = {{
'''

# Write data as hex bytes (16 per line)
for i in range(0, len(data), 16):
    line = ', '.join(f'0x{b:02x}' for b in data[i:i+16])
    c_content += f'    {line},\n'

c_content += '''};

const lv_image_dsc_t test_image = {
    .header.magic = LV_IMAGE_HEADER_MAGIC,
    .header.cf = LV_COLOR_FORMAT_RGB565,
    .header.flags = 0,
    .header.w = IMAGE_WIDTH,
    .header.h = IMAGE_HEIGHT,
    .header.stride = IMAGE_WIDTH * 2,
    .data_size = IMAGE_SIZE,
    .data = test_image_data,
};
'''

# Write to file
with open('components/core/ui/test_image.c', 'w') as f:
    f.write(c_content)

print(f"Generated test_image.c with {IMAGE_SIZE} bytes ({IMAGE_SIZE // 1024} KB)")
