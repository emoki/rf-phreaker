#pragma once
#include <QString>
#include <QFile>
#include <QDebug>
#include "rf_phreaker/protobuf_specific/rf_phreaker_serialization.h"
#include "rf_phreaker/protobuf_specific/io.h"
#include "rf_phreaker/common/measurement_io.h"
#include <google/protobuf/io/zero_copy_stream_impl.h>

//namespace rf_phreaker { namespace gui {

class IO {
public:
	IO() {}
	~IO() {}

	void close() {
		api_file_output_.clear();
	}

	void output_api_data(rf_phreaker::protobuf::update_pb &update_pb, const QString &filename, rf_phreaker::gps &g) {
		auto proto = update_pb.protobuf_const();
		switch(proto.update_case()) {
		case rf_phreaker::protobuf::rp_update::UpdateCase::kLog:
			break;
		case rf_phreaker::protobuf::rp_update::UpdateCase::kMsg:
			break;
		case rf_phreaker::protobuf::rp_update::UpdateCase::kDevice:
			output_data(rf_phreaker::protobuf::rp_update::kDeviceFieldNumber, filename.toStdString() + "_" + "device", update_pb.get_hardware());
			break;
		case rf_phreaker::protobuf::rp_update::UpdateCase::kGps:
			output_data(rf_phreaker::protobuf::rp_update::kGpsFieldNumber, filename.toStdString() + "_" + "gps", update_pb.get_gps());
			break;
		case rf_phreaker::protobuf::rp_update::UpdateCase::kGsmFullScan:
			output_data(rf_phreaker::protobuf::rp_update::kGsmFullScanFieldNumber, filename.toStdString() + "_" + "gsm_full_scan", update_pb.get_gsm_full_scan(), g);
			break;
		case rf_phreaker::protobuf::rp_update::UpdateCase::kWcdmaFullScan:
			output_data(rf_phreaker::protobuf::rp_update::kWcdmaFullScanFieldNumber, filename.toStdString() + "_" + "wcdma_full_scan", update_pb.get_wcdma_full_scan(), g);
			break;
		case rf_phreaker::protobuf::rp_update::UpdateCase::kLteFullScan:
			output_data(rf_phreaker::protobuf::rp_update::kLteFullScanFieldNumber, filename.toStdString() + "_" + "lte_full_scan", update_pb.get_lte_full_scan(), g);
			break;
		case rf_phreaker::protobuf::rp_update::UpdateCase::kGsmSweep:
			output_data(rf_phreaker::protobuf::rp_update::kGsmSweepFieldNumber, filename.toStdString() + "_" + "gsm_sweep", update_pb.get_gsm_sweep_basic(), g);
			break;
		case rf_phreaker::protobuf::rp_update::UpdateCase::kWcdmaSweep:
			output_data(rf_phreaker::protobuf::rp_update::kWcdmaSweepFieldNumber, filename.toStdString() + "_" + "wcdma_sweep", update_pb.get_wcdma_sweep_basic(), g);
			break;
		case rf_phreaker::protobuf::rp_update::UpdateCase::kLteSweep:
			output_data(rf_phreaker::protobuf::rp_update::kLteSweepFieldNumber, filename.toStdString() + "_" + "lte_sweep", update_pb.get_lte_sweep_basic(), g);
			break;
		default:
			qDebug() << "Unknown protobuf message.";
		}
	}

	template<typename Data> void open(int i, const std::string &name, const Data &d) {
		if(api_file_output_.find(i) == api_file_output_.end()) {
			api_file_output_.insert(std::make_pair(i, std::ofstream()));
			auto filename = name + "_" + ".txt";
			api_file_output_[i].open(filename.c_str());
			if(!api_file_output_[i])
				qDebug() << "Unable to open debug " << filename.c_str() << ".";
			rf_phreaker::header(api_file_output_[i], d) << std::endl;
		}
	}
	
	template<typename Data> void open(int i, const std::string &name, const Data &d, const rf_phreaker::gps &g) {
		if(api_file_output_.find(i) == api_file_output_.end()) {
			api_file_output_.insert(std::make_pair(i, std::ofstream()));
			auto filename = name + "_" + ".txt";
			api_file_output_[i].open(filename.c_str());
			if(!api_file_output_[i])
				qDebug() << "Unable to open debug " << filename.c_str() << ".";
			rf_phreaker::header(api_file_output_[i], g) << "\t";
			rf_phreaker::header(api_file_output_[i], d) << std::endl;
		}
	}

