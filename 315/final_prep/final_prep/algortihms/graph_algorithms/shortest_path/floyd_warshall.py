from typing import Tuple, List

import numpy as np

from final_prep.data_structures.graph import Graph, DiGraph


def floyd_warshall(g: Graph, source: str = None, target: str = None):
    """
    Applies Floyd-Warshall algorithm to find shortest path.

    Note:
        This is function returns ultimate shortest paths for all pairs
        using any number of vertex while constructing shortest-paths.
        Extending this function s.t the shortest path containing less than
        or equal to k vertices (k as input) could be implemented in the
        future.

    Args:
        g: (Graph) Graph object.
        source: (str) source vertex name.
        target: (str) target vertex name.

    Returns:
        List of vertices constructing the path from source to target.
    """
    def initialize(g: Graph) -> Tuple[np.ndarray, np.ndarray]:
        n = len(g)
        table = np.empty((n, n))
        prevs = - np.ones((n, n))
        table[:, :] = np.inf
        np.fill_diagonal(table, 0)
        for _, edges in g.adjacency_map.items():
            for edge_id in edges:
                edge = g.get_edge(edge_id)
                table[edge.v1_id, edge.v2_id] = edge.weight
                prevs[edge.v1_id, edge.v2_id] = edge.v1_id
                if not isinstance(g, DiGraph):
                    table[edge.v2_id, edge.v1_id] = edge.weight
                    prevs[edge.v2_id, edge.v1_id] = edge.v2_id
        return table, prevs

    def relax(i, j, k, table, prevs):
        if table[i, j] > table[i, k] + table[k, j]:
            table[i, j] = table[i, k] + table[k, j]
            prevs[i, j] = k

    def path_from_table(prevs: np.ndarray) -> List[str]:
        target_id = g.get_vertex_id(target)
        prev = target_id
        path = []
        while prev != -1:
            path.insert(0, g.get_vertex_name(prev))
            prev = int(prevs[source_id, prev])
        return path

    source_id = g.get_vertex_id(source)

    table, prevs = initialize(g)
    for k in range(len(g)):
        for i in range(len(g)):
            for j in range(len(g)):
                relax(i, j, k, table, prevs)

    if not source and not target:
        return table
    elif source and not target:
        return table[source_id, :]

    path = path_from_table(prevs)
    distance = table[g.get_vertex_id(target), 0]
    return distance, path


if __name__ == "__main__":
    fp = "C:\\Users\\devri\\lab\\projects\\ceng21\\315\\final_prep\\example_graph.csv"
    g = Graph.from_file(fp)
    distance, path = floyd_warshall(g, "A", "J")
    print("Distance:", distance, " | path:", path)
