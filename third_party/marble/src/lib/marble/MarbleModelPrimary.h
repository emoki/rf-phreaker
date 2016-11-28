//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2006-2007 Torsten Rahn <tackat@kde.org>
// Copyright 2007      Inge Wallin  <ingwa@kde.org>
//

#ifndef MARBLE_MARBLEMODELPRIMARY_H
#define MARBLE_MARBLEMODELPRIMARY_H

#include "marble_export.h"
#include <QObject>

namespace Marble {

	/**
	* @short A class that allows injection of a primary MarbleModel.
	*
	* The class basically allows multiple MarbleMaps to use the same
	* MarbleModel.  It is called in the constructor of MarbleMaps which 
	* will use the MarbleModel if one exists.  This also allows us to 
	* get around the fact that QML doesn't allow parameterized items 
	* to be passed to MarbleQuickItem, i.e. we cannot directly pass in 
	* an existing MarbleModel.
	*
	*/

	class MarbleModel;

	class MARBLE_EXPORT MarbleModelPrimary
	{
	public:
		MarbleModelPrimary();

		static void setMarbleModel(MarbleModel* model);

		static MarbleModel* marbleModel();

	private:
		Q_DISABLE_COPY(MarbleModelPrimary)
		class Private;
		Private  * const d;
	};

}

#endif
