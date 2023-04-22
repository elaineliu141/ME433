# plot imu data to python 

import serial
ser = serial.Serial('/dev/tty.usbserial-0232B059',230400)
print('Opening port: ')
print(ser.name)

read_samples = 10 # anything bigger than 1 to start out
ax = []
ay = []
az = []
gx = []
gy = []
gz = []
temp = []
pitch = []
roll = [] 
print('Collecting data...')
ser.write(b'\n')
while read_samples > 1:
    data_read = ser.read_until(b'\n',200) # get the data as bytes
    data_text = str(data_read,'utf-8') # turn the bytes to a string
    data = [float(i) for i in data_text.split()] # turn the string into a list of floats

    if(len(data)==10):
        read_samples = int(data[0]) # keep reading until this becomes 1
        ax.append(data[1])
        ay.append(data[2])
        az.append(data[3])
        gx.append(data[4])
        gy.append(data[5])
        gz.append(data[6])
        temp.append(data[7])
        pitch.append(data[8])
        roll.append(data[9])
print('Data collected complete')
# plot it
import matplotlib.pyplot as plt 
t = range(len(ax)) # time array
plt.plot(t,ax,'r*-',t,ay,'b*-',t,az,'k*-')
plt.ylabel('Accelerations for x,y,z')
plt.xlabel('Sample')
plt.legend(['X','Y','Z'])
plt.show()

t = range(len(gx)) # time array
plt.plot(t,gx,'r*-',t,gy,'b*-',t,gz,'k*-')
plt.ylabel('Omega value')
plt.xlabel('Sample')
plt.legend(['Gx','Gy','Gz'])
plt.show()

t = range(len(temp)) # time array
plt.plot(t,temp,'r*-')
plt.ylabel('Temperature')
plt.xlabel('Sample')
plt.show()

t = range(len(temp)) # time array
plt.plot(t,pitch,'r*-',t,roll,'b*-')
plt.ylabel('Pitch and Roll (Radians)')
plt.xlabel('Sample')
plt.legend(['Pitch','Roll'])
plt.show()

# be sure to close the port
ser.close()
