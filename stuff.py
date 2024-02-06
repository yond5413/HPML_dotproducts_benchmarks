import matplotlib.pyplot as plt
import numpy as np

# Peak performance and bandwidth for the hardware
peak_flops = 200e9  # 200 GFLOPS
peak_bytes = 30e9   # 30 GB/s

# Sample performance data for 10 measurements
'''num_measurements = 10
np.random.seed(42)  # For reproducibility
data_points = {
    f'Measurement {i}': {
        'flops': np.random.uniform(1e-8, 1e9),
        'bytes': np.random.uniform(1e-7, 5e8),
    } for i in range(1, num_measurements + 1)
}'''
data_points = {
    'dp1 N =  1000000, measurements =  1000': {'FLOP/s': 1.308555e9, 'Bytes/s': 5.234219e9},
    'dp1 N = 300000000, measurements = 20': {'FLOP/s': 1.279944e9, 'Bytes/s': 1.454898e9},
    'dp2 N = 1000000, measurements = 1000': {'FLOP/s': 16.263874e9, 'Bytes/s': 4.065969e9},
    'dp2 N = 300000000, measurements = 20': {'FLOP/s': 2.859163e9, 'Bytes/s': 2.859163e9},
    'dp3 N = 1000000, measurements = 1000': {'FLOP/s': 5.901847e9, 'Bytes/s': 23.607389e9},
    'dp3 N = 300000000, measurements = 20': {'FLOP/s': 10.109340e9, 'Bytes/s': 11.491170e9},
    'dp4 N = 1000000, measurements = 1000': {'FLOP/s': 4.956514870714945e9, 'Bytes/s': 19.82605948285978e9},
    'dp4 N = 300000000 , measurements =20': {'FLOP/s': 0.09061828368733878e9, 'Bytes/s': 0.3624731347493551e9},
    'dp5 N = 1000000 , measurements =1000': {'FLOP/s': 6.20599528548939, 'Bytes/s': 24.82398114195756},
    'dp5 N = 300000000, measurements =  20': {'FLOP/s': 0.11296808679821894e9, 'Bytes/s': 0.4518723471928758e9},
}

# Set the threshold for flattening the line
arithmetic_intensity_threshold = peak_flops / peak_bytes

# Plot the roofline
plt.figure(figsize=(10, 6))

# Plot roofline components
plt.plot([0, peak_bytes], [0, peak_flops], color='black', label='Memmory Bandwidth limit')

# Plot vertical line for arithmetic intensity
arithmetic_intensity = np.linspace(0, 2, 100)  # Adjust the range accordingly

# Set values of the line to be constant beyond the threshold
arithmetic_intensity_line = np.minimum(arithmetic_intensity, arithmetic_intensity_threshold)
arithmetic_intensity_line[arithmetic_intensity > arithmetic_intensity_threshold] = arithmetic_intensity_threshold

#plt.plot(arithmetic_intensity_line * peak_bytes, arithmetic_intensity_line * peak_flops, '--', color='orange',label='Arithmetic Intensity')

# Add a flat line continuing from the clipped part
flat_line_values = np.ones_like(arithmetic_intensity) #* arithmetic_intensity_threshold
#plt.plot(arithmetic_intensity * peak_bytes, flat_line_values * peak_flops, '--', label='Memmory Bandwidth limit', color='red')
#############################3

plt.plot([peak_bytes,peak_flops], [peak_flops, peak_flops], color='blue', linestyle='-', label='Peak FLops')

'''
for the AI stuff it is 2 floating point operations and since a float in C 
is a 32 bit data type ie: 4 byte the computation is 2/(2*4) or 
AI = Instructions/(sizeof(float)*variables)
'''

# Plot data points
for measurement, data in data_points.items():
    flops = data['FLOP/s']
    bytes_accessed = data['Bytes/s']
    plt.scatter(bytes_accessed, flops, label=measurement)
    
for position, data in data_points.items():
    #print(data)
    plt.vlines(x=data['Bytes/s'], ymin=0, ymax=data['FLOP/s'], color='red', linestyle='--')
    #plt.vlines(x=bytes_accessed, ymin=0, ymax=flops, color='red', linestyle='--')

plt.vlines(x=peak_bytes, ymin=0, ymax=peak_flops, color='orange',linestyle='--',label="Optimal peak thoughput and beak bandwidth")
# Set axis labels
plt.xlabel('Arithmetic Intensity (AI) Bytes/S')
plt.ylabel('FLOPs')
plt.xscale('log')
plt.yscale('log')

# Set the legend
plt.legend(loc='upper left')#, bbox_to_anchor=(1, 0.5))

# Set title
plt.title('Roofline Model ')

# Show the plot
plt.show()
