/*
 * midi_import.h - support for importing MIDI-files
 *
 * Copyright (c) 2005-2006 Tobias Doerffel <tobydox/at/users.sourceforge.net>
 * 
 * This file is part of Linux MultiMedia Studio - http://lmms.sourceforge.net
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */


#ifndef _MIDI_IMPORT_H
#define _MIDI_IMPORT_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


#include "qt3support.h"

#ifdef QT4

#include <QString>
#include <QPair>
#include <QVector>

#else

#include <qstring.h>
#include <qpair.h>
#include <qvaluevector.h>

#endif


#include "midi.h"
#include "import_filter.h"


class midiImport : public importFilter
{
public:
	midiImport( const QString & _file );
	virtual ~midiImport();


private:
	virtual bool tryImport( trackContainer * _tc );

	bool FASTCALL readSMF( trackContainer * _tc );
	bool FASTCALL readRIFF( trackContainer * _tc );
	bool FASTCALL readTrack( int _track_end );

	void error( void );


	inline int readInt( int _bytes )
	{
		int c, value = 0;
		do
		{
			c = readByte();
			if( c == -1 )
			{
				return( -1 );
			}
			value = ( value << 8 ) | c;
		} while( --_bytes );
		return( value );
	}
	inline Sint32 read32LE( void )
	{
		int value = readByte();
		value |= readByte() << 8;
		value |= readByte() << 16;
		value |= readByte() << 24;
		return( value );
	}
	inline int readVar( void )
	{
		int c = readByte();
		int value = c & 0x7f;
		if( c & 0x80 )
		{
			c = readByte();
			value = ( value << 7 ) | ( c & 0x7f );
			if( c & 0x80 )
			{
				c = readByte();
				value = ( value << 7 ) | ( c & 0x7f );
				if( c & 0x80 )
				{
					c = readByte();
					value = ( value << 7 ) | c;
					if( c & 0x80 )
					{
						return -1;
					}
				}
			}
	        }
        	return( !file().atEnd() ? value : -1 );
	}

	inline Sint32 readID( void )
	{
		return( read32LE() );
	}
	inline void skip( int _bytes )
	{
		while( _bytes > 0 )
		{
			readByte();
			--_bytes;
		}
	}


	typedef vvector<QPair<int, midiEvent> > eventVector;
	eventVector m_events;
	bool m_smpteTiming;

} ;


#endif
