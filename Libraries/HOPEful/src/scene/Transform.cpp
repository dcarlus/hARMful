#include <scene/Transform.hpp>

using namespace Hope ;

void Transform::setRotation(const Mind::Quaternion& rotation) {
    if (rotation == m_rotation) {
        return ;
    }

    m_rotation = rotation ;
    m_outdatedMatrix = true ;

    float roll ;
    float pitch ;
    float yaw ;
    m_rotation.to(roll, pitch, yaw) ;
    m_eulerAngles.set(roll, pitch, yaw) ;
}

void Transform::setRotationOnX(const float rotation) {
    if (m_eulerAngles.get(Mind::Vector3f::X) == rotation) {
        return ;
    }

    m_eulerAngles.set(Mind::Vector3f::X, rotation) ;
    Mind::Quaternion newRotation ;
    // Need to implement Quaternion::from(euler angles values):
    // newRotation.from(roll, pitch, yaw) ;

    if (newRotation != m_rotation) {
        m_rotation = newRotation ;
        m_outdatedMatrix = true ;
    }
}

void Transform::setRotationOnY(const float rotation) {
    if (m_eulerAngles.get(Mind::Vector3f::Y) == rotation) {
        return ;
    }

    m_eulerAngles.set(Mind::Vector3f::Y, rotation) ;
    Mind::Quaternion newRotation ;
    // Need to implement Quaternion::from(euler angles values):
    // newRotation.from(roll, pitch, yaw) ;

    if (newRotation != m_rotation) {
        m_rotation = newRotation ;
        m_outdatedMatrix = true ;
    }
}

void Transform::setRotationOnZ(const float rotation) {
    if (m_eulerAngles.get(Mind::Vector3f::Z) == rotation) {
        return ;
    }

    m_eulerAngles.set(Mind::Vector3f::Z, rotation) ;
    Mind::Quaternion newRotation ;
    // Need to implement Quaternion::from(euler angles values):
    // newRotation.from(roll, pitch, yaw) ;

    if (newRotation != m_rotation) {
        m_rotation = newRotation ;
        m_outdatedMatrix = true ;
    }
}

void Transform::setTranslation(const Mind::Vector3f& translation) {
    if (m_translation == translation) {
        return ;
    }

    m_translation = translation ;
    m_outdatedMatrix = true ;
}

void Transform::setScale(const float scale) {
    if (m_scale.get(Mind::Vector3f::X) == scale) {
        return ;
    }

    setScale3D(Mind::Vector3f(scale, scale, scale)) ;
}

void Transform::setScale3D(const Mind::Vector3f& scale) {
    if (m_scale == scale) {
        return ;
    }

    m_scale = scale ;
    m_outdatedMatrix = true ;
}

void Transform::setMatrix(const Mind::Matrix4x4f& matrix) {
    // Implement matrix comparison.
    // if (m_matrix == matrix) {
    //     return ;
    // }

    m_matrix = matrix ;
    m_outdatedMatrix = false ;

    // Decompose the matrix to rotation, translation and scale.
    // Put values in the fields.
}


Mind::Quaternion Transform::rotation() const {
    return m_rotation ;
}

float Transform::rotationOnX() const {
    return m_eulerAngles.get(Mind::Vector3f::X) ;
}

float Transform::rotationOnY() const {
    return m_eulerAngles.get(Mind::Vector3f::Y) ;
}

float Transform::rotationOnZ() const {
    return m_eulerAngles.get(Mind::Vector3f::Z) ;
}

Mind::Vector3f Transform::translation() const {
    return m_translation ;
}

float Transform::scale() const {
    return m_scale.get(Mind::Vector3f::X) ;
}

Mind::Vector3f Transform::scale3D() const {
    return m_scale ;
}

Mind::Matrix4x4f Transform::matrix() {
    if (m_outdatedMatrix) {
        // Recompose the matrix from the different component values.
        m_outdatedMatrix = false ;
    }

    return m_matrix ;
}