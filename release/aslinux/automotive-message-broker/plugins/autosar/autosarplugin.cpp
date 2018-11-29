/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2016  AS <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */
/* ============================ [ INCLUDES  ] ====================================================== */
#include <boost/assert.hpp>
#include <glib.h>
#include <deque>

#include <vehicleproperty.h>
#include <listplusplus.h>

#include <logger.h>
#include <ambplugin.h>

#include <pthread.h>

#include "autosarplugin.h"

using namespace std;
/* ============================ [ MACROS    ] ====================================================== */
#define COM_SID_VehicleSpeed                     0
#define COM_SID_EngineSpeed                      1
/* ============================ [ TYPES     ] ====================================================== */
typedef uint16_t Com_SignalIdType;
/* ============================ [ DECLARES  ] ====================================================== */
extern "C" void* EcuM_Init(void*);
extern "C" uint8_t Com_SendSignal(Com_SignalIdType SignalId, const void *SignalDataPtr);
extern "C" uint8_t Com_ReceiveSignal(Com_SignalIdType SignalId, void* SignalDataPtr);
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
static gboolean timeoutCallback(gpointer data)
{
	AUTOSARSource* src = (AUTOSARSource*)data;

	src->MainFunction();

	return true;
}
/* ============================ [ FUNCTIONS ] ====================================================== */
extern "C" void StartupHook(void)
{

}
/* library exported function for plugin loader */
extern "C" void create(AbstractRoutingEngine* routingengine, std::map<std::string, std::string> config)
{
#if 0
	new AUTOSARSource(routingengine, config);
#else
	pthread_t thread;
	pthread_create((pthread_t*)&(thread),NULL,EcuM_Init,NULL);
#endif
	new AUTOSARSink(routingengine, config);
}


AUTOSARSource::AUTOSARSource(AbstractRoutingEngine* re, map<string, string> config) :
	AbstractSource(re, config)
{

	int delay = 1000;

	if(config.find("delay") != config.end())
	{
		delay = boost::lexical_cast<int>(config["delay"]);
	}

	g_timeout_add(delay, timeoutCallback, this );

	addPropertySupport(VehicleProperty::EngineSpeed, Zone::None);
	addPropertySupport(VehicleProperty::VehicleSpeed, Zone::None);

	pthread_create((pthread_t*)&(thread),NULL,EcuM_Init,NULL);

	DebugOut()<<"AUTOSARSource: AS COM STACK ON LINE!"<<endl;
}

AUTOSARSource::~AUTOSARSource()
{

}

AsyncPropertyReply* AUTOSARSource::setProperty(AsyncSetPropertyRequest request)
{
	AsyncPropertyReply *reply = new AsyncPropertyReply(request);
	reply->success = false;

	reply->error = AsyncPropertyReply::InvalidOperation;
	reply->completed(reply);
	return reply;
}

void AUTOSARSource::subscribeToPropertyChanges(VehicleProperty::Property property)
{
	mRequests.push_back(property);
}

void AUTOSARSource::unsubscribeToPropertyChanges(VehicleProperty::Property property)
{
	if(contains(mRequests,property))
		removeOne(&mRequests, property);
}

void AUTOSARSource::MainFunction()
{
	uint16_t v;

	Com_ReceiveSignal(COM_SID_VehicleSpeed,&v);
	vel.setValue(v);
	vel.sequence++;
	routingEngine->updateProperty(&vel, uuid());

	Com_ReceiveSignal(COM_SID_EngineSpeed,&v);
	eng.setValue(v);
	eng.sequence++;
	routingEngine->updateProperty(&eng, uuid());
}
void AUTOSARSource::getRangePropertyAsync(AsyncRangePropertyReply *reply)
{

}

void AUTOSARSource::getPropertyAsync(AsyncPropertyReply *reply)
{
	DebugOut()<<"AUTOSARSource: getPropertyAsync called for property: "<<reply->property<<endl;
	if(reply->property == VehicleProperty::VehicleSpeed)
	{
		VehicleProperty::VehicleSpeedType temp(120);
		reply->value = &temp;
		reply->success = true;
		reply->completed(reply);
	}
	else if(reply->property == VehicleProperty::EngineSpeed)
	{
		VehicleProperty::EngineSpeedType temp(120);
		reply->value = &temp;
		reply->success = true;
		reply->completed(reply);
	}
	else
	{
		reply->success=false;
		reply->error = AsyncPropertyReply::InvalidOperation;
		reply->completed(reply);
	}
}

