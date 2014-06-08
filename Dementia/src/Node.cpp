#include "Node.h"

namespace Dementia{

	Node::Node(UINT id) :
		m_id(id),
		m_parent(nullptr),
		m_entity(nullptr),
		m_position(XMVectorZero()),
		m_scale(XMVectorSet(1.0f,1.0f,1.0f,1.0f)),
		m_rotation(XMVectorZero()),
		m_worldPosition(XMVectorZero()),
		m_worldScale(XMVectorSet(1.0f,1.0f,1.0f,1.0f)),
		m_worldRotation(XMVectorZero())
	{
		calcScaleMatrix();
		calcRotationMatrix();
		calcTranslationMatrix();
		calcWorldMatrix();
	}

	Node::Node(UINT id, XMVECTOR position, XMVECTOR scale, XMVECTOR rotation) :
		m_id(id),
		m_parent(nullptr),
		m_entity(nullptr),
		m_position(position),
		m_scale(scale),
		m_rotation(rotation),
		m_worldPosition(XMVectorZero()),
		m_worldScale(XMVectorSet(1.0f,1.0f,1.0f,1.0f)),
		m_worldRotation(XMVectorZero())
	{
		calcScaleMatrix();
		calcRotationMatrix();
		calcTranslationMatrix();
		calcWorldMatrix();
	}
	
	Node::~Node(void)
	{
	}

	void Node::setLocalPosition(XMVECTOR position)
	{
		m_position = position;
		if(m_parent != nullptr){
			recalcWorldPosition();
			for(auto child : m_childs)
			{
				child->recalcWorldPosition();
			}
		}
	}

	void Node::recalcWorldPosition()
	{
		m_worldPosition = m_position + m_parent->getWorldPosition();
		calcTranslationMatrix();
		calcWorldMatrix();
	}

	void Node::setLocalScale(XMVECTOR scale)
	{
		m_scale = scale;
		if(m_parent != nullptr){
			recalcWorldScale();
			for(auto child : m_childs)
			{
				child->recalcWorldScale();
			}
		}
	}

	void Node::recalcWorldScale()
	{
		m_worldScale = m_scale * m_parent->getWorldScale();
		calcScaleMatrix();
		calcWorldMatrix();
	}

	void Node::setLocalRotation(XMVECTOR rotation)
	{
		m_rotation = rotation;
		if(m_parent != nullptr){
			recalcWorldRotation();
			for(auto child : m_childs)
			{
				child->recalcWorldRotation();
			}
		}
	}

	void Node::recalcWorldRotation()
	{
		m_worldRotation = m_rotation + m_parent->getWorldRotation();
		calcRotationMatrix();
		calcWorldMatrix();
	}

	void Node::calcTranslationMatrix()
	{
		m_mTranslation = XMMatrixTranspose(XMMatrixTranslationFromVector(m_worldPosition));
	}

	void Node::calcScaleMatrix()
	{
		m_mScale = XMMatrixScalingFromVector(m_worldScale);
	}

	void Node::calcRotationMatrix()
	{
		m_mRotation = XMMatrixRotationRollPitchYawFromVector(m_worldRotation);
	}

	void Node::calcWorldMatrix()
	{
		XMMATRIX scale = m_mScale;
		XMMATRIX rotation = m_mRotation;
		XMMATRIX translation = m_mTranslation;
		m_mWorld = scale * rotation * translation;
	}

	XMMATRIX Node::getWorldMatrix()
	{
		return m_mWorld;
	}

	void Node::setParent(Dementia::Node* parent)
	{
		if(m_parent != nullptr)
		{
			m_parent->removeChild(m_id);
		}

		m_parent = parent;
		
		m_worldPosition = m_position + parent->getWorldPosition();
		m_worldScale = m_scale * parent->getWorldScale();
		m_worldRotation = m_rotation + parent->getWorldRotation();
			
		calcScaleMatrix();
		calcRotationMatrix();
		calcTranslationMatrix();
		calcWorldMatrix();
	};

	void Node::getAllNodes(std::vector<Dementia::Node*>* nodes)
	{
		for(Dementia::Node* node : m_childs)
		{
			node->getAllNodes(nodes);
		}
		
		nodes->push_back(this);
	}

	void Node::addChild(Dementia::Node* child)
	{
		child->setParent(this);
		m_childs.push_back(child);
	}

	Dementia::Node* Node::getChild(UINT id)
	{
		for(Dementia::Node* node : m_childs){
			if(node->getId() == id){
				return node;
			}
		}
		return nullptr;
	}

	//TODO: Probar que funcione
	bool Node::removeChild(UINT id)
	{
		for(auto it = m_childs.begin(); it != m_childs.end(); it++)
		{
			if( (*it)->getId() == id )
			{
				m_childs.erase(it);
				return true;
			}
		}

		return false;
	}

}