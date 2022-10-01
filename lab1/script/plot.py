import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt

des_type = "pdf"
des_file = "out" + "." + des_type

mpl.rcParams.update({"font.size": 15})
fig_size = (4.8, 4.0)
x_axis_name = "Epoch"
y_axis_name = "$\log_{10} || \pi - \pi' ||_2$"


def main():
    # Run pyplot.
    fig, ax = plt.subplots(1, 1, figsize=fig_size)
    ax.set_xlabel(x_axis_name)
    ax.set_ylabel(y_axis_name)

    # Plot.
    n = 100
    norms = []
    print('Input:')
    for i in range(n):
        s = input()
        norms.append(float(s.split()[-1]))
    x = np.arange(n)
    y = np.log10(np.array(norms, dtype=np.float64))
    ax.plot(x, y)

    # Set the ranges.

    # Pyplot standby.
    plt.tight_layout()
    fig.savefig(des_file)
    plt.show()
    plt.close()


if __name__ == "__main__":
    main()

