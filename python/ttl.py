import serial, time
# hex = open("FLASHER.hex", "r")
hex = open("blinkLed.hex", "r")
# hex = open("blinkLed(app1).hex", "r")
end = "END\n\n"
ttl = serial.Serial('COM4', 9600, 8, 'N', 1)
for line in hex :
   for char in line:
      ttl.write(char.encode())
      ttl.read_until('k',1)
      print(char)
   ttl.read_until('k',1)
time.sleep(.5)
for char in end:
   ttl.write(char.encode())
   ttl.read_until('k',1)
   print(char)
 