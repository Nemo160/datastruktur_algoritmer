#include "adjlist.h"
// local prototypes
pnode create_node(char nname);
pnode node_cons(pnode first, pnode second);
pedge create_edge(char to, double weight);
pedge edge_cons(pedge first, pedge second);
pedge _add_edge(pedge edge, char to, double weight);
pedge _rem_edge(pedge edges, char to);
void remove_all_edges_to(pnode G, char name);
void remove_all_edges_from(pnode G, char name);

//own functions
pedge helper_remove_edges_to(pedge E, char name);


// create_node: creates node with name nname
pnode create_node(char nname)
{
	pnode new_node = (pnode)calloc(1, sizeof(node));
	new_node->name = nname;
	new_node->d = INFINITY;
	new_node->pi = '-';
	new_node->next_node = NULL;
	new_node->edges = NULL;
	return new_node;
}
// function implementations
bool is_empty(pnode G)
{
	return !G;
}
char get_name(pnode G)
{
	return is_empty(G) ? '-' : G->name;
}
pnode set_name(pnode G, char name)
{
	if (!is_empty(G))
		G->name = name;
	return G;
}
pedge get_edges(pnode G)
{
	return is_empty(G) ? NULL : G->edges;
}
pnode set_edges(pnode G, pedge E)
{
	if (!is_empty(G))
		G->edges = E;
	return G;
}
pnode get_next(pnode G)
{
	return is_empty(G) ? NULL : G->next_node;
}
// see node_cons() for the corresponding "set-next" function
double get_d(pnode G)
{
	return is_empty(G) ? INFINITY : G->d;
}
pnode set_d(pnode G, double d)
{
	if (!is_empty(G))
		G->d = d;
	return G;
}
char get_pi(pnode G)
{
	return is_empty(G) ? '-' : G->pi;
}
pnode set_pi(pnode G, char pi)
{
	if (!is_empty(G))
		G->pi = pi;
	return G;
}
// node_cons: connects two nodes in adjacency list
pnode node_cons(pnode first, pnode second)
{
	if (is_empty(first))
		return NULL;
	first->next_node = second;
	return first;
}
// add_node: adds a new node with name nname to adjacency list G
//           in lexicographical order. If it already exists
//           in graph, nothing is done
pnode add_node(pnode G, char nname)
{

	
	return is_empty(G) ? create_node(nname) :
	nname > get_name(G) ? node_cons(create_node(nname), G) :
	nname < get_name(G) ? node_cons(G,create_node(nname)) :
	G;
	
	/*if(!G){
		return create_node(nname);
	}
	else if(nname > G->name){
		return node_cons(create_node(nname),G);
	}
	else if(nname < G->name){
		return node_cons(G,create_node(nname));
	}
	else
	return G;*/
}
// rem_node: removes node with name name from adjacency list G
//           if node does not exist, nothing happens
pnode rem_node(pnode G, char name)
{
	// TODO
	return G;
}
// get_node: returns pointer to node with name name from adjacency list G
pnode get_node(pnode G, char name)
{
	return is_empty(G)  ? G :
	get_name(G) != name ? get_node(G->next_node,name) :
	G;

}
// get_node: returns true if node with name name exists in adjacency list G
//           false otherwise
bool find_node(pnode G, char name)
{
	return is_empty(G)	   ? false :
	       get_name(G) == name ? true :
				     find_node(G->next_node, name);
}
// create_edge: creates edge
pedge create_edge(char to, double weight)
{
	pedge new_edge = (pedge)calloc(1, sizeof(edge));
	new_edge->to = to;
	new_edge->weight = weight;
	return new_edge;
}
bool edge_empty(pedge E)
{
	return !E;
}
char get_to(pedge E)
{
	return edge_empty(E) ? '-' : E->to;
}
pedge set_to(pedge E, char to)
{
	if (!edge_empty(E))
		E->to = to;
	return E;
}
double get_weight(pedge E)
{
	return edge_empty(E) ? INFINITY : E->weight;
}
pedge set_weight(pedge E, double weight)
{
	if (!edge_empty(E))
		E->weight = weight;
	return E;
}
pedge get_next_edge(pedge E)
{
	return edge_empty(E) ? NULL : E->next_edge;
}
// edge_cons: connects two edges in edge list
pedge edge_cons(pedge first, pedge second)
{
	if (edge_empty(first))
		return NULL;
	first->next_edge = second;
	return first;
}
// upd_edge: updates edge E to new weight
pedge upd_edge(pedge E, double weight)
{
	if(E){
		E->weight = weight;
	}
	return E;
}
// _add_edge: creates and connects new edge to edge-list
pedge _add_edge(pedge E, char to, double weight)
{
	if(edge_empty(E)) {
		return create_edge(to,weight);;
	}

	pedge current = E;
	while(current){
		if(current->to == to){
			current->weight = weight;
			return E;
		}
		current = current->next_edge;
	}

	pedge new_edge = create_edge(to, weight);
	new_edge->next_edge = E;
	return new_edge;
	//DONE
}

