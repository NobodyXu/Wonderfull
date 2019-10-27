/*!
 * The functions in this file wrap over functions provided by 
 * HardwareSerial and SoftwareSerial so that they are more instinct.
 */
#ifndef  __Wonderfull_project_core_Serial_HPP__
# define __Wonderfull_project_core_Serial_HPP__

/*!
 * is_avilable(serial) test whether serial has the next byte available.
 */
template <class Serial_t>
bool is_available(Serial_t &&serial) {
    return serial.available();
}

/*!
 * getChar(serial) is a blocking function call.
 * It will block until is_avilable(serial) == true and then
 * convert serial.read() to type char so that it can be latter printed.
 */
template <class Serial_t>
char getChar(Serial_t &&serial) {
    while (!is_available(serial))
        /* block */;

    return serial.read();
}

/*!
 * print(serial, objs...) will print all objects to serial.
 */
template <class Serial_t, class T, class ...Ts>
void print(Serial_t &&serial, T && t, Ts &&...ts);

/*!
 * base case of recursion:
 *     no arguments is supplied (they are exhausted by recursion)
 */
template <class Serial_t>
void print(Serial_t &&serial) {}

/*!
 * recursion body
 */
template <class Serial_t, class T, class ...Ts>
void print(Serial_t &&serial, T &&t, Ts &&...ts) {
    serial.print(t);
    // Recursion
    print(serial, ts...);
}

/*!
 * println(serial, objs...) will print all objs to serial, along
 * with a trailing newline.
 */
template <class Serial_t, class ...Ts>
void println(Serial_t &&serial, Ts &&...ts) {
    print(serial, ts..., '\n');
}

#endif
