#!/usr/bin/env python3
"""
Compress Alexander the Great image - Using Pillow for high quality
"""

import re
import os
from PIL import Image

SOURCE_WIDTH = 3750
SOURCE_HEIGHT = 5000
TARGET_WIDTH = 240
TARGET_HEIGHT = 240

def read_rgb565_data_from_c(filename):
    """Extract RGB565 data from the .c file"""
    print(f"Reading {filename}...")
    
    data_bytes = bytearray()
    hex_pattern = re.compile(rb'0x([0-9a-fA-F]{2})')
    
    chunk_size = 10 * 1024 * 1024
    
    with open(filename, 'rb') as f:
        while True:
            chunk = f.read(chunk_size)
            if not chunk:
                break
            
            matches = hex_pattern.findall(chunk)
            for match in matches:
                data_bytes.append(int(match, 16))
    
    expected_size = SOURCE_WIDTH * SOURCE_HEIGHT * 2
    print(f"Extracted {len(data_bytes)} bytes, expected {expected_size}")
    
    if len(data_bytes) > expected_size:
        data_bytes = data_bytes[:expected_size]
    
    return bytes(data_bytes)

def rgb565_to_rgb888_image(data, width, height):
    """Convert RGB565 data to PIL Image"""
    print(f"Converting {width}x{height} RGB565 to RGB888...")
    
    img = Image.new('RGB', (width, height))
    pixels = img.load()
    
    for y in range(height):
        if y % 500 == 0:
            print(f"  Row {y}/{height}...")
        for x in range(width):
            idx = (y * width + x) * 2
            if idx + 1 < len(data):
                # Little-endian RGB565
                pixel = data[idx] | (data[idx + 1] << 8)
                
                # Extract RGB components
                r5 = (pixel >> 11) & 0x1F
                g6 = (pixel >> 5) & 0x3F
                b5 = pixel & 0x1F
                
                # Convert to 8-bit (scale up)
                r8 = (r5 << 3) | (r5 >> 2)
                g8 = (g6 << 2) | (g6 >> 4)
                b8 = (b5 << 3) | (b5 >> 2)
                
                pixels[x, y] = (r8, g8, b8)
    
    return img

def rgb888_image_to_rgb565(img):
    """Convert PIL Image back to RGB565 data"""
    width, height = img.size
    print(f"Converting {width}x{height} RGB888 back to RGB565...")
    
    data = bytearray(width * height * 2)
    pixels = img.load()
    
    for y in range(height):
        for x in range(width):
            r8, g8, b8 = pixels[x, y][:3]  # Handle RGBA
            
            # Convert to 5-6-5 bits
            r5 = r8 >> 3
            g6 = g8 >> 2
            b5 = b8 >> 3
            
            # Pack into RGB565 (little-endian)
            pixel = (r5 << 11) | (g6 << 5) | b5
            
            idx = (y * width + x) * 2
            data[idx] = pixel & 0xFF
            data[idx + 1] = (pixel >> 8) & 0xFF
    
    return bytes(data)

def generate_c_file(data, output_filename):
    """Generate C file"""
    print(f"Generating {output_filename}...")
    
    c_content = f'''#include "lvgl.h"

// Compressed Alexander the Great image: {TARGET_WIDTH}x{TARGET_HEIGHT} RGB565
// Using Pillow LANCZOS resampling for high quality

#define ALEXANDER_IMAGE_WIDTH {TARGET_WIDTH}
#define ALEXANDER_IMAGE_HEIGHT {TARGET_HEIGHT}
#define ALEXANDER_IMAGE_SIZE {len(data)}

static const uint8_t alexander_image_data[ALEXANDER_IMAGE_SIZE] = {{
'''
    
    for i in range(0, len(data), 16):
        line = ', '.join(f'0x{b:02x}' for b in data[i:i+16])
        c_content += f'    {line},\n'
    
    c_content += '''};

const lv_image_dsc_t Alexander_the_Great_Ny_Carlsberg_Glyptotek_IN574_n1 = {
    .header.magic = LV_IMAGE_HEADER_MAGIC,
    .header.cf = LV_COLOR_FORMAT_RGB565,
    .header.flags = 0,
    .header.w = ALEXANDER_IMAGE_WIDTH,
    .header.h = ALEXANDER_IMAGE_HEIGHT,
    .header.stride = ALEXANDER_IMAGE_WIDTH * 2,
    .data_size = ALEXANDER_IMAGE_SIZE,
    .data = alexander_image_data,
};
'''
    
    with open(output_filename, 'w') as f:
        f.write(c_content)
    
    print(f"Generated {output_filename}")

def main():
    input_file = "Alexander_the_Great_Ny_Carlsberg_Glyptotek_IN574_n1.c"
    output_file = "components/core/ui/alexander_compressed.c"
    
    print("=" * 60)
    print("Alexander Image Compressor - Pillow High Quality")
    print("=" * 60)
    
    if not os.path.exists(input_file):
        print(f"Error: {input_file} not found!")
        return False
    
    # Read RGB565 data
    source_data = read_rgb565_data_from_c(input_file)
    
    # Convert to PIL Image
    print()
    img = rgb565_to_rgb888_image(source_data, SOURCE_WIDTH, SOURCE_HEIGHT)
    
    # Center crop to square
    print()
    print("Cropping to center square...")
    crop_size = min(SOURCE_WIDTH, SOURCE_HEIGHT)
    left = (SOURCE_WIDTH - crop_size) // 2
    top = (SOURCE_HEIGHT - crop_size) // 2
    right = left + crop_size
    bottom = top + crop_size
    img = img.crop((left, top, right, bottom))
    print(f"Cropped to {img.size[0]}x{img.size[1]}")
    
    # Resize with high quality (LANCZOS)
    print()
    print(f"Resizing to {TARGET_WIDTH}x{TARGET_HEIGHT} using LANCZOS...")
    img = img.resize((TARGET_WIDTH, TARGET_HEIGHT), Image.LANCZOS)
    
    # Convert back to RGB565
    print()
    output_data = rgb888_image_to_rgb565(img)
    
    # Generate C file
    print()
    generate_c_file(output_data, output_file)
    
    print()
    print("=" * 60)
    print("Done! High quality image generated.")
    print("=" * 60)
    
    return True

if __name__ == "__main__":
    success = main()
    exit(0 if success else 1)
