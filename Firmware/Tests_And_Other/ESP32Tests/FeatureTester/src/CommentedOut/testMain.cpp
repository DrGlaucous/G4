

// #include <Arduino.h>
// // The RMT (Remote Control) module library is used for generating the DShot signal.
// #include <driver/rmt.h>
// #include <esp32-hal-rmt.h>



// #include "Utils.h"


// #define DSHOT_CLK_DIVIDER 8
// #define PIN_TX 23
// #define PIN_RX 18
// #define CHANNEL_TX 0
// #define CHANNEL_RX 1

// //enums for easy flag setting with the arduino rmt library
// enum
// {
//     FLAG_RX_INVERT_IN = 0x1, /*!< Whether to invert the incoming RMT channel signal */
//     FLAG_RX_WITH_DMA = 0x2, /*!< If set, the driver will allocate an RMT channel with DMA capability */
//     FLAG_RX_IO_LOOPBACK = 0x4, /*!< For debug/test, the signal output from the GPIO will be fed to the input path as well */
// };
// enum
// {
//     FLAG_TX_INVERT_OUT = 0x1, /*!< Whether to invert the RMT channel signal before output to GPIO pad */
//     FLAG_TX_WITH_DMA = 0x2, /*!< If set, the driver will allocate an RMT channel with DMA capability */
//     FLAG_TX_IO_LOOPBACK = 0x4, /*!< The signal output from the GPIO will be fed to the input path as well */
//     FLAG_TX_IO_OD_MODE = 0x8, /*!< Configure the GPIO as open-drain mode */

// };

// //DMA: Direct Memory Access
// //RMT can access system memory without the need for the CPU if this flag is enabled
// //https://youtu.be/ejyt-kWmys8


// //open drain only pulls on a signal from one direction, so that way,
// //something else can pull on it too and not have its signal stomped on by the ESP32 pushing more data out


// //rmt_transmit_config_t::eot_level  is the same as .tx_config.idle_level = RMT_IDLE_LEVEL_HIGH;


// //forward delcarations
// void tx_End_Callback();
// void rx_End_Callback();
// void buildRMTItem(void);


// uint32_t responseHolder; //holds the data that comes from the DSHOT telemetry
// bool txCalledBack;
// bool rxCalledBack;

// //array of timings for the RMT packet
// #define DSHOT_PACKET_LENGTH 17
// rmt_item32_t dshot_tx_rmt_item[DSHOT_PACKET_LENGTH];

// //timing configs(compliant with dshot300)
// uint16_t ticks_per_bit = 32;
// uint16_t ticks_zero_high = 12;
// uint16_t ticks_one_high = 24;
// uint16_t ticks_zero_low = (ticks_per_bit - ticks_zero_high);
// uint16_t ticks_one_low = (ticks_per_bit - ticks_one_high);


// RingbufHandle_t rxHouse = NULL; //pointer to the ringbuffer where RX data goes from RMT



// rmt_rx_data_cb_t inVat(uint32_t *data, size_t len, void *arg);

// void setup8()
// {
//     buildRMTItem();
//     txCalledBack = false;
//     rxCalledBack = false;
//     responseHolder = 0;
//     Serial.begin(9600);


//     //ensure that each rmt channel has only a single memory block (dshot only gives us 16 bytes of data, each buffer is 256 bytes)
//     rmt_set_mem_block_num((rmt_channel_t)CHANNEL_TX, 1);
//     //rmt_set_mem_block_num((rmt_channel_t)CHANNEL_RX, 1);

//     //set up a TX RMT object with loopback intent (SEND)
//     rmt_config_t txRMTConfig = 
//     {
//         .rmt_mode = RMT_MODE_TX, //note: RMT_MODE_MAX is just a cap. there is no functionality there.
//         .channel = static_cast<rmt_channel_t>(CHANNEL_TX), //RMT_CHANNEL_0,
//         .gpio_num = static_cast<gpio_num_t>(PIN_TX), //convert arduino pin to ESP32 pin
//         .clk_div = DSHOT_CLK_DIVIDER, //divide clock to 0.1 microseconds / 100 nanoseconds per cycle
//         .mem_block_num = 1, //RMT_CHANNEL_MAX - CHANNEL_TX,
//         .flags = (FLAG_TX_IO_LOOPBACK | FLAG_TX_IO_OD_MODE), //set the loopback config
//         .tx_config =
//         {
//             .idle_level = RMT_IDLE_LEVEL_HIGH, //HIGH if in dshot mode
//             .carrier_en = false,
//             .loop_en = true,//false,                    
//             .idle_output_en = true,
//         }
//     };
//     //rmt_register_tx_end_callback((rmt_tx_end_fn_t)tx_End_Callback, NULL);

    

