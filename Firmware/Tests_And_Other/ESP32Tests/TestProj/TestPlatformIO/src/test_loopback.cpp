#include <Arduino.h>

#include "driver/rmt_tx.h"
#include "driver/rmt_rx.h"

//esp32 error handling
#include "unity.h"


typedef struct {
    TaskHandle_t task_to_notify;
    size_t received_symbol_num;
} test_nec_rx_user_data_t;


static bool test_rmt_rx_done_callback(rmt_channel_handle_t channel, const rmt_rx_done_event_data_t *edata, void *user_data)
{
    Serial.println("Callback gotten");
    return false;
}



void test_init(void)
{
    Serial.begin(9600);

    //config for RX channel
    rmt_rx_channel_config_t rx_channel_cfg = {
        .gpio_num = 0,
        .clk_src = 0, //use clock channel 0
        .resolution_hz = 1000000, // 1MHz, 1 tick = 1us
        .mem_block_symbols = 64, //minimal size
        .flags
        {
            .with_dma = false, //don't use DMA for this one
            .io_loop_back = true, // the GPIO will act like a loopback
        }
    };

    //register RX channel
    Serial.printf("install rx channel\r\n");
    rmt_channel_handle_t rx_channel = NULL;
    TEST_ESP_OK(rmt_new_rx_channel(&rx_channel_cfg, &rx_channel));

    //set up callbacks for the RX channel
    Serial.printf("register rx event callbacks\r\n");
    rmt_rx_event_callbacks_t cbs = {
        .on_recv_done = test_rmt_rx_done_callback,
    };
       test_nec_rx_user_data_t test_user_data = {
        .task_to_notify = xTaskGetCurrentTaskHandle(),
    };
    TEST_ESP_OK(rmt_rx_register_event_callbacks(rx_channel, &cbs, &test_user_data));

    

    //config for TX channel
    rmt_tx_channel_config_t tx_channel_cfg = {
        .gpio_num = 0,
        .clk_src = 0,
        .resolution_hz = 1000000, // 1MHz, 1 tick = 1us
        .mem_block_symbols = SOC_RMT_MEM_WORDS_PER_CHANNEL,
        .trans_queue_depth = 4,
        .flags
        {
            .io_loop_back = true,
            .io_od_mode = true //enable open drain
        } // TX channel and RX channel will bounded to the same GPIO
    };
    Serial.printf("install tx channel\r\n");
    rmt_channel_handle_t tx_channel = NULL;
    TEST_ESP_OK(rmt_new_tx_channel(&tx_channel_cfg, &tx_channel));

    //how many times to loop the packet when transmitting
    rmt_transmit_config_t transmit_config = {
        .loop_count = 0, // no loop
    };


    //start the channels (tx before rx)
    Serial.printf("enable tx channel\r\n");
    TEST_ESP_OK(rmt_enable(tx_channel));
    Serial.printf("enable rx channel\r\n");
    TEST_ESP_OK(rmt_enable(rx_channel));

    //set up the place to get the stuff in
    rmt_symbol_word_t remote_codes[128];

    //set up signal filtering on the RX channel
    rmt_receive_config_t receive_config = {
        .signal_range_min_ns = 1250,
        .signal_range_max_ns = 12000000,
    };

    //begin listening for data packets
    Serial.printf("begin listening\r\n");
    TEST_ESP_OK(rmt_receive(rx_channel, remote_codes, sizeof(remote_codes), &receive_config));
    
    //TEST_ESP_OK(rmt_transmit(tx_channel, nec_encoder, (uint16_t[]) {
    //    0x0440, 0x3003 // address, command
    //}, 4, &transmit_config));




}

void test_run(void)
{

}

