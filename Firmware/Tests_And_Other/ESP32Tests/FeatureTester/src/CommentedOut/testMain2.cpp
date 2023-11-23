// #include "Arduino.h"
// #include "esp32-hal.h"

// #include <DShotRMT.h>

// #define DSHOT_CLK_DIVIDER 8
// #define PIN_TX 23
// #define PIN_RX 18
// #define CHANNEL_TX 0
// #define CHANNEL_RX 1
// //array of timings for the RMT packet
// #define DSHOT_PACKET_LENGTH 17
// rmt_data_t dshot_tx_rmt_item[DSHOT_PACKET_LENGTH];

// //timing configs(compliant with dshot300)
// uint16_t ticks_per_bit = 32;
// uint16_t ticks_zero_high = 12;
// uint16_t ticks_one_high = 24;
// uint16_t ticks_zero_low = (ticks_per_bit - ticks_zero_high);
// uint16_t ticks_one_low = (ticks_per_bit - ticks_one_high);


// rmt_obj_t* rmt_send = NULL;
// void buildRMTItem(void);

// extern "C" void receive_trampoline(uint32_t *data, size_t len, void * arg);

// class MyProcessor {
//   private:
//     rmt_obj_t* rmt_recv = NULL;
//     float realNanoTick;
//     uint32_t buff; // rolling buffer of most recent 32 bits.
//     int at = 0;

//   public:
//     MyProcessor(uint8_t pin, float nanoTicks) {
//       if ((rmt_recv = rmtInit(pin, RMT_RX_MODE, RMT_MEM_64)) == NULL)
//       {
//         Serial.println("init receiver failed\n");
//       }

//       realNanoTick = rmtSetTick(rmt_recv, nanoTicks);
//     };
//     void begin() {
//       rmtRead(rmt_recv, receive_trampoline, this);
//     };

//     void process(rmt_data_t *data, size_t len) {
//       for (int i = 0; len; len--) {
//         if (data[i].duration0 == 0)
//           break;
//         buff = (buff << 1) | (data[i].level0 ? 1 : 0);
//         i++;

//         if (data[i].duration1 == 0)
//           break;
//         buff = (buff << 1) | (data[i].level1 ? 1 : 0);
//         i++;
//       };
//     };
//     uint32_t val() {
//       return buff;
//     }
// };

// void receive_trampoline(uint32_t *data, size_t len, void * arg)
// {
//   MyProcessor * p = (MyProcessor *)arg;
//   p->process((rmt_data_t*) data, len);
// }

// // Attach 1 processor
// MyProcessor mp1 = MyProcessor(PIN_RX, DSHOT_CLK_DIVIDER);

// // Initialize a DShotRMT object for the motor
// DShotRMT motor01(PIN_TX, RMT_CHANNEL_0);

// void setup()
// {

//     Serial.begin(9600);

//     mp1.begin();
    
//     //buildRMTItem();
//     //if ((rmt_send = rmtInit(PIN_TX, RMT_TX_MODE, RMT_MEM_64)) == NULL)
//     //{
//     //    Serial.println("init sender failed\n");
//     //}
//     //float realTick = rmtSetTick(rmt_send, DSHOT_CLK_DIVIDER);
//     //Serial.printf("real tick set to: %fns\n", realTick);

//     // Start generating DShot signal for the motor
//     motor01.begin(DSHOT300, false);

// }

// void loop()
// {

//     // Send the throttle value to the motor
//     motor01.sendThrottleValue(random());


//     if(mp1.val() != 0)
//     {
//         Serial.printf("OBJ A: %08x\n", mp1.val());
        
//     }
//     delay(500);

// }







// void buildRMTItem(void)
// {
//     for(int i = 0; i < DSHOT_PACKET_LENGTH - 1; ++i)
//     {
//         //flip-flop for testing
//         if(i%2)
//         {
//             dshot_tx_rmt_item[i].duration0 = ticks_one_low;
//             dshot_tx_rmt_item[i].duration1 = ticks_one_high;
//         }
//         else
//         {
//             dshot_tx_rmt_item[i].duration0 = ticks_one_low;
//             dshot_tx_rmt_item[i].duration1 = ticks_one_high;
//         }

//         dshot_tx_rmt_item[i].level0 = 0;
//         dshot_tx_rmt_item[i].level1 = 1;
//     }



//     dshot_tx_rmt_item[DSHOT_PACKET_LENGTH - 1].duration0 = 32;
//     dshot_tx_rmt_item[DSHOT_PACKET_LENGTH - 1].duration1 = 24;
//     dshot_tx_rmt_item[DSHOT_PACKET_LENGTH - 1].level0 = 0;
//     dshot_tx_rmt_item[DSHOT_PACKET_LENGTH - 1].level1 = 1;
// }













