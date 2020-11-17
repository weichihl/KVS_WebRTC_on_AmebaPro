Example Description

This example implement AT command called "PS" that include several power saving features.
To check the status, your should also check UART log from LS (low speed) CPU.

HS
	You can use command PS to test several power saving features

	PS=[deepsleep|standby|sleeppg|wowlan|ls_wake_reason|tcp_keep_alive|wowlan_pattern],[options]

	PS=deepsleep
			deepsleep for default 1 minute
	PS=deepsleep,stimer=10
			deepsleep for 10 seconds
	PS=deepsleep,gpio
			deepsleep and configure GPIOA_13 as wakeup source

	PS=standby
			standby for default 1 minute
	PS=standby,stimer=10
			standby for 10 seconds
	PS=standby,gpio=2
			standby and configure GPIOA_2 as wakeup source
	PS=standby,gpio_setting=0x1555562,gpio=3
			standby and configure GPIOA_3 as wakeup source, GPIOA_0-A_12 pull setting 0x1555562
	PS=standby,gpio=13
			standby and configure GPIOA_13 as wakeup source, GPIOA_13 default PullDown & IRQ_RISE
	PS=standby,gpio13_setting=0,gpio_setting=0x1555562,gpio=13
			standby and configure GPIOA_13 as wakeup source, GPIOA_0-A_12 pull setting 0x1555562, "gpio13_setting=0" GPIOA_13 default PullDown & IRQ_RISE, "gpio13_setting=1" GPIOA_13 default PullUp & IRQ_FALL

	PS=wowlan
			Init wlan and connect to AP with hardcode ssid & pw, and then enter wake on wlan mode
	PS=wowlan,your_ssid
			Init wlan and connect to AP with "your_ssid" in open mode, and then enter wake on wlan mode
	PS=wowlan,your_ssid,your_pw
			Init wlan and connect to AP with "your_ssid" and "your_pw" in WPA2 AES mode, and then enter wake on wlan mode

	PS=ls_wake_reason
			Get LS wake reason

	PS=tcp_keep_alive
			Enable TCP KEEP ALIVE with hardcode server IP & PORT. This setting only works in wake on wlan mode
	PS=tcp_keep_alive,192.168.1.100,5566
			Enable TCP KEEP ALIVE with server IP 192.168.1.100 and port 5566. This setting only works in wake on wlan mode

	PS=wowlan_pattern
			Enable user defined wake up pattern. This settting only works in wake on wlan mode

LS



