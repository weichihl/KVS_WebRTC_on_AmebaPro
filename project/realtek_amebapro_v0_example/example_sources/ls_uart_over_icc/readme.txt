Example Description

This example code demostrate how the example code on HS platform controls the UART of LS platform over the ICC communication.
Please connect the TX & RX of the UART to be tested on LS.


Required Components:
Connect to the UART TX pin and RX pin.


A7      <----->     A8 (UART 0)
          or
A0      <----->     A1 (UART 1)

This example run the steps:
1. The HS send an ICC command to the LS to initial a LS UART port.
2. The HS send a block of data by an ICC message to the LS.
3. The LS transmit the received data on the UART TX pin.
4. The LS UART TX data will be loop-back to the LS UART RX.
5. The LS use an ICC message to send the UART RX data to the HS.
6. The HS verify the received ICC message data and print the result.
