from sort import sort
import random

buff = [random.randint(0, 100) for i in range(20)]
print(buff)
print(sort.c_bubble_sort(buff))
