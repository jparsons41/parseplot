//	SyntroRecord.h - Defines for Syntro records
//
//  Copyright (c) 2012 Pansenti, LLC.
//	
//  This file is part of SyntroLib
//
//  SyntroLib is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  SyntroLib is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with SyntroLib.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef SYNTRORECORD_H
#define SYNTRORECORD_H

//		Store format options

#define	SYNTRO_RECORD_STORE_FORMAT_SRF		"srf"			// structured record file
#define	SYNTRO_RECORD_STORE_FORMAT_RAW		"raw"			// raw file format (just data - no record headers on any sort)

//	Flat file defs

#define	SPACES_RECORD_FLAT_EXT				"dat"
#define	SPACES_RECORD_FLAT_FILTER			"*.dat"

//	SRF defs

#define	SYNC_LENGTH		8									// 8 bytes in sync sequence

#define	SYNC_STRINGV0	"SpRSHdV0"							// for version 0

#define	SPACES_RECORD_SRF_RECORD_EXT	"srf"				// file extension for record files
#define	SPACES_RECORD_SRF_INDEX_EXT		"srx"				// file extension for index files
#define	SPACES_RECORD_SRF_RECORD_FILTER	"*.srf"				// filter for record files
#define	SPACES_RECORD_SRF_INDEX_FILTER	"*.srx"				// filter extension for index files

typedef struct	
{
	char pSync[SYNC_LENGTH];								// the sync sequence
	SYNTRO_UC4	nSize;										// size of the record that follows
	SYNTRO_UC4	nData;										// unused at this time
} SPACES_RECORD_HEADER;


#endif // SYNTRORECORD_H