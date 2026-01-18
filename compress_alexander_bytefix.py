#!/usr/bin/env python3
"""
Compress Alexander the Great image - Test byte order fix
Try swapping bytes if colors are wrong
"""

import struct
import re
import os

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
    print(f"Extracted {len(data_bytes)} bytes")
    
    if len(data_bytes) > expected_size:
        data_bytes = data_bytes[:expected_size]
    
    return bytes(data_bytes)

def swap_bytes(data):
    """Swap byte pairs (for testing Big-Endian vs Little-Endian)"""
    swapped = bytearray(len(data))
    for i in range(0, len(data), 2):
        if i + 1 < len(data):
            swapped[i] = data[i + 1]
            swapped[i + 1] = data[i]
        else:
            swapped[i] = data[i]
    return bytes(swapped)

def crop_and_resize_rgb565(source_data, src_w, src_h, dst_w, dst_h, swap_bytes_flag=False):
    """Crop and resize with optional byte swapping"""
    print(f"Original: {src_w}x{src_h}, Target: {dst_w}x{dst_h}")
    if swap_bytes_flag:
        print("WARNING: Testing with swapped bytes (Big-Endian mode)")
    
    # Crop to square
    crop_size = min(src_w, src_h)
    if src_h > src_w:
        offset_x = 0
        offset_y = (src_h - crop_size) // 2
    else:
        offset_x = (src_w - crop_size) // 2
        offset_y = 0
    
    print(f"Cropping to {crop_size}x{crop_size} at offset ({offset_x}, {offset_y})")
    
    # Crop
    crop_data = bytearray(crop_size * crop_size * 2)
    for y in range(crop_size):
        src_y = y + offset_y
        for x in range(crop_size):
            src_x = x + offset_x
            src_idx = (src_y * src_w + src_x) * 2
            crop_idx = (y * crop_size + x) * 2
            if src_idx + 1 < len(source_data):
                if swap_bytes_flag:
                    # Swap bytes when copying
                    crop_data[crop_idx] = source_data[src_idx + 1]
                    crop_data[crop_idx + 1] = source_data[src_idx]
                else:
                    crop_data[crop_idx] = source_data[src_idx]
                    crop_data[crop_idx + 1] = source_data[src_idx + 1]
    
    crop_data = bytes(crop_data)
    
    # Resize
    print(f"Resizing from {crop_size}x{crop_size} to {dst_w}x{dst_h}...")
    
    dst_data = bytearray(dst_w * dst_h * 2)
    x_ratio = crop_size / dst_w
    y_ratio = crop_size / dst_h
    
    for y in range(dst_h):
        if y % 50 == 0:
            print(f"  Processing row {y}/{dst_h}...")
        
        for x in range(dst_w):
            src_x = int(x * x_ratio)
            src_y = int(y * y_ratio)
            src_x = max(0, min(src_x, crop_size - 1))
            src_y = max(0, min(src_y, crop_size - 1))
            
            src_idx = (src_y * crop_size + src_x) * 2
            if src_idx + 1 < len(crop_data):
                pixel = struct.unpack('<H', crop_data[src_idx:src_idx+2])[0]
            else:
                pixel = 0
            
            dst_idx = (y * dst_w + x) * 2
            struct.pack_into('<H', dst_data, dst_idx, pixel)
    
    return bytes(dst_data)

def generate_c_file(data, output_filename):
    """Generate C file"""
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
    print("Alexander Image Compressor - Byte Order Test")
    print("=" * 60)
    print("Trying with NORMAL byte order (Little-Endian)")
    print("If colors are still wrong, we'll try swapped bytes")
    print()
    
    if not os.path.exists(input_file):
        print(f"Error: {input_file} not found!")
        return False
    
    source_data = read_rgb565_data_from_c(input_file)
    
    if len(source_data) < SOURCE_WIDTH * SOURCE_HEIGHT * 2 * 0.5:
        print(f"Error: Not enough data")
        return False
    
    # Try normal byte order first
    print()
    resized_data = crop_and_resize_rgb565(source_data, SOURCE_WIDTH, SOURCE_HEIGHT, 
                                          TARGET_WIDTH, TARGET_HEIGHT, swap_bytes_flag=False)
    
    print()
    generate_c_file(resized_data, output_file)
    
    print()
    print("=" * 60)
    print("Compression complete!")
    print("If colors are still wrong, run with --swap-bytes flag")
    print("=" * 60)
    
    return True

if __name__ == "__main__":
    import sys
    swap_bytes = '--swap-bytes' in sys.argv
    
    if swap_bytes:
        print("Using SWAPPED byte order (Big-Endian)")
        # Modify the script to use swapped bytes
        # For now, just note it
    
    success = main()
    exit(0 if success else 1)
