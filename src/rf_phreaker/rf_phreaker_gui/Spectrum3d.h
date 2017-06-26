#pragma once
#include "boost/circular_buffer.hpp"
#include <QObject>
#include <QtDataVisualization/QSurface3DSeries>
#include <QVector3D>
#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/common/exception_types.h"

class Spectrum3d : public QObject {
	Q_OBJECT
	Q_PROPERTY(int capacity READ capacity WRITE setCapacity NOTIFY capacityChanged)
	Q_PROPERTY(int maxDataLimit READ maxDataLimit NOTIFY maxDataLimitChanged)
	//Q_PROPERTY(bool isDirty MEMBER isDirty_ NOTIFY isDirtyChanged)

signals:
	void capacityChanged(int capacity);
	void maxDataLimitChanged(int limit);
	void isDisabledChanged(int isDisabled);
	//void isDirtyChanged(bool isDirty);

public:
	Spectrum3d(QObject *parent = nullptr)
		: QObject(parent)
		, proxyArray_(nullptr)
		, columnCount_(0)
		, capacity_(30)
		, isDirty_(false)
		, isDisabled_(false)
		, maxDataLimit_(100000) {
		storage_.set_capacity(capacity_);
		clear();
	}

	void setCapacity(int cap) {
		if(cap != capacity_ && capacity_ > 0) {
			capacity_ = cap;
			emit capacityChanged(capacity_);
		}
	}

	int capacity() { return capacity_; }
	int maxDataLimit() { return maxDataLimit_; }
	void setMaxDataLimit(int dataLimit) {
		if(maxDataLimit_ != dataLimit) {
			maxDataLimit_ = dataLimit;
			emit maxDataLimitChanged(maxDataLimit_);
		}
	}
	bool isDisabled() { return isDisabled_; }
	void setIsDisabled(bool dis) {
		if(isDisabled_ != dis) {
			isDisabled_ = dis;
			emit isDisabledChanged(isDisabled_);
		}
	}

	Q_INVOKABLE void clear() {}

	Q_INVOKABLE void updateSeries(QtDataVisualization::QSurface3DSeries *series) {
		using namespace QtDataVisualization;
		if(isDirty_ && series && series->dataProxy() && !storage_.empty()) {
			auto proxy = series->dataProxy();
			if(proxyArray_ == nullptr || proxy->columnCount() != columnCount_) {
				// If we haven't taken taken control of the proxyArray do so.
				// Also if columns are different reset array by giving it our storage.
				//qDebug() << "new array";
				proxyArray_ = new QSurfaceDataArray();
				proxyArray_->reserve(capacity_);
			}

			populateSurfaceArray(*proxyArray_);
			//qDebug() << "resetting array";
			proxy->resetArray(proxyArray_);
			//qDebug() << "resetting array finished";
			isDirty_ = false;
		}
	}

	void populateSurfaceArray(QtDataVisualization::QSurfaceDataArray &arr) {
		for(int i = 0; i < (int)storage_.size(); ++i) {
			if(i >= arr.size()) {
				//qDebug() << "row: " << i << " - creating and pushing row onto proxyarray.";
				auto row = createSurfaceDataRow(storage_[i], storage_.size() - i);
				arr.push_back(row);
			}
			else {
				//qDebug() << "row: " << i << " - populating existing row in proxyarray.";
				populateSurfaceDataRow(arr[i], storage_[i], storage_.size() - i);
			}
		}
	}

	void setIndexOnSurfaceRow(QtDataVisualization::QSurfaceDataRow &row, int index) {
		for(int i = 0; i < row.size(); ++i) {
			row[i].setZ(index);
		}
	}

	void updateStorage(const std::map<size_t, rf_phreaker::power_spectrum_data> &specs) {
		using namespace QtDataVisualization;
		if(specs.size()) {
			auto columnCount = (int)specs.rbegin()->first;
			if(columnCount > maxDataLimit_) {
				setIsDisabled(true);
				return;
			}
			setIsDisabled(false);
			// If columns do not match clear the storage, assuming memory deallocation occurs in series.
			if(columnCount != columnCount_) {
				storage_.clear();
				columnCount_ = columnCount;
			}
			//qDebug() << "Pushing back specs";
			storage_.push_back(specs);
			isDirty_ = true;
		}
	}

	QtDataVisualization::QSurfaceDataRow* createSurfaceDataRow(
		const std::map<size_t, rf_phreaker::power_spectrum_data> &specs, int index) {
		using namespace QtDataVisualization;
		if(specs.empty())
			return nullptr;
		auto row = new QSurfaceDataRow(specs.rbegin()->first);
		columnCount_ = row->size();
		auto j = 0;
		for(const auto &i : specs) {
			auto freq = i.second.params_.start_frequency_;
			auto step = (rf_phreaker::frequency_type)i.second.params_.step_size_;
			auto power = i.second.power_;
			for(const auto &p : power) {
				(*row)[j++].setPosition(QVector3D(freq / 1e6f, p, index));
				freq += step;
			}
		}
		return row;
	}

	void populateSurfaceDataRow(QtDataVisualization::QSurfaceDataRow *row,
		const std::map<size_t, rf_phreaker::power_spectrum_data> &specs, int index) {
		using namespace QtDataVisualization;
		if(specs.empty())
			return;
		if(row->size() != specs.rbegin()->first) {
			throw rf_phreaker::rf_phreaker_gui_error("Spectrum data aggregate size is the wrong dimension.");
		}
		auto j = 0;
		for(const auto &i : specs) {
			auto power = i.second.power_;
			for(const auto &p : power) {
				(*row)[j].setY(p);
				(*row)[j++].setZ(index);
			}
		}
	}

private:
	boost::circular_buffer<std::map<size_t, rf_phreaker::power_spectrum_data>> storage_;
	QtDataVisualization::QSurfaceDataArray *proxyArray_;
	int capacity_;
	int columnCount_;
	bool isDirty_;
	int maxDataLimit_;
	bool isDisabled_;
};

