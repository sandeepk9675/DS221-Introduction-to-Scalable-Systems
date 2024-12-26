import matplotlib.pyplot as plt
import numpy as np


# Define a np array having values [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000]
number_of_newhashtags = np.array([
    10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 
    1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000
])

#define an array with name clustering time having values given below. clustring time is given in milliseconds
avg_batch_process_time = np.array([
    57276, 55824, 56573, 56164, 56681, 56099, 56126, 56944, 55673, 55594, 
    56560, 59522, 60372, 59799, 61849, 62105, 63129, 64923, 65023, 74967, 
    84671, 92687, 98643, 106552, 113079, 132204, 125676, 131108
])

# define an array with name peak memory usage having values given below. peak memory usage is given in KB
peak_memory_usage = np.array([
    4180, 4064, 4416, 4416, 4320, 4348, 4392, 4336, 4416, 4388, 4524, 4612, 4572, 4792, 4900, 5060, 5276, 5384, 
    5436, 6332, 7108, 7588, 8264, 8944, 9424, 9688, 10228, 10804
])
#define any array with name writing_time having values given below. writing time is given in milliseconds
writing_time = np.array([
    4973, 6795, 8944, 12312, 15949, 15365, 20735, 22151, 22817, 26293, 
    51624, 74298, 99591, 121798, 153443, 175057, 208224, 220400, 252073, 
    516041, 808936, 1142206, 1308037, 1567327, 1878948, 2286540, 2452800, 
    2583597
])

#define an array with name compute_time having values given below. compute time is given in milliseconds
compute_time = np.array([
    246052, 355148, 476966, 586645, 705024, 816120, 931801, 1059768, 1148457, 1265067,
    2443868, 3792259, 5081638, 6260534, 7737552, 9059160, 10497241, 12149358, 13502846,
    31049641, 52586813, 76761860, 102676612, 132793226, 164448558, 219062626, 235574095,
    273374708
])

# define an array with name function_time having values given below. function time is given in milliseconds
function_time = np.array([
    251025, 361943, 485910, 598957, 720973, 831485, 952536, 1081919, 1171274, 1291360,
    2495492, 3866557, 5181229, 6382332, 7890995, 9234217, 10705465, 12369758, 13754919,
    31565682, 53395749, 77904066, 103984649, 134360553, 166327506, 221349166, 238026895,
    275958305
])

"""fig, ax = plt.subplots(1, 2, figsize=(20, 10))

# Plot for data structure populating time
ax[0].plot(number_of_newhashtags, avg_batch_process_time, marker='o')
ax[0].set_title('Average Batch Process time vs Number of newHashtags')
ax[0].set_xlabel('Number of newHashtags')
ax[0].set_ylabel('Average Batch Process time(microseconds)')

# Plot for peak memory usage
ax[1].plot(number_of_newhashtags, peak_memory_usage, marker='o')
ax[1].set_title('Peak Memory Usage vs newHashtags')
ax[1].set_xlabel('Number of newHashtags')
ax[1].set_ylabel('Peak Memory Usage (KB)')

plt.show()"""

fig, ax = plt.subplots(1, 2, figsize=(20, 10))
# Plot for writing time
ax[0].plot(number_of_newhashtags, writing_time, marker='o')
ax[0].set_title('Writing Time vs Number of newHashtags')
ax[0].set_xlabel('Number of newHashtags')
ax[0].set_ylabel('Writing Time (microseconds)')


# Plot for compute and function time
ax[1].plot(number_of_newhashtags, compute_time, marker='o', label='Compute time')  # Label for compute_time curve
ax[1].plot(number_of_newhashtags, function_time, marker='o', label='Function time')  # Label for function_time curve
ax[1].set_title('Compute Time and Function Time vs Number of newHashtags')
ax[1].set_xlabel('Number of newHashtags')
ax[1].set_ylabel('Time (microseconds)')
ax[1].legend()  # Add a legend to differentiate between the two curves

plt.show()


