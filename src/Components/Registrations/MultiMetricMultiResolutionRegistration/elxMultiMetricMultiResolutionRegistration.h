#ifndef __elxMultiMetricMultiResolutionRegistration_H__
#define __elxMultiMetricMultiResolutionRegistration_H__

#include "itkMultiMetricMultiResolutionImageRegistrationMethod.h"

#include "elxIncludes.h"

namespace elastix
{
using namespace itk;

	/**
	 * \class MultiMetricMultiResolutionRegistration
	 * \brief A registration framework based on the itk::MultiMetricMultiResolutionImageRegistrationMethod.
	 *
	 * This MultiMetricMultiResolutionRegistration gives a framework for registration with a
	 * multi-resolution approach, using multiple metrics. The metrics can use the same pair of images/
   * image pyramids/interpolators/masks, but also different pairs of fixed/moving images etc. 
   * If the metrics use the same moving image and the same moving image pyramid, they can use the
   * same interpolator. If multiple moving images are used, enter multiple interpolators, possibly 
   * of the same type:
   * Like this for example:
   * (Interpolator "BSplineInterpolator" "BSplineInterpolator")
   *
   * Note, that the number of metrics should always be larger than or equal to the number
   * if fixed/moving images, interpolators, image pyramids etc.
   *
	 *
	 * The parameters used in this class are:
	 * \parameter Registration: Select this registration framework as follows:\n
	 *		<tt>(Registration "MultiMetricMultiResolutionRegistration")</tt>
	 * \parameter NumberOfResolutions: the number of resolutions used. \n
	 *		example: <tt>(NumberOfResolutions 4)</tt> \n
	 *		The default is 3.
   * \parameter MetricWeight<i>: The weight for the i-th metric, in each resolution \n
	 *		example: <tt>(MetricWeight0 0.5 0.5 0.8)</tt> \n
   *		example: <tt>(MetricWeight1 0.5 0.5 0.2)</tt> \n
	 *		The default is 1.0.
   *
	 * \ingroup Registrations
	 */

