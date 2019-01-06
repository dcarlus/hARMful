#include <scene/Component.hpp>
#include <scene/Entity.hpp>
#include <algorithm>
#include <cassert>

using namespace Hope ;

Component::Component(const ComponentType type) {
    m_type = type ;
}

Component::~Component() {
    for(Entity* entity : m_entities) {
        onDetach(entity) ;
    }

    m_entities.clear() ;
}

ComponentType Component::type() const {
    return m_type ;
}

size_t Component::amountAttachedEntities() const {
    return m_entities.size() ;
}

void Component::attach(Entity* entity) {
    auto posEntity = std::find(m_entities.begin(), m_entities.end(), entity) ;
    bool alreadyAttached = (posEntity != m_entities.end()) ;

    if (!alreadyAttached) {
        m_entities.push_back(entity) ;
        onAttach(entity) ;
    }
}

void Component::detach(Entity* entity) {
    auto posEntity = std::find(m_entities.begin(), m_entities.end(), entity) ;
    bool isAttached = (posEntity != m_entities.end()) ;

    if (isAttached) {
        onDetach(entity) ;
        m_entities.erase(posEntity) ;
    }
}

void Component::onAttach(Entity*) {}

void Component::onDetach(Entity*) {}
