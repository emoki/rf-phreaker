#pragma once
#include <QtQml/QQmlListProperty>
#include "rf_phreaker/rf_phreaker_gui/CollectionInfo.h"

//namespace rf_phreaker { namespace gui {

class CollectionInfoList : public QObject {
	Q_OBJECT
	Q_PROPERTY(QQmlListProperty<CollectionInfo> list READ list NOTIFY listChanged)
    Q_PROPERTY(int size READ size NOTIFY sizeChanged)

signals:
	void listChanged();
    void sizeChanged();

public:
	CollectionInfoList(QObject *parent = 0);

	QQmlListProperty<CollectionInfo> list();
    int size() { return list_.size(); }

	Q_INVOKABLE void remove(int index);
	Q_INVOKABLE void append(CollectionInfo *item);
	Q_INVOKABLE CollectionInfo* at(int index);
	Q_INVOKABLE void clear();
	Q_INVOKABLE int count();

	void setList(const QList<CollectionInfo*> &list);
	const QList<CollectionInfo *> &qlist() const;

private:
	static void append(QQmlListProperty<CollectionInfo> *list, CollectionInfo *item);
	static CollectionInfo* at(QQmlListProperty<CollectionInfo> *list, int index);
	static void clear(QQmlListProperty<CollectionInfo> *list);
	static int count(QQmlListProperty<CollectionInfo> *list);

	QList<CollectionInfo*> list_;
};

//}}
