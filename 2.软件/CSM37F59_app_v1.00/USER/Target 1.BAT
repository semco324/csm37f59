SET PATH=D:\Keil_v5\ARM\ARMCC\Bin;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;D:\Program Files (x86)\Altium Designer Summer 09\System;C:\Program Files\MATLAB\R2016a\runtime\win64;C:\Program Files\MATLAB\R2016a\bin;C:\Program Files\MATLAB\R2016a\polyspace\bin;C:\Program Files (x86)\Microsoft SQL Server\100\Tools\Binn\;C:\Program Files\Microsoft SQL Server\100\Tools\Binn\;C:\Program Files\Microsoft SQL Server\100\DTS\Binn\;C:\Program Files\IVI Foundation\VISA\Win64\Bin\;C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Bin\;C:\Program Files\TortoiseSVN\bin;C:\Program Files (x86)\SSH Communications Security\SSH Secure Shell;C:\MinGW\bin;;C:\Program Files (x86)\MyDrivers\DriverGenius;C:\Program Files (x86)\MyDrivers\DriverGenius\ksoft
SET CPU_TYPE=CSA37F60
SET CPU_VENDOR=Chipsea
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x00B71B00
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\main.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\csa37fx60_it.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\system_csa37fx60.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\addr_map.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via "..\obj\startup_csa37fx60._ia"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\csa37fx60_afe.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\csa37fx60_crc32.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\csa37fx60_fmc.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\csa37fx60_gpio.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\csa37fx60_hdiv.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\csa37fx60_iic.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\csa37fx60_nvic.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\csa37fx60_pwr.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\csa37fx60_rcc.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\csa37fx60_system.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\csa37fx60_systick.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\csa37fx60_timer.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\csa37fx60_uart.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\csa37fx60_wdt.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\csa37fx60_wdt_smart.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\csa37fx60_wwdt.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\delay.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\uart.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\hw_iic.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\cs1258.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\timer.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\fmc.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via "..\OBJ\temp.lnp"
"D:\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" "..\OBJ\temp.axf" --i32combined --output "..\OBJ\temp.hex"
