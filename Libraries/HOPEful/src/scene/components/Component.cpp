#include <scene/components/Component.hpp>
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

void Component::entities(std::vector<Entity*>& entities) const {
    if (m_entities.size() > 0) {
        std::copy(m_entities.begin(), m_entities.end(), entities.begin()) ;
    }
}

Entity* Component::firstEntity() const {
    if (m_entities.size() > 0) {
        return m_entities[0] ;
    }

    return nullptr ;
}

bool Component::attach(Entity* entity) {
    if (!entity -> isEditable()) {
        return false ;
    }

    auto posEntity = std::find(m_entities.begin(), m_entities.end(), entity) ;
    bool alreadyAttached = (posEntity != m_entities.end()) ;

    if (!alreadyAttached || isShareable()) {
        m_entities.push_back(entity) ;
        onAttach(entity) ;
        return true ;
    }

    return false ;
}

bool Component::detach(Entity* entity) {
    if (!entity -> isEditable()) {
        return false ;
    }
    auto posEntity = std::find(m_entities.begin(), m_entities.end(), entity) ;
    bool isAttached = (posEntity != m_entities.end()) ;

    if (isAttached) {
        onDetach(entity) ;
        m_entities.erase(posEntity) ;
        return true ;
    }

    return false ;
}

void Component::onAttach(Entity*) {}

void Component::onDetach(Entity*) {}
