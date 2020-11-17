Example Description

This example describes how to use GPIO read/write in a light weight way.

Requirement Components:
    a LED
    a push button


HS
Pin name PH_0 and PH_1 map to GPIOH_0 and GPIOH_1:
 - PH_1 as input with internal pull-high, connect a push button to this pin and ground.
 - PH_0 as output, connect a LED to this pin and ground.

LS
Pin name PA_2 and PA_3 map to GPIOA_2 and GPIOA_3:
 - PA_3 as input with internal pull-high, connect a push button to this pin and ground.
 - PA_2 as output, connect a LED to this pin and ground.

In this example, the LED is on when the push button is pressed.

