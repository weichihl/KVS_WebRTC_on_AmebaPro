Example Description

This example describes how to implement high/low level trigger on 1 gpio pin.

HS
Pin name PH_0 and PH_1 map to GPIOH_0 and GPIOH_1:
Connect PH_0 and PH_1 
 - PH_1 as gpio input high/low level trigger.
 - PH_0 as gpio output.

LS
Pin name PA_2 and PA_3 map to GPIOA_2 and GPIOA_3:
Connect PA_2 and PA_3 
 - PA_3 as gpio input high/low level trigger.
 - PA_2 as gpio output.

In this example, PH_0 is signal source that change level to high and low periodically.

PH_1 setup to listen low level events in initial.
When PH_1 catch low level events, it disable the irq to avoid receiving duplicate events.
(NOTE: the level events will keep invoked if level keeps in same level)

Then PH_1 is configured to listen high level events and enable irq.
As PH_1 catches high level events, it changes back to listen low level events.

Thus PH_1 can handle both high/low level events.

In this example, you will see log that prints high/low level event periodically.
