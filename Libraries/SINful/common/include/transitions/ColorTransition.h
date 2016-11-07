#ifndef __SIN_COLOR_TRANSITION__
#define __SIN_COLOR_TRANSITION__


#include <transitions/AbstractTransition.h>
#include <PixelColor.h>


namespace Sin {

    /**
     * @brief   Animated elements on their color.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/09
     */
    class ColorTransition : public AbstractTransition {
        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create a new AbstractTransition.
             * @param   last            Last of the while transition.
             * @param   interpolation   Interpolation used to compute the
             *                          intermediary values.
             */
            ColorTransition(const int& last, IInterpolation* interpolation) ;

            /**
             * @brief   Destruction of the ColorTransition.
             */
            virtual ~ColorTransition() ;

                                                             /*** UTILITIES ***/
            /**
             * @brief   Compute the transition from start to end property, for
             *          the current time in transition.
             * @param   start   Start value property to be animated.
             * @param   end     End value property to be animated.
             * @param   result  The value for the current time of the transition
             *                  property.
             */
            void compute(
                         const void* start,
                         const void* end,
                         void* result
                        ) ;
    } ;

} ;


#endif
