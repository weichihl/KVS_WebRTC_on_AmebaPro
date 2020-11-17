Example Description

This example describes how to use SPI read/write by mbed api.


The SPI Interface provides a "Serial Peripheral Interface" Master.

This interface can be used for communication with SPI slave devices,
such as FLASH memory, LCD screens and other modules or integrated circuits.

In this example, it use 2 sets of SPI. One is master, the other is slave.
By default it use SPI0 as slave, and use SPI3 as master.
So we connect them as below:
    Connect SPI0_MOSI (PG_2) to SPI3_MOSI (PH_2)
    Connect SPI0_MISO (PG_3) to SPI3_MISO (PH_3)
    Connect SPI0_SCLK (PG_1) to SPI3_SCLK (PH_1)
    Connect SPI0_CS   (PG_0) to SPI3_CS   (PH_0)


After boot up, the master will send data to slave and shows result on LOG_OUT.


