import serial, time
# yellow
# hex = open("blinkLed.hex", "r")
# red
hex = open("blinkLed(app1).hex", "r")
end = "END\n"
ttl = serial.Serial('COM4', 9600, 8, 'N', 1)
lines = hex.readlines()
lineNumber = len(lines)
line = 0
while (line < lineNumber) :
   for char in lines[line]:
      ttl.write(char.encode())
      ttl.read_until('k',1)
      print(char)
   while(ttl.in_waiting < 1):
      pass
   response = ttl.read(ttl.in_waiting)
   if(response == b'k'):
      line +=1
   else:
      pass 
time.sleep(.5)
for char in end:
   ttl.write(char.encode())
   ttl.read_until('k',1)
   print(char)
 