/* 
 * Copyright 2008, 2009 Nicolas Maingot
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
 * Portions of this code are also Copyright � 1996-2005 Valve Corporation, All rights reserved
 */

#ifndef __COMMON_H__
#define __COMMON_H__

#ifdef _MSC_VER // VC++ only
#pragma warning(disable : 4290) /* C++ exception specification ignored except to indicate a 
								 * function is not __declspec(nothrow) */
#pragma warning(disable :4101) /* unreferenced local variable */
#endif // _MSC_VER

#define GAME_DLL 1 // required by cbase.h
#include "cbase.h" // TEAM_INVALID, TEAM_UNASSIGNED, TEAM_SPECTATOR + some headers
#undef GAME_DLL // however, we're not the game dll...

#include "edict.h" // requited by iplayerinfo.h
#include "dlls/iplayerinfo.h"

// Some Valve's objects we use
struct edict_t;
class IPlayerInfo;
class IServerEntity;
class CBaseEntity;
class IServerUnknown;
class CBasePlayer;
class CBaseCombatCharacter;

#include <string>
#include <sstream>

struct tm; // will be defined in time.h

#include "../exceptions/BaseException.h" // here because I generally define the exception object inline

#define PLUGIN_NAME "CSSMatch"

#define PLUGIN_VERSION_LIGHT "2.0.0 Alpha"

#define PLUGIN_SITE "http://code.google.com/p/cssmatch-plugin-en/"

#define PLUGIN_VERSION "Nico's " \
		PLUGIN_NAME ", version " \
		PLUGIN_VERSION_LIGHT " (" __DATE__ "), " \
		PLUGIN_SITE

/** Invalid entity index */
#define INVALID_ENTITY_INDEX 0

/** invalid player userid */
#define INVALID_PLAYER_USERID -1

namespace cssmatch
{
	/** Get the current local time (using <time.h>)
	 * @return A pointer to a struct tm
	 */
	tm * getLocalTime();

	/** Convert any type to std::string 
	 * @param toConvert Value to convert
	 * @return The string convertion
	 */
	template<class T>
	std::string toString(const T & toConvert)
	{
		std::ostringstream convertion;
		convertion << toConvert;

		return convertion.str();
	}

	//TODO : validNameFile (strip console's escape characters + forbidden characters in windows file names)

	/** Print a debug message into the console
	 * @param fileName The source file where the debug message come from (typically __FILE__)
	 * @param line The source file line where the debug message come from (typically __LINE__)
	 * @param message The message
	 */
	void print(const std::string & fileName, int line, const std::string & message);

	/** Print debug informations relating to an exception
	 * @param e The exception to debug
	 * @param fileName The source file where the exception was threw (typically __FILE__)
	 * @param line The line of the source file where the exception was threw (typically __LINE__)
	 */
	void printException(const BaseException & e, const std::string & fileName, int line);

	/** Make sure that an entity pointer is valid
	 * @param entity The entity pointer to check
	 * @return <code>true</code> if the entity pointer is valid, <code>false</code> otherwise
	 */
	inline bool isValidEntity(edict_t * entity)
	{
		return (entity != NULL) && (! entity->IsFree());
	}

	/** Make sure that a player pointer is valid
	 * @param pInfo The player pointer to check
	 * @return <code>true</code> if the player pointer is valid, or <code>false</code> if the player is invalid or SourceTV
	 */
	inline bool isValidPlayer(IPlayerInfo * pInfo)
	{
		return (pInfo != NULL) && pInfo->IsConnected() && pInfo->IsPlayer() && (! pInfo->IsHLTV());
	}

	/** Make sure that a player index is valid
	 * @param index The player index to check
	 * @ param maxClients The current max clients of the server
	 * @return <code>true</code> if the player index is valid, <code>false</code> otherwise
	 */
	inline bool isValidPlayerIndex(int index, int maxClients)
	{
		return (index > INVALID_ENTITY_INDEX) && index <= maxClients;
	}

	/** Make sure that a player userid is valid
	 * (Do not check the existence of the player, just if the value is possible.)
	 * @param userid The player's userid to check
	 * @return <code>true</code> if the player userid is valid, <code>false</code> otherwise
	 */
	inline bool isValidPlayerUserid(int userid)
	{
		return userid > INVALID_PLAYER_USERID;
	}

	/** Make sure that a server entity pointer is valid
	 * @param sEntity The server entity pointer to check
	 * @return <code>true</code> if the server entity pointer is valid, <code>false</code> otherwise
	 */
	inline bool isValidServerEntity(IServerEntity * sEntity)
	{
		return sEntity != NULL;
	}

	/** Make sure that a base entity pointer is valid
	 * @param bEntity The base entity pointer to check
	 * @return <code>true</code> if the base entity pointer is valid, <code>false</code> otherwise
	 */
	inline bool isValidBaseEntity(CBaseEntity * bEntity)
	{
		return bEntity != NULL;
	}

	/** Make sure that a server unknown pointer is valid
	 * @param bEntity The server unknown pointer to check
	 * @return <code>true</code> if the server unknown pointer is valid, <code>false</code> otherwise
	 */
	inline bool isValidServerUnknown(IServerUnknown * sUnknown)
	{
		return sUnknown != NULL;
	}

	/** Make sure that a base player pointer instance is valid
	 * @param bEntity The base player pointer to check
	 * @return <code>true</code> if the base player pointer is valid, <code>false</code> otherwise
	 */
	inline bool isValidBasePlayer(CBasePlayer * bPlayer)
	{
		return bPlayer != NULL;
	}

	/** Make sure that a base combat character pointer is valid
	 * @param bEntity The base combat character pointer to check
	 * @return <code>true</code> if the base combat character pointer is valid, <code>false</code> otherwise
	 */
	inline bool isValidBaseCombatCharacter(CBaseCombatCharacter * bCombatCharacter)
	{
		return bCombatCharacter != NULL;
	}

	/** Get a server entity pointer corresponding to this entity
	 * @param entity The entity
	 * @return The server entity pointer corresponding to this entity, or NULL if something was invalid
	 */
	IServerEntity * getServerEntity(edict_t * entity);

	/** Get a base player entity pointer corresponding to this entity
	 * @param entity The entity
	 * @return The base player entity pointer corresponding to this entity, or NULL if something was invalid
	 */
	CBaseEntity * getBaseEntity(edict_t * entity);

	/** Get a server unknown pointer corresponding to this entity
	 * @param entity The entity
	 * @return The server unknown pointer corresponding to this entity, or NULL if something was invalid
	 */
	IServerUnknown * getServerUnknow(edict_t * entity);
}

#endif // __COMMON_H__