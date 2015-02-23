/*======================================================================

  This file is part of the elastix software.

  Copyright (c) University Medical Center Utrecht. All rights reserved.
  See src/CopyrightElastix.txt or http://elastix.isi.uu.nl/legal.php for
  details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE. See the above copyright notices for more information.

======================================================================*/


#ifndef __itkPCAMetric_ss_F_multithreaded_h
#define __itkPCAMetric_ss_F_multithreaded_h

#include "itkSmoothingRecursiveGaussianImageFilter.h"
#include "itkImageRandomCoordinateSampler.h"
#include "itkNearestNeighborInterpolateImageFunction.h"
#include "itkAdvancedImageToImageMetric.h"
#include "itkExtractImageFilter.h"

namespace itk
{
    template < class TFixedImage, class TMovingImage >
class PCAMetric_ss :
    public AdvancedImageToImageMetric< TFixedImage, TMovingImage>
{
public:

  /** Standard class typedefs. */
  typedef PCAMetric_ss   Self;
  typedef AdvancedImageToImageMetric<
    TFixedImage, TMovingImage >                   Superclass;
  typedef SmartPointer<Self>                      Pointer;
  typedef SmartPointer<const Self>                ConstPointer;

  typedef typename Superclass::FixedImageRegionType       FixedImageRegionType;
  typedef typename FixedImageRegionType::SizeType         FixedImageSizeType;

  /** Method for creation through the object factory. */
  itkNewMacro( Self );

  /** Run-time type information (and related methods). */
  itkTypeMacro( PCAMetric_ss, AdvancedImageToImageMetric );

  /** Set functions. */
  itkSetMacro( GridSize, FixedImageSizeType );
  itkSetMacro( TransformIsStackTransform, bool );
  itkSetMacro( NumEigenValues, unsigned int );

  /** Typedefs from the superclass. */
  typedef typename
    Superclass::CoordinateRepresentationType              CoordinateRepresentationType;
  typedef typename Superclass::MovingImageType            MovingImageType;
  typedef typename Superclass::MovingImagePixelType       MovingImagePixelType;
  typedef typename Superclass::MovingImageConstPointer    MovingImageConstPointer;
  typedef typename Superclass::FixedImageType             FixedImageType;
  typedef typename Superclass::FixedImageConstPointer     FixedImageConstPointer;
  typedef typename Superclass::TransformType              TransformType;
  typedef typename Superclass::TransformPointer           TransformPointer;
  typedef typename Superclass::InputPointType             InputPointType;
  typedef typename Superclass::OutputPointType            OutputPointType;
  typedef typename Superclass::TransformParametersType    TransformParametersType;
  typedef typename Superclass::TransformJacobianType      TransformJacobianType;
  typedef typename Superclass::InterpolatorType           InterpolatorType;
  typedef typename Superclass::InterpolatorPointer        InterpolatorPointer;
  typedef typename Superclass::RealType                   RealType;
  typedef typename Superclass::GradientPixelType          GradientPixelType;
  typedef typename Superclass::GradientImageType          GradientImageType;
  typedef typename Superclass::GradientImagePointer       GradientImagePointer;
  typedef typename Superclass::GradientImageFilterType    GradientImageFilterType;
  typedef typename Superclass::GradientImageFilterPointer GradientImageFilterPointer;
  typedef typename Superclass::FixedImageMaskType         FixedImageMaskType;
  typedef typename Superclass::FixedImageMaskPointer      FixedImageMaskPointer;
  typedef typename Superclass::MovingImageMaskType        MovingImageMaskType;
  typedef typename Superclass::MovingImageMaskPointer     MovingImageMaskPointer;
  typedef typename Superclass::MeasureType                MeasureType;
  typedef typename Superclass::DerivativeType             DerivativeType;
  typedef typename Superclass::ParametersType             ParametersType;
  typedef typename Superclass::FixedImagePixelType        FixedImagePixelType;
  typedef typename Superclass::MovingImageRegionType      MovingImageRegionType;
  typedef typename Superclass::ImageSamplerType           ImageSamplerType;
  typedef typename Superclass::ImageSamplerPointer        ImageSamplerPointer;
  typedef typename Superclass::ImageSampleContainerType   ImageSampleContainerType;
  typedef typename
    Superclass::ImageSampleContainerPointer               ImageSampleContainerPointer;
  typedef typename Superclass::FixedImageLimiterType      FixedImageLimiterType;
  typedef typename Superclass::MovingImageLimiterType     MovingImageLimiterType;
  typedef typename
    Superclass::FixedImageLimiterOutputType               FixedImageLimiterOutputType;
 typedef typename
    Superclass::MovingImageLimiterOutputType              MovingImageLimiterOutputType;
  typedef typename
    Superclass::MovingImageDerivativeScalesType           MovingImageDerivativeScalesType;
  typedef typename DerivativeType::ValueType        DerivativeValueType;
  typedef typename Superclass::ThreaderType                    ThreaderType;
  typedef typename Superclass::ThreadInfoType                  ThreadInfoType;

  typedef vnl_matrix< RealType >                  MatrixType;
  typedef vnl_matrix< DerivativeValueType > DerivativeMatrixType;

  /** The fixed image dimension. */
  itkStaticConstMacro( FixedImageDimension, unsigned int,
    FixedImageType::ImageDimension );

  /** The moving image dimension. */
  itkStaticConstMacro( MovingImageDimension, unsigned int,
    MovingImageType::ImageDimension );

  /** Get the value for single valued optimizers. */
  virtual MeasureType GetValue( const TransformParametersType & parameters ) const;

  /** Get the derivatives of the match measure. */
  virtual void GetDerivative(const TransformParametersType & parameters,
	  DerivativeType & derivative ) const;

  /** Get value and derivatives for multiple valued optimizers. */
  void GetValueAndDerivativeSingleThreaded(const TransformParametersType& parameters,
      MeasureType& Value, DerivativeType& Derivative) const;

  virtual void GetValueAndDerivative(const TransformParametersType& parameters,
      MeasureType& Value, DerivativeType& Derivative) const;

  /** Initialize the Metric by making sure that all the components
   *  are present and plugged together correctly.
   * \li Call the superclass' implementation.   */

  virtual void Initialize(void) throw ( ExceptionObject );

protected:
  PCAMetric_ss();
  virtual ~PCAMetric_ss();
  void PrintSelf( std::ostream& os, Indent indent ) const;

  /** Protected Typedefs ******************/

  /** Typedefs inherited from superclass */
  typedef typename Superclass::FixedImageIndexType                FixedImageIndexType;
  typedef typename Superclass::FixedImageIndexValueType           FixedImageIndexValueType;
  typedef typename Superclass::MovingImageIndexType               MovingImageIndexType;
  typedef typename Superclass::FixedImagePointType                FixedImagePointType;
  typedef typename itk::ContinuousIndex< CoordinateRepresentationType, FixedImageDimension >
                                                                  FixedImageContinuousIndexType;
  typedef typename Superclass::MovingImagePointType               MovingImagePointType;
  typedef typename Superclass::MovingImageContinuousIndexType     MovingImageContinuousIndexType;
  typedef typename Superclass::BSplineInterpolatorType            BSplineInterpolatorType;
  typedef typename Superclass::CentralDifferenceGradientFilterType CentralDifferenceGradientFilterType;
  typedef typename Superclass::MovingImageDerivativeType          MovingImageDerivativeType;
  typedef typename Superclass::NonZeroJacobianIndicesType         NonZeroJacobianIndicesType;

  /** Computes the innerproduct of transform Jacobian with moving image gradient.
   * The results are stored in imageJacobian, which is supposed
   * to have the right size (same length as Jacobian's number of columns). */
  void EvaluateTransformJacobianInnerProduct(
    const TransformJacobianType & jacobian,
    const MovingImageDerivativeType & movingImageDerivative,
    DerivativeType & imageJacobian) const;

  struct PCAMetricssMultiThreaderParameterType
  {
    Self * m_Metric;
  };

  PCAMetricssMultiThreaderParameterType m_PCAMetricssThreaderParameters;

  struct PCAMetricssGetSamplesPerThreadStruct
  {
    SizeValueType   st_NumberOfPixelsCounted;
    MatrixType      st_DataBlock;
    std::vector< FixedImagePointType > st_ApprovedSamples;
    DerivativeType st_Derivative;
  };

  itkPadStruct( ITK_CACHE_LINE_ALIGNMENT, PCAMetricssGetSamplesPerThreadStruct,
    PaddedPCAMetricssGetSamplesPerThreadStruct );

  itkAlignedTypedef( ITK_CACHE_LINE_ALIGNMENT,
                     PaddedPCAMetricssGetSamplesPerThreadStruct,
                     AlignedPCAMetricssGetSamplesPerThreadStruct );

  mutable AlignedPCAMetricssGetSamplesPerThreadStruct * m_PCAMetricssGetSamplesPerThreadVariables;
  mutable ThreadIdType  m_PCAMetricssGetSamplesPerThreadVariablesSize;


  /** Get value and derivatives for each thread. */
  inline void ThreadedGetSamples( ThreadIdType threadID );

  inline void ThreadedComputeDerivative( ThreadIdType threadID );

  /** Gather the values and derivatives from all threads */
  inline void AfterThreadedGetSamples( MeasureType & value ) const;

  inline void AfterThreadedComputeDerivative( DerivativeType & derivative ) const;

  /** Helper function to launch the threads. */
  static ITK_THREAD_RETURN_TYPE GetSamplesThreaderCallback( void * arg );
  static ITK_THREAD_RETURN_TYPE ComputeDerivativeThreaderCallback( void * arg );

  /** Helper functions to launch the threads. */
  void LaunchGetSamplesThreaderCallback( void ) const;
  void LaunchComputeDerivativeThreaderCallback( void ) const;

  /** Initialize some multi-threading related parameters. */
  virtual void InitializeThreadingParameters( void ) const;

private:
  PCAMetric_ss(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  unsigned int m_G;
  unsigned int m_LastDimIndex;

  /** Bool to determine if we want to subtract the mean derivate from the derivative elements. */
  bool m_SubtractMean;

  /** GridSize of B-spline transform. */
  FixedImageSizeType m_GridSize;

  /** Bool to indicate if the transform used is a stacktransform. Set by elx files. */
  bool m_TransformIsStackTransform;

  /** Integer to indicate how many eigenvalues you want to use in the metric */
  unsigned int m_NumEigenValues;

  /** Matrices, needed for derivative calculation */
  mutable std::vector< unsigned int > m_PixelStartIndex;
  mutable MatrixType m_Atmm;
  mutable DerivativeMatrixType m_vSAtmm;
  mutable DerivativeMatrixType m_CSv;
  mutable DerivativeMatrixType m_Sv;
  mutable DerivativeMatrixType m_vdSdmu_part1;

}; // end class PCAMetric_F_multithreaded

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkPCAMetric_ss_F_multithreaded.hxx"
#endif

#endif // end #ifndef __itkPCAMetric_F_multithreaded_h
