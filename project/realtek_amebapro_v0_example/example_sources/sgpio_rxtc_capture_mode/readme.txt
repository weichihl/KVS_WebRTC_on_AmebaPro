Example Description

This example describes how to capture the duration of the trigger.

Required Components:
 - Connect SGPIO TX and SGPIO RX  
 
Output Waveform:  
                   -----------------       
                   |<----600us---->|                            
--------------------               ------------------------
           ^	   ^               ^
MULTC:     0us     400us           1000us
   
This example shows:
 1. Initilize SGPIO. 
 2. Initilize the rxtc capture mode.
 3. Set SGPIO output low.
 4. Initilize the multc timer mode.
 5. Set the match time to generate the external output.
 6. Start the multc timer to output the waveform.
 7. Check the capture value 600us(600000ns). 