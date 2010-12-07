

cd C:\WinDDK\7600.16385.1\bin\selfsign
inf2cat /driver:C:\Users\Reed\Programming\wii_mouse\driver\deploy\driver /os:7_x64

cd C:\WinDDK\7600.16385.1\bin\amd64
SignTool sign /s RiedlerCoStore /n "RiedlerCo - for testing only" /t http://timestamp.verisign.com/scripts/timestamp.dll C:\Users\Reed\Programming\wii_mouse\driver\deploy\driver\catalog\wii_mouse.cat

cd C:\Users\Reed\Programming\wii_mouse\driver\driver_signing