consistent-hash-playground
==========================
### Notes
- Severs (including duplicates) mapped to random location of the hash-ring (eg `location = hash(server)`)
- Requests also mapped to arbitary part of the ring (eg `location = hash(request)`)
- Therefore, these requests will be served by nearest server (clockwise)
- Since hash-ring is circular (using math "modulo operation") obviously, any dead server will not stop serving incoming requests, since these requests always have nearest server
- The problem of this algorithm is: the distribution of servers may not be balanced - there may be a lot of servers mapped to part of the ring, and not many to the rest of the ring. Therefore, some servers may have much more workload than other servers
- Therefore, there are other algorithms or this algorithm implemented differently

### TODOs
- [ ] implement return `nullptr` in `get` method
- [ ] implement hashing with `number_of_replicas`
- [ ] fix server collision

### Notes
- [Chord (peer-to-peer) - Wikipedia](https://en.wikipedia.org/wiki/Chord_(peer-to-peer))
- C++17 is required

### Reference
- [What is Consistent Hashing and Where is it used? - YouTube](https://www.youtube.com/watch?v=zaRkONvyGr8)
    -   > Andrei Marculescu
        > 
        > 3 anni fa (modificato)
        > the best solution is not to use K hash functions, but to generate K replica ids for each server id. Designing K hash functions while maintaining random uniformity and consistency is hard. Generating K replica ids is easy: xxx gives K replicas xxx + '1', xxx + '2', ..., xxx + 'K'. Then you take these replicas and generate K points on the ring with the same hash function
        > 
        > and this is what is actually used in practice. Chord algorithm is just an example of this technique to add K replicas for each server id
- [A Brief Introduction to Consistent Hashing - YouTube](https://www.youtube.com/watch?v=tHEyzVbl4bg)
- [groupcache/consistenthash at master · golang/groupcache](https://github.com/golang/groupcache/tree/master/consistenthash)
- [一致性hash解决节点弹缩问题_一致性哈希做弹性伸缩的系统-CSDN博客](https://blog.csdn.net/gyunling/article/details/100121110)




<!-- Security scan triggered at 2026-09-15 09:37:31 -->