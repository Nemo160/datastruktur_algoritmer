//=============================================================================
// avl.c - AVL-tree based on binary search tree (bst.h/bst.c)
//=============================================================================
#include "avl.h"
#define DEBUG 0
//=============================================================================
// local prototypes
//-----------------------------------------------------------------------------
static AVL srr(AVL T);
static AVL slr(AVL T);
static AVL drr(AVL T);
static AVL dlr(AVL T);
static int bf(AVL T);
static int height_AVL(AVL T);
static int max_height_AVL(int L, int R);
static AVL AVL_findMinRem(AVL T);
//=============================================================================
// Public functions, exported via .h-file
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// avl_add: adds the value val to AVL T in a balanced fashion
//-----------------------------------------------------------------------------
AVL avl_add(AVL T, int val)
{
	if(DEBUG)printf("avl_add (%d)\n",val);
	if(!T){ return new_BT(val);}
	if (val < get_val(T)) {
		return balance(cons(avl_add(get_LC(T), val), T, get_RC(T)));
	}
	if (val > get_val(T)) {
		return balance(cons(get_LC(T), T, avl_add(get_RC(T), val)));
	}
	return T;
}
//-----------------------------------------------------------------------------
// avl_rem: removes the value val from AVL T in a balanced fashion
//-----------------------------------------------------------------------------
AVL avl_rem(AVL T, int val)
{
	if(DEBUG)printf("avl_rem (%d)\n",val);
	if(!T){
		return NULL;
	}
        //searching för val
    if(val < get_val(T)){
		AVL new_tree = cons(avl_rem(get_LC(T),val), T,  get_RC(T));
        return balance(new_tree);
    }
    if(val > get_val(T))
    {
		AVL new_tree = cons(get_LC(T), T, avl_rem(get_RC(T), val));
		return balance(new_tree);
    }

	if(!get_RC(T) && !get_LC(T)){ //no child nodes
        return NULL;
    }
        
	if(!get_LC(T)){  //one child node return existing child)
        return get_RC(T);
    }
        
	if(!get_RC(T)){
		return get_LC(T);
	}

		//two children 
	AVL tmp = AVL_findMinRem(get_RC(T));
	set_val(T,get_val(tmp));
	AVL subtree = cons(get_LC(T), T, avl_rem(get_RC(T), get_val(tmp)));
	return balance(subtree);
}
//-----------------------------------------------------------------------------
// balance: balances the AVL tree T if needed
//-----------------------------------------------------------------------------
AVL balance(AVL T)
{
	if(bf(T) == 2){ //left balance
		if(bf(get_LC(T)) >= 0)
			return srr(T);
		else
			return drr(T);
	}
	if(bf(T) ==-2){ //right balance
		if(bf(get_RC(T)) <= 0)
			return slr(T);
		else
			return dlr(T);
	}
	return T;
}
//=============================================================================
// Private functions, for local use only
//-----------------------------------------------------------------------------
static AVL AVL_findMinRem(AVL T) //copy from bst
{
    while(get_LC(T))
    {
        T = get_LC(T);
    }

    return T;
} 

static AVL srr(AVL T)
{
	if(DEBUG)printf("srr\n");
	AVL T1 = get_LC(T);
	T->LC = T1->RC;
	T1->RC = T;
	return T1;
}
static AVL slr(AVL T)
{
	if(DEBUG)printf("slr\n");
	AVL T1 = get_RC(T);
	T->RC = T1->LC;
	T1->LC = T;
	return T1;
}
static AVL drr(AVL T)
{
	if(DEBUG)printf("drr\n");
	T->LC = slr(get_LC(T));
	return srr(T);
}
static AVL dlr(AVL T)
{
	if(DEBUG)printf("dlr\n");
	T->RC = srr(get_RC(T));
	return slr(T);
}

static int bf(AVL T){
	if(!T) return 0;
	int hl = height_AVL(get_LC(T));
	int hr = height_AVL(get_RC(T));
	return hl - hr;
}

//copy from bst
static int height_AVL(AVL T)
{
	if(!T) return 0;
	int h_left = height_AVL(get_LC(T));
	int h_right = height_AVL(get_RC(T));

	return 1 + max_height_AVL(h_left,h_right);
}

static int max_height_AVL(int L, int R){
	if(L>R) return L;
	else return R;
}
