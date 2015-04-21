#include "rf_phreaker/rf_phreaker_gui/CollectionInfoList.h"

//namespace rf_phreaker { namespace gui {

CollectionInfoList::CollectionInfoList(QObject *parent)
	: QObject(parent)
{}

QQmlListProperty<CollectionInfo> CollectionInfoList::list() {
	return QQmlListProperty<CollectionInfo>(this, &list_, &CollectionInfoList::append,
										 &CollectionInfoList::count,
										 &CollectionInfoList::at,
										 &CollectionInfoList::clear);
}

void CollectionInfoList::remove(int index) {
	if(index < list_.count()) {
		list_.removeAt(index);
		emit listChanged();
	}
}

void CollectionInfoList::append(CollectionInfo *item) {
	if(item) {
		item->setParent(this);
		list_.append(item);
		emit listChanged();
	}
}

CollectionInfo* CollectionInfoList::at(int index){
	return list_.at(index);
}

void CollectionInfoList::clear() {
	list_.clear();
	emit listChanged();
}

int CollectionInfoList::count() {
	return list_.count();
}

void CollectionInfoList::append(QQmlListProperty<CollectionInfo> *list, CollectionInfo *item) {
	auto tmp = qobject_cast<CollectionInfoList*>(list->object);
	if(tmp) {
		tmp->append(item);
	}
}

CollectionInfo* CollectionInfoList::at(QQmlListProperty<CollectionInfo> *list, int index) {
	auto tmp = qobject_cast<CollectionInfoList*>(list->object);
	if(tmp) {
		return tmp->at(index);
	}
	else
		return nullptr;
}

void CollectionInfoList::clear(QQmlListProperty<CollectionInfo> *list) {
	auto tmp = qobject_cast<CollectionInfoList*>(list->object);
	if(tmp) {
		tmp->clear();
	}
}

int CollectionInfoList::count(QQmlListProperty<CollectionInfo> *list) {
	auto tmp = qobject_cast<CollectionInfoList*>(list->object);
	if(tmp)
		return tmp->count();
	else
		return 0;
}

void CollectionInfoList::setList(const QList<CollectionInfo*> &list) {
	list_ = list;
}

const QList<CollectionInfo*>& CollectionInfoList::qlist() const {
	return list_;
}



//}}
