#pragma once

#include "rf_phreaker/scanner/packet_container.h"
#include "rf_phreaker/scanner/packet.h"
#include "rf_phreaker/scanner/comm_info.h"

#include <vector>
#include <memory>


namespace rf_phreaker { namespace scanner {

class scanner_comm;
typedef std::unique_ptr<scanner_comm> scanner_comm_ptr;

class scanner_comm 
{
public:
	virtual ~scanner_comm() {};

	virtual std::vector<comm_info_ptr> list_scanners() = 0;

	virtual bool open_scanner(const scanner_id_type &id) = 0;

	virtual bool close_scanner() = 0;

	virtual void transfer_packet(packet &p) = 0;

	virtual void transfer_packet_container(packet_container &container) = 0;

	virtual void transfer_packet_container(packet_container &container, char *read_buf) = 0;

	virtual void write(const char *write_buf, size_t bytes_to_write = 0) = 0;

	virtual void read(char *read_buf, size_t bytes_to_read = 0) = 0;

	virtual void reset() = 0;

	virtual bool is_scanner_open() const = 0;

	virtual std::string connected_scanner_description() const = 0;

	virtual scanner_id_type connected_scanner_id() const = 0;

protected:


};

}}