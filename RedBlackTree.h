/*
 * RedBlackTree.h
 *
 *  Created on: Nov 19, 2019
 *      Author: root
 */

#ifndef REDBLACKTREE_H_
#define REDBLACKTREE_H_

#include <memory>
#include <tr1/memory>

namespace TREE
{
template<typename T>
struct TreeNode
{
	T		data;
	bool	bIsBlack;

	std::tr1::weak_ptr<TreeNode>		parent;
	std::tr1::shared_ptr<TreeNode>	lchild; //child
	std::tr1::shared_ptr<TreeNode>	rchild; //right child
	TreeNode():bIsBlack(false){}
	TreeNode(const T& d):data(d),bIsBlack(false){}
};

}

class RedBlackTree
{
public:
	typedef TREE::TreeNode<int> TreeNodeInt;
	typedef std::tr1::shared_ptr<TreeNodeInt> _PtrTreeNode;
public:
	RedBlackTree();
	virtual ~RedBlackTree();

	_PtrTreeNode insert(int data);

	const _PtrTreeNode begin() const;
	const _PtrTreeNode next(_PtrTreeNode node) const;
	_PtrTreeNode end() const { return _PtrTreeNode(); }

private:
	_PtrTreeNode CreateNode(int data);

	_PtrTreeNode findNearByNode(int data);
	//@return curnode
	_PtrTreeNode OnInsertNode(_PtrTreeNode node);

	_PtrTreeNode _FatherNode(_PtrTreeNode node);
	_PtrTreeNode _GrandFatherNode(_PtrTreeNode node);
	_PtrTreeNode _BrotherNode(_PtrTreeNode node);
	_PtrTreeNode _UncleNode(_PtrTreeNode node);

	_PtrTreeNode leftRotate(_PtrTreeNode node);
	_PtrTreeNode rightRotate(_PtrTreeNode node);
public:
	_PtrTreeNode	m_head;
	_PtrTreeNode	m_leftmost; // 左边最下层叶子节点
};

class RedBlackTest
{
public:
	void test();
};

#endif /* REDBLACKTREE_H_ */
