#include <ipmid/api.h>
#include <ipmid/api.hpp>
#include <ipmid/utils.hpp>
#include <ipmid/api-types.hpp>
#include <iostream>
#include <variant>
#include <sdbusplus/bus.hpp>
#include <ipmid/handler.hpp>

int get_dbus();
void set_dbus();
// Declares register function with attribute "constructor".
void register_netfn_oem_functions() __attribute__((constructor));

int get_dbus()
{
    using Value = std::variant<int32_t>;
    Value value;
    auto sdbus = sdbusplus::bus::new_default();
    auto sdmethod = sdbus.new_method_call("xyz.openbmc_project.hello_dbus", "/xyz/openbmc_project/hello_dbus/custom", "org.freedesktop.DBus.Properties", "Get");
    sdmethod.append("xyz.openbmc_project.hello_dbus.custom.Example", "OemInt");
    auto reply = sdbus.call(sdmethod);
    reply.read(value);
    auto oemInt = std::get<int32_t>(value);
    std::cout<<"OemInt: "<<oemInt<<"\n";

    return oemInt; 
}

void set_dbus()
{
    using Value = std::variant<int32_t>;
    Value value = 28;
    auto sdbus = sdbusplus::bus::new_default();
    auto sdmethod = sdbus.new_method_call("xyz.openbmc_project.hello_dbus", "/xyz/openbmc_project/hello_dbus/custom", "org.freedesktop.DBus.Properties", "Set");
    sdmethod.append("xyz.openbmc_project.hello_dbus.custom.Example", "OemInt", value);
    auto reply = sdbus.call(sdmethod);
}

// Callback function for handling Oem command 0xBA.
ipmi_ret_t ipmi_my_handler1(ipmi_netfn_t netfn, ipmi_cmd_t cmd,
                            ipmi_request_t request, ipmi_response_t response,
                            ipmi_data_len_t data_len, ipmi_context_t context)
{
    std::cout << __FUNCTION__ << " entered! " << std::endl;

    ipmi_ret_t rc = IPMI_CC_OK;
    //uint8_t rsp[] = {0xFF, 0x00, 0xAA, 0x55};
    uint8_t rsp = get_dbus();
    //memcpy(response, &rsp, 4);
    memcpy(response, &rsp, 1);
    //*data_len = 4;
    *data_len = 1;

    return rc;
}

// Callback function for handling OEM command 0xBE.
ipmi_ret_t ipmi_my_handler2(ipmi_netfn_t netfn, ipmi_cmd_t cmd,
                            ipmi_request_t request, ipmi_response_t response,
                            ipmi_data_len_t data_len, ipmi_context_t context)
{
    std::cout << __FUNCTION__ << " entered! " << std::endl;

    ipmi_ret_t rc = IPMI_CC_OK;
    //uint8_t rsp[] = {0x55, 0xAA, 0x00, 0xFF};
    //memcpy(response, &rsp, 4);
	set_dbus();
    *data_len = 0;

    return rc;
}

// Register function
void register_netfn_oem_functions()
{
    std::cout << "Registering OEM command handlers" << std::endl;
    ipmi_register_callback(NETFUN_OEM, 0xBA, NULL, ipmi_my_handler1, PRIVILEGE_USER);
    ipmi_register_callback(NETFUN_OEM, 0xBE, NULL, ipmi_my_handler2, PRIVILEGE_USER);

    return;
}