	template <class TElastix>
		class MultiMetricMultiResolutionRegistration :
		public	
			MultiMetricMultiResolutionImageRegistrationMethod<
      ITK_TYPENAME RegistrationBase<TElastix>::FixedImageType,
      ITK_TYPENAME RegistrationBase<TElastix>::MovingImageType >,
		public
			RegistrationBase<TElastix>
	{
	public:

		/** Standard ITK: Self */
		typedef MultiMetricMultiResolutionRegistration			Self;

    /** Standard ITK: Superclasses */
		typedef	MultiMetricMultiResolutionImageRegistrationMethod<
      typename RegistrationBase<TElastix>::FixedImageType,
      typename RegistrationBase<TElastix>::MovingImageType >
                                                        Superclass1;
		typedef RegistrationBase<TElastix>									Superclass2;

    /** Standard ITK: SmartPointers */
		typedef SmartPointer<Self>													Pointer;
		typedef SmartPointer<const Self>										ConstPointer;
		
		/** Method for creation through the object factory. */
		itkNewMacro(Self);
		
		/** Run-time type information (and related methods). */
		itkTypeMacro( MultiMetricMultiResolutionRegistration,
      MultiMetricMultiResolutionImageRegistrationMethod );

		/** Name of this class.
		 * Use this name in the parameter file to select this specific registration framework. \n
		 * example: <tt>(Registration "MultiMetricMultiResolutionRegistration")</tt>\n
		 */
		elxClassNameMacro( "MultiMetricMultiResolutionRegistration" );
		
		/** Typedef's inherited from Superclass1. */
		
		/**  Type of the Fixed image. */
		typedef typename Superclass1::FixedImageType						FixedImageType;
		typedef typename Superclass1::FixedImageConstPointer		FixedImageConstPointer;
		typedef typename Superclass1::FixedImageRegionType			FixedImageRegionType;
		
		/**  Type of the Moving image. */
		typedef typename Superclass1::MovingImageType						MovingImageType;
		typedef typename Superclass1::MovingImageConstPointer		MovingImageConstPointer;
		
		/**  Type of the metric. */
		typedef typename Superclass1::MetricType								MetricType;
		typedef typename Superclass1::MetricPointer							MetricPointer;
		
		/**  Type of the Transform . */
		typedef typename Superclass1::TransformType							TransformType;
		typedef typename Superclass1::TransformPointer					TransformPointer;
		
		/**  Type of the Interpolator. */
		typedef typename Superclass1::InterpolatorType					InterpolatorType;
		typedef typename Superclass1::InterpolatorPointer				InterpolatorPointer;
		
		/**  Type of the optimizer. */
		typedef typename Superclass1::OptimizerType							OptimizerType;
    typedef typename Superclass1::OptimizerPointer					OptimizerPointer;
		
		/** Type of the Fixed image multiresolution pyramid. */
		typedef typename Superclass1::FixedImagePyramidType			FixedImagePyramidType;
		typedef typename Superclass1::FixedImagePyramidPointer	FixedImagePyramidPointer;
		
		/** Type of the moving image multiresolution pyramid. */
		typedef typename Superclass1::MovingImagePyramidType		MovingImagePyramidType ;
		typedef typename Superclass1::MovingImagePyramidPointer	MovingImagePyramidPointer;
		
		/** Type of the Transformation parameters. This is the same type used to
		 *  represent the search space of the optimization algorithm. */
		typedef typename Superclass1::ParametersType						ParametersType;

    /** The CombinationMetric type, which is used internally by the Superclass1 */
    typedef typename Superclass1::CombinationMetricType	 	  CombinationMetricType;
		typedef typename Superclass1::CombinationMetricPointer  CombinationMetricPointer;
		
		/** Typedef's from Elastix. */
		typedef typename Superclass2::ElastixType						ElastixType;
		typedef typename Superclass2::ElastixPointer				ElastixPointer;
		typedef typename Superclass2::ConfigurationType			ConfigurationType;
		typedef typename Superclass2::ConfigurationPointer	ConfigurationPointer;
		typedef typename Superclass2::RegistrationType			RegistrationType;
		typedef typename Superclass2::RegistrationPointer		RegistrationPointer;
		typedef typename Superclass2::ITKBaseType						ITKBaseType;
    typedef typename Superclass2::UseMaskErosionArrayType UseMaskErosionArrayType;

    /** Get	the dimension of the fixed image. */
		itkStaticConstMacro( FixedImageDimension, unsigned int, Superclass2::FixedImageDimension );
		/** Get	the dimension of the moving image. */
		itkStaticConstMacro( MovingImageDimension, unsigned int, Superclass2::MovingImageDimension );

    /** Execute stuff before the actual registration:
		 * \li Connect all components to the registration framework.
		 * \li Set the number of resolution levels.
		 * \li Set the fixed image regions. 
     * \li Add the sub metric columns to the iteration info object  */
		virtual void BeforeRegistration(void);

    /** Execute stuff before each resolution:
		 * \li Update masks with an erosion. 
     * \li Set the metric weights */
    virtual void BeforeEachResolution(void);

    /** Execute stuff after each iteration 
     * \li Print the latest computed submetric values to screen  */
    virtual void AfterEachIteration(void);
		
	protected:

		/** The constructor. */
    MultiMetricMultiResolutionRegistration(){};
		/** The destructor. */
		virtual ~MultiMetricMultiResolutionRegistration() {};
    
    /** Typedef for timer.*/
		typedef tmr::Timer					TimerType;
		/** Typedef for timer.*/
		typedef TimerType::Pointer	TimerPointer;

    /** Typedef's for mask support. */
    typedef typename Superclass2::MaskPixelType                   MaskPixelType;
    typedef typename Superclass2::FixedMaskImageType              FixedMaskImageType;
    typedef typename Superclass2::MovingMaskImageType             MovingMaskImageType;
    typedef typename Superclass2::FixedMaskImagePointer           FixedMaskImagePointer;
    typedef typename Superclass2::MovingMaskImagePointer          MovingMaskImagePointer;
		typedef typename Superclass2::FixedMaskSpatialObjectType      FixedMaskSpatialObjectType;
		typedef typename Superclass2::MovingMaskSpatialObjectType     MovingMaskSpatialObjectType;
		typedef typename Superclass2::FixedMaskSpatialObjectPointer   FixedMaskSpatialObjectPointer;
		typedef typename Superclass2::MovingMaskSpatialObjectPointer  MovingMaskSpatialObjectPointer;
    
    /** Function to update masks. */
		void UpdateFixedMasks( unsigned int level );
    void UpdateMovingMasks( unsigned int level );

		/** Read the components from m_Elastix and set them in the Registration class. */
		virtual void SetComponents(void);		
		
	private:

		/** The private constructor. */
		MultiMetricMultiResolutionRegistration( const Self& );	// purposely not implemented
		/** The private copy constructor. */
		void operator=( const Self& );							// purposely not implemented

	}; // end class MultiMetricMultiResolutionRegistration


} // end namespace elastix

#ifndef ITK_MANUAL_INSTANTIATION
#include "elxMultiMetricMultiResolutionRegistration.hxx"
#endif

#endif // end #ifndef __elxMultiMetricMultiResolutionRegistration_H__