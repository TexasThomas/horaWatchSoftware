#!/usr/bin/env python3
"""
Compress Alexander the Great image from .c file
Resizes from 3750x5000 to 240x240 pixels (fits ESP32 display)
"""

import struct
import re
import os

# Source dimensions (from the .c file)
SOURCE_WIDTH = 3750
SOURCE_HEIGHT = 5000
SOURCE_SIZE = SOURCE_WIDTH * SOURCE_HEIGHT * 2  # RGB565 = 2 bytes per pixel

# Target dimensions (ESP32 display)
TARGET_WIDTH = 240
TARGET_HEIGHT = 240
TARGET_SIZE = TARGET_WIDTH * TARGET_HEIGHT * 2

def read_rgb565_data_from_c(filename):
    """Extract RGB565 data from the .c file"""
    print(f"Reading {filename}...")
    print(f"Expected size: {SOURCE_SIZE / (1024*1024):.1f} MB")
    
    # Read file in chunks and extract hex bytes
    data_bytes = bytearray()
    hex_pattern = re.compile(rb'0x([0-9a-fA-F]{2})')
    
    chunk_size = 10 * 1024 * 1024  # 10MB chunks
    bytes_read = 0
    
    with open(filename, 'rb') as f:
        while True:
            chunk = f.read(chunk_size)
            if not chunk:
                break
            
            # Find all hex bytes in this chunk
            matches = hex_pattern.findall(chunk)
            for match in matches:
                data_bytes.append(int(match, 16))
                bytes_read += 1
            
            # Progress indicator
            if bytes_read % 1000000 == 0:
                print(f"  Extracted {bytes_read / 1000000:.1f}M bytes...")
    
    print(f"Extracted {len(data_bytes)} bytes total")
    
    # Trim to expected size (in case there's extra data)
    if len(data_bytes) > SOURCE_SIZE:
        print(f"Trimming from {len(data_bytes)} to {SOURCE_SIZE} bytes")
        data_bytes = data_bytes[:SOURCE_SIZE]
    elif len(data_bytes) < SOURCE_SIZE * 0.9:
        print(f"Warning: Only got {len(data_bytes)} bytes, expected ~{SOURCE_SIZE}")
    
    return bytes(data_bytes)

def resize_rgb565(source_data, src_w, src_h, dst_w, dst_h):
    """Resize RGB565 image using bilinear interpolation"""
    print(f"Resizing from {src_w}x{src_h} to {dst_w}x{dst_h}...")
    
    dst_data = bytearray(dst_w * dst_h * 2)
    
    x_ratio = src_w / dst_w
    y_ratio = src_h / dst_h
    
    for y in range(dst_h):
        if y % 50 == 0:
            print(f"  Processing row {y}/{dst_h}...")
        
        for x in range(dst_w):
            # Calculate source coordinates
            src_x = x * x_ratio
            src_y = y * y_ratio
            
            # Get integer and fractional parts
            x1 = int(src_x)
            y1 = int(src_y)
            x2 = min(x1 + 1, src_w - 1)
            y2 = min(y1 + 1, src_h - 1)
            
            fx = src_x - x1
            fy = src_y - y1
            
            # Get 4 surrounding pixels
            def get_pixel(px, py):
                idx = (py * src_w + px) * 2
                if idx + 1 >= len(source_data):
                    return 0
                return struct.unpack('<H', source_data[idx:idx+2])[0]
            
            try:
                p11 = get_pixel(x1, y1)
                p21 = get_pixel(x2, y1)
                p12 = get_pixel(x1, y2)
                p22 = get_pixel(x2, y2)
            except:
                # Fallback if out of bounds
                pixel = get_pixel(min(x1, src_w-1), min(y1, src_h-1))
                rgb565 = pixel
                idx = (y * dst_w + x) * 2
                struct.pack_into('<H', dst_data, idx, rgb565)
                continue
            
            # Bilinear interpolation
            def interpolate(a, b, t):
                return int(a + (b - a) * t)
            
            # Extract RGB components
            def rgb565_to_rgb(pixel):
                r = (pixel >> 11) & 0x1F
                g = (pixel >> 5) & 0x3F
                b = pixel & 0x1F
                return r, g, b
            
            def rgb_to_rgb565(r, g, b):
                return ((r & 0x1F) << 11) | ((g & 0x3F) << 5) | (b & 0x1F)
            
            r11, g11, b11 = rgb565_to_rgb(p11)
            r21, g21, b21 = rgb565_to_rgb(p21)
            r12, g12, b12 = rgb565_to_rgb(p12)
            r22, g22, b22 = rgb565_to_rgb(p22)
            
            # Interpolate horizontally
            r1 = interpolate(r11, r21, fx)
            g1 = interpolate(g11, g21, fx)
            b1 = interpolate(b11, b21, fx)
            
            r2 = interpolate(r12, r22, fx)
            g2 = interpolate(g12, g22, fx)
            b2 = interpolate(b12, b22, fx)
            
            # Interpolate vertically
            r = interpolate(r1, r2, fy)
            g = interpolate(g1, g2, fy)
            b = interpolate(b1, b2, fy)
            
            # Convert back to RGB565
            pixel = rgb_to_rgb565(r, g, b)
            
            # Write to destination
            idx = (y * dst_w + x) * 2
            struct.pack_into('<H', dst_data, idx, pixel)
    
    return bytes(dst_data)

