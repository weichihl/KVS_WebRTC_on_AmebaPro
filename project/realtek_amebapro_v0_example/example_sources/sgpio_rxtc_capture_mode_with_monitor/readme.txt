Example Description

This example describes how to monitor the capture result.
When the capture value is bigger than monitor time, generate the interrupt.

Required Components:
 - Connect SGPIO TX and SGPIO RX  
 
Output Waveform:  
       ------------------     ------------------     ------------------     
       |<----1000us---->|     |<----1000us---->|     |<----1000us---->|                    
--------                -------                -------                -------    
                                                                      ^
                                                                      Interrupt   
   
This example shows:
 1. Initilize SGPIO. 
 2. Initilize the rxtc capture mode.
 3. Initilize the monitor condition. Monitor time 500us, and need to happen three times.
 4. Set SGPIO output low.
 5. Initilize the multc timer mode.
 6. Set the match time to generate the external output.
 7. Start the multc timer to output the waveform.
 8. Print " Occur the capture monitor event".