cd "C:\Program Files\SEGGER\JLink"
start JLinkGDBServerCL.exe -nogui -if swd -nolocalhostonly -port 50000 -swoport 50001 -telnetport 50002 -device MKV46F256xxx16
