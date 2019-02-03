#ifndef __HOPE__FRAMEGRAPH_NODE__
#define __HOPE__FRAMEGRAPH_NODE__

#include <string>
#include <vector>
#include <interfaces/visitors/framegraph/IFrameGraphVisitant.hpp>

namespace Hope {

    class Entity ;

    /**
     * Base of nodes for the frame graph.
     * The frame graph can be used to make rendering passes, layers, post-prod
     * effects, etc.
     * The FrameGraphNode is usually not used as is in a frame graph as it does
     * nothing. However it can interesting to create a group of nodes in a
     * hierarchy.
     */
    class FrameGraphNode : public IFrameGraphVisitant {
        friend class Scene ;

        private:
            /**
             * Parent node.
             */
            FrameGraphNode* m_parent = nullptr ;

            /**
             * Children of the current node.
             */
            std::vector<FrameGraphNode*> m_children ;

            /**
             * Root entity of the scene.
             */
            Entity* m_sceneGraphRoot = nullptr ;

        public:
            /**
             * Create a new node instance.
             * @param   parent  Parent node of the new one.
             */
            FrameGraphNode(FrameGraphNode* parent = nullptr) ;

            /**
             * Destruction of the node instance.
             */
            virtual ~FrameGraphNode() ;

            /**
             * Accept the visitor.
             */
            void accept(IFrameGraphVisitor* visitor) override {
                specificAccept(visitor) ;
                generalAccept(visitor) ;
            }

            /**
             * Set the parent of the current node.
             */
            void setParent(FrameGraphNode* parent) ;

            /**
             * Get the parent of the current node.
             */
            const FrameGraphNode* parent() const ;

            /**
             * Get the list of children.
             */
            const std::vector<FrameGraphNode*>& children() const ;

            // Remove copy/move operations.
            FrameGraphNode(const FrameGraphNode& copied) = delete;
            FrameGraphNode(FrameGraphNode&& moved) = delete;
            FrameGraphNode& operator=(const FrameGraphNode& copied) = delete;
            FrameGraphNode& operator=(FrameGraphNode&& moved) = delete;

        protected:
            /**
             * Specific implementation for visitors.
             */
            virtual void specificAccept(IFrameGraphVisitor* /*visitor*/) {}

            /**
             * Root of the scene graph.
             */
            Entity* sceneRoot() ;

        private:
            /**
             * General method for accepting visitors.
             */
            void generalAccept(IFrameGraphVisitor* visitor) ;

            /**
             * Set the root entity of the scene graph.
             */
            void setSceneGraphRoot(Entity* root) ;

            /**
             * Add a child.
             * @param   newChild    Child node to add to the children list.
             * @return  true on success; false otherwise.
             */
            bool addChild(FrameGraphNode* newChild) ;

            /**
             * Remove a child.
             * @param   child       Child node to remove from the children list.
             * @return  true on success; false otherwise.
             */
            bool removeChild(FrameGraphNode* child) ;
    };
}

#endif
