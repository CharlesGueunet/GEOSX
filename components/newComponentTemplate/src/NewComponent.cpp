/*
 * NewComponent.cpp
 *
 *  Created on: Jun 8, 2016
 *      Author: settgast
 */

#include "NewComponent.hpp"

namespace geosx
{

NewComponent::NewComponent( std::string const & name,
                            WrapperCollection * const parent ):
    SolverBase(name,parent)
{

}

NewComponent::~NewComponent()
{
  // TODO Auto-generated destructor stub
}

void NewComponent::Registration( dataRepository::WrapperCollection& /*domain*/ )
{}


void NewComponent::TimeStep( real64 const& /*time_n*/,
               real64 const& /*dt*/,
               int32 const /*cycleNumber*/,
               dataRepository::WrapperCollection& /*domain*/ )
{}

//REGISTER_FACTORY( NewComponent, SolverBase, std::string )
REGISTER_CATALOGUE_ENTRY( SolverBase, NewComponent, std::string, dataRepository::WrapperCollection * const )

} /* namespace geosx */
