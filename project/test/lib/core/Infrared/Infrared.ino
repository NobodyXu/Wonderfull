#include "Infrared.hpp"
#include "serial.hpp"

core::Sensor::Infrared ir{4};

void setup() {
    serial.begin(9600);
}

void loop() {
    serial.println("Infrared ", ir.has_obstacles() ? "detected obstacles." : "detected nothing.");
}
