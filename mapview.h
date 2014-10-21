/*
   Copyright (c) 2013, Sean Kasun
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 THE POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef __MAPVIEW_H__
#define __MAPVIEW_H__

#include <QtWidgets/QWidget>
#include "chunkcache.h"
class DefinitionManager;
class BiomeIdentifier;
class BlockIdentifier;

class MapView : public QWidget
{
	Q_OBJECT
public:

	/// Values for the individual flags
	enum
	{
		flgLighting     = 1,
		flgMobSpawn     = 2,
		flgCaveMode     = 4,
		flgDepthShading = 8,
		flgShowEntities = 16
	};


	MapView(QWidget *parent=0);

	QSize minimumSizeHint() const;
	QSize sizeHint() const;

	void attach(DefinitionManager *);

	void setLocation(double x,double z);
	void setDimension(QString path,int scale);
	void setFlags(int flags);
	void addSpecialBlockType(QString type);
	void clearSpecialBlockTypes();

	// public for saving the png
	void renderChunk(Chunk *chunk);
	QString getWorldPath();


public slots:
	void setDepth(int depth);
	void chunkUpdated(int x,int z);
	void redraw();
	void markBlock(QString type,
				   double x1, double y1, double z1,
				   double x2, double y2, double z2,
				   QColor color, QString display);

	/// Clears the cache and redraws, causing all chunks to be re-loaded; but keeps the viewport
	void clearCache();

signals:
	void hoverTextChanged(QString text);
	void demandDepthChange(int value);
	void foundSpecialBlock(int x, int y, int z, QString type, QString display, QVariant properties);
	void showProperties(int x, int y, int z);

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *);
	void mouseDoubleClickEvent(QMouseEvent*event);
	void wheelEvent(QWheelEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void resizeEvent(QResizeEvent *);
	void paintEvent(QPaintEvent *);

private:

	class SpecialBlock
	{
	public:
		SpecialBlock(double x1, double y1, double z1,
					 double x2, double y2, double z2,
					 QColor color, const QString& display);
		void draw(double offsetX, double offsetZ, double scale, QPainter& canvas) const;

		bool intersects(double x1, double y1, double z1,
						double x2, double y2, double z2) const;

		double getX1() const { return x1; }
		double getY1() const { return y1; }
		double getZ1() const { return z1; }
		double getX2() const { return x2; }
		double getY2() const { return y2; }
		double getZ2() const { return z2; }
		const QString& getDisplay() const { return display; }

		static const int MIN_SIZE = 10;
	private:
		void clampSize(int& left, int& right);

		double x1, y1, z1;
		double x2, y2, z2;
		QColor color;
		QString display;
	};

	void drawChunk(int x,int z);
	void getToolTip(int x,int z);
	int getY(int x, int z);

	int depth;
	double x,z;
	int scale;
	double zoom;
	int flags;
	ChunkCache cache;
	QImage image;
	DefinitionManager *dm;
	BlockIdentifier *blocks;
	BiomeIdentifier *biomes;
	uchar placeholder[16*16*4]; // no chunk found placeholder
	QSet<QString> specialBlockTypes;
	QMap<QString, QList<SpecialBlock> > specialBlocks;
};

#endif
