#include "Bluetooth.hpp"
#include "joystick.hpp"
#include "serial.hpp"
#include "led.hpp"
//#include "RGB.hpp"

auto master = core::Comm::Bluetooth{10, 9, 8};
auto joystick = core::Control::joystick{A5, A4, 2};
auto led = core::effect::led{4};
//auto frontRGB = core::Effect::RGB{4, 3, A0};
//auto leftRGB = core::Effect::RGB{12, 13, A0};
//auto rightRGB = core::Effect::RGB{11, 1, A0};

void setup() {
    // Wait for serial monitor to be opened
    delay(9000);
    serial.begin(9600);
    serial.println("Serial initialized...");

    serial.println("Start to initialize bluetooth...");
    serial.println("Testing bluetooth...");
    master.info();

    int ret;
    do {
        serial.println("Trying to make the connection...");
        ret = master.as_master("1862E43DF32F");
    } while (ret != 0);

    delay(2000);
    serial.println("Bluetooth is ready...");
}

void loop() {
    using axis = typename core::Control::joystick::axis;
    using pos = typename axis::pos;
    using dir = typename axis::dir;
    //if (serial.is_available()) {
    //    auto ch = serial.getChar_noblock();
    //    if (ch != '\n')
    //        master.print(ch);
    //}

    auto positions = joystick.read();

    if (positions.get(dir::y) == pos::up) {
        master.print('F');
    } else if (positions.get(dir::y) == pos::down) {
        master.print('B');
    }
    
    if (positions.get(dir::x) == pos::up) {
        master.print('R');
    } else if (positions.get(dir::x) == pos::down) {
        master.print('L');
    }

    if (positions.get(dir::x) == pos::deadzone && positions.get(dir::y) == pos::deadzone) {
        master.print('S');
    }

    if (master.is_available()) {
        if (master.getChar_noblock() == 'F')
            led.setOn();
        else
            led.setOff();
    }

    /*
    if (master.is_available()) {
        auto ch = master.getChar_noblock();

        if (ch == 'F') {
            frontRGB.setRed();
        } else {
            frontRGB.unsetRed();
            frontRGB.setGre();
        }

        if (ch == 'L') {
            leftRGB.setRed();
        } else {
            leftRGB.unsetRed();
            leftRGB.setGre();
        }
        
        if (ch == 'R') {
            rightRGB.setRed();
        } else {
            rightRGB.unsetRed();
            rightRGB.setGre();
        }
    } else {
        frontRGB.unsetRed();
        frontRGB.setGre();
        leftRGB.unsetRed();
        leftRGB.setGre();
        rightRGB.unsetRed();
        rightRGB.setGre();
    }
    */
}
