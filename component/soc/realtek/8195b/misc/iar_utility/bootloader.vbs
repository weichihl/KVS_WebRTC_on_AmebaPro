Dim WshShell

Set WshShell = WScript.CreateObject("WScript.Shell")

WshShell.Run "cmd /c """""+WScript.Arguments.Item(1)+"\..\..\..\component\soc\realtek\8195b\misc\iar_utility\bootloader.bat"" """+WScript.Arguments.Item(0)+""" """+WScript.Arguments.Item(1)+""" """+WScript.Arguments.Item(2)+""" """+WScript.Arguments.Item(3)+""" """, 1