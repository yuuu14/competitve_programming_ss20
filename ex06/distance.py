import matplotlib.pyplot as plt

c1 = plt.Circle((0, 0), 2, color='r')

fig, ax = plt.subplots()
ax.add_artist(c1)

plt.show()