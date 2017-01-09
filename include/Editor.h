/*
 * Editor.h - declaration of Editor class
 *
 * Copyright (c) 2014 Lukas W <lukaswhl/at/gmail.com>
 *
 * This file is part of LMMS - http://lmms.io
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
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */

#ifndef EDITOR_COMMON_H
#define EDITOR_COMMON_H

#include <QAction>
#include <QMainWindow>
#include <QToolBar>

#include "TimeLineWidget.h"
#include "ToolButton.h"

class DropToolBar;

/// \brief Superclass for editors with a toolbar.
///
/// Those editors include the Song Editor, the Automation Editor, B&B Editor,
/// and the Piano Roll.
class Editor : public QMainWindow
{
	Q_OBJECT
public:
	void setPauseIcon(bool displayPauseIcon=true);
	QAction *playAction() const;
protected:
	DropToolBar * addDropToolBarToTop(QString const & windowTitle);
	DropToolBar * addDropToolBar(Qt::ToolBarArea whereToAdd, QString const & windowTitle);
	DropToolBar * addDropToolBar(QWidget * parent, Qt::ToolBarArea whereToAdd, QString const & windowTitle);

protected slots:
	virtual void play() {}
	virtual void record() {}
	virtual void recordAccompany() {}
	virtual void stop() {}

private slots:
	/// Called by pressing the space key. Plays or stops.
	void togglePlayStop();

signals:

protected:
	/// \brief	Constructor.
	///
	/// \param	record	If set true, the editor's toolbar will contain record
	///					buttons in addition to the play and stop buttons.
	Editor(bool record = false);
	virtual ~Editor();


	DropToolBar* m_toolBar;

	QAction* m_playAction;
	QAction* m_recordAction;
	QAction* m_recordAccompanyAction;
	QAction* m_stopAction;
};


/// Small helper class: A QToolBar that accepts and exposes drop events as signals
class DropToolBar : public QToolBar
{
	Q_OBJECT
public:
	DropToolBar(QWidget* parent=0);

signals:
	void dragEntered(QDragEnterEvent* event);
	void dropped(QDropEvent* event);

protected:
	void dragEnterEvent(QDragEnterEvent* event);
	void dropEvent(QDropEvent* event);
};


#endif