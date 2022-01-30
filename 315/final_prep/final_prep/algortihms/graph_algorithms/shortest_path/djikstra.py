"""Implementation of Djikstra's shortest path algorithm"""
import queue
from dataclasses import dataclass
from typing import List

import numpy as np

from final_prep.data_structures.graph import Vertex, Graph, Edge


@dataclass
class DistanceVertexPair(object):
    distance: int = None
    vertex: Vertex = None

    def __lt__(self, other: "DistanceVertexPair"):
        """For min-heap to use"""
        return self.distance < other.distance


def djikstra(g: Graph, source: str, target: str = None):
    """
    Applies Djisktra's algorithm to find shortest path.

    Worst-case:
        - O((V+E)logV) using min-heap (*)
        - O(VlogV + E) using Fibonacci heap
        - O(V^2) using array
        (*) current implementation

    Args:
        g: (Graph) Graph object.
        source: (str) source vertex name.
        target: (str) target vertex name.

    Returns:
        List of vertices constructing the path from source to target.
    """
    def initialize(n: int, s: int) -> np.ndarray:
        table = np.zeros((n, 2))
        table[:, 0] = np.inf
        table[:, 1] = -1
        table[s, 0] = 0
        return table

    def relax(edge: Edge, current_vertex: int, table: np.ndarray):
        u = current_vertex
        v = edge.complementary(current_vertex)
        d_u = table[u, 0]
        d_v = table[v, 0]
        if d_v > d_u + edge.weight:
            table[v, 0] = d_u + edge.weight
            table[v, 1] = u
        return d_v

    def path_from_table(table: np.ndarray) -> List[str]:
        target_id = g.get_vertex_id(target)
        prev = target_id
        path = []
        while prev != -1:
            path.insert(0, g.get_vertex_name(prev))
            prev = int(table[prev, 1])
        return path

    g.unmark_all_vertices()
    source_vertex = g.get_vertex(source)
    table = initialize(len(g), source_vertex.id)

    heap = queue.PriorityQueue(maxsize=len(g))
    heap.put(DistanceVertexPair(distance=0, vertex=source_vertex))

    while not heap.empty():
        dvpair = heap.get()
        u = dvpair.vertex
        g.mark_vertex(u.name)
        for edge in g.get_edges(u.name):
            d_v = relax(edge, u.id, table)
            v = g.get_vertex(edge.complementary(u.id))
            if not v.marked:
                heap.put(DistanceVertexPair(distance=d_v, vertex=v))

    g.unmark_all_vertices()

    if target is None:
        return table, None

    path = path_from_table(table)
    distance = table[g.get_vertex_id(target), 0]
    return distance, path


if __name__ == "__main__":
    fp = "C:\\Users\\devri\\lab\\projects\\ceng21\\315\\final_prep\\example_graph.csv"
    g = Graph.from_file(fp)
    distance, path = djikstra(g, "A", "J")
    print("Distance:", distance, " | path:", path)
