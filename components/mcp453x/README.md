## External Component MCP453X (MCP4531, MCP4532, MCP4541 MCP4542) for ESPHOME 2025.2.1 ->


Copy the folder `mcp453x` which is located in `components` to the identical folder at your instance.
Create your YAML and smile again - MCP453X is back and working in ESPHOME :)


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

# Create the MCP453X base component
mcp453x:
  id: my_mcp453x
  address: 0x28

# Create the MCP453X output
output:
  - platform: mcp453x
    id: fan_output
    mcp453x_id: my_mcp453x

# Fan component
fan:
  - platform: speed
    output: fan_output
    name: "MCP453X Fan"
    speed_count: 100
```
