/*-----------------------------------------------------------------------------------------------------------
 *                                                                                                           
 *  bluetooth.cpp                                                                           
 *  This file is adapted from Slave_ELEC1601_Student_2019_v3.ino and Master_ELEC1601_Student_2019_v3,
 *  and have undergone a lot of refactorization.
 *
 *  Below is the original header declaration of Slave_ELEC1601_Student_2019_v3.ino:
 *
 *-----------------------------------------------------------------------------------------------------------
 *
 *  Slave_ELEC1601_Student_2019_v3
 *  The Instructor version of this code is identical to this version EXCEPT it also sets PIN codes           
 *  20191008 Peter Jones                                                                                     
 *                                                                                                           
 *  Bi-directional passing of serial inputs via Bluetooth                                                    
 *  Note: the void loop() contents differ from "capitalise and return" code                                  
 *                                                                                                           
 *  This version was initially based on the 2011 Steve Chang code but has been substantially revised         
 *  and heavily documented throughout.                                                                       
 *                                                                                                           
 *  20190927 Ross Hutton                                                                                     
 *  Identified that opening the Arduino IDE Serial Monitor asserts a DTR signal which resets the Arduino,    
 *  causing it to re-execute the full connection setup routine. If this reset happens on the Slave system,   
 *  re-running the setup routine appears to drop the connection. The Master is unaware of this loss and      
 *  makes no attempt to re-connect. Code has been added to check if the Bluetooth connection remains         
 *  established and, if so, the setup process is bypassed.                                                   
 *
 *-----------------------------------------------------------------------------------------------------------
 *
 *  And below is the one of Master_ELEC1601_Student_2019_v3.ino:
 *
 *-----------------------------------------------------------------------------------------------------------
 *
 *   Master_ELEC1601_Student_2019_v3                                                                         
 *   The Instructor version of this code is identical to this version EXCEPT it also sets PIN codes           
 *   20191008 Peter Jones                                                                                     
 *                                                                                                             
 *   Bi-directional passing of serial inputs via Bluetooth                                                    
 *   Note: the void loop() contents differ from "capitalise and return" code                                  
 *                                                                                                            
 *   This version auto-searches for slave MAC using slave name and attempts connection repeatedly             
 *   (as implemented in original BluetoothShield demo code "Master.pde" by Steve Chang / Seeed Tech. 2011)    
 *                                                                                                            
 *   This version was initially based on the 2011 Steve Chang code but has been substantially revised         
 *   and heavily documented throughout.                                                                       
 * 
 *   20190927 Ross Hutton
 *   Identified that opening the Arduino IDE Serial Monitor asserts a DTR signal which resets the Arduino,
 *   causing it to re-execute the full connection setup routine. If this reset happens on the Master system,
 *   it should subsequently re-connect to the Slave but appears to hang while searching for the slave
 *   address. As the Bluetooth shield itself is not reset by opening the Serial Monitor, code has been added
 *   to check if the Bluetooth connection remains established and, if so, the setup process is bypassed.
 *
 *-----------------------------------------------------------------------------------------------------------
 *
 * This file will not be possible without
 * 
 *  - Peter Jones
 *  - Ross Hutton
 *
 * from usyd ELEC 1601.
 *
 *-----------------------------------------------------------------------------------------------------------
 */

#include "bluetooth.hpp"
#include <Arduino.h>