PropertyList AUTOSARSource::supported()
{
	//DebugOut()<<"AUTOSARSource: supported " <<endl;
	return mSupported;
}

int AUTOSARSource::supportedOperations()
{
	DebugOut()<<"AUTOSARSource: supportedOperations " <<endl;
	return Get | Set | GetRanged;;
}

void AUTOSARSource::addPropertySupport(VehicleProperty::Property property, Zone::Type zone)
{
	mSupported.push_back(property);

	Zone::ZoneList zones;

	zones.push_back(zone);

	PropertyInfo info(0, zones);

	propertyInfoMap[property] = info;
}


AUTOSARSink::AUTOSARSink(AbstractRoutingEngine* engine, map<string, string> config): AbstractSink(engine, config)
{
	routingEngine->subscribeToProperty(VehicleProperty::Heater, this);
	routingEngine->subscribeToProperty(VehicleProperty::Defrost, this);

	supportedChanged(engine->supported());
}


PropertyList AUTOSARSink::subscriptions()
{

}

void AUTOSARSink::supportedChanged(const PropertyList & supportedProperties)
{
	DebugOut()<<"Support changed!"<<endl;

	if(contains(supportedProperties, VehicleProperty::Heater))
	{
		AsyncPropertyRequest heaterRequest;
		heaterRequest.property = VehicleProperty::Heater;
		heaterRequest.completed = [](AsyncPropertyReply* reply)
		{
			if(!reply->success)
				DebugOut(DebugOut::Error)<<"Heater Async request failed ("<<reply->error<<")"<<endl;
			else
				DebugOut(0)<<"Heater Async request completed: "<<reply->value->toString()<<endl;
			delete reply;
		};

		routingEngine->getPropertyAsync(heaterRequest);
	}

	if(contains(supportedProperties, VehicleProperty::Defrost))
	{
		AsyncPropertyRequest defrostRequest;
		defrostRequest.property = VehicleProperty::Defrost;
		defrostRequest.completed = [](AsyncPropertyReply* reply)
		{
			if(!reply->success)
				DebugOut(DebugOut::Error)<<"Defrost Async request failed ("<<reply->error<<")"<<endl;
			else
				DebugOut(0)<<"Defrost Async request completed: "<<reply->value->toString()<<endl;
			delete reply;
		};

		routingEngine->getPropertyAsync(defrostRequest);
	}

	auto getRangedCb = [](gpointer data)
	{
		AbstractRoutingEngine* routingEngine = (AbstractRoutingEngine*)data;

		AsyncRangePropertyRequest vehicleSpeedFromLastWeek;

		vehicleSpeedFromLastWeek.timeBegin = amb::Timestamp::instance()->epochTime() - 10;
		vehicleSpeedFromLastWeek.timeEnd = amb::Timestamp::instance()->epochTime();

		PropertyList requestList;
		requestList.push_back(VehicleProperty::Heater);
		requestList.push_back(VehicleProperty::Defrost);

		vehicleSpeedFromLastWeek.properties = requestList;
		vehicleSpeedFromLastWeek.completed = [](AsyncRangePropertyReply* reply)
		{
			std::list<AbstractPropertyType*> values = reply->values;
			for(auto itr = values.begin(); itr != values.end(); itr++)
			{
				auto val = *itr;
				DebugOut(1) <<"Value from past: (" << val->name << "): " << val->toString()
						   <<" time: " << val->timestamp << " sequence: " << val->sequence << endl;
			}

			delete reply;
		};

		routingEngine->getRangePropertyAsync(vehicleSpeedFromLastWeek);

		return 0;
	};

	g_timeout_add(10000, getRangedCb, routingEngine);
}

void AUTOSARSink::propertyChanged(AbstractPropertyType *value)
{
	VehicleProperty::Property property = value->name;
	DebugOut()<<property<<" value: "<<value->toString()<<endl;
}

