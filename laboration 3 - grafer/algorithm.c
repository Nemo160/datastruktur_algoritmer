#include "algorithm.h"
// queue - defines a queue as a pointer to an array of pointers to nodes
typedef pnode *queue;
// local prototypes
void init_single_source(pnode G, char s);
void relax(pnode u, pnode v, int w);
int Q_insert(queue Q, pnode u, int index);
int Q_is_empty(queue Q, int size);
pnode Q_extract_min(queue Q, int size);
bool Q_exists(queue Q, int qsize, char name);
int name_to_pos(pnode G, char c);
void list_to_matrix(pnode G, double matrix[MAXNODES][MAXNODES]);
//--------------------------------------------------------------------------
// init single source, relax and min are to be used by algorithms
//--------------------------------------------------------------------------
void init_single_source(pnode G, char s)
{
	for (pnode node = G; !is_empty(node); node = get_next(node)) {
		if (get_name(node) == s) // start node
			set_d(node, 0);
		else
			set_d(node, INFINITY);
		set_pi(node, '-');
	}
}
void relax(pnode u, pnode v, int w)
{
	if (get_d(v) > (get_d(u) + w)) {
		set_d(v, get_d(u) + w);
		set_pi(v, get_name(u));
	}
}
double min(double a, double b)
{
	return a < b ? a : b;
}
//--------------------------------------------------------------------------
// Q functions - used by other algorithms
//--------------------------------------------------------------------------
int Q_insert(queue Q, pnode u, int index)
{
	Q[index] = u; 
	// DONE
	return 0;
}
int Q_is_empty(queue Q, int size)
{
	return size == 0; 
	// DONE

}
pnode Q_extract_min(queue Q, int size)
{
	double min_d = get_d(Q[0]);
	int min_p = 0;
	
	for(int i = 1; i < size; i++)	{ //find min
		if(get_d(Q[i]) <= min_d){
			min_d = get_d(Q[i]);
			min_p = i;
		}
	}

	pnode tmp = Q[min_p];
	
	for(int i = min_p; i < size-1; i++){ //extract from Q
		Q[i] = Q[i+1];
	}
	return tmp;
	// DONE
}
bool Q_exists(queue Q, int qsize, char name)
{
	for(int i = 0; i < qsize; i++){
		if(get_name(Q[i]) == name){
			return true;
		}
	}
	return false;
}
//--------------------------------------------------------------------------
// Dijkstra's algorithm, single source shortest path tree generator
// a -> b(1) -> c(5)
// b -> c(2)           --> d: [  0,   1,   3]
// c                       e: [  -,   a,   b]
//--------------------------------------------------------------------------
void dijkstra(pnode G, char s, double *d, char *e) // s:startnamn, d: distance, e : name
{
  //  for (pnode u = G; !is_empty(u); u = get_next(u)) { printf("\n%c: d=%f pi=%c\n", get_name(u), get_d(u), get_pi(u)); }/////////////////////////
	if(is_empty(G)){
		return;
	}
	int q_size = 0;
	int number_of_nodes = node_cardinality(G);
	queue Q = malloc(sizeof(pnode) * number_of_nodes);  

	init_single_source(G,s);
	for(pnode u = G; !is_empty(u) ; u = get_next(u)){ //////////////////
		Q_insert(Q, u, q_size);
		q_size++;
	}
	while(!Q_is_empty(Q, q_size)){
		pnode u = Q_extract_min(Q, q_size);
		q_size--;
        
		for(pedge E = u->edges; !edge_empty(E); E = E->next_edge)
        { 
			char vname = get_to(E);
			if(Q_exists(Q, q_size, vname)){
				pnode v = get_node(G, vname);
				if(!is_empty(v)){
					relax(u, v, (int)E->weight);
				}
			}
		}
	}
	for(pnode u = G; !is_empty(u); u = get_next(u)){
		int pos = name_to_pos(G, get_name(u));
		if(pos >= 0){
			
			d[pos] = get_d(u);
			e[pos] = get_pi(u);
		}
	}
	free(Q);
}


//--------------------------------------------------------------------------
// Prim's algorithm - Minimum Spanning Tree generator
// start_node: a
// a -> b(1) -> c(5)
// b -> c(2)           --> d: [inf,   1,   2]
// c                       e: [  -,   a,   b]
//--------------------------------------------------------------------------
void prim(pnode G, char start_node, double *d, char *e)
{
    if(is_empty(G)){
        return;
    }
	int number_of_nodes = node_cardinality(G);
	queue Q = malloc(sizeof(pnode) * number_of_nodes);  

    int qsize = 0;
    //initialize
    for(pnode u = G; !is_empty(u); u = get_next(u)){
        if(get_name(u) == start_node){
			set_d(u, 0.0);
        }
        else{
			set_d(u, INFINITY);
        }
        set_pi(u,'-');
        Q_insert(Q, u, qsize);
        qsize++;
    }

    //prim algorithm
    while(!Q_is_empty(Q, qsize)){
        pnode u = Q_extract_min(Q, qsize);
        qsize--;
        
        for(pedge E = get_edges(u); !edge_empty(E); E = E->next_edge){
            char vname = get_to(E); 
            pnode v = get_node(G, vname);
            if(is_empty(v)) continue;
            
            if(Q_exists(Q, qsize, vname) && get_weight(E) < get_d(v)){
                set_pi(v, get_name(u));
                set_d(v, get_weight(E));
            }
        }
    }

    for (pnode u = G; !is_empty(u); u = get_next(u)) {
        int pos = name_to_pos(G, get_name(u));
        if (pos >= 0) {
            e[pos] = get_pi(u);
            d[pos] = (get_name(u) == start_node) ? INFINITY : get_d(u);
        }
    }
    free(Q);
}

//--------------------------------------------------------------------------
// Floyd's algorithm: returns matrix of distances
// a -> b(1)
// |                   |0  |1  |3  |
// b -> c(2)    -->    |INF|0  |2  |
// |                   |INF|INF|0  |
// c
//--------------------------------------------------------------------------
void floyd(pnode G, double W[MAXNODES][MAXNODES])
{
    if(is_empty(G)){
        return;
    }
    int n = node_cardinality(G);
    list_to_matrix(G,W);
    
    for(int k=0; k<n; k++)
        for(int i = 0; i<n; i++)
            for(int j = 0; j < n;j++){

                // finns ingen väg
                if(W[i][k] == INFINITY || W[k][j] == INFINITY) { 
                    continue;
                }
                double path = W[i][k] + W[k][j];
                W[i][j] = min(W[i][j], path);  
            }

    
	// DONE
}
//--------------------------------------------------------------------------
// Warshall's algorithm: returns matrix of closures, i.e. if paths exists
// a -> b(1)
// |                   |T  |T  |T  |
// b -> c(2)    -->    |F  |T  |T  |
// |                   |F  |F  |T  |
// c
//--------------------------------------------------------------------------
void warshall(pnode G, double W[MAXNODES][MAXNODES])
{
    if(is_empty(G)){
        return;
    }
    int n = node_cardinality(G);
    list_to_matrix(G,W);
    //init
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
			if(W[i][j] != INFINITY){
                W[i][j] = 1.0;
            }
				
			else{
                W[i][j] = 0.0;
            }
		}
    }
    
    for(int k=0; k<n; k++)
        for(int i = 0; i<n; i++)
            for(int j = 0; j < n;j++)
                W[i][j] = W[i][j] || (W[i][k] && W[k][j]);
}


