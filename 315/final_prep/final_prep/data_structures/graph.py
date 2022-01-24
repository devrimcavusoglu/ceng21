"""Implementation of ADT Graph with adjacency list"""
import queue
from copy import deepcopy
from dataclasses import dataclass
from typing import Union, List, Callable, Dict

import numpy as np
import pandas as pd


@dataclass
class Vertex:
	name: str = None
	id: int = None
	marked: bool = False

	def __eq__(self, other):
		return self.id == other.id


@dataclass
class Edge:
	v1_id: int = None
	v2_id: int = None
	weight: float = None
	id: int = None

	def __eq__(self, other):
		return self.id == other.id

	def complementary(self, v_id: int) -> int:
		return self.v1_id if self.v1_id != v_id else self.v2_id


class Graph:
	def __init__(self):
		self._adjacency_map: Dict[int, List[int]] = {}
		self._vertices: Dict[int, Vertex] = {}
		self._vertex_name_to_id: Dict[str, int] = {}
		self._edges: Dict[int, Edge] = {}
		self.__vid: int = 0
		self.__eid: int = 0

	def __len__(self):
		return len(self._vertices)

	@property
	def adjacency_map(self):
		return self._adjacency_map

	@property
	def vertices(self):
		return self._vertices

	@property
	def _vid(self):
		self.__vid += 1
		return deepcopy(self.__vid - 1)

	@property
	def _eid(self):
		self.__eid += 1
		return deepcopy(self.__eid - 1)

	def _create_vertex(self, name: str) -> Vertex:
		if not name:
			raise ValueError("'name' cannot be empty or None.")
		return Vertex(name=name, id=self._vid)

	def _create_edge(self, v1_id: int, v2_id: int, weight: float):
		return Edge(v1_id=v1_id, v2_id=v2_id, weight=weight, id=self._eid)

	def get_vertex_id(self, name: str) -> int:
		return self._vertex_name_to_id.get(name)

	def get_vertex_name(self, id: int) -> str:
		for name, id_ in self._vertex_name_to_id.items():
			if id == id_:
				return name

	def get_vertex(self, id_or_name: Union[str, int]) -> Vertex:
		if isinstance(id_or_name, str):
			id_or_name = self.get_vertex_id(id_or_name)
		return self._vertices[id_or_name]

	def get_edge(self, v1_id_or_name: Union[str, int], v2_id_or_name: Union[str, int] = None) -> Edge:
		if v2_id_or_name is None:
			return self._edges[v1_id_or_name]
		v1_id = v1_id_or_name if isinstance(v1_id_or_name, int) else self.get_vertex_id(v1_id_or_name)
		v2_id = v2_id_or_name if isinstance(v2_id_or_name, int) else self.get_vertex_id(v2_id_or_name)

		for e_id, edge in self._edges.items():
			if {edge.v1_id, edge.v2_id} == {v1_id, v2_id}:
				return edge

	def add_vertex(self, name: str) -> None:
		v = self._create_vertex(name)
		self._vertices[v.id] = v
		self._vertex_name_to_id[name] = v.id
		self._adjacency_map[v.id] = []

	def add_edge(self, v1_name: str, v2_name: str, weight: float):
		v1_id = self.get_vertex_id(v1_name)
		v2_id = self.get_vertex_id(v2_name)
		e = self._create_edge(v1_id, v2_id, weight)
		self._edges[e.id] = e
		self._adjacency_map[v1_id].append(e.id)
		self._adjacency_map[v2_id].append(e.id)

	def delete_vertex(self, name: str):
		v_id = self._vertex_name_to_id.get(name)
		self.delete_edge(name)
		self._vertex_name_to_id.pop(name)
		self._vertices.pop(v_id)
		self._adjacency_map.pop(v_id)

	def delete_edge(self, v1_name: str, v2_name: str = None):
		v1_id = self.get_vertex_id(v1_name)
		if v2_name is not None:
			neighbors = [self.get_vertex_id(v2_name)]
		else:
			neighbors = [v.id for v in self.get_neighbors(v1_name)]

		for neighbor_id in neighbors:
			edge = self.get_edge(v1_id, neighbor_id)
			self._edges.pop(edge.id)
			self._adjacency_map[neighbor_id].remove(edge.id)

	@classmethod
	def from_array(cls, array: np.ndarray) -> "Graph":
		G = cls()
		vertices = np.unique(array[:, [0, 1]]).tolist()
		for vertex in vertices:
			G.add_vertex(vertex)

		for edge in array:
			v1, v2, w = edge
			G.add_edge(v1, v2, w)

		return G

	@classmethod
	def from_file(cls, path: str) -> "Graph":
		df = pd.read_csv(path, sep=" ", header=None)
		return cls.from_array(array=df.to_numpy())

	def print(self):
		print("Printing graph..")
		for vertex in self._vertices.values():
			print(f"{vertex.name} -->")
			for edge_id in self._adjacency_map[vertex.id]:
				edge = self.get_edge(edge_id)
				connected_vertex_id = edge.v1_id if vertex.id != edge.v1_id else edge.v2_id
				print(f"--> {self.get_vertex_name(connected_vertex_id)} w={edge.weight}")

	def get_edges(self, name: str) -> List[Edge]:
		v_id = self.get_vertex_id(name)
		return [self.get_edge(e_id) for e_id in self._adjacency_map[v_id]]

	def get_neighbors(self, name: str) -> List[Vertex]:
		v_id = self.get_vertex_id(name)
		return [self.get_vertex(edge.complementary(v_id)) for edge in self.get_edges(name)]

	def mark_vertex(self, name: str):
		v_id = self.get_vertex_id(name)
		self._vertices[v_id].marked = True

	def unmark_vertex(self, name: str):
		v_id = self.get_vertex_id(name)
		self._vertices[v_id].marked = False

	def unmark_all_vertices(self):
		for vertex in self._vertices.values():
			vertex.marked = False

	def is_all_vertices_marked(self):
		return all([v.marked for v in self._vertices.values()])

	def get_unmarked_vertex(self):
		for v in self._vertices.values():
			if not v.marked:
				return v

	def _BFS(self, s: Vertex, q: queue.Queue, visit_func: Callable = None):
		q.put(s)
		while not q.empty():
			v = q.get()
			if visit_func:
				visit_func(v)
			else:
				print(v.name, end=" ")
			self.mark_vertex(v.name)
			neighbors = self.get_neighbors(v.name)
			for neighbor in neighbors:
				if not neighbor.marked and neighbor not in q.queue:
					q.put(neighbor)

		if not self.is_all_vertices_marked():
			# We need to check if there are any nodes possibly disconnected
			# from some SCC set.
			return self._BFS(self.get_unmarked_vertex(), q, visit_func)

	def BFS(self, s: str, visit_func: Callable = None):
		s = self.get_vertex_id(s)
		s = self._vertices[s]

		self.unmark_all_vertices()
		q = queue.Queue(maxsize=len(self))
		self._BFS(s, q, visit_func)
		print("\nBFS completed.")
		self.unmark_all_vertices()

	def _DFS(self, v: Vertex, visit_func: Callable = None):
		"""Depth-First Search on the graph."""
		if visit_func:
			visit_func(v)
		else:
			print(v.name, end=" ")
		self.mark_vertex(v.name)
		for neighbor in self.get_neighbors(v.name):
			if not neighbor.marked:
				self._DFS(neighbor, visit_func)

		if not self.is_all_vertices_marked():
			# We need to check if there are any nodes possibly disconnected
			# from some SCC set.
			return self._DFS(self.get_unmarked_vertex(), visit_func)

	def DFS(self, s: str, visit_func: Callable = None):
		s = self.get_vertex_id(s)
		s = self._vertices[s]

		self.unmark_all_vertices()
		self._DFS(s, visit_func)
		print("\nDFS completed.")
		self.unmark_all_vertices()


