from typing import List

import numpy as np

from final_prep.data_structures.graph import Graph, Edge


def bellman_ford(g: Graph, source: str, target: str = None):
    """
    Applies Bellman-Ford algorithm to find shortest path.

    # TODO: Big TODO need to check negative cycles as the algorithm fails.
    # -> (undirected) Graph containing a negative weight has a negative cycle.
    # If it's a Digraph, then need to explicitly check whether the graph contains
    # a negative cycle or not.

    Worst-case: O(VE)

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

    def path_from_table(table: np.ndarray) -> List[str]:
        target_id = g.get_vertex_id(target)
        prev = target_id
        path = []
        while prev != -1:
            path.insert(0, g.get_vertex_name(prev))
            prev = int(table[prev, 1])
        return path

    source_id = g.get_vertex_id(source)
    table = initialize(len(g), source_id)

    for vertex in g:
        for edge in g.get_edges(vertex.name):
            relax(edge, vertex.id, table)

    if target is None:
        return table, None

    path = path_from_table(table)
    distance = table[g.get_vertex_id(target), 0]
    return distance, path


if __name__ == "__main__":
    fp = "C:\\Users\\devri\\lab\\projects\\ceng21\\315\\final_prep\\example_graph.csv"
    g = Graph.from_file(fp)
    distance, path = bellman_ford(g, "A", "J")
    print("Distance:", distance, " | path:", path)
