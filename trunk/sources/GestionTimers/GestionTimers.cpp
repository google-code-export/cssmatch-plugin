/* 
 * Copyright 2007, 2008 Nicolas Maingot
 * 
 * This file is part of CSSMatch.
 * 
 * CSSMatch is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * CSSMatch is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with CSSMatch; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Portions of this code are also Copyright © 1996-2005 Valve Corporation, All rights reserved
 */

#include "GestionTimers.h"

GestionTimers::GestionTimers()
{
	timers = NULL;
	taille = 0;
}

GestionTimers::GestionTimers(int taille)
{
	this->taille = taille;
	timers = new Timer [taille];
}

GestionTimers::~GestionTimers()
{
	if (timers)
		delete [] timers;
}

GestionTimers::GestionTimers(const GestionTimers & gTimers)
{
	taille = gTimers.taille;

	timers = new Timer [taille];

	for (int i=0;i<taille;i++)
		timers[i] = gTimers.timers[i];
}

GestionTimers & GestionTimers::operator = (const GestionTimers & gTimers)
{
	taille = gTimers.taille;

	timers = new Timer [taille];

	for (int i=0;i<taille;i++)
		timers[i] = gTimers.timers[i];

	return *this;
}

void GestionTimers::addTimer(const Timer & timer)
{
	for (int i=0;i<taille;i++)
	{
		if (!timers[i].estValide())
		{
			timers[i] = timer;
			return;
		}
	}

	API::debug("Gestionnaire de timers débordé !");
}

void GestionTimers::execute()
{
	for (int i=0;i<taille;i++)
		if (timers[i].estValide() && timers[i].getDateExecution()<API::gpGlobals->curtime)
			timers[i].execute();
}

void GestionTimers::purge()
{
	for (int i=0;i<taille;i++)
		timers[i] = Timer();
}