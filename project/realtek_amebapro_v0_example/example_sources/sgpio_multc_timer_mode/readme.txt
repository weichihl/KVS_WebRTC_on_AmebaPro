Example Description

This example describes how to use the multc timer mode.
 
Required Components:
 
This example shows:
 1. Initilize SGPIO. 
 2. Release SGPIO pins because only use the timer mode.
 3. Set the multc timer reset every 1 sec and generate the interrupt.
 4. Start the multc timer.  
 5. When occur ten interrupts, close the multc timer and reset the multc.