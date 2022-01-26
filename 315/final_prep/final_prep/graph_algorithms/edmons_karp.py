"""Maximum-Flow Problem"""

import queue
from typing import Dict

from final_prep.data_structures.flow import FlowNetwork, ResidualNetwork


def edmonds_karp(network: FlowNetwork) -> float:
    """
    Implementation of Edmonds-Karp algorithm to find the maximum
    flow in the graph.

    https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm
    TODO: Algorithm currently not working correctly, needs investigation.
    """
    def initialize_pred(network: FlowNetwork) -> Dict[int, int]:
        pred = {node.id: -1 for node in network if node.id != 1}
        # Since sink node id is reserved as 1, little trick to
        # put it at the end of the dict. In Python3.8(?) and later
        # builtin dict() is an ordered dict.
        pred[1] = -1
        return pred

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
            for edge in G_f.get_edges(current_node.name):
                if pred[edge.v2_id] == -1 and edge.v2_id != source_id and edge.weight > edge.flow:
                    pred[edge.v2_id] = edge.id
                    q.put(G_f.get_vertex(edge.v2_id))

        if pred[sink_id] != -1:
            df = float("inf")
            for edge_id in reversed(pred.values()):
                if edge_id == -1:
                    continue
                edge = G_f.get_edge(edge_id)
                df = min(df, edge.weight - edge.flow)

            for edge_id in reversed(pred.values()):
                if edge_id == -1:
                    continue
                edge = G_f.get_edge(edge_id)
                reverse_edge = G_f.get_edge(edge.reverse_edge_id)
                edge.flow += df
                reverse_edge.flow += df
            flow += df
        else:
            stop = True

    return flow


if __name__ == "__main__":
    fp = "C:\\Users\\devri\\lab\\projects\\ceng21\\315\\final_prep\\example_flow.csv"
    fn = FlowNetwork.from_file(fp, source="S", sink="T")
    res = edmonds_karp(fn)
    print("Desired Max Flow: 14")
    print("Actual Max flow:", res)
