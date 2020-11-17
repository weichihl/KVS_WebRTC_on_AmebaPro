Example Description

This example describes how to use the counter mode and filter counts by timeout. 
Make multc count external triggers, and use rxtc to become the timer. 
(Set " NULL " to timeout_cb in order to avoid waking up in the sleep mode.)

Required Components:
 - Connect SGPIO TX and SGPIO RX 

Output Waveform:
 
   -----   -----                           -----   -------------------------------
   |   |   |   |                           |   |   |
 ---   -----   -----------------------------   -----
               ^                           <-------------200us---------------->
               |                                                              |
               Match and interrupt                                            Timeout, MULTC reset                               
 
This example shows:
 1. Initilize SGPIO. 
 2. Set the counter mode and the filter function. When multc is 4, happen the interrupt. 
    If multc does not count 4 in two hundred microseconds, multc will be reset.  
 3. Give 4 external triggers. Happen the match interrupt and print " multc match".  
 4. Give 3 external triggers and wait timeout. 
    Happen the timeout interrupt, and print " The multc is reset, and this value is 0.".   
  