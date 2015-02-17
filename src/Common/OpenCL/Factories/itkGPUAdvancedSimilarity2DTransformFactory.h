/*=========================================================================
 *
 *  Copyright UMC Utrecht and contributors
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef __itkGPUAdvancedSimilarity2DTransformFactory_h
#define __itkGPUAdvancedSimilarity2DTransformFactory_h

#include "itkGPUObjectFactoryBase.h"
#include "itkGPUAdvancedSimilarity2DTransform.h"

namespace itk
{
/** \class GPUAdvancedSimilarity2DTransformFactory
 * \brief Object Factory implementation for GPUAdvancedSimilarity2DTransform
 *
 * \author Denis P. Shamonin and Marius Staring. Division of Image Processing,
 * Department of Radiology, Leiden, The Netherlands
 *
 * \note This work was funded by the Netherlands Organisation for
 * Scientific Research (NWO NRG-2010.02 and NWO 639.021.124).
 *
 */
template< typename NDimentions >
class GPUAdvancedSimilarity2DTransformFactory2 : public GPUObjectFactoryBase< NDimentions >
{
public:

  typedef GPUAdvancedSimilarity2DTransformFactory2 Self;
  typedef GPUObjectFactoryBase< NDimentions >      Superclass;
  typedef SmartPointer< Self >                     Pointer;
  typedef SmartPointer< const Self >               ConstPointer;

  /** Return a descriptive string describing the factory. */
  const char * GetDescription() const { return "A Factory for GPUAdvancedSimilarity2DTransform"; }

  /** Method for class instantiation. */
  itkFactorylessNewMacro( Self );

  /** Run-time type information (and related methods). */
  itkTypeMacro( GPUAdvancedSimilarity2DTransformFactory2, GPUObjectFactoryBase );

  /** Register one factory of this type. */
  static void RegisterOneFactory();

  /** Operator() to register override. */
  template< typename TType >
  void operator()( void )
  {
    this->RegisterOverride(
      typeid( AdvancedSimilarity2DTransform< TType > ).name(),
      typeid( GPUAdvancedSimilarity2DTransform< TType > ).name(),
      "GPU AdvancedSimilarity2DTransform override", true,
      CreateObjectFunction< GPUAdvancedSimilarity2DTransform< TType > >::New()
      );
  }


protected:

  GPUAdvancedSimilarity2DTransformFactory2();
  virtual ~GPUAdvancedSimilarity2DTransformFactory2() {}

  /** Typedef for real type list. */
  typedef typelist::MakeTypeList< float, double >::Type RealTypeList;

  /** Register methods for 2D. */
  virtual void Register2D();

private:

  GPUAdvancedSimilarity2DTransformFactory2( const Self & ); // purposely not implemented
  void operator=( const Self & );                           // purposely not implemented

};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkGPUAdvancedSimilarity2DTransformFactory.hxx"
#endif

#endif /* __itkGPUAdvancedSimilarity2DTransformFactory_h */