	template<typename Data> void output_data(int i, const std::string &name, const Data &d) {
		open(i, name, d);
		api_file_output_[i] << d << std::endl;
	}

	template<typename Data> void output_data(int i, const std::string &name, const Data &d, const rf_phreaker::gps &g) {
		open(i, name, d, g);
		api_file_output_[i] << g << "\t" << d << std::endl;
	}

	template<typename Data> void output_data(int i, const std::string &name, const std::vector<Data> &d) {
		open(i, name, d);
		for(auto &j : d) {
			api_file_output_[i] << j << std::endl;
		}
	}

	template<typename Data> void output_data(int i, const std::string &name, const std::vector<Data> &d, const rf_phreaker::gps &g) {
		open(i, name, d, g);
		for(auto &j : d) {
				api_file_output_[i] << g << "\t" << j << std::endl;
		}
	}

	static void convert_rpf(QString filename) {
		qDebug() << "Converting RPF file. " << filename << ".";
		QFile f(filename);
		if(!f.open(QIODevice::ReadOnly | QIODevice::Unbuffered)) {
			qDebug() << "Failed to open RPF file. " << f.errorString();
		}
		else {
			auto input_file = std::make_unique<google::protobuf::io::FileInputStream>(f.handle());
			IO io;
			rf_phreaker::protobuf::update_pb message;
			auto &proto = message.protobuf();
			rf_phreaker::gps gps;
			gps.lock_ = false;
			gps.latitude_ = 0;
			gps.longitude_ = 0;
			gps.tracking_satellites_ = 0;
			gps.visible_satellites_ = 0;
			gps.coordinated_universal_time_ = 0;
			gps.raw_status_ = 0;
			gps.speed_ = 0;
			while(rf_phreaker::protobuf::read_delimited_from(input_file.get(), &proto)) {

				switch(proto.update_case()) {
				case rf_phreaker::protobuf::rp_update::UpdateCase::kLog:
					break;
				case rf_phreaker::protobuf::rp_update::UpdateCase::kMsg:
					break;
				case rf_phreaker::protobuf::rp_update::UpdateCase::kDevice:
					break;
				case rf_phreaker::protobuf::rp_update::UpdateCase::kGps:
					gps = message.get_gps();
					break;
				case rf_phreaker::protobuf::rp_update::UpdateCase::kGsmFullScan:
						io.output_data(rf_phreaker::protobuf::rp_update::kGsmFullScanFieldNumber, filename.toStdString() + "_converted_" + "gsm_full_scan", message.get_gsm_full_scan(), gps);
					break;
				case rf_phreaker::protobuf::rp_update::UpdateCase::kWcdmaFullScan:
						io.output_data(rf_phreaker::protobuf::rp_update::kWcdmaFullScanFieldNumber, filename.toStdString() + "_converted_" + "wcdma_full_scan", message.get_wcdma_full_scan(), gps);
					break;
				case rf_phreaker::protobuf::rp_update::UpdateCase::kLteFullScan:
						io.output_data(rf_phreaker::protobuf::rp_update::kLteFullScanFieldNumber, filename.toStdString() + "_converted_" + "lte_full_scan", message.get_lte_full_scan(), gps);
					break;
				case rf_phreaker::protobuf::rp_update::UpdateCase::kGsmSweep:
						io.output_data(rf_phreaker::protobuf::rp_update::kGsmSweepFieldNumber, filename.toStdString() + "_converted_" + "gsm_sweep", message.get_gsm_sweep_basic(), gps);
					break;
				case rf_phreaker::protobuf::rp_update::UpdateCase::kWcdmaSweep:
						io.output_data(rf_phreaker::protobuf::rp_update::kWcdmaSweepFieldNumber, filename.toStdString() + "_converted_" + "wcdma_sweep", message.get_wcdma_sweep_basic(), gps);
					break;
				case rf_phreaker::protobuf::rp_update::UpdateCase::kLteSweep:
						io.output_data(rf_phreaker::protobuf::rp_update::kLteSweepFieldNumber, filename.toStdString() + "_converted_" + "lte_sweep", message.get_lte_sweep_basic(), gps);
					break;
				default:
					qDebug() << "Unknown protobuf message.";
				}
				proto.Clear();
			}
		}
	}

private:
	std::map<int, std::ofstream> api_file_output_;
};

//}}