//     //set up RX RMT object with loopback intent (RECEIVE)
//     /*
//     rmt_config_t rxRMTConfig = 
//     {
//         .rmt_mode = RMT_MODE_RX, //note: RMT_MODE_MAX is just a cap. there is no functionality there.
//         .channel = static_cast<rmt_channel_t>(CHANNEL_RX), //RMT_CHANNEL_0,
//         .gpio_num = static_cast<gpio_num_t>(PIN_RX), //convert arduino pin to ESP32 pin
//         .clk_div = DSHOT_CLK_DIVIDER, //divide clock to 0.1 microseconds / 100 nanoseconds per cycle
//         .mem_block_num = 7, //RMT_CHANNEL_MAX - CHANNEL_RX,
//         .flags = FLAG_RX_IO_LOOPBACK, //set the loopback config and open drain
//         .rx_config =
//         {                          
//             .idle_threshold = (uint16_t)(8), //consider receive finished when we encounter a bit that lasts longer than this
//             .filter_ticks_thresh = 1, //consider pulses shorter than this glitches
//             .filter_en = false, //enable the filter
//         } 
//     };*/

//     //we don't set up explicit callbacks because if we do that, we can't use the rmt_driver_install function
//     //we would have to be a bit more explicit with memory handling




//     //important to install the RX channel before the TX one (if we're using loopback, but I'm not sure this is possible with the current lib version)

//     //push the configs to the backend
//     //rmt_config(&rxRMTConfig);
//     //rmt_driver_install(rxRMTConfig.channel, 1000, 0); //set ringbuffer size to 16 (what? bits? bytes?)
//     //rmt_get_ringbuf_handle(rxRMTConfig.channel, &rxHouse); //get rx_in data location
//     //assert(rxHouse != NULL);

//     //rmt_rx_start(rxRMTConfig.channel, true);

//     rmt_config(&txRMTConfig);
//     rmt_driver_install(txRMTConfig.channel, 0, 0);

//     rmt_write_items((rmt_channel_t)CHANNEL_TX, dshot_tx_rmt_item, DSHOT_PACKET_LENGTH, 0);

//     /*
// rmt_rx_config_t rx_channel_cfg = {
//         .clk_src = clk_src,
//         .resolution_hz = 1000000, // 1MHz, 1 tick = 1us
//         .mem_block_symbols = mem_block_symbols,
//         .gpio_num = 0,
//         .flags.with_dma = with_dma,
//         .flags.io_loop_back = true, // the GPIO will act like a loopback
//     };*/


// }



// void loop8()
// {
//     //GetTicks();

//     //static unsigned long localTimer = 0;
//     //if(MillisecondTicks - localTimer > 1000) //the nature of the if statement renders this obsolete: && MillisecondTicks != LastMillisecondTicks)
//     //{
//     //    localTimer = MillisecondTicks;
//     //    //Serial.println(responseHolder);
//     //}
//     //if(txCalledBack)
//     //{
//     //    txCalledBack = false;
//     //    Serial.println("TX callback");
//     //    
//     //    //check for data in the ringbuffer
//     //    size_t rxSize = 0;
//     //    uint16_t* item = (uint16_t*)xRingbufferReceive(rxHouse, &rxSize, 10);//I don't know how long tickstowait should be...
//     //    Serial.println(rxSize);
//     //}

//     //rmt_write_items((rmt_channel_t)CHANNEL_TX, dshot_tx_rmt_item, DSHOT_PACKET_LENGTH, 0);


//     size_t rxSize = 0;
//     uint16_t* item = (uint16_t*)xRingbufferReceive(rxHouse, &rxSize, 10);//I don't know how long tickstowait should be...
//     if(item != NULL)
//     {
//         Serial.println(rxSize);
//         vRingbufferReturnItem(rxHouse, (void*)item);
        
//     }

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



//     dshot_tx_rmt_item[DSHOT_PACKET_LENGTH - 1].duration0 = ticks_per_bit* 8;
//     dshot_tx_rmt_item[DSHOT_PACKET_LENGTH - 1].duration1 = ticks_per_bit* 8;
//     dshot_tx_rmt_item[DSHOT_PACKET_LENGTH - 1].level0 = 1;
//     dshot_tx_rmt_item[DSHOT_PACKET_LENGTH - 1].level1 = 1;
// }



// void tx_End_Callback()
// {
//     txCalledBack = true;
// }
// void rx_End_Callback()
// {
//     rxCalledBack = true;
// }
