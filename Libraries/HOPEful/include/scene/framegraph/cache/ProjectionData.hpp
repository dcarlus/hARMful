#ifndef __HOPE__PROJECTION_DATA__
#define __HOPE__PROJECTION_DATA__

namespace Hope {
    class ViewportNode ;

    /**
     * Data thet are useful to correctly set up view/projection matrices.
     */
    struct ProjectionData {
        /**
         * Are the data initialized?
         */
        bool initialized = false ;

        /**
         * Last viewport to be updated.
         */
        ViewportNode* lastViewport = nullptr ;

        /**
         * Absolute width in pixels of the draw area.
         */
        float absoluteAreaWidth ;

        /**
         * Absolute height in pixels of the draw area.
         */
        float absoluteAreaHeight ;
    } ;
}

#endif
