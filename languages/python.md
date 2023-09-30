
# Sort
```py
strs = ['a', 'bb', 'dddd', 'cc', 'cbc']
sorted(strs)
sorted(strs, key=str.lower, reverse=True)
sorted(strs, key=lambda x: x[1])    # key argument is a function that returns 1 value -- to be used as the key

# Sort tuples
from operator import itemgetter, attrgetter
grade = [('Freddy', 'Frank', 3), ('Anil', 'Frank', 100), ('Anil', 'Wang', 24)]
sorted(grade, key=itemgetter(1,0))      # sort by x[1], then x[0]
sorted(student_objects, key=attrgetter('grade', 'age'))
```

# Deque
```py
from collections import deque
q = deque(arr)
q.append(x)     # q.appendLeft(x)   may be for stack
q.popleft()    # q.pop() may be for stack
q.rotate(k)
q.reverse()
```

# Heap / Priority Queue
```py
heapq.heapify(arr)
heapq.heappush(arr, x)
top = heapq.heappop(arr)
```