// add_edge: adds an edge to G by finding correct start node
//           and then calling _add_edge to create new edge
void add_edge(pnode G, char from, char to, double weight)
{
	if(is_empty(G)){
		return;
	}
		if(G->name == from){ //if start node
			G->edges = _add_edge(G->edges,to,weight);
			return;
		}
	add_edge(G->next_node, from, to, weight);
	//DONE
}	

// _find_edge: finds edge in edge-list
bool _find_edge(pedge E, char to)
{
	pedge current = E;
	while(current){
		if(current->to == to){
			return true;
		}
		current = current->next_edge;
	}
	return false;
	//DONE
}

// find_edge: returns true if edge between from and to exists, false otherwise
bool find_edge(pnode G, char from, char to)
{
	if(is_empty(G)){
		return false;
	}
	if(G->name == from){
		return _find_edge(G->edges,to);
	}
	return find_edge(G->next_node, from, to);
	//DONE
	
}
// _edge_cardinality: returns the number of edges from one node
int _edge_cardinality(pedge E)
{
	int count = 0;
	pedge current_edge = E;
	while(current_edge){
		count++;
		current_edge = current_edge->next_edge;
	}
	return count;
}
// edge_cardinality: returns the total number of edges in G
int edge_cardinality(pnode G)
{
	if(is_empty(G))
		return 0;
	return _edge_cardinality(G->edges) + edge_cardinality(G->next_node);
}
// _self_loops: returns the number of edges going back to
//              source node
int _self_loops(pedge E, char src)
{

	// TODO
	return 0;
}
// self_loops: counts the number of self-loops, i.e. edges to and from
//             the same node
int self_loops(pnode G)
{

	// TODO
	return 0;
}
// _rem_edge: removes edge from edge-list
pedge _rem_edge(pedge E, char to)
{

	// TODO
	return E;
}
// rem_edge: removes edge from G
void rem_edge(pnode G, char from, char to)
{

	if(is_empty(G)){
		return;
	}
	if(G->name == from){
		G->edges = _rem_edge(G->edges, to);
		return;
	}
	rem_edge(G->next_node, from, to);
// DONE
}

pedge helper_remove_edges_to(pedge E, char name){
	if(!E){
		return NULL;
	}

	if(E->to == name){
		pedge next = E->next_edge;
		free(E);
		return helper_remove_edges_to(next,name);
	}
	E->next_edge = helper_remove_edges_to(E->next_edge,name);
	return E;
}
// remove_all_edges_to: removes all edges going towards node with name name
void remove_all_edges_to(pnode G, char name)
{
	if(is_empty(G)){
		return;
	}
	G->edges = helper_remove_edges_to(G->edges, name);
	remove_all_edges_to(G->next_node,name);
	// DONE
}
// remove_all_edges_from: removes all edges from node with name name
void remove_all_edges_from(pnode G, char name)
{
	if(is_empty(G)){
		return;
	}
	if(G->name == name){
		pedge e = G->edges;
		while(e){
			pedge tmp = G->edges;
			e = e->next_edge;
			free(tmp);
		}
		G->edges = NULL;
		return;
	}
	remove_all_edges_from(G->next_node,name);
	// DONE
}
// node_cardinality: returns the number of nodes in G
int node_cardinality(pnode G)
{
	if(is_empty(G)){
		return 0;
	}
	int count = 0;
	pnode current_node = G;
	while(current_node){
		count++;
		current_node = current_node->next_node;
	}
	// DONE??
	return count;
}
// name_to_pos: returns position of node with name c, -1 if not found
int name_to_pos(pnode G, char c)
{
	if(is_empty(G)){
		return -1;
	}
	int i = 0;
	pnode current_node = G;
	while(current_node){
		if(current_node-> name == c){
			return i;
		}
		current_node = current_node->next_node;
		i++;
	}
	//DONE
	return -1;
}
// pos_to_name: returns name of node at position pos in G
char pos_to_name(pnode G, int pos)
{
	if(is_empty(G)){
		return '-';
	}
	pnode current_node = G;
	while(current_node){
		if(pos == 0){
			return current_node->name;
		}
		current_node = current_node->next_node;
		pos--;
	}
	
	return '-';
	//DONE
	
}
// list_to_pos: creates adjacency matrix from adjacency list
void list_to_matrix(pnode G, double matrix[MAXNODES][MAXNODES])
{
	pnode curr_node = G;
	while(curr_node){
		int i = name_to_pos(G, curr_node->name);

	//	matrix[i][i] = 0;
		pedge e = curr_node->edges;
		while(e){
			int j = name_to_pos(G, e->to);
			matrix[i][j] = e->weight;
			e = e->next_edge;
		}
		curr_node = curr_node->next_node;
	}
	// TODO
}
