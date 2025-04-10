/*
Copyright 2019 Adobe. All rights reserved.
This file is licensed to you under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License. You may obtain a copy
of the License at http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
OF ANY KIND, either express or implied. See the License for the specific language
governing permissions and limitations under the License.
*/

//! @file system.h
//! @brief Core and system application type
//! @author Galen Helfter - Adobe
//! @date 20190616
//! @copyright Adobe. All rights reserved.

/******************************************************************************
 * The system class's purpose is to track connector events related to other connections.
 * It handles events for when connections are established and closed but also provided an
 * event for providing details for each new available connection such as what features the
 * other connection supports or which version of the connector framework the other connection
 * is using.
 *
 * The event for this is mRecvConnectionContext and this information is provided through a
 * connection_schema instance.
 ******************************************************************************/

#pragma once

#include <substance/connector/framework/application.h>

namespace Substance
{
namespace Connector
{
namespace Framework
{
class System : public Application
{
public:
	//! @brief Constructor
	System();

	//! @brief Destructor
	~System() override;

	//! @brief Run system application preinitialization steps
	void preInit() override;

	//! @brief Run system application postinitialization
	void postInit() override;

	//! @brief Run system application postshutdown
	void postShutdown() override;

	//! @brief Returns a vector of supported feature or application IDs
	const std::vector<substance_connector_uuid_t> getFeatureIds() override;

	//! @brief Callback handler to send connection context
	//! @parameter incoming_connection_context is the conenction id for the new connection
	static void connectionEstablished(unsigned int incoming_connection_context,
									  const substance_connector_uuid_t* uuid,
									  const char* message);

public:
	static const substance_connector_uuid_t sConnectionEstablishedId;
	static const substance_connector_uuid_t sConnectionClosedId;
	static const substance_connector_uuid_t sConnectionUpdateContextId;

	MessageCallback mRecvConnectionEstablished;
	MessageCallback mRecvConnectionClosed;
	MessageCallback mRecvConnectionContext;

	size_t mUserData;
};
} // namespace Framework
} // namespace Connector
} // namespace Substance
