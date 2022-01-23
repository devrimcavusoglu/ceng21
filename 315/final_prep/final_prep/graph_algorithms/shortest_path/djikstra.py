import queue
from dataclasses import dataclass

import numpy as np

from data_structures.graph import Graph, Edge, DiGraph, Vertex


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

    :param g: (Graph) Graph object.
    :param source: source vertex name.
    :param target: target vertex name.
    :return: list of vertices constructing the path from source to target.
    """
    def _init(n: int, s: int) -> np.ndarray:
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

    source = g.get_vertex(source)
    table = _init(len(g), source.id)

    heap = queue.PriorityQueue(maxsize=len(g))
    heap.put(DistanceVertexPair(distance=0, vertex=source))

    while not heap.empty():
        dvpair = heap.get()
        u = dvpair.vertex
        g.mark_vertex(u.name)
        for edge in g.get_edges(u.name):
            d_v = relax(edge, u.id, table)
            v = g.get_vertex(edge.complementary(u.id))
            if not v.marked:
                heap.put(DistanceVertexPair(distance=d_v, vertex=v))

    if target is None:
        return table

    target_id = g.get_vertex_id(target)
    prev = target_id
    path = []
    while prev != -1:
        path.insert(0, g.get_vertex_name(prev))
        prev = int(table[prev, 1])
    return path


if __name__ == "__main__":
    fp = "C:\\Users\\devri\\lab\\projects\\ceng21\\315\\final_prep\\example_graph.csv"
    g = DiGraph.from_file(fp)
    table = djikstra(g, "A", "F")
    print(table)
