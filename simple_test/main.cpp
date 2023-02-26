#include "CppLinuxSerial/SerialPort.hpp"

using namespace mn::CppLinuxSerial;

int main() {
	// Create serial port object and open serial port at 57600 buad, 8 data bits, no parity bit, one stop bit (8n1),
	// and no flow control
	SerialPort serialPort("/dev/ttyUSB2", BaudRate::B_115200, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE, HardwareFlowControl::ON, SoftwareFlowControl::OFF);
	// Use SerialPort serialPort("/dev/ttyACM0", 13000); instead if you want to provide a custom baud rate
	serialPort.SetTimeout(1000); // Block for up to 100ms to receive data
	serialPort.Open();

	// WARNING: If using the Arduino Uno or similar, you may want to delay here, as opening the serial port causes
	// the micro to reset!

	// Write some ASCII data
	//serialPort.Write("ATE?\r\n");

	// Read some data back (will block for up to 100ms due to the SetTimeout(100) call above)
	while(1) {
		uint8_t byte;
		ssize_t n = serialPort.ReadByte(&byte);
		if(n == 0) {
			std::cout << "Timeout!" << std::endl;
		} else {
			std::cout << (char)byte;
		}
	}
	//std::cout << "Read data = \"" << readData << "\"" << std::endl;

	// Close the serial port
	serialPort.Close();
}
