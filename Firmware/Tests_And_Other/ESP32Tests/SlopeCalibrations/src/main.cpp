#include <Arduino.h>
#include <Bounce2.h> 
#include <DShotRMT.h>

#include "configuration.h"

// #include <driver/rmt_common.h>
// #include <driver/rmt_rx.h>
// #include <driver/rmt_tx.h>

// https://github.com/espressif/esp-idf/blob/master/components/driver/test_apps/rmt/main/test_rmt_rx.c#L43
// https://github.com/espressif/esp-idf/issues/11768
// https://github.com/espressif/esp-idf/tree/release/v5.1/examples/peripherals/rmt/onewire

Bounce2::Button trggr = Bounce2::Button();
DShotRMT dshot_driver = DShotRMT(ESC_1_PIN);

//the map function but it uses floats
float map_float(float x, float in_min, float in_max, float out_min, float out_max) {
    const float run = in_max - in_min;
    if(run == 0){
        log_e("map(): Invalid input range, min == max");
        return -1; // AVR returns -1, SAM returns 0
    }
    const float rise = out_max - out_min;
    const float delta = x - in_min;
    return (delta * rise) / run + out_min;
}

void run_esc_test(bool execute, int speed)
{
	static bool subtick_a = false;
	
	//send dshot commands to the ESC every 10 ms
	if (millis() % 5 == 0)
	{
		if(!subtick_a)
		{
			subtick_a = true;

			uint16_t rpm_out = 0;
			int err = dshot_driver.get_dshot_packet(&rpm_out);
			if (execute && millis() % 50 == 0)
			{
				float volts = analogRead(VOLTMETER_PIN) * 0.0126 + 2.25;//2.15;
				if(err == 0)
					Serial.printf("%d, %f,\n", rpm_out, volts);
			}

			dshot_driver.send_dshot_value(execute ? (uint16_t)speed : 48); //DSHOT_THROTTLE_MAX


		}
	}
	else
		subtick_a = false;
}


void setup()
{
	// put your setup code here, to run once:

	Serial.begin(115200);

	pinMode(VOLTMETER_PIN, INPUT);
	
	//pinMode(TRIGGER_PIN, INPUT_PULLUP);
	
	trggr.attach(TRIGGER_PIN, INPUT_PULLUP);
	trggr.interval(10);
	trggr.setPressedState(LOW);

	dshot_driver.begin(DSHOT600, ENABLE_BIDIRECTION, 14);

}

void loop()
{
	// put your main code here, to run repeatedly:
	static bool has_pressed = false;

	static bool test_flip_flop = false;

	trggr.update();
	bool triggered = trggr.pressed();

	//uint16_t vomtmeter_read = analogRead(VOLTMETER_PIN);


	if (triggered && !has_pressed)
	{

		//float volts = map_float(vomtmeter_read, ADC_VALUE_REF_1, ADC_VALUE_REF_2, ADC_VOLTAGE_REF_1, ADC_VOLTAGE_REF_2) *
		//				(R1_VAL + R2_VAL) / R2_VAL;
		//float volts = vomtmeter_read * 0.0126 + 2.25;//2.15;
		//Serial.printf("Raw Voltage: %d || Mapped Voltage: %f\n", vomtmeter_read, volts);

		test_flip_flop = !test_flip_flop; //start/stop flywheel testing

		Serial.printf("Flywheel State: %d\n", test_flip_flop);

	}
	//make sure the trigger only affects 
	if (triggered)
		has_pressed = true;
	else
		has_pressed = false;
	



	static int speed = 200;
	if (Serial.available())
	{
		speed = Serial.parseInt();
		Serial.printf("New Speed Set: %d\n", speed);
	}
	run_esc_test(test_flip_flop, speed);



}

////////////////////////////////////////////////////////////////////////

// #include <Arduino.h>

// //TEST
// //#include <hal/gpio_hal.h>

// #include <DShotRMT.h>
// #include "configuration.h"

// // USB serial port needed for this example
// const int USB_SERIAL_BAUD = 115200;
// #define USB_Serial Serial

// // Define the GPIO pin connected to the motor and the DShot protocol used
// const auto MOTOR01_PIN = ESC_1_PIN;
// const auto MOTOR02_PIN = ESC_2_PIN;
// const auto DSHOT_MODE = DSHOT600;

// // Define the failsafe and initial throttle values
// const auto FAILSAFE_THROTTLE = 999;
// const auto INITIAL_THROTTLE = 48;


// DShotRMT anESC(MOTOR01_PIN);
// DShotRMT anotherESC(MOTOR02_PIN);

// void setup()
// {
// 	USB_Serial.begin(USB_SERIAL_BAUD);
// 	anESC.begin(DSHOT_MODE, ENABLE_BIDIRECTION, 14);
// 	anotherESC.begin(DSHOT_MODE, ENABLE_BIDIRECTION, 14);
	
// 	pinMode(VOLTMETER_PIN, INPUT);
// }




// int loopCount = 0;
// void loop()
// {
// 	if(loopCount < 700)
// 	{
// 		anESC.send_dshot_value(INITIAL_THROTTLE);
// 		anotherESC.send_dshot_value(INITIAL_THROTTLE);
// 	}
// 	else if(loopCount < 1200)
// 	{

//     	anESC.send_dshot_value(500);
// 		anotherESC.send_dshot_value(300);
// 	}
// 	else
// 	{
// 		anESC.send_dshot_value(300);
// 		anotherESC.send_dshot_value(500);
// 	}

// 	if(loopCount % 10 == 0)
// 	{
// 		//Serial.print(anESC.get_dshot_RPM());
// 		//Serial.print(",");
// 		//Serial.print(anotherESC.get_dshot_RPM());

// 		float volts = analogRead(VOLTMETER_PIN) * 0.0126 + 2.25;//2.15;
// 		Serial.printf("%d,%d,%f\n", anESC.get_dshot_packet(), anotherESC.get_dshot_RPM(), volts);
// 	}

// 	delay(10);
// 		++loopCount;

// }


