#!/usr/bin/env python3
"""Fix RGB565 byte order in test.c by swapping every pair of bytes."""

import re

# Read the file
with open('components/core/ui/test.c', 'r', encoding='utf-8') as f:
    content = f.read()

# Find the data array section
start_marker = 'const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMAGE_TEST uint8_t test_map[] = {'
end_marker = '};'

start_idx = content.find(start_marker)
end_idx = content.find(end_marker, start_idx)

if start_idx == -1 or end_idx == -1:
    print("ERROR: Could not find data array in file!")
    exit(1)

# Extract header and footer
header = content[:start_idx + len(start_marker)]
footer = content[end_idx:]

# Extract data section
data_section = content[start_idx + len(start_marker):end_idx]

# Parse all hex bytes from the data section
hex_bytes = re.findall(r'0x([0-9a-fA-F]{2})', data_section)

print(f"Found {len(hex_bytes)} bytes ({len(hex_bytes)//2} pixels)")

# Swap every pair of bytes (RGB565 pixel = 2 bytes)
swapped_bytes = []
for i in range(0, len(hex_bytes), 2):
    if i + 1 < len(hex_bytes):
        # Swap: original [b1, b2] -> swapped [b2, b1]
        swapped_bytes.append(hex_bytes[i+1])
        swapped_bytes.append(hex_bytes[i])
    else:
        # Odd number of bytes (shouldn't happen, but handle it)
        swapped_bytes.append(hex_bytes[i])

print(f"Swapped to {len(swapped_bytes)} bytes")

# Reconstruct the data section with swapped bytes
# Keep the same formatting style (16 bytes per line)
lines = []
bytes_per_line = 16

for i in range(0, len(swapped_bytes), bytes_per_line):
    line_bytes = swapped_bytes[i:i+bytes_per_line]
    hex_str = ', '.join(f'0x{b}' for b in line_bytes)
    if i + bytes_per_line < len(swapped_bytes):
        lines.append(f'  {hex_str},')
    else:
        # Last line - no trailing comma
        lines.append(f'  {hex_str}')

new_data_section = '\n'.join(lines)

# Reconstruct the full file
new_content = header + '\n' + new_data_section + '\n' + footer

# Write back
with open('components/core/ui/test.c', 'w', encoding='utf-8') as f:
    f.write(new_content)

print("Successfully swapped bytes in components/core/ui/test.c")
