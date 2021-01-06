#include <ipmid/api.h>
#include <iostream>

//#include <sdbusplus/server.hpp>
#include <systemd/sd-bus.h>

//#include <sdbusplus/bus.hpp>
//#include <ipmid/utils.hpp>

static constexpr auto vsensorIntf = "xyz.openbmc_project.Sensor.Value";
static constexpr auto vsensorObj = "/xyz/openbmc_project/sensors/voltage/P3V3_STBY";
static constexpr auto vsensorProp = "Value";

// Declares register function with attribute "constructor".
void register_netfn_oem_functions() __attribute__((constructor));

// Callback function for handling Oem command 0xBA.
ipmi_ret_t ipmi_my_handler1(ipmi_netfn_t netfn, ipmi_cmd_t cmd,
ipmi_request_t request, ipmi_response_t response,
ipmi_data_len_t data_len, ipmi_context_t context)
{
    std::cout << __FUNCTION__ << " entered! " << std::endl;
    ipmi_ret_t rc = IPMI_CC_OK;
//sdbusplus::bus::bus bus{ipmid_get_sd_bus_connection()};
//getservice (bus, interface, path)
//auto service = ipmi::getService(bus, vsensorIntf , vsensorObj );
// getdbusproperty (bus , service , objpath, interface, property)
//auto value = ipmi::getDbusProperty(bus, service, vsensorObj,
//                                       vsensorIntf, vsensorProp );
//    std::cout << "aaarrv-->service=" << service << std::endl;
//    std::cout << "aaarrv-->value=" << value << std::endl;

    uint8_t rsp[] = {0xFF, 0x00, 0xAA, 0x55};
    memcpy(response, &rsp, 4);
    *data_len = 4;
    return rc;
}
// Callback function for handling OEM command 0xBE.
ipmi_ret_t ipmi_my_handler2(ipmi_netfn_t netfn, ipmi_cmd_t cmd,
ipmi_request_t request, ipmi_response_t response,
ipmi_data_len_t data_len, ipmi_context_t context)
{
    std::cout << __FUNCTION__ << " entered! " << std::endl;
    ipmi_ret_t rc = IPMI_CC_OK;
    uint8_t rsp[] = {0x55, 0xAA, 0x00, 0xFF};
    memcpy(response, &rsp, 4);
    *data_len = 4;
    return rc;
}
// Register function
void register_netfn_oem_functions()
{
    std::cout << "Registering OEM command handlers" << std::endl;
    ipmi_register_callback(NETFUN_OEM, 0xB3, NULL, ipmi_my_handler1, PRIVILEGE_USER);
    ipmi_register_callback(NETFUN_OEM, 0xB4, NULL, ipmi_my_handler2, PRIVILEGE_USER);
    return;
}
