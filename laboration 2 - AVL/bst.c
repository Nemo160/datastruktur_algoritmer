//=============================================================================
// bst.c - binary search tree, based on binary tree (bt.h/bt.c)
//=============================================================================
#include "global.h"
#include "bst.h"

//-----------------------------------------------------------------------------
// local function prototypes
//-----------------------------------------------------------------------------
static void _preorder(BST T, int* pos, int* a);
static void _inorder(BST node, int* a, int* i);
static void _postorder(BST node, int* a, int* i);
static int max_height(int l, int r);
static BST BST_findMinRem(BST T);

//-----------------------------------------------------------------------------
// public functions, exported through bst.h
//-----------------------------------------------------------------------------

// new_BST: creates a new BST
BST new_BST(int val)
{
	return new_BT(val);
}

//-----------------------------------------------------------------------------
// bst_add: adds the value v to the BST T (unless duplicate)
//-----------------------------------------------------------------------------
BST bst_add(BST T, int v)
{
	return	!T            	?	new_BST(v)                            :
		v < get_val(T)	?	cons(add(get_LC(T), v), T, get_RC(T)) :
		v > get_val(T)	?	cons(get_LC(T), T, add(get_RC(T), v)) :
		/* duplicate */		T;
}


//-----------------------------------------------------------------------------
// bst_rem: removes the value val from the BST (if it exists)
//-----------------------------------------------------------------------------


	BST bst_rem(BST T, int val)
{
    if(!T){
		return NULL;
	}
        //Searching för val
        if(val < get_val(T))
        {
            return cons(bst_rem(get_LC(T),val), T,  get_RC(T));
        }
        if(val > get_val(T))
        {
			return cons(get_LC(T), T, bst_rem(get_RC(T), val));
        }
    
        //cases:
        if(!get_RC(T) && !get_LC(T))    //no child nodes return null)
        {
            return NULL;
        }
        
		if(!get_LC(T))    //one child node return existing child)
        {
            return get_RC(T);
        }
        
		if(!get_RC(T))
        {
			return get_LC(T);
		}
		//two children 
		BST tmp = BST_findMinRem(get_RC(T));
		set_val(T,get_val(tmp));

		return cons(get_LC(T), T, bst_rem(get_RC(T), get_val(tmp)));
}



void preorder(BST T, int* a)
{
	int pos = 0;
	_preorder(T, &pos, a);
}

void inorder(BST T, int* a)
{
	int i = 0;
	_inorder(T,a,&i);
}

void postorder(BST T, int* a)
{
	int i = 0;
	_postorder(T,a,&i);
}
//-----------------------------------------------------------------------------
// bfs: puts the BST T values into array a in bfs-order, non-nodes
// are indicated by X, as defined in global.h
//-----------------------------------------------------------------------------
//   2                    2
//  / \	--> [2,1,3]      / \  --> [2,X,3]
// 1  3                 *  3
//-----------------------------------------------------------------------------
void bfs(BST T, int* a, int max)
{
	for(int i = 0; i <max; i++){
		a[i]= X;
	}
	if(!T) return;

	BST Q[max*2];
	int front = 0, back = 0;
	Q[back++] = T;
	int i = 0;
	while(front < back && i<max){
		BST curr = Q[front++];
		if(curr){
			//store current value of node into array
			a[i] = get_val(curr);
			//enqueue children of that node
			Q[back++] = get_LC(curr);
			Q[back++] = get_RC(curr);
		}
		//if missing node
		else{ 
			a[i] = X;
			Q[back++] = NULL;
			Q[back++] = NULL; 
		}
		i++;
	}
}

//-----------------------------------------------------------------------------
// is_member: checks if value val is member of BST T
//-----------------------------------------------------------------------------
bool is_member(BST T, int val)
{
	while(T != NULL){
		if(val == get_val(T)){
			return true;
		}
		if(val < get_val(T)){
			T = get_LC(T);
		}
		else{
			T = get_RC(T);
		}
	}
	return false;
}
//-----------------------------------------------------------------------------
// height: returns height of BST T
//-----------------------------------------------------------------------------
int height(BST T)
{
	if(!T){
		return 0;
	}

	int h_left = height(get_LC(T));
	int h_right = height(get_RC(T));

	return 1 + max_height(h_left,h_right);
}
//-----------------------------------------------------------------------------
// size: returns size of BST T
//-----------------------------------------------------------------------------
int size(BST T)
{
	if(!T){
		return 0;
	}
		
	return 1 + size(get_LC(T)) +size(get_RC(T));
}

//-----------------------------------------------------------------------------
// private helper functions, not exported
//-----------------------------------------------------------------------------
static void _preorder(BST T, int* pos, int* a)
{
	if (T){
		a[(*pos)++] = get_val(T);
		_preorder(get_LC(T), pos, a);
		_preorder(get_RC(T), pos, a);
	}
}

static void _inorder(BST T, int* a, int* i){
	if(!T)
		return;

	_inorder(get_LC(T),a,i);

	a[*i] = get_val(T);
	(*i)++;
	_inorder(get_RC(T),a,i);	

}

static void _postorder(BST T, int* a, int* i){
	if(!T) 
		return;

	_postorder(get_LC(T),a,i);
	_postorder(get_RC(T),a,i);
	a[*i] = get_val(T);
	(*i)++;

}

static int max_height(int L, int R){
	if(L>R) 
		return L;

	else 
		return R;
}

static BST BST_findMinRem(BST T)
{
    while(get_LC(T))
    {
        T = get_LC(T);
    }

    return T;
} 


