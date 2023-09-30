<h1>Software Systems</h1>

- [Clustering Strategy](#clustering-strategy)
  - [Active-active](#active-active)
  - [Active-passive](#active-passive)

# Clustering Strategy
## Active-active
Both (or all n) nodes are serving. Actually is the normal horizontal scaling we learn in uni.
- Higher throughput, shorter response times, good user experience!
- Load balancing: can scale horizontally depending on loads like with k8s orchestration.
- High availability: provides failover
- Georgraphical redundancy
- Parallel processing: image processing jobs can be distributed among all active nodes.

## Active-passive
Not learnt in uni. Only one node is serving; another node stands by for failover
- Saves cost: while maintaining high availability
- Good for **database clustering**: maintains data consistency and integrity because it's easier to maintain data consistency when only the active node will have changes.
