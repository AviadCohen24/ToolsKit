#!/bin/bash
# Run node-gyp configure
node-gyp configure

# Run node-gyp build
node-gyp build

# Copy the HardwareManagerAddon.node to the specified directory
cp build/Release/HardwareManagerAddon.node ../electron/src/shared/hardware

echo "Process completed."
