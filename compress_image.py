#!/usr/bin/env python3
"""
Script to compress and resize the Alexander image for ESP32.
Target: ~500KB max (to fit in 2MB flash with other code)
Display: 240x240 pixels (16-bit color depth)
"""

import sys
from PIL import Image
import os

def compress_image(input_path, output_path, target_size_kb=500, max_dimension=240):
    """
    Compress and resize image for ESP32 display.
    
    Args:
        input_path: Path to input image file
        output_path: Path to output image file (will be overwritten)
        target_size_kb: Target file size in KB
        max_dimension: Maximum width or height in pixels
    """
    print(f"Loading image from: {input_path}")
    
    # Check if input file exists
    if not os.path.exists(input_path):
        print(f"Error: Input file '{input_path}' not found!")
        return False
    
    # Get original file size
    original_size = os.path.getsize(input_path) / 1024 / 1024  # MB
    print(f"Original file size: {original_size:.2f} MB")
    
    # Open and process image
    try:
        img = Image.open(input_path)
        print(f"Original dimensions: {img.width}x{img.height}")
        print(f"Original mode: {img.mode}")
        
        # Convert to RGB if necessary
        if img.mode != 'RGB':
            img = img.convert('RGB')
        
        # Calculate resize dimensions (maintain aspect ratio)
        if img.width > img.height:
            new_width = max_dimension
            new_height = int(img.height * (max_dimension / img.width))
        else:
            new_height = max_dimension
            new_width = int(img.width * (max_dimension / img.height))
        
        print(f"Resizing to: {new_width}x{new_height}")
        img_resized = img.resize((new_width, new_height), Image.Resampling.LANCZOS)
        
        # Save with compression - try different quality levels
        quality = 85
        while quality >= 50:
            img_resized.save(output_path, 'JPEG', quality=quality, optimize=True)
            file_size_kb = os.path.getsize(output_path) / 1024
            
            print(f"Quality {quality}: {file_size_kb:.1f} KB", end="")
            
            if file_size_kb <= target_size_kb:
                print(" ✓ (target reached)")
                break
            else:
                print(f" (target: {target_size_kb} KB)")
            
            quality -= 5
        
        final_size = os.path.getsize(output_path) / 1024 / 1024  # MB
        print(f"\nFinal file size: {final_size:.2f} MB ({os.path.getsize(output_path) / 1024:.1f} KB)")
        print(f"Compression ratio: {original_size / final_size:.1f}x")
        print(f"\nCompressed image saved to: {output_path}")
        
        return True
        
    except Exception as e:
        print(f"Error processing image: {e}")
        return False

if __name__ == "__main__":
    # Default paths
    input_file = "Alexander_the_Great_Ny_Carlsberg_Glyptotek_IN574_n1.c"
    output_file = "Alexander_compressed.jpg"
    
    # If input is a .c file, try to find the original image
    if input_file.endswith('.c'):
        print("Note: Input is a .c file. Looking for original image file...")
        # Try common image extensions
        base_name = input_file.replace('.c', '')
        for ext in ['.png', '.jpg', '.jpeg', '.bmp', '.tiff', '.tif']:
            if os.path.exists(base_name + ext):
                input_file = base_name + ext
                print(f"Found: {input_file}")
                break
        else:
            print("Error: Could not find original image file!")
            print("Please provide the original image file path as argument:")
            print("  python compress_image.py <input_image> [output_image]")
            sys.exit(1)
    
    # Allow command line arguments
    if len(sys.argv) > 1:
        input_file = sys.argv[1]
    if len(sys.argv) > 2:
        output_file = sys.argv[2]
    
    success = compress_image(input_file, output_file)
    sys.exit(0 if success else 1)
