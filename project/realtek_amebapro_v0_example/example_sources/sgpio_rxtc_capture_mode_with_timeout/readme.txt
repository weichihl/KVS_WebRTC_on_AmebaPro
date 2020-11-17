Example Description

This example describes how to use the capture timeout function.
Avoid that don't acquire the capture trigger when already get the start trigger.

Required Components:
 - Connect SGPIO TX and SGPIO RX  
 
Output Waveform1:  
       -----------------         
       |<----550us---->|                     
--------               -------             
        <----500us-->          
                    ^
                    Timeout Interrupt   
   
Output Waveform2:  
       ---------         
       |<450us>|                     
--------       -------             
               ^
               Capture Interrupt   
   
This example shows:
 1. Initilize SGPIO. 
 2. Initilize the rxtc capture mode.
 3. Initilize the capture timeout function.
 4. Set SGPIO output low.
 5. Initilize the multc timer mode.
 6. Set the match time to generate the external output " Waveform1 ".
 7. Start the multc timer.
 8. Happen the capture timeout. Print " Capture Timeout".
 9. Set the match time to generate the external output " Waveform2 ".
10. Start the multc timer.
11. Don't happen timeout, and check the capture value 450us. 