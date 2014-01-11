#include "usb_ftdi.h"
#include "rf_phreaker/common/log.h"
#include "rf_phreaker/common/exception_types.h"

#include <boost/lexical_cast.hpp>
#include <boost/shared_array.hpp>
#include <boost/format.hpp>
#include <boost/timer/timer.hpp>

using namespace rf_phreaker;
using namespace rf_phreaker::scanner;

usb_ftdi::usb_ftdi()
: logger_(false)
{}


std::vector<comm_usb_info_ptr> usb_ftdi::list_devices()
{
    ////VLOG(5) << ("Listing devices.");

    std::vector<comm_usb_info_ptr> info;

    DWORD num_devices;

    if(FT_SUCCESS(log_error_if_any(FT_CreateDeviceInfoList(&num_devices), "FT_CreateDeviceInfoList")))
    {
        ////VLOG(5) << ("Number of devices: " + boost::lexical_cast<std::string>(num_devices));

        if(num_devices > 0)
        {
            boost::shared_array<FT_DEVICE_LIST_INFO_NODE> nodes(new FT_DEVICE_LIST_INFO_NODE[num_devices]);

            if(FT_SUCCESS(log_error_if_any(FT_GetDeviceInfoList(nodes.get(), &num_devices))))
            {
                for(DWORD i = 0; i < num_devices; i++)
					info.push_back(comm_usb_info_ptr(new comm_usb_ftdi_info(nodes[i])));
            }
        }
    }

	return std::move(info);
}

void usb_ftdi::open_device(int location, FT_HANDLE &handle)
{
    handle = 0;

    ////VLOG(5) << ("Opening device at location " + boost::lexical_cast<std::string>(location));

    (log_error_if_any(FT_OpenEx((PVOID)location, FT_OPEN_BY_LOCATION, &handle), "FT_OpenExByLocation"));

    // (log_error_if_any(FT_SetUSBParameters(handle, 64*1024, 0), "FT_SetUSBParameters"));
 //   (log_error_if_any(FT_Purge(handle, FT_PURGE_RX | FT_PURGE_TX), "FT_Purge"));
	//(log_error_if_any(FT_ResetPort(handle), "FT_ResetPort"));
}

void usb_ftdi::open_device(const std::string &serial, FT_HANDLE &handle)
{
    handle = 0;

    ////VLOG(5) << ("Opening device with serial " + serial);

	(log_error_if_any(FT_OpenEx((PVOID)serial.c_str(), FT_OPEN_BY_SERIAL_NUMBER, &handle), "FT_OpenExBySerial"));

 //   (log_error_if_any(FT_Purge(handle, FT_PURGE_RX | FT_PURGE_TX), "FT_Purge"));
	//(log_error_if_any(FT_ResetPort(handle), "FT_ResetPort"));
}

void usb_ftdi::close_device(FT_HANDLE handle)
{
    ////VLOG(5) << (std::string("Close device with FT_HANDLE: ") + str(boost::format("0x%x") % handle));

    (log_error_if_any(FT_Close(handle), "FT_Close"));
}

void usb_ftdi::write(FT_HANDLE handle, char *buf, size_t bytes_to_write, size_t &bytes_written)
{
	logger_.log_write(buf, bytes_to_write);

	////VLOG(5) << (str(boost::format("Writing %d bytes to handle (0x%x).") % bytes_to_write % handle));

    (log_error_if_any(FT_Write(handle, buf, bytes_to_write, (LPDWORD)&bytes_written), "FT_Write"));

    ////VLOG(5) << (str(boost::format("%d bytes written to handle (0x%x).") % bytes_written % handle));
}

