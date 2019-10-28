#include "Bluetooth.hpp"
#include "serial.hpp"

void setup() {
    // Wait for serial monitor to be opened
    delay(9000);
    serial.begin(9600);
    serial.println("Serial initialized...");
}

void loop() {
    serial.println("Start to initialize bluetooth...");
    auto master = core::Comm::Bluetooth{8, 7, 4};

    serial.println("Testing bluetooth...");
    master.info();

    int ret;
    do {
        serial.println("Trying to make the connection...");
        ret = master.as_master("1862E43DF32F");
    } while (ret != 0);

    delay(2000);
    serial.println("Bluetooth is ready...");

    while (1) {
        if (master.is_available())
            serial.print(master.getChar_noblock());
    }
}
