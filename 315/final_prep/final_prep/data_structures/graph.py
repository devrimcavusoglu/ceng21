"""Implementation of ADT Graph with adjacency list"""
import queue
from dataclasses import dataclass
from typing import Union, List, Tuple, Callable

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
		self._adjacency_list = []
		self._vertex_list = []
		self.__vid = 0
		self.__eid = 0

	def __len__(self):
		return len(self._vertex_list)

	@property
	def adjacency_list(self):
		return self._adjacency_list

	@property
	def vertex_list(self):
		return self._vertex_list

	@property
	def _vid(self):
		self.__vid += 1
		return self.__vid - 1

	@property
	def _eid(self):
		self.__eid += 1
		return self.__eid - 1

	def _create_vertex(self, name: str) -> Vertex:
		if not name:
			raise ValueError("'name' cannot be empty or None.")
		return Vertex(name=name, id=self._vid)

	def _create_edge(self, v1_id: int, v2_id: int, weight: float):
		return Edge(v1_id=v1_id, v2_id=v2_id, weight=weight, id=self._eid)

	def get_vertex_id(self, name: str) -> int:
		for i, v in enumerate(self._vertex_list):
			if v.name == name:
				return i
		return -1

	def get_vertex_name(self, id: int) -> str:
		for i, v in enumerate(self._vertex_list):
			if id == i:
				return v.name
		return ""

	def get_vertex(self, id_or_name: Union[str, int]) -> Vertex:
		if isinstance(id_or_name, str):
			id_or_name = self.get_vertex_id(id_or_name)
		return self._vertex_list[id_or_name]

	def get_edge(self, id: int) -> Edge:
		for v_edges in self._adjacency_list:
			for edge in v_edges:
				if edge.id == id:
					return edge

	def add_vertex(self, name: str) -> None:
		v = self._create_vertex(name)
		self._vertex_list.append(v)
		self._adjacency_list.append([])

	def add_edge(self, v1_name: str, v2_name: str, weight: float):
		v1_id = self.get_vertex_id(v1_name)
		v2_id = self.get_vertex_id(v2_name)
		e = self._create_edge(v1_id, v2_id, weight)
		self._adjacency_list[v1_id].append(e)
		self._adjacency_list[v2_id].append(e)

	def delete_vertex(self, name: str):
		# TODO: Incomplete.
		v_id = self.get_vertex_id(name)
		self._adjacency_list[v_id] = []
		self._vertex_list.pop(v_id)

	def delete_edge(self, v1_name: str, v2_name: str):
		v1_id = self.get_vertex_id(v1_name)
		v2_id = self.get_vertex_id(v2_name)

		for edge in self._adjacency_list[v1_id]:
			if edge.v1_id == v2_id or edge.v2_id == v2_id:
				self._adjacency_list[v1_id].remove(edge)

		for edge in self._adjacency_list[v2_id]:
			if edge.v1_id == v1_id or edge.v2_id == v1_id:
				self._adjacency_list[v2_id].remove(edge)

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
		for vertex in self._vertex_list:
			print(f"{vertex.name} -->")
			for edge in self._adjacency_list[vertex.id]:
				connected_vertex_id = edge.v1_id if vertex.id != edge.v1_id else edge.v2_id
				print(f"--> {self.get_vertex_name(connected_vertex_id)} w={edge.weight}")

	def get_edges(self, name: str) -> List[Edge]:
		v_id = self.get_vertex_id(name)
		return self._adjacency_list[v_id]

	def get_neighbors(self, name: str) -> List[Vertex]:
		v_id = self.get_vertex_id(name)
		return [self.get_vertex(edge.complementary(v_id)) for edge in self.get_edges(name)]

	def mark_vertex(self, name: str):
		v_id = self.get_vertex_id(name)
		self._vertex_list[v_id].marked = True

	def unmark_vertex(self, name: str):
		v_id = self.get_vertex_id(name)
		self._vertex_list[v_id].marked = False

	def unmark_all_vertices(self):
		for vertex in self._vertex_list:
			vertex.marked = False

	def BFS(self, s: str = None, visit_func: Callable = None):
		if s is None:
			s = self._vertex_list[0]
		else:
			s = self.get_vertex_id(s)
			s = self._vertex_list[s]

		self.unmark_all_vertices()
		q = queue.Queue(maxsize=len(self))
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

	def DFS(self, s: str = None, visit_func: Callable = None):
		if s is None:
			s = self._vertex_list[0]
		else:
			s = self.get_vertex_id(s)
			s = self._vertex_list[s]

		self.unmark_all_vertices()
		self._DFS(s, visit_func)
		print("\nDFS completed.")
		self.unmark_all_vertices()


class DiGraph(Graph):
	def add_edge(self, v1_name: str, v2_name: str, weight: float):
		v1_id = self.get_vertex_id(v1_name)
		v2_id = self.get_vertex_id(v2_name)
		e = self._create_edge(v1_id, v2_id, weight)
		self._adjacency_list[v1_id].append(e)


if __name__ == "__main__":
	fp = "C:\\Users\\devri\\lab\\projects\\ceng21\\315\\final_prep\\example_graph.csv"
	g = Graph.from_file(fp)
	g.BFS("A")
	g.DFS("A")
