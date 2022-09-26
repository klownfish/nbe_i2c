# non blocking i2c

## usage
imagine a sensor with address 42 and we want to read 3 bytes from register 17.
### most basic

```
static nbe_i2c_t nbe_i2c
nbe_i2c_init(&nbe_i2c, 0, GPIO_NUM_22, GPIO_NUM_23, 400000)

static uint8_t tx_buf[512] 
static uint8_t rx_buf[512] //both must be valid during the whole process!

nbe_i2c_reset() //always reset before a new transaction

// start by preparing our buffers, they will be written later
tx_buf[0] = i2c_first_byte_write(42) // all i2c transactions start with the device address + 1 read/write bit. first_byte_xxx manages this
tx_buf[1] = 17 // write the register we want to read
tx_buf[2] = i2c_first_byte_read(42) // prepare address for the read transaction

//set the buffers
nbe_i2c_set_tx_buf(&nbe_i2c, tx_buf);
nbe_i2c_set_rx_buf(&nbe_i2c, rx_buf);

//start the command chain
nbe_i2c_start(&nbe_i2c); //signal the start of a new transaction
nbe_i2c_write(&nbe_i2c, 2); //queue a write for the device address and the register

nbe_i2c_start(&nbe_i2c); // after the write is done queue another transaction to read
nbe_i2c_write(&nbe_i2c, 1); // write the device address again
nbe_i2c_read_ack(&nbe_i2c, 2);
nbe_i2c_read_nak(&nbe_i2c, 1); // according to the i2c standard you should NAK to stop reading

// that's the whole process, now commit it
nbe_i2c_commit(&nbe_i2c);

//and now it will process quietly in the background through interrupts
while (nbe_i2c_is_busy(&nbe_i2c)) {
    yield(); // or whatever you want to do
}
// the result will be stored in the rx buf
```

### more advanced
the above mentioned are the "atomic" functions. The others are just wrappers to make it slightly nicer to use