class DiGraph(Graph):
	def add_edge(self, v1_name: str, v2_name: str, weight: float):
		v1_id = self.get_vertex_id(v1_name)
		v2_id = self.get_vertex_id(v2_name)
		e = self._create_edge(v1_id, v2_id, weight)
		self._edges[e.id] = e
		self._adjacency_map[v1_id].append(e.id)

	def delete_edge(self, v1_name: str, v2_name: str = None, how="all"):
		v1_id = self.get_vertex_id(v1_name)
		if v2_name is not None:
			edge = self.get_edge(v1_name, v2_name)
			self._edges.pop(edge.id)
			self._adjacency_map[v1_id].remove(edge.id)
		else:
			all_edges = list(self._edges.values())
			for edge in all_edges:
				if how in ["outgoing", "all"] and v1_id == edge.v1_id:
					self._edges.pop(edge.id)
					self._adjacency_map[v1_id].remove(edge.id)
				if how in ["incoming", "all"] and v1_id	== edge.v2_id:
					self._edges.pop(edge.id)
					self._adjacency_map[edge.v1_id].remove(edge.id)


if __name__ == "__main__":
	fp = "C:\\Users\\devri\\lab\\projects\\ceng21\\315\\final_prep\\example_graph.csv"
	g = DiGraph.from_file(fp)
	g.BFS("A")
	g.DFS("A")
	g.delete_vertex("F")
	g.add_vertex("H")
	g.add_vertex("I")
	g.add_edge("H", "I", 7)
	g.DFS("A")
