"""Maximum-Flow Problem"""

import queue
from typing import Dict

from final_prep.data_structures.flow import FlowNetwork, ResidualNetwork


def edmonds_karp(network: FlowNetwork) -> float:
    """
    Implementation of Edmonds-Karp algorithm to find the maximum
    flow in the graph. You can see the algorithm and the pseudo-code
    in detail via the following URL.
    https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm

    Worst-case: O(VE^2)

    NOTE:
        This implementation slightly differs from the pseudo-code from
        the given wiki page above. It manipulates flow for edges, we here
        instead manipulate the capacities (weight) of edges. Moreover,
        construction of the path in the pseudo-code is missing. There is
        a comment block in the implementation noting this issue.

    Args:
        network: (FlowNetwork) Flow network.

    Returns:
        Maximum flow in the given network.
    """
    def initialize_pred(network: FlowNetwork) -> Dict[int, int]:
        return {node.id: -1 for node in network}

    flow = 0.0
    source_id = network.source_id
    sink_id = network.sink_id
    G_f = ResidualNetwork.from_flow_network(network)
    stop = False
    while not stop:
        q = queue.Queue()
        q.put(G_f.get_vertex(source_id))
        pred = initialize_pred(network)
        while not q.empty():
            current_node = q.get()
            if current_node.id == sink_id:
                break
            for edge in G_f.get_edges(current_node.name):
                if pred[edge.v2_id] == -1 and edge.v2_id != source_id and edge.weight > 0:
                        pred[edge.v2_id] = edge.id
                        q.put(G_f.get_vertex(edge.v2_id))

        if pred[sink_id] != -1:
            df = float("inf")

            # NOTE: The following lines constructs the path using
            # the array filled in BFS (`pred`). The pseudo-code in the
            # provided url in the docstring missing this part.
            current = sink_id
            path = {}
            while current != source_id:
                path[current] = pred[current]
                edge = G_f.get_edge(pred[current])
                df = min(df, edge.weight - edge.flow)
                current = edge.v1_id

            for node_id, edge_id in path.items():
                edge = G_f.get_edge(edge_id)
                reverse_edge = G_f.get_edge(edge.reverse_edge_id)
                edge.weight -= df
                reverse_edge.weight += df

            flow += df
        else:
            stop = True

    return flow


if __name__ == "__main__":
    fp = "C:\\Users\\devri\\lab\\projects\\ceng21\\315\\final_prep\\example_flow.csv"
    fn = FlowNetwork.from_file(fp, source="S", sink="T")
    res = edmonds_karp(fn)
    print("Actual Max flow:", res)
    print("Desired Max Flow: 14")
