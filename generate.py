import sys
import random

# 乘法快速幂
def pow(a,b):
    res=1
    while b:
        if (b&1):
            res*=a
        a*=a
        b>>=1
    return res
        
def generate_file(file_size,filename):
    count =int(file_size)*pow(1024,2)
    f = open(filename, 'w')
    while count>0:
        x = random.randint(1, 999)
        s = 'https://github.com/gzgywh/project/{}\n'.format(x)
        print(s)
        count -= len(s)
        f.write(s)

if __name__=='__main__':
    generate_file(sys.argv[1],sys.argv[2])
