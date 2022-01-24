import numpy as np

from data_structures.graph import Graph, Edge, DiGraph


def bellman_ford(g: Graph, source: str, target: str = None):
    """
    Applies Bellman-Ford algorithm to find shortest path.

    # TODO: Big TODO need to check negative cycles as the algorithm fails.
    # -> (undirected) Graph containing a negative weight has a negative cycle.
    # If it's a Digraph, then need to explicitly check whether the graph contains
    # a negative cycle or not.

    :param g: (Graph) Graph object.
    :param source: source vertex name.
    :param target: target vertex name.
    :return: list of vertices constructing the path from source to target.
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

    source_id = g.get_vertex_id(source)
    table = initialize(len(g), source_id)

    for vertex in g.vertices:
        for edge in g.get_edges(vertex.name):
            relax(edge, vertex.id, table)

    if target is None:
        return table

    target_id = g.get_vertex_id(target)
    prev = target_id
    path = []
    while prev != -1:
        path.insert(0, g.get_vertex_name(prev))
        prev = int(table[prev, 1])
    print(f"Shortest path from '{source}' to '{target}':", table[target_id, 0])
    return path


if __name__ == "__main__":
    fp = "C:\\Users\\devri\\lab\\projects\\ceng21\\315\\final_prep\\example_graph.csv"
    g = DiGraph.from_file(fp)
    table = bellman_ford(g, "A", "F")
    print(table)
