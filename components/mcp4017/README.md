## External Component MCP4017 /AD5246 /MAX5395  for ESPHOME 2025.2.1 ->


Copy the folder `mcp4017` which is located in `components` to the identical folder at your instance.
Create your YAML and smile again - MCP4017 is back and working in ESPHOME :)


> Example YAML:
```
# Include components directory

external_components:
  - source: github://ananyevgv/esphome-components/

# I2C bus configuration
i2c:
  sda: GPIO6          # Replace with your GPIO configuration
  scl: GPIO7          # Replace with your GPIO configuration
  scan: true
  frequency: 100kHz   # Lower frequency for reliability

# Create the MCP4017 base component
mcp4017:
  id: my_mcp4017
  address: 0x2F

# Create the MCP4017 output
output:
  - platform: mcp4017
    id: fan_output
    mcp4017_id: my_mcp4017

# Fan component
fan:
  - platform: speed
    output: fan_output
    name: "MCP4017 Fan"
    speed_count: 100
```
