
import sys
# a = [0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88]
a=b":035490006566004E"
# a=b"1122334455667788"


# crc = 0xffffffff
# for x in a:
#     crc ^= int(x) << 24
#     for k in range(8):
#         crc = (crc << 1) ^ 0x04c11db7 if crc & 0x80000000 else crc << 1
# crc &= 0xffffffff


count = 0
crc = 0xffffffff
a = (bytearray(a))
extra = (4-(len(a)%4))
if extra == 4:
    extra = 0
for x in range(0, extra):
    a.append(48)
print(len(a))
print(a)
for x in a:
    crc ^= (int(x) << 24) 
    for k in range(8):
        crc = (crc << 1) ^ 0x04c11db7 if crc & 0x80000000 else crc << 1
crc &= 0xffffffff


print(hex(crc))
print(crc)

