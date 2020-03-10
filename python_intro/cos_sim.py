import sys
import numpy as np

def cos_sim(x, y):
    nume = np.dot(x, y)
    deno = np.sqrt(np.dot(x, x)) * np.sqrt(np.dot(y, y))
    return nume / deno

x_file = sys.argv[1]
y_file = sys.argv[2]

if __name__ == '__main__':
    x = np.loadtxt(x_file)
    y = np.loadtxt(y_file)
    ans = cos_sim(x, y)
    print(ans)