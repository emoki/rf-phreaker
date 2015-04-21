//#pragma once
//#include <QObject>
//#include <QtQml/QQmlListProperty>
//#include "rf_phreaker/rf_phreaker_gui/Wcdma.h"

////namespace rf_phreaker { namespace gui {


//class WcdmaList : public QObject {
//	Q_OBJECT
//	Q_PROPERTY(QQmlListProperty<Wcdma> list READ list NOTIFY listChanged)

//signals:
//	void listChanged();

//public:
//	WcdmaList(QObject *parent = 0) : QObject(parent)
//	{}
//	QQmlListProperty<Wcdma> list()  {
//		return QQmlListProperty<Wcdma>(this, &list_, &WcdmaList::append,
//											 &WcdmaList::count,
//											 &WcdmaList::at,
//											 &WcdmaList::clear);
//	}
//	Q_INVOKABLE void remove(int index) {
//		if(index < list_.count()) {
//			list_.removeAt(index);
//			emit listChanged();
//		}
//	}
//	Q_INVOKABLE void append(Wcdma *item) {
//		if(item) {
//			item->setParent(this);
//			list_.append(item);
//			emit listChanged();
//		}
//	}
//	Q_INVOKABLE Wcdma* at(int index) {
//		return list_.at(index);
//	}
//	Q_INVOKABLE void clear() {
//		list_.clear();
//		emit listChanged();
//	}
//	Q_INVOKABLE int count() {
//		return list_.count();
//	}
//	void setList(const QList<Wcdma*> &list) {
//		list_ = list;
//	}
//	const QList<Wcdma *> &qlist() const {
//		return list_;
//	}
//private:
//	static void append(QQmlListProperty<Wcdma> *list, Wcdma *item) {
//		auto tmp = qobject_cast<WcdmaList*>(list->object);
//		if(tmp) {
//			tmp->append(item);
//		}
//	}
//	static Wcdma* at(QQmlListProperty<Wcdma> *list, int index) {
//		auto tmp = qobject_cast<WcdmaList*>(list->object);
//		if(tmp) {
//			return tmp->at(index);
//		}
//		else
//			return nullptr;
//	}
//	static void clear(QQmlListProperty<Wcdma> *list) {
//		auto tmp = qobject_cast<WcdmaList*>(list->object);
//		if(tmp) {
//			tmp->clear();
//		}
//	}
//	static int count(QQmlListProperty<Wcdma> *list) {
//		auto tmp = qobject_cast<WcdmaList*>(list->object);
//		if(tmp)
//			return tmp->count();
//		else
//			return 0;
//	}

//	QList<Wcdma*> list_;
//};


////}}
