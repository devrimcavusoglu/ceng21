from dataclasses import dataclass
from typing import Union, Dict

import numpy as np
import pandas as pd

from final_prep.data_structures.graph import DiGraph, Vertex


@dataclass
class FlowNode(Vertex):
    node_type: str = "intermediate"
    incoming_flow: float = 0
    outgoing_flow: float = 0


class FlowNetwork(DiGraph):
    def __init__(self, init_source_and_sink: bool = True):
        super().__init__()
        self._vertices: Dict[int, FlowNode] = {}
        self._vertex_name_to_id: Dict[str, int] = {}
        self._flow = 0
        self._vid = 2
        if init_source_and_sink:
            self.add_vertex("_source", node_type="source")
            self.add_vertex("_sink", node_type="sink")

    def __iter__(self) -> FlowNode:
        for vertex in self._vertices.values():
            yield vertex

    @property
    def flow(self):
        if not self.is_valid():
            raise ValueError("Flow Network is not valid.")
        source_node = self.get_vertex(self.source_id)
        return source_node.outgoing_flow - source_node.incoming_flow

    @property
    def source_id(self):
        # Reserved for source node
        return 0

    @property
    def sink_id(self):
        # Reserved for sink node
        return 1

    @classmethod
    def from_array(cls, array: np.ndarray, source: str = None, sink: str = None) -> "FlowNetwork":
        if not source and not sink:
            raise ValueError("'source' and 'sink' cannot be None using 'from_file()'.")
        G = cls(init_source_and_sink=False)
        vertices = np.unique(array[:, [0, 1]]).tolist()
        for vertex in vertices:
            if vertex == source:
                G.add_vertex(vertex, "source")
            elif vertex == sink:
                G.add_vertex(vertex, "sink")
            else:
                G.add_vertex(vertex)

        for edge in array:
            v1, v2, w = edge
            G.add_edge(v1, v2, w)

        return G

    @classmethod
    def from_file(cls, path: str, source: str = None, sink: str = None) -> "FlowNetwork":
        if not source and not sink:
            raise ValueError("'source' and 'sink' cannot be None using 'from_file()'.")
        df = pd.read_csv(path, sep=" ", header=None)
        return cls.from_array(array=df.to_numpy(), source=source, sink=sink)

    def _create_vertex(self, name: str, node_type: str = "intermediate") -> FlowNode:
        if not name:
            raise ValueError("'name' cannot be empty or None.")
        if node_type == "source":
            _id = self.source_id
        elif node_type == "sink":
            _id = self.sink_id
        else:
            _id = self._next_vid()
        return FlowNode(name=name, id=_id, node_type=node_type)

    def is_valid(self):
        for node in self:
            if node.node_type not in ["source", "sink"]:
                if node.incoming_flow != node.outgoing_flow:
                    return False
        return True

    def get_vertex(self, id_or_name: Union[str, int]) -> FlowNode:
        if isinstance(id_or_name, str):
            id_or_name = self.get_vertex_id(id_or_name)
        return self._vertices[id_or_name]

    def add_vertex(self, name: str, node_type: str = "intermediate") -> None:
        if node_type not in ["intermediate", "source", "sink"]:
            raise ValueError(f"Unknown node type '{node_type}'. Expected "
                             f"one of [intermediate, source, sink]")
        v = self._create_vertex(name, node_type)
        self._vertices[v.id] = v
        self._vertex_name_to_id[name] = v.id
        self._adjacency_map[v.id] = []

    def add_edge(self, v1_name: str, v2_name: str, weight: float):
        if self.contains_edge(v2_name, v1_name):
            # TODO: This can be inherently handled by this method, by introducing
            #   an intermediate node.
            raise ValueError(f"Edge ('{v2_name}', '{v1_name}') exists, an "
                             f"anti-parallel edge cannot be added to flow.")
        v1 = self.get_vertex(v1_name)
        v2 = self.get_vertex(v2_name)
        e = self._create_edge(v1.id, v2.id, weight)
        self._edges[e.id] = e
        self._adjacency_map[v1.id].append(e.id)
        v1.outgoing_flow += weight
        v2.incoming_flow += weight


if __name__ == "__main__":
    fp = "C:\\Users\\devri\\lab\\projects\\ceng21\\315\\final_prep\\example_flow.csv"
    g = FlowNetwork.from_file(fp, source="A", sink="G")
    g.print()

    print("Valid:", g.is_valid())
    for node in g:
        print("name:", node.name, "incoming:", node.incoming_flow, "outgoing:", node.outgoing_flow)

    g.BFS("A")
    print("Flow:", g.flow)