void usb_ftdi::read(FT_HANDLE handle, char *buf, size_t bytes_to_read, size_t &bytes_read)
{	
	////VLOG(5) << (str(boost::format("Reading %d bytes from handle (0x%x).") % bytes_to_read % handle));
	//boost::timer::cpu_timer t; t.start();
    (log_error_if_any(FT_Read(handle, buf, bytes_to_read, (LPDWORD)&bytes_read), "FT_Read"));
	//t.stop(); std::cout << t.format();
    ////VLOG(5) << (str(boost::format("%d bytes read from handle (0x%x).") % bytes_read % handle));

	logger_.log_read(buf, bytes_read);	
}

void usb_ftdi::set_receive_synchronous_fifo_mode(FT_HANDLE handle)
{
    //    ucMode Mode value.  Can be one of the following:
    //    0x0 = Reset
    //    0x1 = Asynchronous Bit Bang
    //    0x2 = MPSSE (FT2232, FT2232H, FT4232H and FT232H devices only)
    //    0x4 = Synchronous Bit Bang (FT232R, FT245R, FT2232, FT2232H, FT4232H and FT232H devices only)
    //    0x8 = MCU Host Bus Emulation Mode (FT2232, FT2232H, FT4232H and FT232H devices only)
    //    0x10 = Fast Opto-Isolated Serial Mode (FT2232, FT2232H, FT4232H and FT232H devices only)
    //    0x20 = CBUS Bit Bang Mode (FT232R and FT232H devices only)
    //    0x40 = Single Channel Synchronous 245 FIFO Mode (FT2232H and FT232H devices only)

    ////VLOG(5) << (str(boost::format("Setting FIFO synchronous mode for handle (0x%x).") % handle));

    UCHAR mask = 0xff; // All bits set to output.
    UCHAR mode = 0x40;  // Set to Single Channel Synchronous 245 FIFO Mode

    (log_error_if_any(FT_SetBitMode(handle, mask, mode), "FT_FT_SetBitMode"));

	logger_.log_sync(true);
}

void usb_ftdi::reset_fifo_mode(FT_HANDLE handle)
{
//    ucMode Mode value.  Can be one of the following:
//    0x0 = Reset
//    0x1 = Asynchronous Bit Bang
//    0x2 = MPSSE (FT2232, FT2232H, FT4232H and FT232H devices only)
//    0x4 = Synchronous Bit Bang (FT232R, FT245R, FT2232, FT2232H, FT4232H and FT232H devices only)
//    0x8 = MCU Host Bus Emulation Mode (FT2232, FT2232H, FT4232H and FT232H devices only)
//    0x10 = Fast Opto-Isolated Serial Mode (FT2232, FT2232H, FT4232H and FT232H devices only)
//    0x20 = CBUS Bit Bang Mode (FT232R and FT232H devices only)
//    0x40 = Single Channel Synchronous 245 FIFO Mode (FT2232H and FT232H devices only)

    ////VLOG(5) << (str(boost::format("Resetting bit mode for handle (0x%x).") % handle));

    UCHAR mask = 0xff; // All bits set to output.  Does this matter since we're resetting?
    UCHAR mode = 0x00;  // Set to Single Channel Synchronous 245 FIFO Mode

    (log_error_if_any(FT_SetBitMode(handle, mask, mode), "FT_FT_SetBitMode"));

	logger_.log_sync(false);
}

bool usb_ftdi::is_synchronous_fifo_mode(FT_HANDLE handle)
{
    //    ucMode Mode value.  Can be one of the following:
    //    0x0 = Reset
    //    0x1 = Asynchronous Bit Bang
    //    0x2 = MPSSE (FT2232, FT2232H, FT4232H and FT232H devices only)
    //    0x4 = Synchronous Bit Bang (FT232R, FT245R, FT2232, FT2232H, FT4232H and FT232H devices only)
    //    0x8 = MCU Host Bus Emulation Mode (FT2232, FT2232H, FT4232H and FT232H devices only)
    //    0x10 = Fast Opto-Isolated Serial Mode (FT2232, FT2232H, FT4232H and FT232H devices only)
    //    0x20 = CBUS Bit Bang Mode (FT232R and FT232H devices only)
    //    0x40 = Single Channel Synchronous 245 FIFO Mode (FT2232H and FT232H devices only)

    ////VLOG(5) << (str(boost::format("Querying FIFO mode for handle (0x%x).") % handle));

    UCHAR bit_mode = 0;

    bool success = FT_SUCCESS(log_error_if_any(FT_GetBitMode(handle, &bit_mode), "FT_FT_GetBitMode"));

    if(success && (bit_mode & 0x40) == 0x40)
        return true;
    else
        return false;
}

