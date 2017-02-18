/**
 * Mask to perform logical operations on Vector4f.
 */
class Mask {
	private:
		/** Inner vector of booleans (as floats). */
		float32x4_t m_inner ;


                              				  /** CONSTRUCTION / DESTRUCTION **/
        /** Prevent construction from integers. */
        Mask(const int& value) ;

        /**
         * Prevent affecting integer values.
         * @return  Nothing to use.
         */
        Mask& operator=(const int&) ;


    public:
        /**
         * Create an empty Mask.
         */
        Mask() ;

        /**
         * Create from four boolean values.
         * @param   b1  First value mask.
         * @param   b2  Second value mask.
         * @param   b3  Third value mask.
         * @param   b4  Fourth value mask.
         */
        Mask(
             const bool& b0,
             const bool& b1,
             const bool& b2,
             const bool& b3
            ) ;

        /**
         * Create from one boolean, applied to all components of the Mask.
         * @param   value   The boolean to apply to all values of the Mask.
         */
        Mask(const bool& value) ;

        /**
         * Create from inner type data.
         * @param   vec     The inner data to copy.
         */
        Mask(const float32x4_t& vec) ;


        /**
         * Create from a Mask used by integer Vector4.
         * @param   mask    Mask to cast.
         */
        Mask(const Vector4i::Mask& mask) ;

        /**
         * Create from a Mask used by integer Vector4.
         * @param   mask    Mask to cast.
         */
        Mask(const Vector4ui::Mask& mask) ;


        /**
		 * Destruction of the Mask.
		 */
        virtual ~Mask() ;


                                             				 /*** UTILITIES ***/
	protected:
		/**
		 * Copy the values on the Vector4f into an aligned array.
		 * @param 	array 	Output parameter in which values of the
		 *					Vector4f are stored.
		 * @param	count 	Amount of values to set, having
		 *					0 < count < 4.
		 */
		void get(AlignedArray4i& array) ;


	public:
        /**
         * Get one value from the mask.
         * @param   index   Index of the value to get (should be lower than
		 *					length).
         * @return  Value in the mask at the given index.
         */
        bool get(const unsigned int& index) ;

        /**
         * Get the length of the Mask.
         * @return  The length of the Mask.
         */
        size_t length() const ;


        /**
         * Size of the Mask.
         * @return  The length of the Mask.
         */
        static size_t size() ;

		/**
		 * Print the content of the Vector on the console output.
		 */
		void print() ;


                                             				 /*** OPERATORS ***/
                                        				/** AFFECT OPERATORS **/
        /**
         * Get the values from another Mask and put it in inner data.
         * @param   mask    The mask to copy.
         * @return  The current Mask once the vec is affected to its inner data.
         */
        Mask& operator=(const Mask& mask) ;

        /**
		* Affect the inner value of the Mask to the broadcasted one given as
		* parameter.
         * @param   value   The value to put in the Mask, to all its values.
         * @return  The current Mask once the value is affected to its inner
		 *			data.
         */
        Mask& operator=(const bool& value) ;

        /**
         * Affect the inner value to the Mask.
         * @param   vec     The value to put in the Mask.
         * @return  The current Mask once the vec is affected to its inner data.
         */
        Mask& operator=(const int32x4_t& vec) ;

        /**
         * Affect the inner value to the Mask.
         * @param   vec     The value to put in the Mask.
         * @return  The current Mask once the vec is affected to its inner data.
         */
        Mask& operator=(const float32x4_t& vec) ;

        /**
         * Affect the inner value to the Mask.
         * @param   mask    The value to put in the Mask.
         * @return  The current Mask once the vec is affected to its inner data.
         */
        Mask& operator=(const Vector4i::Mask& mask) ;

                                          				  /** CAST OPERATORS **/
        /**
         * Cast the current Mask to its inner data type.
         * @return  The inner data of the Mask.
         */
        operator int32x4_t() const ;

        /**
         * Cast the current Mask to a float32x4_t.
         * @return  The inner data of the Mask as a float32x4_t vector.
         */
        operator float32x4_t() const ;

        /**
         * Cast the current Mask to a Vector4i::Mask.
         * @return  The Vector4i::Mask version of the current Mask.
         */
        operator Vector4i::Mask() const ;

        /**
         * Cast the current Mask to a Vector4ui::Mask.
         * @return  The Vector4ui::Mask version of the current Mask.
         * @warning Be careful with negative values.
         */
        operator Vector4ui::Mask() const ;
} ;