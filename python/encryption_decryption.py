import serial, time
'''
CRC function 
simulate STM32F4 CRC 32 bit register 
'''

##############################################################
# change here for the file name
##############################################################
# yellow
hexFile = open("blinkLed.hex", "r")
# red
# hexFile = open("blinkLed(app1).hex", "r")
##############################################################

end = "END\n" # end of hex file indication 

'''
read hex file 
fetch line by line 
calculate crc 
send data+crc
Wait to receive confirmation after each byte
Wait for the confirmation check after each record
'''
lines = hexFile.readlines()
lineNumber = len(lines)
line = 0
while (line < lineNumber) :
   print(lines[line])
   for char in lines[line]:
      if(char != '\n'):
         print('o',char.encode())
         # char=+ b'0'
         print('e',str(b(char)^0x8c))
         print()
         
         
        
      
