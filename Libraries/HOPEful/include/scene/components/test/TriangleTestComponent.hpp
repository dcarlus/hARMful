#ifndef __HOPE__TRIANGLE_TEST_MESH_COMPONENT__
#define __HOPE__TRIANGLE_TEST_MESH_COMPONENT__

#include <array>
#include <scene/components/Component.hpp>
#include <HopeAPI.hpp>

#ifdef OGL
    #include <GL/glew.h>
    namespace API = Hope::GL ;
#endif

namespace Hope {
    class ISceneGraphVisitor ;

    /**
     * Component that contains a triangle in 2 dimensions. Base test for setting
     * up OpenGL step-by-step.
     */
    class TriangleTestComponent final : public Component {
        public:
            static const unsigned int AmountVertices = 3 ;
            static const unsigned int AmountPositionData = 2 ;
            static const unsigned int AmountColorData = 3 ;
            static const unsigned int DataByVertex = AmountPositionData + AmountColorData ;
            static const unsigned int TotalData = AmountVertices * DataByVertex ;

        private:
            /**
             * Vertex array index of the triangle.
             */
            unsigned int m_vertexArrayIndex = 0 ;

            /**
             * Index buffer of the triangle.
             */
            unsigned int m_indexBuffer = 0 ;

        public:
            /**
             * Create a new TriangleTestComponent.
             */
            TriangleTestComponent() ;

            /**
             * Accept the visitor.
             */
            void accept(ISceneGraphVisitor* visitor) override ;

            /**
             * Render the TriangleTestComponent.
             */
            void render() ;

            /**
             * To know if the component can be shared by several entities.
             * @return  true, the TriangleTestComponent can be shared.
             */
            bool isShareable() const override ;
    } ;
}

#endif  // __HOPE__TRIANGLE_TEST_MESH_COMPONENT__