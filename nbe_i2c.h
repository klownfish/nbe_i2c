#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <hal/i2c_hal.h>
#include <driver/gpio.h>
#include <hal/gpio_hal.h>
#include <stdint.h>

typedef struct nbe_i2c {
    uint8_t *tx_buf;
    uint16_t should_write;
    uint16_t has_written;
    uint8_t *rx_buf;
    uint16_t should_read;
    uint16_t has_read;
    i2c_hal_context_t hi2c;
    i2c_hw_cmd_t cmd;
    uint8_t cmd_index;
    uint8_t i2c_num;
    uint8_t busy;
    uint8_t preamble_size; //up to 32
} nbe_i2c_t;

extern nbe_i2c_t nbe_i2c0;
extern nbe_i2c_t nbe_i2c1;

uint8_t i2c_first_byte_read(uint8_t address);
uint8_t i2c_first_byte_write(uint8_t address);

uint8_t nbe_i2c_is_busy(nbe_i2c_t *nbe_i2c);
void nbe_i2c_reset(nbe_i2c_t *nbe_i2c);
void nbe_i2c_init(nbe_i2c_t *nbe_i2c, gpio_num_t sda, gpio_num_t scl, uint32_t frequency);
void nbe_i2c_set_rx_buf(nbe_i2c_t *nbe_i2c, uint8_t *buf);
void nbe_i2c_set_tx_buf(nbe_i2c_t *nbe_i2c, uint8_t *buf);

void nbe_i2c_start(nbe_i2c_t *nbe_i2c);
void nbe_i2c_single_start_read(nbe_i2c_t *nbe_i2c, uint8_t address, uint8_t *tx_buf, uint8_t *rx_buf);
void nbe_i2c_single_start_write(nbe_i2c_t *nbe_i2c, uint8_t address, uint8_t *tx_buf, uint8_t *rx_buf);

void nbe_i2c_write_preamble(nbe_i2c_t *nbe_i2c, uint8_t *buf, uint8_t len); //max 32 bytes IN TOTAL

void nbe_i2c_write(nbe_i2c_t *nbe_i2c, uint8_t amount);
void nbe_i2c_read(nbe_i2c_t *nbe_i2c, uint8_t amount);

void nbe_i2c_pause(nbe_i2c_t *nbe_i2c);
void nbe_i2c_stop(nbe_i2c_t *nbe_i2c);
void nbe_i2c_commit(nbe_i2c_t *nbe_i2c);

#ifdef __cplusplus
}
#endif