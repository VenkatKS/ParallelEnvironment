import matplotlib.pyplot as plt
import matplotlib
import glob, numpy as np

def gen_plot(x, y, err, xlabel, label, title, subtitle, ylabel, filename):
    # Generate peformance curve using avg_test_rewards
    plt.suptitle(title, fontsize=14)
    plt.title(subtitle, fontsize=10)
    plt.xlabel(xlabel)
    if ylabel:
        plt.ylabel(ylabel)
    # plt.xticks(np.arange(0, 10000, 100))
    # plt.ylim([np.min(y), 1.1 * np.max(y)])
    # plt.ylim([-350, 325])
    if label:
        for y_, err_, l in zip(y, err, label):
            plt.errorbar(x, y_, yerr=[err_, err_], fmt='-x', label=l, capsize=5)
    else:
        plt.errorbar(x, y, yerr=err, fmt='-x', capsize=5)
    if label:
        plt.legend()
    plt.grid()
    plt.savefig(filename, bbox_inches='tight')
    plt.close()

def bar_plot(x, y, err, label, title, subtitle, ylabel, filename):
    # Generate peformance curve using avg_test_rewards
    plt.suptitle(title, fontsize=14)
    plt.title(subtitle, fontsize=10)
    plt.xlabel("Number of agents (in thousands)")
    barwidth = 0.25
    r = [[],[],[],[]]
    r[0] = np.arange(len(x))
    r[1] = [w + barwidth for w in r[0]]
    r[2] = [w + barwidth for w in r[1]]
    r[3] = [w + barwidth for w in r[2]]
    if ylabel:
        plt.ylabel(ylabel)
    # plt.xticks(np.arange(0, 10000, 100))
    # plt.ylim([np.min(y), 1.1 * np.max(y)])
    # plt.ylim([-350, 325])
    for rr, y_, err_, l in zip(r, y, err, label):
        plt.bar(rr, y_, width=barwidth, label=l)
        # plt.errorbar(x, y_, yerr=[err_, err_], fmt='-x', label=l, capsize=5)
    plt.xticks([w + barwidth for w in range(len(r))], x)
    plt.legend()
    plt.grid()
    plt.savefig(filename, bbox_inches='tight')
    plt.close()

fname='mpi_var.csv'
data = np.genfromtxt(fname, delimiter='\t')
gen_plot(data[:,0], data[:, 1], data[:, 2], "Number of nodes", None, "Variation of OpenMPI+OpenMP performance with nodes",
        "100k agents, 16 OMP threads per node", "Averaged step time (ms)", 'mpi_perf.png')

fname='omp_threads.csv'
data = np.genfromtxt(fname, delimiter='\t')
gen_plot(data[:,0], data[:, 1], data[:, 2], "Number of threads", None, "Variation of OpenMP performance with threads",
        "100k agents, 6-core i7-8750H", "Averaged step time (ms)", 'omp_var.png')

fname='var_num_agents.csv'
data = np.genfromtxt(fname, delimiter=',')
means, var = data[:, [0,2,4]], data[:, [1,3,5]]
bar_plot(["Sequential", "OpenMP", "OpenMPI+OMP"],
        means, var, ['1k Agents', '10k Agents', '100k Agents', '1M Agents'],
        "Variation of performance with number of agents",
         "24 OpenMP threads, 4 MPI Nodes, Averaged over 25 runs", "Averaged step time (ms)",
         'method.png')
gen_plot(['1', '10', '100', '1000'],
        means.T, var.T, "Number of agents (thousands)", ["Sequential", "OpenMP", "OpenMPI+OMP"],
        "Variation of performance with number of agents",
         "24 OpenMP threads, 4 MPI Nodes, Averaged over 25 runs", "Averaged step time (ms)",
         'var_agents.png')

#gen_plot(data[:,0], data[:, 2], data[:, 3], "A2C: Avg. cumulative reward vs. training episodes (N=%d)" % (n), "Averaged over 100 episodes every 100 training episodes with multi-step LR", "Average (100-episode) cumulative reward (k=100)", pname)