def generate_c_file(data, output_filename):
    """Generate C file with compressed image data"""
    print(f"Generating {output_filename}...")
    
    c_content = f'''#include "lvgl.h"

// Compressed Alexander the Great image: {TARGET_WIDTH}x{TARGET_HEIGHT} RGB565
// Original: 3750x5000 pixels (214 MB)
// Compressed: {TARGET_WIDTH}x{TARGET_HEIGHT} pixels ({len(data)} bytes, ~{len(data) // 1024} KB)

#define ALEXANDER_IMAGE_WIDTH {TARGET_WIDTH}
#define ALEXANDER_IMAGE_HEIGHT {TARGET_HEIGHT}
#define ALEXANDER_IMAGE_SIZE {len(data)}

static const uint8_t alexander_image_data[ALEXANDER_IMAGE_SIZE] = {{
'''
    
    # Write data as hex bytes (16 per line)
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
    
    print(f"Generated {output_filename} ({len(data)} bytes, ~{len(data) // 1024} KB)")

def main():
    input_file = "Alexander_the_Great_Ny_Carlsberg_Glyptotek_IN574_n1.c"
    output_file = "components/core/ui/alexander_compressed.c"
    
    print("=" * 60)
    print("Alexander the Great Image Compressor")
    print("=" * 60)
    print(f"Source: {SOURCE_WIDTH}x{SOURCE_HEIGHT} pixels")
    print(f"Target: {TARGET_WIDTH}x{TARGET_HEIGHT} pixels")
    print()
    
    if not os.path.exists(input_file):
        print(f"Error: {input_file} not found!")
        return False
    
    # Read source data
    source_data = read_rgb565_data_from_c(input_file)
    
    if len(source_data) < SOURCE_SIZE * 0.5:
        print(f"Error: Not enough data extracted ({len(source_data)} bytes)")
        return False
    
    # Resize
    print()
    resized_data = resize_rgb565(source_data, SOURCE_WIDTH, SOURCE_HEIGHT, 
                                 TARGET_WIDTH, TARGET_HEIGHT)
    
    # Generate C file
    print()
    generate_c_file(resized_data, output_file)
    
    print()
    print("=" * 60)
    print("Compression complete!")
    print(f"Original size: ~214 MB")
    print(f"Compressed size: ~{len(resized_data) // 1024} KB")
    if len(resized_data) > 0:
        print(f"Compression ratio: ~{214 * 1024 / (len(resized_data) // 1024):.0f}x")
    print("=" * 60)
    
    return True

if __name__ == "__main__":
    success = main()
    exit(0 if success else 1)
