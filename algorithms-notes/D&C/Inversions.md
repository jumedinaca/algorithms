## Inversiones

```python
inv = 0
for i = 1 to n-1:
	for j = i + 1 to n:
		if A[i] > A[j]:
			inv+=1

return inv
```

```python
def merge_count_inversions(A,p,q,r):
	n_l = q-p+1
	n_r = r - (q + 1) - 1
	
	L = [0]*n_l
	R = [0]*n_r
	
	for i,_ in enumerate(L):
		L[i] = A[p+i]
	
	for i,_ in enumerate(R):
		R[i] = A[q+1+i]
	
	k = p
	i = 0
	j = 0
	inv = 0
	while i < n_l and j < n_r:
		if L[i] <= R[j]:
			A[k] = L[i]
			i+=1
		else:
			inv = inv + (n_l - i) 
			A[k] = R[j]
			j+=1
	
		k+=1
		
	while i <n_l:
		A[k]=L[i]
		k+=1
		i+=1
		
	while j < n_r:
		A[k] = R[j]
		k+=1
		j+=1
	
	return inv
	
def count_inversions(A,p,r):
	if p < r:
		q = (p+r)//2
		left  = count_inversions(A,p,q) 
		right = count_inversions(A,q+1,r)
		split = merge_count_inversions(A,p,q,r)
		return left + right + split
	return 0
```



## Karatsuba 

