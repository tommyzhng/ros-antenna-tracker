# ros-antenna-tracker

A ROS package that allows an minimal-component antenna to track a drone/vehicle with GPS. Initial coords are placed inside the launch file and the package takes care of the rest.

## `tracker.launch`
Launches the tracker. Params:
- `antenna_latitude`: Lattitude of the antenna.
- `antenna_longitude`: Longitude of the antenna.
- `antenna_initial_heading`: Initial heading of the antenna.

## Rosserial
Allows the ESP32 to obtain topics from the computer:

For an ESP operating at baud=115200 @ USB0: \
`rosrun rosserial_python serial_node.py _port:=/dev/ttyUSB0 _baud:=115200`

## Components
- 2 Servos (MG996R)
- Servo pan and tilt mount
- ESP32
- ROS / PX4 and GPS on the drone.
