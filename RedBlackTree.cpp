/*
 * RedBlackTree.cpp
 *
 *  Created on: Nov 19, 2019
 *      Author: root
 */

#include "RedBlackTree.h"
#include "TypeBase.h"

using namespace TREE;

RedBlackTree::RedBlackTree()
{
	// TODO Auto-generated constructor stub

}

RedBlackTree::~RedBlackTree()
{
	// TODO Auto-generated destructor stub
}

RedBlackTree::_PtrTreeNode RedBlackTree::insert(int data)
{
	_PtrTreeNode nodeFind = findNearByNode(data);

	if (nodeFind && nodeFind->data == data)
		return nodeFind;

	_PtrTreeNode nodeme = CreateNode(data);
	if (!nodeFind)
	{
		m_head = nodeme;
		m_leftmost = nodeme;
	}
	else if (nodeFind->data < data)
	{
		nodeFind->rchild = nodeme;
		nodeme->parent = nodeFind;
	}
	else
	{
		nodeFind->lchild = nodeme;
		nodeme->parent = nodeFind;

		if (nodeFind == m_leftmost)
			m_leftmost = nodeme;
	}

	OnInsertNode(nodeme);
	return nodeme;
}

const RedBlackTree::_PtrTreeNode RedBlackTree::begin() const
{
	return m_leftmost;
}
const RedBlackTree::_PtrTreeNode RedBlackTree::next(_PtrTreeNode node) const
{
	if (node->rchild)
	{
		node = node->rchild;
		while (node->lchild)
			node = node->lchild;
		return node;
	}

	_PtrTreeNode nodeFather;
	while (true)
	{
		nodeFather = node->parent.lock();
		if (!nodeFather)
			return end();
		if (nodeFather->lchild == node)
			return nodeFather;
		node = nodeFather;
	}
	return end();
}

RedBlackTree::_PtrTreeNode RedBlackTree::CreateNode(int data)
{
	_PtrTreeNode node(new TreeNodeInt(data));
	return node;
}

RedBlackTree::_PtrTreeNode RedBlackTree::findNearByNode(int data)
{
	auto node = m_head;
	while (node)
	{
		if (node->data == data)
			return node;
		if (data < node->data)
		{
			if (!node->lchild)
				break;
			node = node->lchild;
		}
		else
		{
			if (!node->rchild)
				break;
			node = node->rchild;
		}
	}
	return node;
}

RedBlackTree::_PtrTreeNode RedBlackTree::OnInsertNode(_PtrTreeNode node)
{
	// 1.插入的新节点 N 是红黑树的根节点
	if (node == m_head)
	{
		node->bIsBlack = true;
		return node;
	}

	auto nodeFather = _FatherNode(node);
	if (!nodeFather)
		return node;

	// 2.N 的父节点是黑色
	if (nodeFather->bIsBlack)
		return node;

	// 父节点是红色 && 本节点为父节点右子节点
	if (node == nodeFather->rchild)
	{
		leftRotate(nodeFather);
		return OnInsertNode(nodeFather);
	}

	auto nodeGrandFa = _FatherNode(nodeFather);
	if (!nodeGrandFa)
		return OnInsertNode(nodeFather);

	auto nodeUncle = _BrotherNode(nodeFather);
	// 4. N 的父节点为红色，叔叔节点为黑色。
	if (!nodeUncle || nodeUncle->bIsBlack)
	{
		nodeGrandFa->bIsBlack = false;
		nodeFather->bIsBlack = true;
		if (nodeFather == nodeGrandFa->lchild)
			rightRotate(nodeGrandFa);
		else
			leftRotate(nodeGrandFa);
		return OnInsertNode(nodeFather);
	}
	// 5.N 的父节点为红色，叔叔节点为红色
	nodeGrandFa->bIsBlack = false;
	nodeFather->bIsBlack = true;
	nodeUncle->bIsBlack = true;
	return OnInsertNode(nodeGrandFa);
}

RedBlackTree::_PtrTreeNode RedBlackTree::_FatherNode(_PtrTreeNode node)
{
	if (!node)
		return node;
	if (node->parent.expired())
		return _PtrTreeNode();
	return node->parent.lock();
}
RedBlackTree::_PtrTreeNode RedBlackTree::_GrandFatherNode(_PtrTreeNode node)
{
	node = _FatherNode(node);
	return _FatherNode(node);
}
RedBlackTree::_PtrTreeNode RedBlackTree::_BrotherNode(_PtrTreeNode node)
{
	if (!node)
		return node;
	auto nodeFather = _FatherNode(node);
	if (!nodeFather)
		return nodeFather;
	if (nodeFather->lchild == node)
		return nodeFather->rchild;
	return nodeFather->lchild;
}
RedBlackTree::_PtrTreeNode RedBlackTree::_UncleNode(_PtrTreeNode node)
{
	if (!node)
		return node;
	node = _FatherNode(node);
	return _BrotherNode(node);
}
RedBlackTree::_PtrTreeNode RedBlackTree::leftRotate(_PtrTreeNode node)
{
	if (!node)
		return node;
	if (!node->rchild)
		return node;

	auto rchild = node->rchild;
	auto nodeFather = _FatherNode(node);
	if (nodeFather)
	{
		if (node == nodeFather->lchild)
			nodeFather->lchild = rchild;
		else
			nodeFather->rchild = rchild;
	}
	rchild->parent = nodeFather;

	node->rchild = rchild->lchild;
	if (rchild->lchild)
		rchild->lchild->parent = node;

	node->parent = rchild;
	rchild->lchild = node;

	if (m_head == node)
		m_head = rchild;
	return node;
}
RedBlackTree::_PtrTreeNode RedBlackTree::rightRotate(_PtrTreeNode node)
{
	if (!node)
		return node;
	if (!node->lchild)
		return node;

	auto lchild = node->lchild;
	auto nodeFather = _FatherNode(node);
	if (nodeFather)
	{
		if (node == nodeFather->lchild)
			nodeFather->lchild = lchild;
		else
			nodeFather->rchild = lchild;
	}
	lchild->parent = nodeFather;

	node->lchild = lchild->rchild;
	if (lchild->rchild)
		lchild->rchild->parent = node;

	node->parent = lchild;
	lchild->rchild = node;

	if (m_head == node)
		m_head = lchild;
	return node;
}

void RedBlackTest::test()
{
	RedBlackTree t;
	t.insert(9);
	t.insert(3);
	t.insert(1);
	t.insert(6);
	t.insert(0);
	t.insert(1);

	for (auto node = t.begin(); node != t.end(); node = t.next(node))
	{
		DEBUG("%d", node->data);
	}
}

