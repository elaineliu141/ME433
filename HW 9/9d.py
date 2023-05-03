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
# FIR
filter = []
h = [
    -0.000000000000000001,
    0.000043541292267123,
    0.000176344651832234,
    0.000404797194788599,
    0.000739047329518378,
    0.001192286008710532,
    0.001779792045546624,
    0.002517790095454350,
    0.003422179716127461,
    0.004507200939721495,
    0.005784105682311753,
    0.007259904884080140,
    0.008936258482840001,
    0.010808569295114675,
    0.012865332887312906,
    0.015087783978668300,
    0.017449866362141138,
    0.019918538389622466,
    0.022454410439905852,
    0.025012695202007565,
    0.027544436792036039,
    0.029997971373837952,
    0.032320560699852154,
    0.034460131360228206,
    0.036367046935130445,
    0.037995837956404953,
    0.039306815716250110,
    0.040267500469159272,
    0.040853802259194855,
    0.041050903119868622,
    0.040853802259194855,
    0.040267500469159272,
    0.039306815716250110,
    0.037995837956404953,
    0.036367046935130445,
    0.034460131360228227,
    0.032320560699852174,
    0.029997971373837948,
    0.027544436792036043,
    0.025012695202007586,
    0.022454410439905859,
    0.019918538389622480,
    0.017449866362141138,
    0.015087783978668314,
    0.012865332887312923,
    0.010808569295114678,
    0.008936258482840014,
    0.007259904884080149,
    0.005784105682311751,
    0.004507200939721497,
    0.003422179716127458,
    0.002517790095454349,
    0.001779792045546622,
    0.001192286008710532,
    0.000739047329518379,
    0.000404797194788599,
    0.000176344651832233,
    0.000043541292267124,
    -0.000000000000000001,
]
filter.append(0)
filter[0:(len(h)-1)] = data1[0:len(h)]
average = 0
for i in range(len(t)-len(h)):
    for k in range(len(h)):
        sum1 = (data1[i:i+(len(h))])[k]*h[k]
        average = average + sum1
    filter.append(average)


#dt = 1.0/10000.0 # 10kHz
#t = np.arange(0.0, 1.0, dt) # 10s
    # a constant plus 100Hz and 1000Hz
#s = 4.0 * np.sin(2 * np.pi * 100 * t) + 0.25 * np.sin(2 * np.pi * 1000 * t) + 25

Fs = 1 / (t[1]-t[0]) # sample rate
Ts = 1.0/Fs; # sampling interval
ts = np.arange(0,t[-1],Ts) # time vector

#filtered data
y = filter # the data to make the fft from
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