import numpy as np

from data_structures.graph import Graph, Edge, DiGraph


def floyd_warshall(g: Graph, source: str, target: str = None):
    """
    Applies Floyd-Warshall algorithm to find shortest path.
    """


if __name__ == "__main__":
    fp = "C:\\Users\\devri\\lab\\projects\\ceng21\\315\\final_prep\\example_graph.csv"
    g = Graph.from_file(fp)
    path = floyd_warshall(g, "A", "F")
    print(path)