namespace core::Control {
Bluetooth::Bluetooth(pin_t RxD, pin_t TxD, pin_t ConnectionStatus_pin) noexcept:
    blueToothSerial(RxD, TxD), 
    ConnectionStatus{ConnectionStatus_pin, digitalPin_t::Mode::input}
{
    // Set Bluetooth module to default baud rate 38400
    blueToothSerial.begin(38400);
}

void Bluetooth::setupBlueToothConnection(const char *mode, const char *Cmd_str, const char *AdditionalConfigurationCmd,
                                         int shieldPairNumber) {
    String Cmd = Cmd_str;

    Cmd += shieldPairNumber;
    Cmd += "\r\n";
 
    print("\r\n+STWMOD=", mode, "\r\n");      // Set the Bluetooth to work in master mode
    print(Cmd);                      // Set the bluetooth name using masterNameCmd
    print("\r\n+STAUTO=0\r\n");      // Auto-connection is forbidden here
    print(AdditionalConfigurationCmd);

    /*
     * print() sets up a transmit/outgoing buffer for the string which is then transmitted via interrupts one character at a time.
     * This allows the program to keep running, with the transmitting happening in the background.
     * Serial.flush() does not empty this buffer, instead it pauses the program until all Serial.print()ing is done.
     * This is useful if there is critical timing mixed in with Serial.print()s.
     * To clear an "incoming" serial buffer, use while(Serial.available()){Serial.read();}
     */

    flush();
    delay(2000);                                     // This delay is required

    print("\r\n+INQ=1\r\n");         // Make the master Bluetooth inquire
    
    flush();
    delay(2000);                                     // This delay is required
}

auto Bluetooth::getSlaveAddress(int shieldPairNumber, const char *slaveName_s) -> String {
    Serial.print("Searching for address of slave: ");
    Serial.print(slaveName_s);

    String slaveName = slaveName_s;
    slaveName = ";" + slaveName + shieldPairNumber;

    // Start symble when there's any return
    String retSymb = "+RTINQ=";

    /*
     * Initially, read will loop and, character-by-character, fill recvBuf to be:
     * 
     *    +STWMOD=1 followed by a blank line
     *    +STNA=MasterTest (followed by a blank line)
     *    +S
     *    OK (followed by a blank line)
     *    OK (followed by a blank line)
     *    OK (followed by a blank line)
     *    WORK:
     *
     * It will then, character-by-character, add the result of the first device that responds to the +INQ request:
     *    +RTINQ=64,A2,F9,xx,xx,xx;OnePlus 6 (xx substituted for anonymity)
     *
     * If this does not contain slaveName, the loop will continue. If nothing else responds to the +INQ request, the
     * process will appear to have frozen BUT IT HAS NOT. Be patient. Ask yourself why your slave has not been detected.
     * Eventually your slave will respond and the loop will add:
     *    +RTINQ=0,6A,8E,16,C4,1B;SlaveTest
     *
     * nameIndex will identify "SlaveTest"
     * This will strip 0,6A,8E,16,C4,1B from the buffer and return. 
     */

    int nameIndex;
    //auto recvBuf = read(slaveName, nameIndex);
    auto recvBuf = read([&](String &buffer){
        nameIndex = buffer.indexOf(slaveName);
        return nameIndex != -1;
    });

    // Get the start position of slave address
    auto start_pos = nameIndex - retSymb.length() - 3 /* The number of characters per segment */ * 6 /* segments */;
    auto addrIndex = recvBuf.indexOf(retSymb, start_pos) + retSymb.length();

    // Get the string of slave address
    return recvBuf.substring(addrIndex, nameIndex);
}

void Bluetooth::makeConnection(String slaveAddr) {
    String connectCmd = "\r\n+CONN=";
    connectCmd += slaveAddr + "\r\n";
    
    int connectAttempt = 0;
    bool connectOK = false;

	/*
     * Initially, if(blueToothSerial.available()) will loop and, character-by-character, fill recvBuf to be:
     *    OK (followed by a blank line)
     *    +BTSTATE:3 (followed by a blank line)(BTSTATE:3 = Connecting)
     *
     * It will then, character-by-character, add the result of the connection request.
     * If that result is "CONNECT:OK", the while() loop will break and the do() loop will exit.
     * If that result is "CONNECT:FAIL", the while() loop will break with an appropriate "FAIL" message
     * and a new connection command will be issued for the same slave address.
	 */
    do {
        Serial.print("Connect attempt: ");
        Serial.println(++connectAttempt);

        print(connectCmd);

		auto recvBuf = read([&](String &buffer) noexcept {
            if (buffer.indexOf("CONNECT:OK") != -1) {
                connectOK = true;
                return true;
            } else if (buffer.indexOf("CONNECT:FAIL") != -1)
                return true;
            return false;
        });
	} while (!connectOK);
}

static void delay_and_flush(Bluetooth &bt) {
    delay(1000);
    Serial.flush();
    bt.flush();
}

auto Bluetooth::master(pin_t RxD, pin_t TxD, pin_t ConnectionStatus_pin, int shieldPairNumber) noexcept -> Bluetooth {
    Bluetooth bt{RxD, TxD, ConnectionStatus_pin};

    if (!bt.is_connected()) {
        Serial.println("Setting up the local (master) Bluetooth module.");
        bt.setupBlueToothConnection("1", "\r\n+STNA=Master", "", shieldPairNumber);
        Serial.println("Master is inquiring!");

        auto slaveAddr = bt.getSlaveAddress(shieldPairNumber, "Slave");
        Serial.print("Slave address found: ");
        Serial.println(slaveAddr);

        bt.makeConnection(slaveAddr);
        Serial.println("Connected to slave!");

        delay_and_flush(bt);
    } else
        Serial.println("Already connected to Slave - remove USB cabe if reboot of Master Bluetooth is required.");

    return bt;
}

auto Bluetooth::slave(pin_t RxD, pin_t TxD, pin_t ConnectionStatus_pin, int shieldPairNumber) noexcept -> Bluetooth {
    Bluetooth bt{RxD, TxD, ConnectionStatus_pin};

    if (!bt.is_connected()) {
        Serial.println("Setting up the local (slave) Bluetooth module.");
        bt.setupBlueToothConnection("0", "\r\n+STNA=Slave", "\r\n+STOAUT=1\r\n", shieldPairNumber);
        Serial.println("Slave is inquirable!");

        delay_and_flush(bt);
    } else
        Serial.println("Already connected to Master - remove USB cabe if reboot of Master Bluetooth is required.");

    return bt;
}

bool Bluetooth::is_connected() const noexcept {
    return ConnectionStatus.read() == digitalPin_t::Level::high;
}

char Bluetooth::read() {
    while (!is_available())
        /* blocks */;

    return blueToothSerial.read();
}

bool Bluetooth::is_available() const noexcept {
    return blueToothSerial.available();
}

void Bluetooth::flush() {
    blueToothSerial.flush();
}
} /* namespace core::Control */
