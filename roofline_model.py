import matplotlib.pyplot as plt
import numpy as np

# Peak performance and bandwidth for the hardware
peak_flops = 200e9  # 200 GFLOPS
peak_bytes = 30e9   # 30 GB/s

# Sample performance data for 10 measurements
num_measurements = 10
np.random.seed(42)  # For reproducibility
data_points = {
    f'Measurement {i}': {
        'flops': np.random.uniform(1e-8, 1e9),
        'bytes': np.random.uniform(1e-7, 5e8),
    } for i in range(1, num_measurements + 1)
}

# Set the threshold for flattening the line
arithmetic_intensity_threshold = peak_flops / peak_bytes

# Plot the roofline
plt.figure(figsize=(10, 6))

# Plot roofline components
plt.plot([0, peak_bytes], [0, peak_flops], color='black', label='Roofline')

# Plot vertical line for arithmetic intensity
arithmetic_intensity = np.linspace(0, 2, 100)  # Adjust the range accordingly

# Set values of the line to be constant beyond the threshold
arithmetic_intensity_line = np.minimum(arithmetic_intensity, arithmetic_intensity_threshold)
arithmetic_intensity_line[arithmetic_intensity > arithmetic_intensity_threshold] = arithmetic_intensity_threshold

plt.plot(arithmetic_intensity_line * peak_bytes, arithmetic_intensity_line * peak_flops, '--', color='orange',label='Arithmetic Intensity')

# Add a flat line continuing from the clipped part
flat_line_values = np.ones_like(arithmetic_intensity) #* arithmetic_intensity_threshold
plt.plot(arithmetic_intensity * peak_bytes, flat_line_values * peak_flops, '--', label='Flat Line', color='red')
#############################3

plt.plot([peak_bytes,peak_flops], [peak_flops, peak_flops], color='green', linestyle='-', label='ligma')

# Plot data points
for measurement, data in data_points.items():
    flops = data['flops']
    bytes_accessed = data['bytes']
    plt.scatter(bytes_accessed, flops, label=measurement)

# Set axis labels
plt.xlabel('Bytes Accessed (B)')
plt.ylabel('FLOPs')
plt.xscale('log')
plt.yscale('log')

# Set the legend
plt.legend()

# Set title
plt.title('Roofline Model with Slope=0 Beyond Threshold and Continuing Flat Line')

# Show the plot
plt.show()
