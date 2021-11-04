from typing import *
from collections import namedtuple, defaultdict
import heapq

Edge = namedtuple('Edge', ['to', 'weight'])

class Solution:
    def networkDelayTime(self, times: List[List[int]], n: int, k: int) -> int:
      g = defaultdict(list)
      for u, v, w in times:
        g[u].append(Edge(v, w))

      distance = {k: 0}
      q = []
      heapq.heappush(q, (0, k))
      while len(q) > 0:
        w, at = heapq.heappop(q)
        if w > distance[at]: continue
        for to, extra in g[at]:
          nw = w + extra
          if not to in distance or nw < distance[to]:
            distance[to] = nw
            heapq.heappush(q, (nw, to))

      for i in range(1, n+1):
        if not i in distance: return -1

      return max(distance.values())





