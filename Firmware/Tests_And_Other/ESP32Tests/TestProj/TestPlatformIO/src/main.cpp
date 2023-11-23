#include <Arduino.h>

#include <driver/rmt_common.h>
#include <driver/rmt_rx.h>
#include <driver/rmt_tx.h>

//https://github.com/espressif/esp-idf/blob/master/components/driver/test_apps/rmt/main/test_rmt_rx.c#L43
//https://github.com/espressif/esp-idf/issues/11768
//https://github.com/espressif/esp-idf/tree/release/v5.1/examples/peripherals/rmt/onewire


// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}