Example Description

This example describes how to use the rxtc timer mode.
 
Required Components:
 
This example shows:
 1. Initilize SGPIO. 
 2. Release SGPIO pins because only use the timer mode.
 3. Set the rxtc match time. 
    Set to match time1 '1s', match time2 '2s', and match time3 '3s'.
    When match time3, make rxtc reset.  
 4. Start the rxtc timer.  
 5. print "1S" "2S" "3S" "1S" "2S" "3S" ...   