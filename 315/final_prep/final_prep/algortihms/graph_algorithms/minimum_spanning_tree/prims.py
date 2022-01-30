"""Implementation of Prim's MST Algortihm"""
import queue
from dataclasses import dataclass

import numpy as np

from final_prep.data_structures.graph import Graph, Vertex


@dataclass
class DistanceVertexPair(object):
    distance: int = None
    vertex: Vertex = None

    def __lt__(self, other: "DistanceVertexPair"):
        """For min-heap to use"""
        return self.distance < other.distance


def prims(g: Graph, s: int = None) -> Graph:
    """
    Implementation of Prim's MST algorithm using a min-heap.

    Worst-case:
        - O((V+E)logV) using min-heap (*)
        - O(VlogV + E) using Fibonacci heap
        - O(V^2) using array
        (*) current implementation

    Args:
        g: (Graph) Input graph.
        s: (int) (optional) start node id.

    Returns:
        MST for g as graph.
    """
    def initialize(n: int, s: int) -> np.ndarray:
        table = np.zeros((n, 2))
        table[:, 0] = np.inf
        table[:, 1] = -1
        table[s, 0] = 0
        return table

    def grow(edge, current_vertex: int, table):
        u = current_vertex
        v = edge.complementary(u)
        d_v = table[v, 0]
        if d_v > edge.weight:
            table[v, 0] = edge.weight
            table[v, 1] = u
            should_mark = True
        else:
            should_mark = False
        return d_v, should_mark

    def mst_from_table(table: np.ndarray) -> Graph:
        mst = Graph()
        for vertex in g:
            mst.add_vertex(vertex.name)
        for i, (d, n) in enumerate(table):
            if n == -1:
                continue
            u = mst[i]
            v = mst[n]
            mst.add_edge(u.name, v.name, d)
        return mst

    g.unmark_all_vertices()
    s = s or 0
    source_vertex = g[s]
    table = initialize(len(g), s)
    heap = queue.PriorityQueue(maxsize=len(g))
    heap.put(DistanceVertexPair(distance=0, vertex=source_vertex))

    while not heap.empty():
        dvpair = heap.get()
        u = dvpair.vertex
        g.mark_vertex(u.name)
        for edge in g.get_edges(u.name):
            if edge.marked:
                continue
            d_v, should_mark = grow(edge, u.id, table)
            v = g[edge.complementary(u.id)]
            if should_mark:
                g.mark_edge(u.name, v.name)
            if not v.marked:
                heap.put(DistanceVertexPair(distance=d_v, vertex=v))

    g.unmark_all_edges()
    g.unmark_all_vertices()

    mst = mst_from_table(table)
    return mst


if __name__ == "__main__":
    fp = "C:\\Users\\devri\\lab\\projects\\ceng21\\315\\final_prep\\example_graph.csv"
    g = Graph.from_file(fp)
    mst = prims(g)
    mst.print()
