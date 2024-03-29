#include <scene/Node.hpp>
#include <algorithm>
#include <cassert>

using namespace Hope ;

Node::Node(Node* parent) {
    if (parent) {
        bool success = parent -> addChild(this) ;

        if (success) {
            m_parent = parent ;
        }
    }
}

Node::~Node() {
    m_children.clear() ;
}

void Node::setParent(Node* parent) {
    if (m_parent) {
        m_parent -> removeChild(this) ;
    }

    m_parent = parent ;

    if (m_parent) {
        m_parent -> addChild(this) ;
    }
}

Node* Node::parent() const {
    return m_parent ;
}

const std::vector<Node*>& Node::children() const {
    return m_children ;
}

std::vector<Node*> Node::children() {
	std::vector<Node*> copied(m_children) ;
    return copied ;
}

size_t Node::childrenCount() const {
    return m_children.size() ;
}

bool Node::addChild(Node* newChild) {
    assert(newChild != nullptr) ;

    if (newChild == this) {
        // Avoid being its own child...
        return false ;
    }

    auto posNode = std::find(m_children.begin(), m_children.end(), newChild) ;
    bool hasChild = (posNode != m_children.end()) ;

    if (!hasChild) {
        m_children.push_back(newChild) ;
        return true ;
    }

    return false ;
}

bool Node::removeChild(Node* child) {
    assert(child != nullptr) ;

    auto posNode = std::find(m_children.begin(), m_children.end(), child) ;
    bool hasChild = (posNode != m_children.end()) ;

    if (hasChild) {
        m_children.erase(posNode) ;
        return true ;
    }

    return false ;
}
