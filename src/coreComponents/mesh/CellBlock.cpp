/*
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Copyright (c) 2018, Lawrence Livermore National Security, LLC.
 *
 * Produced at the Lawrence Livermore National Laboratory
 *
 * LLNL-CODE-746361
 *
 * All rights reserved. See COPYRIGHT for details.
 *
 * This file is part of the GEOSX Simulation Framework.
 *
 * GEOSX is a free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License (as published by the
 * Free Software Foundation) version 2.1 dated February 1999.
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

/**
 * @file CellBlock.cpp
 *
 */

#include "CellBlock.hpp"

#include "NodeManager.hpp"

namespace geosx
{
using namespace dataRepository;
//using namespace constitutive;


CellBlock::CellBlock( string const & name, ManagedGroup * const parent ):
  ObjectManagerBase( name, parent ),
  m_CellBlockViewKeys(),
  m_numNodesPerElement(),
  m_numEdgesPerElement(),
  m_numFacesPerElement(),
  m_toNodesRelation(),
  m_toEdgesRelation(),
  m_toFacesRelation(),
  m_elementCenter(),
  m_elementVolume()
{
  RegisterViewWrapper(viewKeyStruct::nodeListString, &m_toNodesRelation, 0 );
  RegisterViewWrapper(viewKeyStruct::edgeListString, &m_toEdgesRelation, 0 );
  RegisterViewWrapper(viewKeyStruct::faceListString, &m_toFacesRelation, 0 );
  RegisterViewWrapper(viewKeyStruct::numNodesPerElementString, &m_numNodesPerElement, 0 );
  RegisterViewWrapper(viewKeyStruct::numEdgesPerElementString, &m_numEdgesPerElement, 0 );
  RegisterViewWrapper(viewKeyStruct::numFacesPerElementString, &m_numFacesPerElement, 0 );
  RegisterViewWrapper(viewKeyStruct::elementCenterString, &m_elementCenter, 0 );
  RegisterViewWrapper(viewKeyStruct::elementVolumeString, &m_elementVolume, 0 );

  m_toNodesRelation.resize(0,8);
  m_toEdgesRelation.resize(0,12);
  m_toFacesRelation.resize(0,6);
//  this->RegisterViewWrapper<mapPair_array>(keys::constitutiveMap).setSizedFromParent(1);

}


CellBlock::~CellBlock()
{}


void CellBlock::FillDocumentationNode()
{
  cxx_utilities::DocumentationNode * const docNode = this->getDocumentationNode();

  ObjectManagerBase::FillDocumentationNode();

  docNode->setName( this->getCatalogName() );
  docNode->setSchemaType( "Node" );
  docNode->setShortDescription( "an element region" );

//  docNode->AllocateChildNode( viewKeys.numNodesPerElement.Key(),
//                              viewKeys.numNodesPerElement.Key(),
//                              -1,
//                              "integer",
//                              "integer",
//                              "Number of Nodes Per Element",
//                              "Number of Nodes Per Element",
//                              "1",
//                              "",
//                              0,
//                              1,
//                              0 );

//  docNode->AllocateChildNode( viewKeys.nodeList.Key(),
//                              viewKeys.nodeList.Key(),
//                              -1,
//                              "integer_array",
//                              "integer_array",
//                              "nodelist",
//                              "nodelist",
//                              "8",
//                              "",
//                              0,
//                              1,
//                              0 );

//  docNode->AllocateChildNode( viewKeys.numFacesPerElement.Key(),
//                              viewKeys.numFacesPerElement.Key(),
//                              -1,
//                              "integer",
//                              "integer",
//                              "Number of Faces Per Element",
//                              "Number of Faces Per Element",
//                              "6",
//                              "",
//                              0,
//                              1,
//                              0 );

//  docNode->AllocateChildNode( keys::defaultMaterial,
//                              keys::defaultMaterial,
//                              -1,
//                              "string",
//                              "string",
//                              "Default Material Name",
//                              "Default Material Name",
//                              "REQUIRED",
//                              "",
//                              0,
//                              1,
//                              0 );
//
//
//  docNode->AllocateChildNode( keys::constitutiveMap,
//                              keys::constitutiveMap,
//                              -1,
//                              "mapPair_array",
//                              "mapPair_array",
//                              "Number of Nodes Per Element",
//                              "Number of Nodes Per Element",
//                              "1",
//                              "",
//                              1,
//                              0,
//                              0 );

//  docNode->AllocateChildNode( keys::numNodesPerElement,
//                              keys::numNodesPerElement,
//                              -1,
//                              "integer",
//                              "integer",
//                              "Number of Nodes Per Element",
//                              "Number of Nodes Per Element",
//                              "1",
//                              "",
//                              1,
//                              0 );


}

void CellBlock::ReadXML_PostProcess()
{
//  integer & numNodesPerElem = this->numNodesPerElement();
//  numNodesPerElem = 8;
  this->numNodesPerElement() = 8;
  this->numFacesPerElement() = 6;

}

//map<string,integer> CellBlock::SetConstitutiveMap( ManagedGroup const * domain
// )
//{
//  map<string,integer> counts;
//  view_rtype<mapPair_array> cellToConstitutiveMap =
// this->getData<mapPair_array>(keys::constitutiveMap);
//  ConstitutiveManager const * constitutiveManager =
// domain->GetGroup<ConstitutiveManager>(keys::ConstitutiveManager);
//
//  ConstitutiveManager::constitutiveMaps constitutiveMapPair =
// constitutiveManager->GetMaps( 1 );
//
//  string defaultMaterial = this->getData<string>(keys::defaultMaterial);
//  integer defaultMaterialIndex =
// constitutiveMapPair.second.at(defaultMaterial);
//
//
//  localIndex counter = 0;
//  for( localIndex k=0 ; k<this->size() ; ++k )
//  {
//    cellToConstitutiveMap[k] = std::make_pair( defaultMaterialIndex, counter++
// );
//    ++(counts.at(defaultMaterial));
//  }
//  return counts;
//}

R1Tensor CellBlock::GetElementCenter(localIndex k, const NodeManager& nodeManager) const
{

  r1_array const & X = nodeManager.referencePosition();
  arrayView1d<localIndex const> nodelist = m_toNodesRelation[k];
  R1Tensor elementCenter(0.0);
  for ( localIndex a = 0 ; a < numNodesPerElement() ; ++a)
  {
    const localIndex b = nodelist[a];
    elementCenter += X[b];
  }
  elementCenter /= numNodesPerElement();

  return elementCenter;
}


//
//void CellBlock::ViewPackingExclusionList( set<localIndex> & exclusionList ) const
//{
//  ObjectManagerBase::ViewPackingExclusionList(exclusionList);
//  exclusionList.insert(this->getWrapperIndex(this->viewKeys.nodeListString));
//  exclusionList.insert(this->getWrapperIndex(this->viewKeys.edgeListString));
//  exclusionList.insert(this->getWrapperIndex(this->viewKeys.elementRegionListString));
//  exclusionList.insert(this->getWrapperIndex(this->viewKeys.elementSubRegionListString));
//  exclusionList.insert(this->getWrapperIndex(this->viewKeys.elementListString));
//}
//
//
//
//
//int CellBlock::PackUpDownMapsSize( localIndex_array const & packList ) const
//{
//  int packedSize = 0;
//  buffer_unit_type * junk = nullptr;
//  packedSize += CommBufferOps::Pack<false>( junk,
//                                           m_nodeList,
//                                           packList,
//                                           this->m_localToGlobalMap,
//                                           m_nodeList.RelatedObjectLocalToGlobal() );
//  return packedSize;
//
//}
//
//
//int CellBlock::PackUpDownMaps( buffer_unit_type * & buffer,
//                               localIndex_array const & packList ) const
//{
//  int packedSize = 0;
//
//  packedSize += CommBufferOps::Pack<true>( buffer,
//                                           m_nodeList,
//                                           packList,
//                                           this->m_localToGlobalMap,
//                                           m_nodeList.RelatedObjectLocalToGlobal() );
//
//  return packedSize;
//}
//
//
//int CellBlock::UnpackUpDownMaps( buffer_unit_type const * & buffer,
//                                 localIndex_array const & packList )
//{
//  int unPackedSize = 0;
//
//  unPackedSize += CommBufferOps::Unpack( buffer,
//                                         m_nodeList,
//                                         packList,
//                                         this->m_globalToLocalMap,
//                                         m_nodeList.RelatedObjectGlobalToLocal() );
//
//  return unPackedSize;
//}

REGISTER_CATALOG_ENTRY( ObjectManagerBase, CellBlock, std::string const &, ManagedGroup * const )

}