void usb_ftdi::set_timeouts(FT_HANDLE handle, int read_timeout, int write_timeout)
{
    ////VLOG(5) << (str(boost::format("Setting timeouts for handle (0x%x): read timeout = %d ms; write timeout = %d ms.") % handle % read_timeout % write_timeout));

    (log_error_if_any(FT_SetTimeouts(handle, read_timeout, write_timeout), "FT_FT_SetTimeouts"));
}

USB_STATUS usb_ftdi::log_error_if_any(USB_STATUS status, const char *description)
{
    if(!FT_SUCCESS(status))
    {
        std::string tmp = std::string("Error occurred during ") +
                std::string(description) +
                std::string(". Error code: ") +
                boost::lexical_cast<std::string>((int)status) +
                std::string(" : ") +
                convert_status(status);

        //LOG(ERROR) << tmp;

        throw comm_error(tmp, status);
    }
    return status;
}

std::string usb_ftdi::convert_status(USB_STATUS status)
{

    switch(status)
    {
    case FT_OK:
        return std::string("FT_OK");
    case FT_INVALID_HANDLE:
        return std::string("FT_INVALID_HANDLE");
    case FT_DEVICE_NOT_FOUND:
        return std::string("FT_DEVICE_NOT_FOUND");
    case FT_DEVICE_NOT_OPENED:
        return std::string("FT_DEVICE_NOT_OPENED");
    case FT_IO_ERROR:
        return std::string("FT_IO_ERROR");
    case FT_INSUFFICIENT_RESOURCES:
        return std::string("FT_INSUFFICIENT_RESOURCES");
    case FT_INVALID_PARAMETER:
        return std::string("FT_INVALID_PARAMETER");
    case FT_INVALID_BAUD_RATE:
        return std::string("FT_INVALID_BAUD_RATE");
    case FT_DEVICE_NOT_OPENED_FOR_ERASE:
        return std::string("FT_DEVICE_NOT_OPENED_FOR_ERASE");
    case FT_DEVICE_NOT_OPENED_FOR_WRITE:
        return std::string("FT_DEVICE_NOT_OPENED_FOR_WRITE");
    case FT_FAILED_TO_WRITE_DEVICE:
        return std::string("FT_FAILED_TO_WRITE_DEVICE");
    case FT_EEPROM_READ_FAILED:
        return std::string("FT_EEPROM_READ_FAILED");
    case FT_EEPROM_WRITE_FAILED:
        return std::string("FT_EEPROM_WRITE_FAILED");
    case FT_EEPROM_ERASE_FAILED:
        return std::string("FT_EEPROM_ERASE_FAILED");
    case FT_EEPROM_NOT_PRESENT:
        return std::string("FT_EEPROM_NOT_PRESENT");
    case FT_EEPROM_NOT_PROGRAMMED:
        return std::string("FT_EEPROM_NOT_PROGRAMMED");
    case FT_INVALID_ARGS:
        return std::string("FT_INVALID_ARGS");
    case FT_NOT_SUPPORTED:
        return std::string("FT_NOT_SUPPORTED");
    case FT_OTHER_ERROR:
        return std::string("FT_OTHER_ERROR");
    default:
        return std::string("Unknown FT error");
    }
}

void usb_ftdi::handle_error(const std::string &/*serial*/, USB_HANDLE &/*handle*/)
{
}
