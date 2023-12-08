// TransportFunctions.h

#pragma once

#include "../database/Database.h"
#include "../models/PublicTransport.h"

void displayMenu();
void bookTransport(Database& Db, PublicTransport::TransportType transportType);
void orderTaxi(Database& Db);
void handleTaxiSelect(Database& Db);
void handleBusSelect(Database& Db);
void handleTrolleyBusSelect(Database& Db);
void createAndAddBus(Database& Db, int isLogged);
void createAndAddTrolleyBus(Database& Db, int isLogged);
void createAndAddTaxi(Database& Db, int isLogged);
void createAndAddStop(Database& Db, int isLogged);
void createAndAddRoute(Database& Db, int isLogged);
void createAndAddSchedule(Database& Db, int isLogged);
void createAndSetRoutePrice(Database& Db, int isLogged);
void createAndLinkTransportToRoute(Database& Db, int isLogged);
void createAndLinkStopToRoute(Database& Db, int isLogged);
void handleAdminActions(Database& Db);
