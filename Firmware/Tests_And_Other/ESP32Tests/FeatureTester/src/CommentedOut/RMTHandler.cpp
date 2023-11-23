
// #include <Arduino.h>
// #include <DshotRMT.h>

// #include "Utils.h"


// // USB serial port needed for this example
// const auto USB_SERIAL_BAUD = 9600;//115200;
// #define USB_Serial Serial

// // Define the GPIO pin connected to the motor and the DShot protocol used
// const auto MOTOR01_PIN = 23;//GPIO_NUM_4;
// const auto DSHOT_MODE = DSHOT600;//DSHOT300;

// // Define the failsafe and initial throttle values
// const auto FAILSAFE_THROTTLE = 999;
// const auto INITIAL_THROTTLE = 48;

// // Initialize a DShotRMT object for the motor
// DShotRMT motor01(MOTOR01_PIN, RMT_CHANNEL_0);

// void setup3()
// {
//     USB_Serial.begin(USB_SERIAL_BAUD);

//     delay(50); //give ESCs a chance to start

//     // Start generating DShot signal for the motor
//     motor01.begin(DSHOT_MODE, false);
// }

// uint16_t readSerialThrottle();

// void loop3()
// {
//     static int lastValue = 0;
// 	static int value = 0;
// 	int result = GetUserInput();
	
// 	value += result;

//     if(value < 0)
//         value = 0;
//     if(value > 2048)
//         value = 2048;

//     if(lastValue != value)
//     {
//         lastValue = value;
//         Serial.println(value);
//     }

//     // Read the throttle value from the USB serial input
//     //uint16_t throttle_input = readSerialThrottle();

//     // Set the throttle value to either the value received from the serial input or the failsafe throttle value
//     //auto throttle_value = (throttle_input > 0) ? throttle_input : FAILSAFE_THROTTLE;
    

//     // Send the throttle value to the motor
//     motor01.sendThrottleValue(value);
// }

// // Read the throttle value from the USB serial input
// uint16_t readSerialThrottle()
// {
//     if (USB_Serial.available() > 0)
//     {
//         return USB_Serial.readStringUntil('\n').toInt();
//     }

//     return 0;
// }















