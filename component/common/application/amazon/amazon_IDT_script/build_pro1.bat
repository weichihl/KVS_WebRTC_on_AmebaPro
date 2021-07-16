set IARDir="C:\Program Files (x86)\IAR Systems\Embedded Workbench 8.1"
set IARProjectDir=D:\WFH_RTK\W_R\KVS_WebRTC_on_AmebaPro\project\realtek_amebapro_v0_example\EWARM-RELEASE
set PorjectName=application_is


%IARDir%\common\bin\IarBuild.exe %IARProjectDir%\%PorjectName%.ewp -clean Debug
%IARDir%\common\bin\IarBuild.exe %IARProjectDir%\%PorjectName%.ewp -make Debug

pause