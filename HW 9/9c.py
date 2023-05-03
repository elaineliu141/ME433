import matplotlib.pyplot as plt
import numpy as np
import csv

t = [] # column 0
data1 = [] # column 1
data2 = [] # column 2

with open('sigA.csv') as f:
    # open the csv file
    reader = csv.reader(f)
    for row in reader:
        # read the rows 1 one by one
        t.append(float(row[0])) # leftmost column
        data1.append(float(row[1])) # second column
        #data2.append(float(row[2])) # third column

# IIR
IIR = []
A = 0.3
B = 0.7
IIR.append(0)

for i in range(len(t)-1):
    IIR.append(A*IIR[i] + B*data1[i-1])
print(len(IIR))
print(len(data1))

#dt = 1.0/10000.0 # 10kHz
#t = np.arange(0.0, 1.0, dt) # 10s
    # a constant plus 100Hz and 1000Hz
#s = 4.0 * np.sin(2 * np.pi * 100 * t) + 0.25 * np.sin(2 * np.pi * 1000 * t) + 25

Fs = 1 / (t[1]-t[0]) # sample rate
Ts = 1.0/Fs; # sampling interval
ts = np.arange(0,t[-1],Ts) # time vector

#filtered data
y = IIR # the data to make the fft from
n = len(y) # length of the signal
k = np.arange(n)
T = n/Fs
frq = k/T # two sides frequency range
frq = frq[range(int(n/2))] # one side frequency range
Y = np.fft.fft(y)/n # fft computing and normalization
Y = Y[range(int(n/2))]

y1 = data1 # the data to make the fft from
n1 = len(y1) # length of the signal
k1 = np.arange(n1)
T1 = n1/Fs
frq1 = k1/T1 # two sides frequency range
frq1 = frq1[range(int(n1/2))] # one side frequency range
Y1 = np.fft.fft(y1)/n1 # fft computing and normalization
Y1 = Y1[range(int(n1/2))]

fig, (ax1, ax2) = plt.subplots(2, 1)
ax1.plot(t,y,'r',t, data1,'black')
ax1.set_xlabel('Time')
ax1.set_ylabel('Amplitude')
ax2.loglog(frq,abs(Y),'r', frq1,abs(Y1), 'black')
ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|Y(freq)|')
plt.show()