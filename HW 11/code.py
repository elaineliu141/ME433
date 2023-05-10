from ulab import numpy as np # to get access to ulab numpy functions
import time
# Declare an array with some made up data like
a = np.array([1,3,5,2,4,8,10])
# Test some stats functions, like
#print(np.min(a))
#print(np.max(a))
#print(np.median(a))
# Want to know all the functions available in numpy? In REPL type np. and press Tab.

elements = 1024
t = np.linspace(0, 100, elements)
a = np.zeros(elements)
for i in range(0, elements):
    sin_1 = np.sin(np.pi*t[i]) #diff frequencies
    sin_2 = 2*np.sin(2*np.pi*t[i])
    sin_3 = 3*np.sin(3*np.pi*t[i])
    a[i] = sin_1 + sin_2 + sin_3

fourier_transform = np.fft.fft(a)
amplitude = abs(fourier_transform[0])[0:int(elements/2)]
frequency = np.linspace(0, 100, int(elements/2))/(2*np.pi*np.pi)

print(amplitude)
print(frequency)
